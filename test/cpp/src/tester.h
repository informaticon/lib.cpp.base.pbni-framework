#pragma once

#include <Framework.h>

namespace Inf
{
    using Encoding = PBEnum<L"encoding">;

    class FrameworkTester : public PBNI_Class
    {
    public:
        // TODO remove?
        void Test()
        {
            pbgroup sysGroup = m_Session->GetSystemGroup();
            pbclass sysFuncClass = m_Session->FindClass(sysGroup, L"SystemFunctions");
            pbmethodID mid = m_Session->GetMethodID(sysFuncClass, L"classname", PBRT_FUNCTION, L"", false);
            PBCallInfo ci;
            m_Session->InitCallInfo(sysFuncClass, mid, &ci);
            0;
        }

        // Simple types
        void SetPBByte    (PBByte        & x, PBByte         y) { x = y; }
        void SetPBBoolean (PBBoolean     & x, PBBoolean      y) { x = y; }
        void SetPBChar    (PBChar        & x, PBChar         y) { x = y; }
        void SetPBInt     (PBInt         & x, PBInt          y) { x = y; }
        void SetPBUint    (PBUint        & x, PBUint         y) { x = y; }
        void SetPBLong    (PBLong        & x, PBLong         y) { x = y; }
        void SetPBUlong   (PBUlong       & x, PBUlong        y) { x = y; }
        void SetPBLongLong(PBLongLong    & x, PBLongLong     y) { x = y; }
        void SetPBReal    (PBReal        & x, PBReal         y) { x = y; }
        void SetPBDouble  (PBDouble      & x, PBDouble       y) { x = y; }
        void SetPBDecimal (PBDecimal     & x, PBDecimal      y) { x = y; }
        void SetPBTime    (PBTime        & x, PBTime         y) { x = y; }
        void SetPBDate    (PBDate        & x, PBDate         y) { x = y; }
        void SetPBDateTime(PBDateTime    & x, PBDateTime     y) { x = y; }
        void SetPBString  (PBString      & x, PBString       y) { x = y; }
        void SetPBBlob    (PBBlob        & x, PBBlob         y) { x = y; }
        void SetPBObject  (DynPBObject   & x, DynPBObject    y) { x = y; }
        void SetPBArray   (PBArray<PBAny>& x, PBArray<PBAny> y) { x = y; }

        PBByte         GetPBByte    (PBByte         x) { return x; }
        PBBoolean      GetPBBoolean (PBBoolean      x) { return x; }
        PBChar         GetPBChar    (PBChar         x) { return x; }
        PBInt          GetPBInt     (PBInt          x) { return x; }
        PBUint         GetPBUint    (PBUint         x) { return x; }
        PBLong         GetPBLong    (PBLong         x) { return x; }
        PBUlong        GetPBUlong   (PBUlong        x) { return x; }
        PBLongLong     GetPBLongLong(PBLongLong     x) { return x; }
        PBReal         GetPBReal    (PBReal         x) { return x; }
        PBDouble       GetPBDouble  (PBDouble       x) { return x; }
        PBDecimal      GetPBDecimal (PBDecimal      x) { return x; }
        PBTime         GetPBTime    (PBTime         x) { return x; }
        PBDate         GetPBDate    (PBDate         x) { return x; }
        PBDateTime     GetPBDateTime(PBDateTime     x) { return x; }
        PBString       GetPBString  (PBString       x) { return x; }
        PBBlob         GetPBBlob    (PBBlob         x) { return x; }
        DynPBObject    GetPBObject  (DynPBObject    x) { return x; }
        // Can't return Array
        // PBArray<PBAny> GetPBArray   (PBArray<PBAny> x) { return x; }

        void CheckEnum(Encoding x) 
        {
            if (x.GetValueName() != L"encodingansi")
                throw PBNI_Exception(L"Not implemented");
        }

        // Any
        void SetAny(PBAny& x, PBAny y);
        PBAny GetAny(PBAny x);

        void SetField(PBObject<L"u_pbni_test_object">& x, PBAny y);
        PBAny GetField(PBObject<L"u_pbni_test_object"> x, PBInt y);

        void SetterField(PBObject<L"u_pbni_test_object">& x, PBAny y);
        PBAny GetterField(PBObject<L"u_pbni_test_object"> x, PBInt y);
        void GetterRefField(PBObject<L"u_pbni_test_object"> x, PBInt y, PBAny& z);
        // TODO test events

        void SetArray(PBArray<PBAny>& x, PBAny y);
        PBAny GetArray(PBAny x);
        PBAny GetArrayArray(PBArray<PBAny> x);
        // TODO bounded array
        // TODO copy complex variables to member variable

        void Throw(PBString message, PBArray<PBString> keys, PBArray<PBString> values);

    private:
        template <typename T>
        void SetArrayHelper(pbarray any_arr, PBAny any_val)
        {
            PBArray<T> arr(m_Session, any_arr);
            T val = any_val.Get<T>();

            arr.Set(1, val);
        }

        template <typename T>
        PBAny GetArrayHelper(PBAny any_arr)
        {
            PBArray<T> arr = any_arr.Get<PBArray<T>>();

            return { m_Session, arr.Get(1) };
        }
    };
}