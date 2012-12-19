#include <Window/Window.hpp>

namespace BD
{
	Window::~Window()
	{

	}

	Window::Window() :
		m_Loaded(false),
		m_HDC(NULL)
	{

	}

	bool Window::IsLoaded() const
	{
		return m_Loaded;
	}

	HDC * Window::GetHDC()
	{
		return &m_HDC;
	}

}

