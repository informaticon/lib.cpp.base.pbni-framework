#include "tester.h"

#include <ClassDescription.h>

INF_REGISTER_CLASS(Inf::FrameworkTester, L"u_pbni_framework_tester");

// TODO remove?
INF_REGISTER_FUNC(Test    , L"of_test");

INF_REGISTER_FUNC(SetPBByte    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBBoolean , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBChar    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBInt     , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBUint    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBLong    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBUlong   , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBLongLong, L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBReal    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBDouble  , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBDecimal , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBTime    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBDate    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBDateTime, L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBString  , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBBlob    , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBObject  , L"of_set", L"aa_to", L"aa_from");
INF_REGISTER_FUNC(SetPBArray   , L"of_set", L"aa_to", L"aa_from");

INF_REGISTER_FUNC(GetPBByte    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBBoolean , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBChar    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBInt     , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBUint    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBLong    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBUlong   , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBLongLong, L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBReal    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBDouble  , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBDecimal , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBTime    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBDate    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBDateTime, L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBString  , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBBlob    , L"of_get", L"aa_x");
INF_REGISTER_FUNC(GetPBObject  , L"of_get", L"aa_x");

INF_REGISTER_FUNC(CheckEnum    , L"of_enum", L"ae_encodingansi");


