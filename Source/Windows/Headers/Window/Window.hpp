#ifndef __BRAINDEAD_WINDOW_HPP__
#define __BRAINDEAD_WINDOW_HPP__

#include <DataTypes.hpp>
#include <windows.h>

namespace BD
{
	class Window
	{

	public:

		~Window();
		Window();
		BD_BOOL IsLoaded() const;
		HDC * GetHDC();
		
	private:

		BD_BOOL m_Loaded;
		HDC m_HDC;

	};

}

#endif