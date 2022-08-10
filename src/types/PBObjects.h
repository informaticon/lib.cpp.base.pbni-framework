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
			auto [group, cls] = ExtractPBGroupClass(session);

			m_Class = cls;
			m_Object = m_Session->NewObject(cls);
		}

		PBObject(IPB_Session* session, pbobject obj)
			: m_Session(session), m_Object(obj)
		{
			if (m_Object != 0)
			{
				m_Class = m_Session->GetClass(m_Object);
			}
			else
			{
				auto [group, cls] = ExtractPBGroupClass(session);
				m_Class = cls;
			}
		}

		template <typename Ret = void, typename... Args>
		inline Ret Invoke(std::wstring method_name, PBRoutineType pbrt, Args... args)
		{
			if (IsNull())
				throw Inf::u_exf_pbni(std::wstring(L"Tried to invoke a method of an object that is Null (type ") + cls_name.data + L", method: " + method_name + L")");

			// Method siganture is the concatenation of the first letter of return value and arguments
			// exceptions: void -> Q, class -> C{class_name} (without {})
			// L"" returns first found function
			pbmethodID mid = m_Session->GetMethodID(m_Class, method_name.c_str(), pbrt, L"");

			if (mid == kUndefinedMethodID)
				throw Inf::u_exf_pbni(std::wstring(L"Tried to invoke a method that doesnt exist (type: ") + cls_name.data + L", method: " + method_name + L")");

			PBCallInfo ci;
			m_Session->InitCallInfo(m_Class, mid, &ci);
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
		inline void Set(const std::wstring& field_name, const PBT t) = delete;

		template<> inline void Set(const std::wstring& field_name, const PBByte t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetByteField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBBoolean t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetCharField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBChar t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetCharField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBInt t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetIntField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBUint t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetUintField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBLong t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetLongField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBUlong t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetUlongField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBLongLong t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetLongLongField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBReal t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetRealField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBDouble t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDoubleField(m_Object, fid, t); }
		template<> inline void Set(const std::wstring& field_name, const PBDecimal t)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (t.IsNull())
			{
				m_Session->SetFieldToNull(fid);
			}
			else
			{
				std::wstring dec_repr = ConvertString<std::wstring>(t.t.str());

				pbdec pb_dec = m_Session->NewDecimal();
				m_Session->SetDecimal(pb_dec, dec_repr.c_str());

				m_Session->SetDecField(m_Object, fid, pb_dec);
			}
		}
		template<> inline void Set(const std::wstring& field_name, const PBTime t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetTimeField(m_Object, fid, t.m_Time); }
		template<> inline void Set(const std::wstring& field_name, const PBDate t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDateField(m_Object, fid, t.m_Date); }
		template<> inline void Set(const std::wstring& field_name, const PBDateTime t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetDateTimeField(m_Object, fid, t.m_DateTime); }
		template<> inline void Set(const std::wstring& field_name, const PBString t)	{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetPBStringField(m_Object, fid, t.m_String); }
		template<> inline void Set(const std::wstring& field_name, const PBBlob t)		{ pbfieldID fid = GetFieldId(field_name); if (t.IsNull()) m_Session->SetFieldToNull(m_Object, fid); else m_Session->SetBlobField(m_Object, fid, t.m_Blob); }

		// There are no partial function specializations yet, so we have to make custom functions for these
		template <typename PBT>
		inline void SetArray(const std::wstring& field_name, const PBArray<PBT> arr)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (arr.IsNull())
				m_Session->SetFieldToNull(m_Object, fid);
			else
				m_Session->SetArrayField(m_Object, fid, arr.m_Object);
		}
		template <Helper::FixedString cls_name>
		inline void SetObject(const std::wstring& field_name, const PBObject<cls_name, group_type> obj)
		{
			pbfieldID fid = GetFieldId(field_name);
			if (obj.IsNull())
				m_Session->SetFieldToNull(m_Object, fid);
			else
				m_Session->SetObjectField(m_Object, fid, obj.m_Object);
		}


		template <typename PBT>
		inline PBT Get(const std::wstring& field_name) const = delete;

		template<> inline PBByte 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbbyte pb_byte			= m_Session->GetByteField(m_Object, fid, is_null);		return is_null ? PBByte() : PBByte(pb_byte); }
		template<> inline PBBoolean 	Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbboolean pb_boolean		= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBBoolean() : PBBoolean(pb_boolean); }
		template<> inline PBChar 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbchar pb_char			= m_Session->GetCharField(m_Object, fid, is_null);		return is_null ? PBChar() : PBChar(pb_char); }
		template<> inline PBInt 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbint pb_int				= m_Session->GetIntField(m_Object, fid, is_null);		return is_null ? PBInt() : PBInt(pb_int); }
		template<> inline PBUint 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbuint pb_uint			= m_Session->GetUintField(m_Object, fid, is_null);		return is_null ? PBUint() : PBUint(pb_uint); }
		template<> inline PBLong 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pblong pb_long			= m_Session->GetLongField(m_Object, fid, is_null);		return is_null ? PBLong() : PBLong(pb_long); }
		template<> inline PBUlong 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbulong pb_ulong			= m_Session->GetUlongField(m_Object, fid, is_null);		return is_null ? PBUlong() : PBUlong(pb_ulong); }
		template<> inline PBLongLong	Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pblonglong pb_longlong	= m_Session->GetLongLongField(m_Object, fid, is_null);	return is_null ? PBLongLong() : PBLongLong(pb_longlong); }
		template<> inline PBReal 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbreal pb_real			= m_Session->GetRealField(m_Object, fid, is_null);		return is_null ? PBReal() : PBReal(pb_real); }
		template<> inline PBDouble 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdouble pb_double		= m_Session->GetDoubleField(m_Object, fid, is_null);	return is_null ? PBDouble() : PBDouble(pb_double); }
		template<> inline PBDecimal 	Get(const std::wstring& field_name) const
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
		template<> inline PBTime 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbtime pb_time			= m_Session->GetTimeField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_time }; }
		template<> inline PBDate 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdate pb_date			= m_Session->GetDateField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_date }; }
		template<> inline PBDateTime	Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbdatetime pb_datetime	= m_Session->GetDateTimeField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_datetime }; }
		template<> inline PBString 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbstring pb_string		= m_Session->GetStringField(m_Object, fid, is_null);	return { m_Session, is_null ? 0 : pb_string }; }
		template<> inline PBBlob 		Get(const std::wstring& field_name) const { pbfieldID fid = GetFieldId(field_name); pbboolean is_null = false; pbblob pb_blob			= m_Session->GetBlobField(m_Object, fid, is_null);		return { m_Session, is_null ? 0 : pb_blob }; }

		// There are no partial function specializations yet, so we have to make custom functions for these
		template <typename PBT>
		inline PBArray<PBT> GetArray(const std::wstring& field_name) const
		{
			pbfieldID fid = GetFieldId(field_name);
			pbboolean is_null = false;

			pbarray pb_array = m_Session->GetArrayField(m_Object, fid, is_null);
			return { m_Session, is_null ? 0 : pb_array };
		}
		template <Helper::FixedString obj_cls_name>
		inline PBObject<obj_cls_name> GetObject(const std::wstring& field_name) const
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

		// TODO possible caching
		static std::tuple<pbgroup, pbclass> ExtractPBGroupClass(IPB_Session* session)
		{
			std::wstring group_name, class_name;

			std::wstring id(cls_name.data);
			size_t i = id.find_first_of(L'.');

			if (i == std::wstring::npos)
			{
				group_name = id;
				class_name = id;
			}
			else
			{
				if (id.find_last_of(L'.') != i)
					throw Inf::u_exf_pbni(L"Tried to get a class with 2 dots in the name (" + id + L")");

				group_name = id.substr(0, i - 1);
				class_name = id.substr(i);
			}

			pbgroup group = session->FindGroup(group_name.c_str(), group_type);
			if (group == 0)
				throw Inf::u_exf_pbni(L"Unbale to find group (" + id + L")");


			pbclass cls = session->FindClass(group, class_name.c_str());
			if (cls == 0)
				throw Inf::u_exf_pbni(L"Unbale to find class (" + id + L")");

			return { group, cls };
		}
	private:
		friend class Type<PBObject<cls_name, group_type>>;
		friend class PBArray<PBObject<cls_name, group_type>>;

		IPB_Session* m_Session;
		pbobject m_Object;
		pbclass m_Class;

		// Takes 0.02 milliseconds on average, no need to cache
		pbfieldID GetFieldId(const std::wstring& field_name) const
		{
			if (IsNull())
				throw Inf::u_exf_pbni(std::wstring(L"Tried to access a field of an object that is Null (type ") + cls_name.data + L")");

			pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

			if (fid == kUndefinedFieldID)
				throw Inf::u_exf_pbni(L"Field " + field_name + L" doesn't exist for class " + cls_name.data);

			return fid;
		}
	};

	template <Helper::FixedString cls_name>
	using PBStruct = PBObject<cls_name, pbgroup_structure>;
	template <Helper::FixedString cls_name>
	using PBWindow = PBObject<cls_name, pbgroup_window>;
}
