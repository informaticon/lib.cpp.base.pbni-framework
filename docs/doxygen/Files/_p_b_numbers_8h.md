---
title: src/PBNumbers.h

---

# src/PBNumbers.h



## Namespaces

| Name           |
| -------------- |
| **[Inf](/doxygen/Namespaces/namespace_inf/)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::PBDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/)**  |




## Source code

```cpp
#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

#include <pbext.h>

#include "Errors.h"

#define INF_STRONG_TYPEDEF(T, D)                                                                                                                            \
struct D                                                                                                                                                    \
    : boost::totally_ordered1< D                                                                                                                            \
    , boost::totally_ordered2< D, T                                                                                                                         \
    > >                                                                                                                                                     \
{                                                                                                                                                           \
    T t;                                                                                                                                                    \
    D(const T& t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t(t_), m_IsNull(false) {}                                             \
    D() BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t(0), m_IsNull(true) {}                                                          \
    D(const D & t_) BOOST_NOEXCEPT_IF(boost::has_nothrow_copy_constructor<T>::value) : t(t_.t), m_IsNull(t_.m_IsNull) {}                                    \
    D& operator=(const D& rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) {t = rhs.t; m_IsNull = rhs.m_IsNull; return *this;}                   \
    D& operator=(const T& rhs) BOOST_NOEXCEPT_IF(boost::has_nothrow_assign<T>::value) {t = rhs; m_IsNull = false; return *this;}                            \
    operator const T&() const { if (m_IsNull) { throw Inf::PBNI_NullPointerException(L""#D); } return t;}                                                   \
    operator T&() { if (m_IsNull) { throw Inf::PBNI_NullPointerException(L""#D); } return t;}                                                               \
    bool operator==(const D& rhs) const { if (m_IsNull) { throw Inf::PBNI_NullPointerException(L""#D); } return t == rhs.t;}                                \
    bool operator<(const D& rhs) const { if (m_IsNull) { throw Inf::PBNI_NullPointerException(L""#D); } return t < rhs.t;}                                  \
    bool IsNull() const { return m_IsNull; }                                                                                                                \
    bool SetToNull() { m_IsNull = true; }                                                                                                                   \
private:                                                                                                                                                    \
    bool m_IsNull;                                                                                                                                          \
}

namespace Inf
{
    INF_STRONG_TYPEDEF(pbbyte, PBByte);
    INF_STRONG_TYPEDEF(pbboolean, PBBoolean);
    INF_STRONG_TYPEDEF(pbchar, PBChar);

    INF_STRONG_TYPEDEF(pbint, PBInt);
    INF_STRONG_TYPEDEF(pbuint, PBUint);
    INF_STRONG_TYPEDEF(pblong, PBLong);
    INF_STRONG_TYPEDEF(pbulong, PBUlong);
    INF_STRONG_TYPEDEF(pblonglong, PBLongLong);

    INF_STRONG_TYPEDEF(pbreal, PBReal);
    INF_STRONG_TYPEDEF(pbdouble, PBDouble);
    using PBFloat = PBReal;

    // Decimals aren't natively supported in C++/std, so we use boost
    // Power builder decimals are max 30 digits long (excluding - and .) Boost decimals are weird 8 -> 32 digits
    namespace Helper
    {
        using PBDecimalImpl = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<8>>;
    };


    class PBDecimal
    {
    public:
        PBDecimal(IPB_Session* session, pbdec dec);
        PBDecimal(IPB_Session* session, const Helper::PBDecimalImpl& value);

        void SetDecimal(const Helper::PBDecimalImpl& value);
        Helper::PBDecimalImpl GetDecimal() const;

        bool IsNull() const;
        void SetToNull();

    private:
        template <typename T>
        friend struct Type;
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

        pbdec m_Decimal;
        IPB_Session* m_Session;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDecimal(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200
