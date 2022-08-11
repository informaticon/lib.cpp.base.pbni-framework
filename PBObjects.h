#pragma once

#include "PBArray.h"


namespace Inf
{
	template <Helper::FixedString cls_name, pbgroup_type group_type = pbgroup_userobject>
	class PBObject
	{
	public:	
		PBObject(IPB_Session* session)
			: m_Session(session)
		{
			m_Object = m_Session->NewObject(PBClass(m_Session));
		}

		PBObject(IPB_Session* session, pbobject obj)
			: m_Session(session), m_Object(obj)
		{ }

		template <typename Ret = void, typename... Args>
			requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && (!std::is_pointer_v<Args> && ...))
		inline Ret Invoke(std::wstring method_name, PBRoutineType pbrt, Args... args)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(std::wstring(L"Tried to invoke a method of an object that is Null (type ") + cls_name.data + L", method: " + method_name + L")");

			std::wstring pb_sig = std::wstring() + Inf::Type<Ret>::PBSignature + ((Inf::Type<Args>::PBSignature) + ...);

			pbmethodID mid = m_Session->GetMethodID(PBClass(m_Session), method_name.c_str(), pbrt, pb_sig.c_str());

			if (mid == kUndefinedMethodID)
				throw Inf::u_exf_pbni(std::wstring(L"Tried to invoke a method that doesnt exist (type: ") + cls_name.data + L", method: " + method_name + L", signature: " + pb_sig + L")");

			PBCallInfo ci;
			m_Session->InitCallInfo(PBClass(m_Session), mid, &ci);
			pbint i = 0;
			(Type<std::remove_reference_t<Args>>::SetValue(m_Session, ci.pArgs->GetAt(i++), args), ...);

			m_Session->InvokeObjectFunction(m_Object, mid, &ci);

			// Apply references
			i = 0;
			([&] {
				if constexpr (std::is_reference_v<Args>)
				{
					args = Type<std::remove_reference_t<Args>>::FromArgument(m_Session, ci.pArgs->GetAt(i));
				}
				i++;
				}(), ...);

