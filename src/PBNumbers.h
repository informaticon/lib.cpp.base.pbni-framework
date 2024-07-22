#pragma once

#include <pbni/pbext.h>

#include <boost/config.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

#include "Errors.h"

/**
 * Taken from <boost/serialization/strong_typedef.hpp>and slightly adapted to be able to set to null
 *
 * \param T     Base Type
 * \param D     Derived Type
 */
#define INF_STRONG_TYPEDEF(T, D)                              \
    struct D                                                  \
    {                                                         \
        D() noexcept                                          \
            : t(0), m_IsNull(true)                            \
        { }                                                   \
        D(T const& t_) noexcept                               \
            : t(t_), m_IsNull(false)                          \
        { }                                                   \
        D& operator=(T const& rhs) noexcept                   \
        {                                                     \
            t = rhs;                                          \
            m_IsNull = false;                                 \
            return *this;                                     \
        }                                                     \
        operator T const&() const                             \
        {                                                     \
            if (m_IsNull)                                     \
                throw Inf::PBNI_NullPointerException(L"" #D); \
            return t;                                         \
        }                                                     \
        operator T&()                                         \
        {                                                     \
            if (m_IsNull)                                     \
                throw Inf::PBNI_NullPointerException(L"" #D); \
            return t;                                         \
        }                                                     \
        bool IsNull() const noexcept                          \
        {                                                     \
            return m_IsNull;                                  \
        }                                                     \
        bool SetToNull() noexcept                             \
        {                                                     \
            m_IsNull = true;                                  \
        }                                                     \
                                                              \
    private:                                                  \
        T t;                                                  \
        bool m_IsNull;                                        \
    }

namespace Inf
{
    /**
     * Needed to add NEW custom types, otherwise(pbuint <->pbchar), (pbint <->pbboolean) would conflict, because they are
     * both base type unsigned short or short. INF_STRONG_TYPEDEF needs to be used because it creates a struct, that is
     * almost equal to base type. This way we were also able to add Nullability.
     */


    INF_STRONG_TYPEDEF(pbbyte, PBByte);
    INF_STRONG_TYPEDEF(pbboolean, PBBoolean);
    INF_STRONG_TYPEDEF(pbchar, PBChar);

    INF_STRONG_TYPEDEF(pbint, PBInt);
    INF_STRONG_TYPEDEF(pbuint, PBUint);
    INF_STRONG_TYPEDEF(pblong, PBLong);
    INF_STRONG_TYPEDEF(pbulong, PBUlong);
    INF_STRONG_TYPEDEF(pblonglong, PBLongLong);
    INF_STRONG_TYPEDEF(void*, PBLongPtr);

    #if _WIN64
        using FakePBLongPtr = PBLongLong;
    #else
        using FakePBLongPtr = PBLong;
    #endif

    INF_STRONG_TYPEDEF(pbreal, PBReal);
    INF_STRONG_TYPEDEF(pbdouble, PBDouble);

    using PBFloat = PBReal;

    namespace Helper
    {
        /**
         * Since decimals arent natively supported, we use boost.
         * PowerBuilder decimals are 30 Digits max (excluding - and .) cpp_dec_float<8> has a precission of 32 digits.
         * If the Number gets too big, it will set to 0.
         */
        using PBDecimalImpl = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<8>>;
    };  // namespace Helper


    /**
     * Small Wrapper for pbdec.
     */
    class PBDecimal
    {
    public:
        /**
         * Creates a Wrapper to an already existing pbdec.
         * Will be Null if dec is 0.
         *
         * \param session   Current session
         * \param dec       The exsiting pbdec or 0
         */
        PBDecimal(IPB_Session* session, pbdec dec);
        /**
         * Creates a new pbdec.
         *
         * \param session   Current Session
         * \param value     The Decimal to copy
         */
        PBDecimal(IPB_Session* session, const Helper::PBDecimalImpl& value);

        /**
         * Copies the Decimal string to PowerBuilder, crates a new Decimal if Null.
         *
         * \param value     The Decimal to copy
         */
        void SetDecimal(const Helper::PBDecimalImpl& value);
        /**
         * Copies the Decimal from PowerBuilder.
         *
         * \return  Boost Decimal
         *
         * \throw Inf::PBNI_NullPointerException if Null
         */
        Helper::PBDecimalImpl GetDecimal() const;
        /**
         * Copies the Decimal from PowerBuilder into a String
         *
         * \return  String
         *
         * \throw Inf::PBNI_NullPointerException if Null
         */
        std::string GetString() const;

        /**
         * Copies the Decimal from PowerBuilder into a WString
         *
         * \return  String
         *
         * \throw Inf::PBNI_NullPointerException if Null
         */
        std::wstring GetWString() const;

        /**
         * Checks whether pbdec is Null.
         *
         * \return Is Null
         */
        bool IsNull() const;
        /**
         * Sets pbdec to Null.
         */
        void SetToNull();

        /**
         * Retrieve the private PB Reference
         */
        operator pbdec() const
        {
            return m_Decimal;
        }

    private:
        friend Helper::PBValue;

        pbdec m_Decimal;
        IPB_Session* m_Session;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDecimal(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}  // namespace Inf