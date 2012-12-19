#ifndef __BRAINDEAD_WINDOW_HPP__
#define __BRAINDEAD_WINDOW_HPP__

#include <windows.h>

class Window
{

public:

	~Window();
	Window();
	bool IsLoaded() const;
	HDC * GetHDC();
	
private:

	bool m_Loaded;
	HDC m_HDC;


};

#endif