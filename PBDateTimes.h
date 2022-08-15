#pragma once

#include <tuple>

#include <pbext.h>

#include "PBString.h"
#include "AcquiredValue.h"


namespace Inf
{
	/**
	 * This is a Wrapper for pbtime.
	 */
	class PBTime {
	public:
		/**
		 * Creates a Wrapper to an already existing pbtime.
		 * Will be Null if time is 0.
		 * 
		 * \param session	Current session
		 * \param time		The exsiting pbtime or 0
		 */
		PBTime(IPB_Session* session, pbtime time);
		/**
		 * Creates a new pbtime.
		 * 
		 * \param session	Current Session
		 */
		PBTime(IPB_Session* session, pbint hours, pbint minutes, pbdouble seconds);

		/**
		 * Gets the Time from PowerBuilder.
		 * 
		 * \return	hours, minutes, seconds
		 */
		std::tuple<pbint, pbint, pbdouble> GetTime() const;
		/**
		 * Sets the Time in PowerBuilder.
		 */
		void SetTime(pbint hours, pbint minutes, pbdouble seconds);

		/**
		 * Checks whether the pbtime is Null
		 */
		bool IsNull() const;
		/**
		 * Sets the pbtime to Null.
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

		IPB_Session* m_Session;
		pbtime m_Time;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

		PBTime(IPB_Session* session, IPB_Value* value, bool acquire);
	};


	/**
	 * This is a Wrapper for pbdate.
	 */
	class PBDate {
	public:
		/**
		 * Creates a Wrapper to an already existing pbdate.
		 * Will be Null if date is 0.
		 *
		 * \param session	Current session
		 * \param date		The exsiting pbdate or 0
		 */
		PBDate(IPB_Session* session, pbdate date);
		/**
		 * Creates a new pbdate.
		 *
		 * \param session	Current Session
		 */
		PBDate(IPB_Session* session, pbint years, pbint months, pbint days);

		/**
		 * Gets the Date from PowerBuilder.
		 *
		 * \return	years, months, days
		 */
		std::tuple<pbint, pbint, pbint> GetDate() const;
		/**
		 * Sets the Date in PowerBuilder.
		 */
		void SetDate(pbint years, pbint months, pbint days);

		/**
		 * Checks whether the pbdate is Null
		 */
		bool IsNull() const;
		/**
		 * Sets the pbdate to Null.
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

		IPB_Session* m_Session;
		pbdate m_Date;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

		PBDate(IPB_Session* session, IPB_Value* value, bool acquire);
	};


	/**
	 * This is a Wrapper for pbdatetime.
	 */
	class PBDateTime {
	public:
		/**
		 * Creates a Wrapper to an already existing pbdatetime.
		 * Will be Null if datetime is 0.
		 *
		 * \param session	Current session
		 * \param datetime		The exsiting pbdatetime or 0
		 */
		PBDateTime(IPB_Session* session, pbdatetime datetime);
		/**
		 * Creates a new pbdatetime.
		 *
		 * \param session	Current Session
		 */
		PBDateTime(IPB_Session* session, pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds);

		/**
		 * Gets the DateTime from PowerBuilder.
		 *
		 * \return	years, months, days, hours, minutes, seconds
		 */
		std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> GetDateTime() const;
		/**
		 * Sets the DateTime in PowerBuilder.
		 */
		void SetDateTime(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds);

		/**
		 * Checks whether the pbdatetime is Null
		 */
		bool IsNull() const;
		/**
		 * Sets the pbdatetime to Null.
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


		IPB_Session* m_Session;
		pbdatetime m_DateTime;
		std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

		PBDateTime(IPB_Session* session, IPB_Value* value, bool acquire);
	};
}