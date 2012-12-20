#ifndef __BRAINDEAD_WINDOW_WINDOW_HPP__
#define __BRAINDEAD_WINDOW_WINDOW_HPP__

#include <DataTypes.hpp>
#include <Windows.h>

#ifdef PLATFORM_WINDOWS
typedef struct __WINDATA
{
	HDC DeviceContext;
}WINDATA;
#elif PLATFORM_LINUX
typedef struct __WINDATA
{
	::Window	Window;
	Display		*pDisplay;
}WINDATA;
#else
#error Platform was not specified on the pre-processor
#endif

namespace BD
{
	class Window
	{
	public:
		virtual ~Window( ){ }

		virtual BD_UINT32 Create( const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen ) = 0;

		virtual BD_BOOL Created( ) const = 0;

		virtual WINDATA Data( ) const = 0;
	};
}

#endif

