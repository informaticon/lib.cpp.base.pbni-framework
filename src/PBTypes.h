#pragma once

#include "PBNumbers.h"
#include "PBDateTimes.h"
#include "PBString.h"
#include "PBBlob.h"
#include "PBEnums.h"
#include "Helper.h"


namespace Inf
{
    /**
     * This is the Genereic Type struct, each PBType implements the Fields it needs.
     * You can Access any one of the Functions using e.g. Type<T>::PBSignature.
     * 
     * \tparam T    The related Type
     */
    template <typename T>
    struct Type {
        // This Field is used to build a Method Signature, if you want to invoke a PowerBuilder Function from C++.
        static constexpr wchar_t PBSignature = L' ';
        // This Field is used to check for correct IPB_Value Types.
        static constexpr pbvalue_type PBType = pbvalue_notype;

        /**
         * This Function is used to generate the Description of a Method, it needs to take in the name of the argument so we can add [] at the end of arrays.
         * This wont add any spaces between the type and argument_name.
         *
         * \param argument_name     The name to put between type and []
         * \return                  The combined string
         */
        static inline std::wstring GetPBName(const std::wstring& argument_name) = delete;
    };

/// \cond typetemplates
    /**
     * We dont want to be used as Argument, only implement whats allowed.
     */
    using PBVoid = void;
    template <>
    struct Type<PBVoid> {
        static constexpr wchar_t PBSignature = L'Q';
    };

    /**
     * Complex Types start with Decimal
     */

#pragma region Any
    template<>
    struct Type<PBAny>
    {
        static constexpr wchar_t PBSignature = L'A';
        static constexpr pbvalue_type PBType = pbvalue_any;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"any" + argument_name; }
    };
#pragma endregion

#pragma region Bytelike
    template<>
    struct Type<PBByte>
    {
        static constexpr wchar_t PBSignature = L'E';
        static constexpr pbvalue_type PBType = pbvalue_byte;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"byte" + argument_name; }
    };

    template<>
    struct Type<PBBoolean>
    {
        static constexpr wchar_t PBSignature = L'B';
        static constexpr pbvalue_type PBType = pbvalue_boolean;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"boolean" + argument_name; }
    };

    template<>
    struct Type<PBChar>
    {
        static constexpr wchar_t PBSignature = L'H';
        static constexpr pbvalue_type PBType = pbvalue_char;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"char" + argument_name; }
    };
#pragma endregion

#pragma region Integer_Numbers
    template<>
    struct Type<PBInt>
    {
        static constexpr wchar_t PBSignature = L'I';
        static constexpr pbvalue_type PBType = pbvalue_int;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"int" + argument_name; }
    };

    template<>
    struct Type<PBUint>
    {
        static constexpr wchar_t PBSignature = L'N';
        static constexpr pbvalue_type PBType = pbvalue_uint;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"uint" + argument_name; }
    };

    template<>
    struct Type<PBLong>
    {
        static constexpr wchar_t PBSignature = L'L';
        static constexpr pbvalue_type PBType = pbvalue_long;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"long" + argument_name; }
    };

    template<>
    struct Type<PBUlong>
    {
        static constexpr wchar_t PBSignature = L'U';
        static constexpr pbvalue_type PBType = pbvalue_ulong;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"ulong" + argument_name; }
    };

    template<>
    struct Type<PBLongLong>
    {
        static constexpr wchar_t PBSignature = L'K';
        static constexpr pbvalue_type PBType = pbvalue_longlong;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"longlong" + argument_name; }
    };
#pragma endregion

#pragma region Floating_Point_Numbers
    template<>
    struct Type<PBReal>
    {
        static constexpr wchar_t PBSignature = L'F';
        static constexpr pbvalue_type PBType = pbvalue_real;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"real" + argument_name; }
    };

    template<>
    struct Type<PBDouble>
    {
        static constexpr wchar_t PBSignature = L'D';
        static constexpr pbvalue_type PBType = pbvalue_double;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"double" + argument_name; }
    };

    template<>
    struct Type<PBDecimal>
    {
        static constexpr wchar_t PBSignature = L'M';
        static constexpr pbvalue_type PBType = pbvalue_dec;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"dec" + argument_name; }
    };
