#ifndef __BRAINDEAD_TIMER_HPP__
#define __BRAINDEAD_TIMER_HPP__

#include <DataTypes.hpp>

namespace BD
{

	class Timer
	{

	public:

		Timer( );
		void Start( );
		void Stop( );
		BD_FLOAT64 GetTime( );
		

	private:

		static BD_FLOAT64 SystemTime( );
		BD_FLOAT64 m_StartTime;
		BD_FLOAT64 m_Time;

	};

}

#endif