INF_REGISTER_FUNC(SetAny, L"of_set_any", L"aa_to", L"aa_from");
void Inf::FrameworkTester::SetAny(PBAny& x, PBAny y)
{
    if (y.IsArray()) {
        x = PBAny(m_Session, y.Get<PBArray<PBAny>>());
        return;
    }

    switch (y.GetType())
    {
    case Type<PBByte    >::PBType: x = PBAny(m_Session, y.Get<PBByte    >()); break;
    case Type<PBBoolean >::PBType: x = PBAny(m_Session, y.Get<PBBoolean >()); break;
    case Type<PBChar    >::PBType: x = PBAny(m_Session, y.Get<PBChar    >()); break;
    case Type<PBInt     >::PBType: x = PBAny(m_Session, y.Get<PBInt     >()); break;
    case Type<PBUint    >::PBType: x = PBAny(m_Session, y.Get<PBUint    >()); break;
    case Type<PBLong    >::PBType: x = PBAny(m_Session, y.Get<PBLong    >()); break;
    case Type<PBUlong   >::PBType: x = PBAny(m_Session, y.Get<PBUlong   >()); break;
    case Type<PBLongLong>::PBType: x = PBAny(m_Session, y.Get<PBLongLong>()); break;
    case Type<PBReal    >::PBType: x = PBAny(m_Session, y.Get<PBReal    >()); break;
    case Type<PBDouble  >::PBType: x = PBAny(m_Session, y.Get<PBDouble  >()); break;
    case Type<PBDecimal >::PBType: x = PBAny(m_Session, y.Get<PBDecimal >()); break;
    case Type<PBTime    >::PBType: x = PBAny(m_Session, y.Get<PBTime    >()); break;
    case Type<PBDate    >::PBType: x = PBAny(m_Session, y.Get<PBDate    >()); break;
    case Type<PBDateTime>::PBType: x = PBAny(m_Session, y.Get<PBDateTime>()); break;
    case Type<PBString  >::PBType: x = PBAny(m_Session, y.Get<PBString  >()); break;
    case Type<PBBlob    >::PBType: x = PBAny(m_Session, y.Get<PBBlob    >()); break;
    case PBAny::Object: x = PBAny(m_Session, y.Get<DynPBObject>()); break;
    case PBAny::Enum:   x = PBAny(m_Session, y.Get<Encoding   >()); break;
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(GetAny, L"of_get_any", L"aa_x");
Inf::PBAny Inf::FrameworkTester::GetAny(PBAny x)
{
    if (x.IsArray()) {
        return PBAny(m_Session, x.Get<PBArray<PBAny>>());
    }

    switch (x.GetType())
    {
    case Type<PBByte    >::PBType: return PBAny(m_Session, x.Get<PBByte    >());
    case Type<PBBoolean >::PBType: return PBAny(m_Session, x.Get<PBBoolean >());
    case Type<PBChar    >::PBType: return PBAny(m_Session, x.Get<PBChar    >());
    case Type<PBInt     >::PBType: return PBAny(m_Session, x.Get<PBInt     >());
    case Type<PBUint    >::PBType: return PBAny(m_Session, x.Get<PBUint    >());
    case Type<PBLong    >::PBType: return PBAny(m_Session, x.Get<PBLong    >());
    case Type<PBUlong   >::PBType: return PBAny(m_Session, x.Get<PBUlong   >());
    case Type<PBLongLong>::PBType: return PBAny(m_Session, x.Get<PBLongLong>());
    case Type<PBReal    >::PBType: return PBAny(m_Session, x.Get<PBReal    >());
    case Type<PBDouble  >::PBType: return PBAny(m_Session, x.Get<PBDouble  >());
    case Type<PBDecimal >::PBType: return PBAny(m_Session, x.Get<PBDecimal >());
    case Type<PBTime    >::PBType: return PBAny(m_Session, x.Get<PBTime    >());
    case Type<PBDate    >::PBType: return PBAny(m_Session, x.Get<PBDate    >());
    case Type<PBDateTime>::PBType: return PBAny(m_Session, x.Get<PBDateTime>());
    case Type<PBString  >::PBType: return PBAny(m_Session, x.Get<PBString  >());
    case Type<PBBlob    >::PBType: return PBAny(m_Session, x.Get<PBBlob    >());
    case PBAny::Object: return PBAny(m_Session, x.Get<DynPBObject>());
    case PBAny::Enum  : return PBAny(m_Session, x.Get<Encoding>());
    default: throw PBNI_Exception(L"Not implemented");
    }

    return { m_Session };
}

INF_REGISTER_FUNC(SetField, L"of_set_field", L"au_x", L"aa_x");
void Inf::FrameworkTester::SetField(PBObject<L"u_pbni_test_object">& x, PBAny y)
{
    switch (y.GetType())
    {
    case Type<PBByte    >::PBType: x.SetField(L"iby_test", y.Get<PBByte    >()); break;
    case Type<PBBoolean >::PBType: x.SetField(L"ibo_test", y.Get<PBBoolean >()); break;
    case Type<PBChar    >::PBType: x.SetField(L"ic_test",  y.Get<PBChar    >()); break;
    case Type<PBInt     >::PBType: x.SetField(L"ii_test",  y.Get<PBInt     >()); break;
    case Type<PBUint    >::PBType: x.SetField(L"iui_test", y.Get<PBUint    >()); break;
    case Type<PBLong    >::PBType: x.SetField(L"il_test",  y.Get<PBLong    >()); break;
    case Type<PBUlong   >::PBType: x.SetField(L"iul_test", y.Get<PBUlong   >()); break;
    case Type<PBLongLong>::PBType: x.SetField(L"ill_test", y.Get<PBLongLong>()); break;
    case Type<PBReal    >::PBType: x.SetField(L"ir_test",  y.Get<PBReal    >()); break;
    case Type<PBDouble  >::PBType: x.SetField(L"ido_test", y.Get<PBDouble  >()); break;
    case Type<PBDecimal >::PBType: x.SetField(L"ide_test", y.Get<PBDecimal >()); break;
    case Type<PBTime    >::PBType: x.SetField(L"it_test",  y.Get<PBTime    >()); break;
    case Type<PBDate    >::PBType: x.SetField(L"ida_test", y.Get<PBDate    >()); break;
    case Type<PBDateTime>::PBType: x.SetField(L"idt_test", y.Get<PBDateTime>()); break;
    case Type<PBString  >::PBType: x.SetField(L"is_test",  y.Get<PBString  >()); break;
    case Type<PBBlob    >::PBType: x.SetField(L"ibl_test", y.Get<PBBlob    >()); break;

    case PBAny::Object: x.SetField(L"iu_test", y.Get<DynPBObject>()); break;
    case PBAny::Enum:   x.SetField(L"ie_test", y.Get<Encoding   >()); break;
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(GetField, L"of_get_field", L"au_x", L"ai_y");
Inf::PBAny Inf::FrameworkTester::GetField(PBObject<L"u_pbni_test_object"> x, PBInt y)
{
    switch (y)
    {
    case  1: return PBAny(m_Session, x.GetField<PBByte     >(L"iby_test"));
    case  2: return PBAny(m_Session, x.GetField<PBBoolean  >(L"ibo_test"));
    case  3: return PBAny(m_Session, x.GetField<PBChar     >(L"ic_test" ));
    case  4: return PBAny(m_Session, x.GetField<PBInt      >(L"ii_test" ));
    case  5: return PBAny(m_Session, x.GetField<PBUint     >(L"iui_test"));
    case  6: return PBAny(m_Session, x.GetField<PBLong     >(L"il_test" ));
    case  7: return PBAny(m_Session, x.GetField<PBUlong    >(L"iul_test"));
    case  8: return PBAny(m_Session, x.GetField<PBLongLong >(L"ill_test"));
    case  9: return PBAny(m_Session, x.GetField<PBReal     >(L"ir_test" ));
    case 10: return PBAny(m_Session, x.GetField<PBDouble   >(L"ido_test"));
    case 11: return PBAny(m_Session, x.GetField<PBDecimal  >(L"ide_test"));
    case 12: return PBAny(m_Session, x.GetField<PBTime     >(L"it_test" ));
    case 13: return PBAny(m_Session, x.GetField<PBDate     >(L"ida_test"));
    case 14: return PBAny(m_Session, x.GetField<PBDateTime >(L"idt_test"));
    case 15: return PBAny(m_Session, x.GetField<PBString   >(L"is_test" ));
    case 16: return PBAny(m_Session, x.GetField<PBBlob     >(L"ibl_test"));
    case 17: return PBAny(m_Session, x.GetField<DynPBObject>(L"iu_test" ));
    case 18: return PBAny(m_Session, x.GetField<Encoding   >(L"ie_test" ));
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(SetterField, L"of_setter_field", L"au_x", L"aa_x");
void Inf::FrameworkTester::SetterField(PBObject<L"u_pbni_test_object">& x, PBAny y)
{
    switch (y.GetType())
    {
    case Type<PBByte    >::PBType: x.Call(L"of_set_iby", y.Get<PBByte    >()); break;
    case Type<PBBoolean >::PBType: x.Call(L"of_set_ibo", y.Get<PBBoolean >()); break;
    case Type<PBChar    >::PBType: x.Call(L"of_set_ic",  y.Get<PBChar    >()); break;
    case Type<PBInt     >::PBType: x.Call(L"of_set_ii",  y.Get<PBInt     >()); break;
    case Type<PBUint    >::PBType: x.Call(L"of_set_iui", y.Get<PBUint    >()); break;
    case Type<PBLong    >::PBType: x.Call(L"of_set_il",  y.Get<PBLong    >()); break;
    case Type<PBUlong   >::PBType: x.Call(L"of_set_iul", y.Get<PBUlong   >()); break;
    case Type<PBLongLong>::PBType: x.Call(L"of_set_ill", y.Get<PBLongLong>()); break;
    case Type<PBReal    >::PBType: x.Call(L"of_set_ir",  y.Get<PBReal    >()); break;
    case Type<PBDouble  >::PBType: x.Call(L"of_set_ido", y.Get<PBDouble  >()); break;
    case Type<PBDecimal >::PBType: x.Call(L"of_set_ide", y.Get<PBDecimal >()); break;
    case Type<PBTime    >::PBType: x.Call(L"of_set_it",  y.Get<PBTime    >()); break;
    case Type<PBDate    >::PBType: x.Call(L"of_set_ida", y.Get<PBDate    >()); break;
    case Type<PBDateTime>::PBType: x.Call(L"of_set_idt", y.Get<PBDateTime>()); break;
    case Type<PBString  >::PBType: x.Call(L"of_set_is",  y.Get<PBString  >()); break;
    case Type<PBBlob    >::PBType: x.Call(L"of_set_ibl", y.Get<PBBlob    >()); break;

    case PBAny::Object: x.SetField(L"iu_test", y.Get<DynPBObject>()); break;
    case PBAny::Enum:   x.SetField(L"ie_test", y.Get<Encoding   >()); break;
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(GetterField, L"of_getter_field", L"au_x", L"ai_y");
Inf::PBAny Inf::FrameworkTester::GetterField(PBObject<L"u_pbni_test_object"> x, PBInt y)
{
    switch (y)
    {
    case  1: return PBAny(m_Session, x.Call<PBByte     >(L"of_get_iby"));
    case  2: return PBAny(m_Session, x.Call<PBBoolean  >(L"of_get_ibo"));
    case  3: return PBAny(m_Session, x.Call<PBChar     >(L"of_get_ic" ));
    case  4: return PBAny(m_Session, x.Call<PBInt      >(L"of_get_ii" ));
    case  5: return PBAny(m_Session, x.Call<PBUint     >(L"of_get_iui"));
    case  6: return PBAny(m_Session, x.Call<PBLong     >(L"of_get_il" ));
    case  7: return PBAny(m_Session, x.Call<PBUlong    >(L"of_get_iul"));
    case  8: return PBAny(m_Session, x.Call<PBLongLong >(L"of_get_ill"));
    case  9: return PBAny(m_Session, x.Call<PBReal     >(L"of_get_ir" ));
    case 10: return PBAny(m_Session, x.Call<PBDouble   >(L"of_get_ido"));
    case 11: return PBAny(m_Session, x.Call<PBDecimal  >(L"of_get_ide"));
    case 12: return PBAny(m_Session, x.Call<PBTime     >(L"of_get_it" ));
    case 13: return PBAny(m_Session, x.Call<PBDate     >(L"of_get_ida"));
    case 14: return PBAny(m_Session, x.Call<PBDateTime >(L"of_get_idt"));
    case 15: return PBAny(m_Session, x.Call<PBString   >(L"of_get_is" ));
    case 16: return PBAny(m_Session, x.Call<PBBlob     >(L"of_get_ibl"));
    case 17: return PBAny(m_Session, x.Call<DynPBObject>(L"of_get_iu" ));
    case 18: return PBAny(m_Session, x.Call<Encoding   >(L"of_get_ie" ));
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(GetterRefField, L"of_getter_field_ref", L"au_x", L"ai_y", L"aa_z");
void Inf::FrameworkTester::GetterRefField(PBObject<L"u_pbni_test_object"> x, PBInt y, PBAny& z)
{
    switch (y)
    {
    case  1: x.Call<void, PBAny&>(L"of_get_iby", z); break;
    case  2: x.Call<void, PBAny&>(L"of_get_ibo", z); break;
    case  3: x.Call<void, PBAny&>(L"of_get_ic" , z); break;
    case  4: x.Call<void, PBAny&>(L"of_get_ii" , z); break;
    case  5: x.Call<void, PBAny&>(L"of_get_iui", z); break;
    case  6: x.Call<void, PBAny&>(L"of_get_il" , z); break;
    case  7: x.Call<void, PBAny&>(L"of_get_iul", z); break;
    case  8: x.Call<void, PBAny&>(L"of_get_ill", z); break;
    case  9: x.Call<void, PBAny&>(L"of_get_ir" , z); break;
    case 10: x.Call<void, PBAny&>(L"of_get_ido", z); break;
    case 11: x.Call<void, PBAny&>(L"of_get_ide", z); break;
    case 12: x.Call<void, PBAny&>(L"of_get_it" , z); break;
    case 13: x.Call<void, PBAny&>(L"of_get_ida", z); break;
    case 14: x.Call<void, PBAny&>(L"of_get_idt", z); break;
    case 15: x.Call<void, PBAny&>(L"of_get_is" , z); break;
    case 16: x.Call<void, PBAny&>(L"of_get_ibl", z); break;
    case 17: x.Call<void, PBAny&>(L"of_get_iu" , z); break;
    case 18: x.Call<void, PBAny&>(L"of_get_ie" , z); break;
    default: throw PBNI_Exception(L"Not implemented");
    }
}


INF_REGISTER_FUNC(SetArray, L"of_set_array", L"aa_array", L"aa_val");
void Inf::FrameworkTester::SetArray(PBArray<PBAny>& x, PBAny y)
{
    if (y.IsArray())
    {
        x.Set(1, { m_Session, y.Get<PBArray<PBAny>>() });
        return;
    }

    switch (y.GetType())
    {
    case Type<PBByte    >::PBType: SetArrayHelper<PBByte     >(x, y); break;
    case Type<PBBoolean >::PBType: SetArrayHelper<PBBoolean  >(x, y); break;
    case Type<PBChar    >::PBType: SetArrayHelper<PBChar     >(x, y); break;
    case Type<PBInt     >::PBType: SetArrayHelper<PBInt      >(x, y); break;
    case Type<PBUint    >::PBType: SetArrayHelper<PBUint     >(x, y); break;
    case Type<PBLong    >::PBType: SetArrayHelper<PBLong     >(x, y); break;
    case Type<PBUlong   >::PBType: SetArrayHelper<PBUlong    >(x, y); break;
    case Type<PBLongLong>::PBType: SetArrayHelper<PBLongLong >(x, y); break;
    case Type<PBReal    >::PBType: SetArrayHelper<PBReal     >(x, y); break;
    case Type<PBDouble  >::PBType: SetArrayHelper<PBDouble   >(x, y); break;
    case Type<PBDecimal >::PBType: SetArrayHelper<PBDecimal  >(x, y); break;
    case Type<PBTime    >::PBType: SetArrayHelper<PBTime     >(x, y); break;
    case Type<PBDate    >::PBType: SetArrayHelper<PBDate     >(x, y); break;
    case Type<PBDateTime>::PBType: SetArrayHelper<PBDateTime >(x, y); break;
    case Type<PBString  >::PBType: SetArrayHelper<PBString   >(x, y); break;
    case Type<PBBlob    >::PBType: SetArrayHelper<PBBlob     >(x, y); break;
    case PBAny::Object: x.Set(1, { m_Session, y.Get<DynPBObject>() }); break;
    case PBAny::Enum:   x.Set(1, { m_Session, y.Get<Encoding >()   }); break;
    default: throw PBNI_Exception(L"Not implemented");
    }
}

INF_REGISTER_FUNC(GetArray, L"of_get_array", L"aa_array");
Inf::PBAny Inf::FrameworkTester::GetArray(PBAny x)
{
    pbarray arr = x.Get<PBArray<PBAny>>();
    pblong i = 1;
    switch (m_Session->GetArrayItemType(arr, &i))
    {
    case Type<PBByte    >::PBType: return GetArrayHelper<PBByte     >(x);
    case Type<PBBoolean >::PBType: return GetArrayHelper<PBBoolean  >(x);
    case Type<PBChar    >::PBType: return GetArrayHelper<PBChar     >(x);
    case Type<PBInt     >::PBType: return GetArrayHelper<PBInt      >(x);
    case Type<PBUint    >::PBType: return GetArrayHelper<PBUint     >(x);
    case Type<PBLong    >::PBType: return GetArrayHelper<PBLong     >(x);
    case Type<PBUlong   >::PBType: return GetArrayHelper<PBUlong    >(x);
    case Type<PBLongLong>::PBType: return GetArrayHelper<PBLongLong >(x);
    case Type<PBReal    >::PBType: return GetArrayHelper<PBReal     >(x);
    case Type<PBDouble  >::PBType: return GetArrayHelper<PBDouble   >(x);
    case Type<PBDecimal >::PBType: return GetArrayHelper<PBDecimal  >(x);
    case Type<PBTime    >::PBType: return GetArrayHelper<PBTime     >(x);
    case Type<PBDate    >::PBType: return GetArrayHelper<PBDate     >(x);
    case Type<PBDateTime>::PBType: return GetArrayHelper<PBDateTime >(x);
    case Type<PBString  >::PBType: return GetArrayHelper<PBString   >(x);
    case Type<PBBlob    >::PBType: return GetArrayHelper<PBBlob     >(x);
    default:
        // ItemType is the class pointer of an object
        return GetArrayHelper<DynPBObject>(x);
    }
}

INF_REGISTER_FUNC(GetArrayArray, L"of_get_array_array", L"aa_array");
Inf::PBAny Inf::FrameworkTester::GetArrayArray(PBArray<PBAny> x)
{
    return { m_Session, x.Get(1).Get<PBArray<PBAny>>() };
}

INF_REGISTER_FUNC(Throw, L"of_throw", L"as_message", L"as_keys", L"as_values");
void Inf::FrameworkTester::Throw(PBString message, PBArray<PBString> keys, PBArray<PBString> values)
{
    std::map<std::wstring, std::wstring> store;
    for (pblong i = 1; i <= keys.Size(); i++) {
        store[keys.Get(i).GetWString()] = values.Get(i).GetWString();
    }

    throw PBNI_Exception(message.GetWString(), store);
}
