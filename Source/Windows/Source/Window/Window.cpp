#include <Window/Window.hpp>

namespace BD
{
	Window::~Window()
	{
	}

	Window::Window() :
		m_Loaded(BD_FALSE),
		m_HDC(BD_NULL)
	{

	}

	BD_BOOL Window::IsLoaded() const
	{
		return m_Loaded;
	}

	HDC * Window::GetHDC()
	{
		return &m_HDC;
	}

}

