#include <Timer.hpp>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM_LINUX
#include <sys/time.h>
#endif

#include <ctime>

namespace BD
{

	Timer::Timer( ) :
		m_StartTime( 0 ),
		m_Time( 0 )
	{
	}

	void Timer::Start( )
	{
		m_StartTime = SystemTime();
	}

	void Timer::Stop( )
	{
		double CurrentTime = SystemTime();
		m_Time = ( CurrentTime - m_StartTime );
	}

	BD_FLOAT64 Timer::GetTime( )
	{
		return m_Time;
	}

	BD_FLOAT64 Timer::SystemTime( )
	{
#ifdef PLATFORM_WINDOWS
		static BD_SINT64 Start = 0;
		static BD_SINT64 Frequency = 0;

		if ( Start == 0 )
		{
			QueryPerformanceCounter( (LARGE_INTEGER*)&Start );
			QueryPerformanceFrequency( (LARGE_INTEGER*)&Frequency );
			return 0.0f;
		}

		BD_SINT64 Counter = 0;
		QueryPerformanceCounter( (LARGE_INTEGER*)&Counter );

		return (BD_FLOAT64)( (Counter - Start ) / BD_FLOAT64( Frequency ) );

#elif PLATFORM_LINUX

		timeval Time;
		gettimeofday( &Time, 0 );
		return Time.tv_sec + ( Time.tv_usec * 0.000001 );

#endif
	}





}