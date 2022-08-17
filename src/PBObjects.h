#pragma once

#include "PBArray.h"


namespace Inf
{
	/**
	 * Wrapper for pbobject type. If the Group and Classnames are the same (most of the times), the ID of the Class is just the Class name.
	 * If the Group and Class names are different, the ID is both combined with a dot (L"group.class"). This is only the case for nested Types.
	 * 
	 * \tparam class_id		ID of Group and Class
	 * \tparam group_type	The Group Type used by PowerBuilder (struct, userobject, ...)
	 */
	template <Helper::FixedString class_id, pbgroup_type group_type = pbgroup_userobject>
	class PBObject
	{
	public:
		/**
		 * Creates a new Wrapper for an already existing object.
		 * Will be Null if obj is 0.
		 * 
		 * \param session	Current Session
		 * \param obj		pbobject or 0
		 */
		PBObject(IPB_Session* session, pbobject obj)
			: m_Session(session), m_Object(obj)
		{
			if (!IsNull())
				session->AddLocalRef(m_Object);
		}

		/**
		 * Will create a new object of the correct Class.
		 * 
		 * \param session	Current Session
		 * 
		 * \throw Inf::PBNI_Exception	If the Group or Class cannot be found
		 */
		PBObject(IPB_Session* session)
			: m_Session(session)
		{
			m_Object = m_Session->NewObject(PBClass(m_Session));
			session->AddLocalRef(m_Object);
		}

		/**
		 * The ability to cast any Class to any other Class.
		 * 
		 * \param other		Object to cast
		 */
		template <Helper::FixedString other_class_id, pbgroup_type other_group_type>
		PBObject(const PBObject<other_class_id, other_group_type>& other)
			: m_Session(other.m_Session), m_Object(other.m_Object)
		{ }


