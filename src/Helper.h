#pragma once

#include <pbext.h>

namespace Inf
{
    namespace Helper
    {
        /**
         * We need this to be able to pass strings as Template parameters. There will probably be a more supported way in C++23.
         * See https://www.quora.com/How-do-you-pass-a-string-literal-as-a-parameter-to-a-C-template-class.
         */
        template<size_t N>
        struct FixedString
        {
            constexpr FixedString(wchar_t const (&s)[N])
            {
                std::copy_n(s, N, this->data);
            }

            constexpr std::strong_ordering operator<=>(FixedString const&) const = default;

            wchar_t data[N];
        };

        class PBValue;
    }

    class PBAny;

    class DynPBObject;

    template <Helper::FixedString class_id, pbgroup_type group_type>
    class PBObject;

    template <typename Item, pblong... dims>
        requires (sizeof...(dims) <= 3 && !std::is_reference_v<Item> && !std::is_pointer_v<Item>)
    class PBArray;

    namespace Helper
    {
        template <typename T>
        struct is_pb_object : public std::false_type {};

        template <Helper::FixedString class_id, pbgroup_type group_type>
        struct is_pb_object<PBObject<class_id, group_type>> : public std::true_type {};

        template <typename T>
        inline constexpr bool is_pb_object_v = is_pb_object<T>::value;


        template <typename>
        struct is_pb_array : public std::false_type {};

        template <typename Item, pblong... dims>
        struct is_pb_array<PBArray<Item, dims...>> : public std::true_type {};

        template <typename T>
        inline constexpr bool is_pb_array_v = is_pb_array<T>::value;
    };
}