			if constexpr (std::is_void_v<Ret>)
			{
				m_Session->FreeCallInfo(&ci);
			}
			else
			{
				Ret ret = Type<Ret>::FromArgument(m_Session, ci.returnValue);

				m_Session->FreeCallInfo(&ci);
				return ret;
			}
		}


		template <typename PBT>
		inline void SetField(const std::wstring& field_name, const PBT t) = delete;

		template<> inline void SetField(const std::wstring& field_name, const PBByte t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetByteField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBBoolean t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetCharField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBChar t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetCharField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBInt t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetIntField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBUint t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetUintField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBLong t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetLongField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBUlong t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetUlongField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBLongLong t) { pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetLongLongField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBReal t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetRealField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBDouble t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDoubleField(m_Object, fid, t); }
		template<> inline void SetField(const std::wstring& field_name, const PBDecimal t)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (t.IsNull())
			{
				m_Session->SetFieldToNull(m_Object, fid);
			}
			else
			{
				std::wstring dec_repr = ConvertString<std::wstring>(t.t.str());

				pbdec pb_dec = m_Session->NewDecimal();
				m_Session->SetDecimal(pb_dec, dec_repr.c_str());

				m_Session->SetDecField(m_Object, fid, pb_dec);
			}
		}
		template<> inline void SetField(const std::wstring& field_name, const PBTime t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetTimeField(m_Object, fid, t.m_Time); }
		template<> inline void SetField(const std::wstring& field_name, const PBDate t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDateField(m_Object, fid, t.m_Date); }
		template<> inline void SetField(const std::wstring& field_name, const PBDateTime t) { pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDateTimeField(m_Object, fid, t.m_DateTime); }
		template<> inline void SetField(const std::wstring& field_name, const PBString t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetPBStringField(m_Object, fid, t.m_String); }
		template<> inline void SetField(const std::wstring& field_name, const PBBlob t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetBlobField(m_Object, fid, t.m_Blob); }

		// There are no partial function specializations yet, so we have to make custom functions for these
		template <typename PBT>
		inline void SetArrayField(const std::wstring& field_name, const PBArray<PBT> arr)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (arr.IsNull())
				m_Session->SetFieldToNull(m_Object, fid);
			else
				m_Session->SetArrayField(m_Object, fid, arr.m_Object);
		}
		template <Helper::FixedString cls_name>
		inline void SetObjectField(const std::wstring& field_name, const PBObject<cls_name, group_type> obj)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (obj.IsNull())
				m_Session->SetFieldToNull(m_Object, fid);
			else
				m_Session->SetObjectField(m_Object, fid, obj.m_Object);
		}


		template <typename PBT>
		inline PBT GetField(const std::wstring& field_name) const = delete;

		template<> inline PBByte 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbbyte pb_byte			= m_Session->GetByteField(m_Object, fid, is_null);		return is_null ? PBByte() : PBByte(pb_byte); }
		template<> inline PBBoolean 	GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbboolean pb_boolean	= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBBoolean() : PBBoolean(pb_boolean); }
		template<> inline PBChar 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbchar pb_char			= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBChar() : PBChar(pb_char); }
		template<> inline PBInt 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbint pb_int			= m_Session->GetIntField(m_Object, fid, is_null);		return is_null ? PBInt() : PBInt(pb_int); }
		template<> inline PBUint 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbuint pb_uint			= m_Session->GetUintField(m_Object, fid, is_null);		return is_null ? PBUint() : PBUint(pb_uint); }
		template<> inline PBLong 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pblong pb_long			= m_Session->GetLongField(m_Object, fid, is_null);		return is_null ? PBLong() : PBLong(pb_long); }
		template<> inline PBUlong 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbulong pb_ulong		= m_Session->GetUlongField(m_Object, fid, is_null);		return is_null ? PBUlong() : PBUlong(pb_ulong); }
		template<> inline PBLongLong	GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pblonglong pb_longlong	= m_Session->GetLongLongField(m_Object, fid, is_null);	return is_null ? PBLongLong() : PBLongLong(pb_longlong); }
		template<> inline PBReal 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbreal pb_real			= m_Session->GetRealField(m_Object, fid, is_null);		return is_null ? PBReal() : PBReal(pb_real); }
		template<> inline PBDouble 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdouble pb_double		= m_Session->GetDoubleField(m_Object, fid, is_null);	return is_null ? PBDouble() : PBDouble(pb_double); }
		template<> inline PBDecimal 	GetField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);
			pbboolean is_null = false;

			LPCTSTR dec_repr = m_Session->GetDecimalString(m_Session->GetDecField(m_Object, fid, is_null));

			PBDecimal dec;
			if (!is_null)
				dec = Helper::PBDecimalImpl(ConvertString<std::string>(dec_repr));

			m_Session->ReleaseDecimalString(dec_repr);

			return dec;
		}
		template<> inline PBTime 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbtime pb_time			= m_Session->GetTimeField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdate pb_date			= m_Session->GetDateField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdatetime pb_datetime	= m_Session->GetDateTimeField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbstring pb_string		= m_Session->GetStringField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob 		GetField(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbblob pb_blob			= m_Session->GetBlobField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_blob }; }

		// There are no partial function specializations yet, so we have to make custom functions for these
		template <typename PBT>
		inline PBArray<PBT> GetArrayField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);
			pbboolean is_null = false;

			pbarray pb_array = m_Session->GetArrayField(m_Object, fid, is_null);
			return { m_Session, is_null ? 0 : pb_array };
		}
		template <Helper::FixedString obj_cls_name, pbgroup_type group_type = pbgroup_userobject>
		inline PBObject<obj_cls_name, group_type> GetObjectField(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);
			pbboolean is_null = false;

			pbobject pb_object = m_Session->GetObjectField(m_Object, fid, is_null);
			return { m_Session, is_null ? 0 : pb_object };
		}


		bool IsNull() const
		{
			return !m_Object;
		}

		void SetToNull()
		{
			m_Object = 0;
		}

		


		static const std::wstring& GroupName()
		{
			static std::wstring s_GroupName = ExtractGroupName();
			return s_GroupName;
		}
		static const std::wstring& ClassName()
		{
			static std::wstring s_ClassName = ExtractClassName();
			return s_ClassName;
		}
		static pbclass PBClass(IPB_Session* session)
		{
			static pbclass s_Class = PBClass(session);
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
		template <Helper::FixedString cls_name, pbgroup_type group_type>
		friend class PBObject;


		IPB_Session* m_Session;
		pbobject m_Object;

		// Takes 0.02 milliseconds on average, no need to cache
		pbfieldID GetFieldId(const std::wstring& field_name) const
		{
			if (IsNull())
				throw Inf::u_exf_pbni(std::wstring(L"Tried to access a field of an object that is Null (type ") + cls_name.data + L")");

			pbfieldID fid = m_Session->GetFieldID(PBClass(m_Session), field_name.c_str());

			if (fid == kUndefinedFieldID)
				throw Inf::u_exf_pbni(L"Field " + field_name + L" doesn't exist for class " + cls_name.data);

			return fid;
		}

		static std::wstring ExtractGroupName()
		{
			std::wstring id(cls_name.data);
			size_t i = id.find_first_of(L'.');

			if (i == 0 || i == std::wstring::npos)
				return id;

			if (id.find_last_of(L'.') != i)
				return L"";

			return id.substr(0, i);
		}

		static std::wstring ExtractClassName()
		{
			std::wstring id(cls_name.data);
			size_t i = id.find_first_of(L'.');

			if (i == std::wstring::npos)
				return id;
			
			if (id.find_last_of(L'.') != i)
				return L"";
	
			return id.substr(i + 1);
		}

		static pbclass FindClass(IPB_Session* session)
		{
			pbgroup group = session->FindGroup(GroupName().c_str(), group_type);
			if (!group)
				throw Inf::u_exf_pbni(std::wstring(L"Unbale to find group (") + GroupName() + L")");


			pbclass cls = session->FindClass(group, ClassName().c_str());
			if (!cls)
				throw Inf::u_exf_pbni(std::wstring(L"Unbale to find class (") + ClassName() + L")");

			return cls;
		}
	};

	template <Helper::FixedString cls_name>
	using PBStruct = PBObject<cls_name, pbgroup_structure>;
	template <Helper::FixedString cls_name>
	using PBWindow = PBObject<cls_name, pbgroup_window>;
}