		/**
		 * Invoke a Function of the pbobject with an unknown Signature.
		 * Generates a signature out of the provided Return and Argument Types.
		 * 
		 * \param method_name	The name of the Function to invoke
		 * \param pbrt			The Type of the Function (Function or Event)
		 * \param ...args		The Arguments to forward to the Function
		 * \return				The acquired Value returned by the Function
		 * 
		 * \tparam Ret	The type to be returned
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching functions were found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_PowerBuilderException			If the function doesnt return PBX_SUCCESS
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename Ret = void, typename... Args>
			requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
		inline Ret Invoke(const std::wstring& method_name, PBRoutineType pbrt, Args... args)
		{
			std::wstring pbsig = std::wstring() + Type<Ret>::PBSignature;
			if constexpr (sizeof...(Args) > 0)
			{
				([&] {
					if constexpr (std::is_reference_v<Args>)
					{
						pbsig += std::wstring(L"R") + Type<std::remove_reference_t<Args>>::PBSignature;
					}
					else
					{
						pbsig += Type<Args>::PBSignature;
					}
				}(), ...);
			}

			return InvokeSig<Ret, Args&...>(method_name, pbrt, pbsig, args...);
		}

		/**
		 * Invokes a Function of a pbobject with a known Signature.
		 * 
		 * \param method_name	The name of the Function to invoke
		 * \param pbrt			The Type of the Function (Function or Event)
		 * \param pbsig			The Signature of the Function (pbsig170), L"" to pick first found
		 * \param ...args		The Arguments to forward to the Function
		 * \return				The acquired Value returned by the Function
		 * 
		 * \tparam Ret	The type to be returned
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching functions were found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_PowerBuilderException			If the function doesnt return PBX_SUCCESS
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename Ret = void, typename... Args>
			requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
		inline Ret InvokeSig(const std::wstring& method_name, PBRoutineType pbrt, const std::wstring& pbsig, Args&&... args)
		{
			if (IsNull())
				throw PBNI_NullPointerException(class_id.data);

			pbmethodID mid = m_Session->GetMethodID(PBClass(m_Session), method_name.c_str(), pbrt, pbsig.c_str());

			if (mid == kUndefinedMethodID)
				throw PBNI_InvalidFieldException(class_id.data, method_name + L"(" + pbsig + L")", L"Method");

			PBCallInfo ci;
			m_Session->InitCallInfo(PBClass(m_Session), mid, &ci);

			// Argument Checking
			if (ci.pArgs->GetCount() != sizeof...(Args))
				throw PBNI_IncorrectArgumentsException(class_id.data, method_name + L"(" + pbsig + L")");

			pbint i = 0;
			([&] {
				IPB_Value* value = ci.pArgs->GetAt(i);
				if (value->GetType() != pbvalue_any && !Type<std::remove_reference_t<Args>>::Assert(m_Session, value))
					throw PBNI_IncorrectArgumentsException(class_id.data, method_name + L"(" + pbsig + L")", i);
				i++;
			}(), ...);


			// Argument Gathering
			i = 0;
			(Type<std::remove_reference_t<Args>>::SetValue(m_Session, ci.pArgs->GetAt(i++), args), ...);

			PBXRESULT res = m_Session->InvokeObjectFunction(m_Object, mid, &ci);
			
			if (res != PBX_OK)
			{
				m_Session->FreeCallInfo(&ci);

				throw PBNI_PowerBuilderException(L"IPB_Session::InvokeObjectFunction", res);
			}

			// Apply references
			i = 0;
			([&] {
				if constexpr (std::is_reference_v<Args>)
				{
					if (ci.pArgs->GetAt(i)->IsByRef())
						args = Type<std::remove_reference_t<Args>>::FromArgument(m_Session, ci.pArgs->GetAt(i), true);
				}
				i++;
			}(), ...);

			if constexpr (std::is_void_v<Ret>)
			{
				m_Session->FreeCallInfo(&ci);
			}
			else
			{
				Ret ret = Type<Ret>::FromArgument(m_Session, ci.returnValue, true);

				m_Session->FreeCallInfo(&ci);
				return ret;
			}
		}

		/**
		 * Sets a Field of the pbobjec to a Value.
		 * 
		 * \param field_name	The name of the PowerBuilder Field
		 * \param t				The Value to set it to
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_PowerBuilderException			If SetField doesn't return PBX_SUCCESS
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename PBT>
		inline void SetField(const std::wstring& field_name, const PBT t)
		{
			pbfieldID fid = GetFieldId(field_name);

			pbuint field_type = m_Session->GetFieldType(PBClass(m_Session), fid);
			if (field_type != Type<PBT>::PBType && field_type != pbvalue_any)
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			if (t.IsNull())
			{
				m_Session->SetFieldToNull(m_Object, fid);
			}
			else
			{
				PBXRESULT res = SetFieldImpl<PBT>(fid, t);

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::Set<Type>Field for " + Type<PBT>::GetPBName(L""), res);
			}
		}

		// There are no partial function specializations yet, so we have to make custom functions for these
		/**
		 * Sets an Array field of a pbobject.
		 * 
		 * \param field_name	The name of the PowerBuilder Field
		 * \param arr			The Array to set the field to
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_PowerBuilderException			If SetField doesn't return PBX_SUCCESS
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename PBT>
		inline void SetArrayField(const std::wstring& field_name, const PBArray<PBT> arr)
		{
			pbfieldID fid = GetFieldId(field_name);
			
			if (!m_Session->IsFieldArray(PBClass(m_Session), fid))
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			if (arr.IsNull())
			{
				m_Session->SetFieldToNull(m_Object, fid);
			}
			else
			{
				PBXRESULT res = m_Session->SetArrayField(m_Object, fid, arr.m_Array);

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::SetArrayField", res);
			}
		}
		/**
		 * Sets an Object field of a pbobject.
		 * 
		 * \param field_name	The name of the PowerBuilder Field
		 * \param obj			The Object to set the field to
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_PowerBuilderException			If SetField doesn't return PBX_SUCCESS
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <Helper::FixedString class_id>
		inline void SetObjectField(const std::wstring& field_name, const PBObject<class_id, group_type> obj)
		{
			pbfieldID fid = GetFieldId(field_name);

			if (!m_Session->IsFieldObject(PBClass(m_Session), fid))
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			if (obj.IsNull())
			{
				m_Session->SetFieldToNull(m_Object, fid);
			}
			else
			{
				PBXRESULT res = m_Session->SetObjectField(m_Object, fid, obj.m_Object);

				if (res != PBX_SUCCESS)
					throw PBNI_PowerBuilderException(L"IPB_Session::SetObjectField", res);
			}
		}


		/**
		 * Gets a Field of the pbobject.
		 *
		 * \param field_name	The name of the PowerBuilder Field
		 * 
		 * \tparam PBT	The Type to be returned, cannot be PBObject or PBArray
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename PBT>
		inline PBT GetField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);

			pbuint field_type = m_Session->GetFieldType(PBClass(m_Session), fid);
			if (field_type != Type<PBT>::PBType && field_type != pbvalue_any)
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			return GetFieldImpl<PBT>(fid);
		};

		// There are no partial function specializations yet, so we have to make custom functions for these
		/**
		 * Gets an Array of the pbobject.
		 *
		 * \param field_name	The name of the PowerBuilder Field
		 *
		 * \tparam PBT	The Type of the Items of the Array to be returned
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <typename PBT>
		inline PBArray<PBT> GetArrayField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);

			if (!m_Session->IsFieldArray(PBClass(m_Session), fid))
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			pbboolean is_null = false;

			pbarray pb_array = m_Session->GetArrayField(m_Object, fid, is_null);
			return { m_Session, is_null ? 0 : pb_array };
		}

		/**
		 * Gets an Object of the pbobject.
		 *
		 * \param field_name	The name of the PowerBuilder Field
		 *
		 * \tparam ret_class_id		The Class ID to be returned
		 * \tparam group_type		The type of the Class Group to be returned
		 * 
		 * \throw Inf::PBNI_InvalidFieldException			If no matching field was found
		 * \throw Inf::PBNI_IncorrectArgumentsException		If the argument types dont match up
		 * \throw Inf::PBNI_NullPointerException			If pbobject is Null
		 * \throw Inf::PBNI_Exception						If the Group or Class cannot be found
		 */
		template <Helper::FixedString ret_class_id, pbgroup_type group_type = pbgroup_userobject>
		inline PBObject<ret_class_id, group_type> GetObjectField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);

