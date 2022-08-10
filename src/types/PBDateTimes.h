#pragma once

#include <tuple>

#include <pbext.h>


namespace Inf
{
	template <typename PBT, pblong... dims>
		requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
	class PBArray;

	template <typename T>
	class Type;


	class PBTime {
	public:
		PBTime(IPB_Session* session, pbtime time);

		std::tuple<pbint, pbint, pbdouble> GetTime() const;
		void SetTime(pbint hours, pbint minutes, pbdouble seconds);
		bool IsNull() const;
		void SetToNull();

	private:
		friend Type<PBTime>;
		friend PBArray<PBTime>;

		IPB_Session* m_Session;
		pbtime m_Time;
	};
	class PBDate {
	public:
		PBDate(IPB_Session* session, pbdate date);
		std::tuple<pbint, pbint, pbint> GetDate() const;
		void SetDate(pbint y, pbint m, pbint d);
		bool IsNull() const;
		void SetToNull();

	private:
		friend Type<PBDate>;
		friend PBArray<PBDate>;

		IPB_Session* m_Session;
		pbdate m_Date;
	};
	class PBDateTime {
	public:
		PBDateTime(IPB_Session* session, pbdatetime datetime);
		std::tuple<pbint, pbint, pbint, pbint, pbint, pbdouble> GetDateTime() const;
		void SetDateTime(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds);
		bool IsNull() const;
		void SetToNull();

	private:
		friend Type<PBDateTime>;
		friend PBArray<PBDateTime>;

		IPB_Session* m_Session;
		pbdatetime m_DateTime;
	};
}