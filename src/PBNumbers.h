#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>

#include <pbext.h>

#include "Errors.h"

/**
 * Taken from <boost/serialization/strong_typedef.hpp>and slightly adapted to be able to set to null
 * 
 * \param T		Base Type
 * \param D		Derived Type
 */
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
	/**
	 * Needed to add NEW custom types, otherwise(pbuint <->pbchar), (pbint <->pbboolean) would conflict, because they are both base type unsigned short or short.
	 * INF_STRONG_TYPEDEF needs to be used because it creates a struct, that is almost equal to base type.
	 * This way we were also able to add Nullability.
	 */


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
		/**
		 * Since decimals arent natively supported, we use boost.
		 * PowerBuilder decimals are 30 Digits max (excluding - and .) cpp_dec_float<8> has a precission of 32 digits.
		 * If the Number gets too big, it will set to 0.
		 */
		using PBDecimalImpl = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<8>>;
	};


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
		 * \param session	Current session
		 * \param dec		The exsiting pbdec or 0
		 */
		PBDecimal(IPB_Session* session, pbdec dec);
		/**
		 * Creates a new pbdec.
		 *
		 * \param session	Current Session
		 */
		PBDecimal(IPB_Session* session, const Helper::PBDecimalImpl& value);

		/**
		 * Copies the Data to PowerBuilder. Creates a new Blob if Null.
		 *
		 * \param data	Pointer to the Data
		 * \param size	Size of the Data
		 */
		void SetDecimal(const Helper::PBDecimalImpl& value);
		/**
		 * Retrieves a Pointer to the Raw Data.
		 *
		 * \return	Pointer to the PowerBuilder Data
		 *
		 * \throw Inf::PBNI_NullPointerException if Null
		 */
		Helper::PBDecimalImpl GetDecimal() const;

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