			if (!m_Session->IsFieldObject(PBClass(m_Session), fid))
				throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

			pbboolean is_null = false;

			pbobject pb_object = m_Session->GetObjectField(m_Object, fid, is_null);
			return { m_Session, is_null ? 0 : pb_object };
		}


		/**
		 * Wheteher the pbobject is Null.
		 * 
		 * \return Is Null
		 */
		bool IsNull() const
		{
			return !m_Object;
		}
		
		/**
		 * Get the Group name extracted from the class_id.
		 * 
		 * \return	Group name
		 */
		static const std::wstring& GroupName()
		{
			static std::wstring s_GroupName = ExtractGroupName();
			return s_GroupName;
		}

		/**
		 * Get the Class name extracted from the class_id.
		 *
		 * \return	Class name
		 */
		static const std::wstring& ClassName()
		{
			static std::wstring s_ClassName = ExtractClassName();
			return s_ClassName;
		}

		/**
		 * Get the pbclass extracted from the class_id.
		 *
		 * \return	pbclass
		 * 
		 * \throw Inf::PBNI_Exception	If the Group or Class cannot be found
		 */
		static pbclass PBClass(IPB_Session* session)
		{
			static pbclass s_Class = FindClass(session);
			return s_Class;
		}

		operator pbobject() const
		{
			return m_Object;
		}
	private:
		template <typename T>
		friend struct Type;
		template <typename PBT, pblong... dims>
			requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
		friend class PBArray;
		template <Helper::FixedString class_id, pbgroup_type group_type>
		friend class PBObject;


		IPB_Session* m_Session;
		pbobject m_Object;

		/**
		 * Returns the ID of a Field.
		 * 
		 * \param field_name	Name of the Field
		 * \return				Field ID
		 * 
		 * \throw Inf::PBNI_InvalidFieldException	If no matching field was found
		 * \throw Inf::PBNI_NullPointerException	If pbobject is Null
		 */
		pbfieldID GetFieldId(const std::wstring& field_name) const
		{
			if (IsNull())
				throw PBNI_NullPointerException(class_id.data);

			pbfieldID fid = m_Session->GetFieldID(PBClass(m_Session), field_name.c_str());

			if (fid == kUndefinedFieldID)
				throw PBNI_InvalidFieldException(class_id.data, field_name, L"Member variable");

			return fid;
		}

		/**
		 * Only used in Inf::PBObject<>::GroupName() to initialize a static variable.
		 * 
		 * \return	The Group Name extracted from class_id
		 */
		static std::wstring ExtractGroupName()
		{
			std::wstring id(class_id.data);
			size_t i = id.find_first_of(L'.');

			if (i == 0 || i == std::wstring::npos)
				return id;

			if (id.find_last_of(L'.') != i)
				return L"";

			return id.substr(0, i);
		}

		/**
		 * Only used in Inf::PBObject<>::ClassName() to initialize a static variable.
		 * 
		 * \return	The Class Name extracted from class_id
		 */
		static std::wstring ExtractClassName()
		{
			std::wstring id(class_id.data);
			size_t i = id.find_first_of(L'.');

			if (i == std::wstring::npos)
				return id;
			
			if (id.find_last_of(L'.') != i)
				return L"";
	
			return id.substr(i + 1);
		}

		/**
		 * Only used in Inf::PBObject<>::PBClass(m_Session) to initialize a static variable.
		 *
		 * \return	The pbclass found using Group and Class Name
		 * 
		 * \throw Inf::PBNI_Exception	If the Group or Class cannot be found
		 */
		static pbclass FindClass(IPB_Session* session)
		{
			pbgroup group = session->FindGroup(GroupName().c_str(), group_type);
			if (!group)
			{
				throw PBNI_Exception({
					{ L"Error", L"Unable to find group" },
					{ L"Group", GroupName() },
					{ L"ID", class_id.data },
				});
			}

			pbclass cls = session->FindClass(group, ClassName().c_str());
			if (!cls)
			{
				throw PBNI_Exception({
					{ L"Error", L"Unable to find group" },
					{ L"Group", GroupName() },
					{ L"Class", ClassName() },
					{ L"ID", class_id.data },
				});
			}

			return cls;
		}

		

		template <typename PBT>
		inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBT t) = delete;

		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBByte t)		{ return m_Session->SetByteField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBBoolean t)	{ return m_Session->SetCharField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBChar t)		{ return m_Session->SetCharField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBInt t)		{ return m_Session->SetIntField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBUint t)		{ return m_Session->SetUintField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBLong t)		{ return m_Session->SetLongField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBUlong t)	{ return m_Session->SetUlongField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBLongLong t)	{ return m_Session->SetLongLongField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBReal t)		{ return m_Session->SetRealField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDouble t)	{ return m_Session->SetDoubleField(m_Object, fid, t); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDecimal t)	{ return m_Session->SetDecField(m_Object, fid, t.m_Decimal); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBTime t)		{ return m_Session->SetTimeField(m_Object, fid, t.m_Time); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDate t)		{ return m_Session->SetDateField(m_Object, fid, t.m_Date); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDateTime t)	{ return m_Session->SetDateTimeField(m_Object, fid, t.m_DateTime); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBString t)	{ return m_Session->SetPBStringField(m_Object, fid, t.m_String); }
		template<> inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBBlob t)		{ return m_Session->SetBlobField(m_Object, fid, t.m_Blob); }

		
		template <typename PBT>
		inline PBT GetFieldImpl(pbfieldID fid) const = delete;

		template<> inline PBByte 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbbyte pb_byte			= m_Session->GetByteField(m_Object, fid, is_null);		return is_null ? PBByte()		: PBByte(pb_byte); }
		template<> inline PBBoolean 	GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbboolean pb_boolean		= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBBoolean()	: PBBoolean(pb_boolean); }
		template<> inline PBChar 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbchar pb_char			= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBChar()		: PBChar(pb_char); }
		template<> inline PBInt 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbint pb_int				= m_Session->GetIntField(m_Object, fid, is_null);		return is_null ? PBInt()		: PBInt(pb_int); }
		template<> inline PBUint 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbuint pb_uint			= m_Session->GetUintField(m_Object, fid, is_null);		return is_null ? PBUint()		: PBUint(pb_uint); }
		template<> inline PBLong 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pblong pb_long			= m_Session->GetLongField(m_Object, fid, is_null);		return is_null ? PBLong()		: PBLong(pb_long); }
		template<> inline PBUlong 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbulong pb_ulong			= m_Session->GetUlongField(m_Object, fid, is_null);		return is_null ? PBUlong()		: PBUlong(pb_ulong); }
		template<> inline PBLongLong	GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pblonglong pb_longlong	= m_Session->GetLongLongField(m_Object, fid, is_null);	return is_null ? PBLongLong()	: PBLongLong(pb_longlong); }
		template<> inline PBReal 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbreal pb_real			= m_Session->GetRealField(m_Object, fid, is_null);		return is_null ? PBReal()		: PBReal(pb_real); }
		template<> inline PBDouble 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbdouble pb_double		= m_Session->GetDoubleField(m_Object, fid, is_null);	return is_null ? PBDouble()		: PBDouble(pb_double); }
		template<> inline PBDecimal 	GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbdec pb_dec				= m_Session->GetDecField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_dec }; }
		template<> inline PBTime 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbtime pb_time			= m_Session->GetTimeField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbdate pb_date			= m_Session->GetDateField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbdatetime pb_datetime	= m_Session->GetDateTimeField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbstring pb_string		= m_Session->GetStringField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob 		GetFieldImpl(pbfieldID fid) const { pbboolean is_null = false; pbblob pb_blob			= m_Session->GetBlobField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_blob }; }

	};

	template <Helper::FixedString class_id>
	using PBStruct = PBObject<class_id, pbgroup_structure>;
	template <Helper::FixedString class_id>
	using PBWindow = PBObject<class_id, pbgroup_window>;
}
