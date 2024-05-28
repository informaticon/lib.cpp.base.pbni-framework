#pragma once

#include <chrono>
#include <tuple>

#include "AcquiredValue.h"
#include "PBString.h"


namespace Inf
{
    /**
     * This is a Wrapper for pbtime.
     */
    class PBTime
    {
    public:
        /**
         * Creates a Wrapper to an already existing pbtime.
         * Will be Null if time is 0.
         *
         * \param session   Current session
         * \param time      The exsiting pbtime or 0
         */
        PBTime(IPB_Session* session, pbtime time);
        /**
         * Creates a new pbtime.
         *
         * \param session   Current Session
         * \param hours     The hour to set
         * \param minutes   The minute to set
         * \param seconds   The second to set
         */
        PBTime(IPB_Session* session, pbint hours, pbint minutes, pbdouble seconds);

        /**
         * Gets the Time from PowerBuilder and converts it to unix time.
         *
         * \return  std::chrono time
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::chrono::time_point<std::chrono::system_clock> GetChrono() const;
        /**
         * Gets the Time from PowerBuilder.
         *
         * \return  hours, minutes, seconds
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::tuple<pbint, pbint, pbdouble> GetTime() const;
        /**
         * Sets the Time in PowerBuilder. Creates a new Time if is Null.
         *
         * \param hours     Hours to set
         * \param minutes   Minutes to set
         * \param seconds   Seconds to set
         *
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
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

        /**
         * Retrieve the private PB Reference
         */
        operator pbtime() const
        {
            return m_Time;
        }

    private:
        friend Helper::PBValue;

        IPB_Session* m_Session;
        pbtime m_Time;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBTime(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    /**
     * This is a Wrapper for pbdate.
     */
    class PBDate
    {
    public:
        /**
         * Creates a Wrapper to an already existing pbdate.
         * Will be Null if date is 0.
         *
         * \param session   Current session
         * \param date      The exsiting pbdate or 0
         */
        PBDate(IPB_Session* session, pbdate date);
        /**
         * Creates a new pbdate.
         *
         * \param session   Current Session
         * \param years     The years to set
         * \param months    The months to set
         * \param days      The days to set
         */
        PBDate(IPB_Session* session, pbint years, pbint months, pbint days);

        /**
         * Gets the Time from PowerBuilder and converts it to unix time.
         *
         * \return  std::chrono time
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::chrono::time_point<std::chrono::system_clock> GetChrono() const;
        /**
         * Gets the Date from PowerBuilder.
         *
         * \return  years, months, days
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::tuple<pbint, pbint, pbint> GetDate() const;
        /**
         * Sets the Date in PowerBuilder. Creates a new Date if is Null.
         *
         * \param years     Years to set
         * \param months    Months to set
         * \param days      Days to set
         *
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
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

        /**
         * Retrieve the private PB Reference
         */
        operator pbdate() const
        {
            return m_Date;
        }

    private:
        friend Helper::PBValue;

        IPB_Session* m_Session;
        pbdate m_Date;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDate(IPB_Session* session, IPB_Value* value, bool acquire);
    };


    /**
     * This is a Wrapper for pbdatetime.
     */
    class PBDateTime
    {
    public:
        /**
         * Creates a Wrapper to an already existing pbdatetime.
         * Will be Null if datetime is 0.
         *
         * \param session   Current session
         * \param datetime      The exsiting pbdatetime or 0
         */
        PBDateTime(IPB_Session* session, pbdatetime datetime);
        /**
         * Creates a new pbdatetime.
         *
         * \param session   Current Session
         * \param years     The years to set
         * \param months    The months to set
         * \param days      The days to set
         * \param hours     The hour to set
         * \param minutes   The minute to set
         * \param seconds   The second to set
         */
        PBDateTime(
            IPB_Session* session,
            pbint years,
            pbint months,
            pbint days,
            pbint hours,
            pbint minutes,
            pbdouble seconds
        );

        /**
         * Gets the Time from PowerBuilder and converts it to unix time.
         *
         * \return  std::chrono time
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::chrono::time_point<std::chrono::system_clock> GetChrono() const;
        /**
         * Gets the DateTime from PowerBuilder.
         *
         * \return  years, months, days, hours, minutes, seconds
         *
         * \throw Inf::PBNI_NullPointerException    If Null
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
         */
        std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> GetDateTime() const;
        /**
         * Sets the DateTime in PowerBuilder. Creates a new DateTime if is Null.
         *
         * \param years     Years to set
         * \param months    Months to set
         * \param days      Days to set
         * \param hours     Hours to set
         * \param minutes   Minutes to set
         * \param seconds   Seconds to set
         *
         * \throw Inf::PBNI_PowerBuilderException   If PowerBuilder function doesnt return PBX_SUCESS
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

        /**
         * Retrieve the private PB Reference
         */
        operator pbdatetime() const
        {
            return m_DateTime;
        }

    private:
        friend Helper::PBValue;

        IPB_Session* m_Session;
        pbdatetime m_DateTime;
        std::shared_ptr<Helper::AcquiredValue> m_AcquiredValue;

        PBDateTime(IPB_Session* session, IPB_Value* value, bool acquire);
    };
}  // namespace Inf