#pragma endregion

#pragma region Date_Times
    template<>
    struct Type<PBTime>
    {
        static constexpr wchar_t PBSignature = L'T';
        static constexpr pbvalue_type PBType = pbvalue_time;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"time" + argument_name; }
    };

    template<>
    struct Type<PBDate>
    {
        static constexpr wchar_t PBSignature = L'Y';
        static constexpr pbvalue_type PBType = pbvalue_date;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"date" + argument_name; }
    };

    template<>
    struct Type<PBDateTime>
    {
        static constexpr wchar_t PBSignature = L'W';
        static constexpr pbvalue_type PBType = pbvalue_datetime;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"datetime" + argument_name; }
    };
#pragma endregion

#pragma region Variable_Sized
    template<>
    struct Type<PBString>
    {
        static constexpr wchar_t PBSignature = L'S';
        static constexpr pbvalue_type PBType = pbvalue_string;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"string" + argument_name; }
    };

    template<>
    struct Type<PBBlob>
    {
        static constexpr wchar_t PBSignature = L'O';
        static constexpr pbvalue_type PBType = pbvalue_blob;
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"blob" + argument_name; }
    };

    /**
     * For Types that have their own template types (PBObject<>, PBArray<>) we cant partially specialize the static Functions.
     * Instead we have to create our own Struct, which can be partially specialized
     */
    template <typename T, pblong... dims>
    struct Type<PBArray<T, dims...>> // <- Partial specialization
    {
        static inline std::wstring PBSignature = std::wstring(1, Type<T>::PBSignature) + L"[]";
        static inline std::wstring GetPBName(const std::wstring& argument_name)
        {
            if constexpr (sizeof...(dims) == 0)
            {
                return Type<T>::GetPBName(argument_name) + L"[]";
            }
            else
            {
                std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
                dimensions.resize(dimensions.size() - 2);
                return Type<T>::GetPBName(argument_name) + L"[" + dimensions + L"]";
            }
        }
    };


    template <Helper::FixedString class_id, pbgroup_type group_type>
    class PBObject;

    template <typename Item, pblong... dims>
        requires (sizeof...(dims) <= 3 && !std::is_reference_v<Item> && !std::is_pointer_v<Item>)
    class PBArray;

    template <Helper::FixedString class_id, pbgroup_type group_type, pblong... dims>
    struct Type<PBArray<PBObject<class_id, group_type>, dims...>>
    {
        static inline std::wstring PBSignature = Type<PBObject<class_id, group_type>>::PBSignature + L"[]";
        static inline std::wstring GetPBName(const std::wstring& argument_name)
        {
            if constexpr (sizeof...(dims) == 0)
            {
                return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[]";
            }
            else
            {
                std::wstring dimensions = ((std::to_wstring(dims) + L", ") + ...);
                dimensions.resize(dimensions.size() - 2);
                return Type<PBObject<class_id, group_type>>::GetPBName(argument_name) + L"[" + dimensions + L"]";
            }
        }
    };

    template<>
    struct Type<DynPBObject>
    {
        static inline std::wstring PBSignature = L"Cpowerobject.";
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return L"powerobject" + argument_name; }
    };

    template <Helper::FixedString class_id, pbgroup_type group_type>
    struct Type<PBObject<class_id, group_type>>
    {
        static inline std::wstring PBSignature = std::wstring(L"C") + DynPBObject::ExtractClassName(class_id.data) + L".";
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return std::wstring(class_id.data) + argument_name; }
    };


    template <Helper::FixedString name>
    struct Type<PBEnum<name>>
    {
        static inline std::wstring PBSignature = std::wstring(L"C") + name.data + L".";
        static inline std::wstring GetPBName(const std::wstring& argument_name) { return name.data + argument_name; }
    };
#pragma endregion
/// \endcond
}