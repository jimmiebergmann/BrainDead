#include <Window/WindowsWindow.hpp>
#include <sstream>

namespace BD
{
	WindowsWindow::WindowsWindow( )
	{
		m_Window = BD_NULL;
		m_DeviceContext = BD_NULL;
		m_pWindowTitle = BD_NULL;
		m_Fullscreen = BD_FALSE;

		memset( &m_WindowRect, 0, sizeof( RECT ) );
	}

	WindowsWindow::~WindowsWindow( )
	{
		if( m_pWindowTitle )
		{
			delete [ ] m_pWindowTitle;
			m_pWindowTitle = BD_NULL;
		}

		if( m_Fullscreen = BD_TRUE )
		{
			ChangeDisplaySettings( BD_NULL, 0 );
			ShowCursor( TRUE );
		}

		if( m_DeviceContext != BD_NULL )
		{
			ReleaseDC( m_Window, m_DeviceContext );
			m_DeviceContext = BD_NULL;
		}

		if( m_Window != BD_NULL )
		{
			DestroyWindow( m_Window );
			m_Window = BD_NULL;
			UnregisterClass( m_pWindowTitle, GetModuleHandle( BD_NULL ) );
		}
	}

	BD_UINT32 WindowsWindow::Create( const BD_UINT32 p_Width,
		const BD_UINT32 p_Height, const BD_BOOL p_Fullscreen )
	{
		WNDCLASSEX WinClass;

		m_Fullscreen = p_Fullscreen;

		std::wstringstream CompleteTitle;

		CompleteTitle << L"BrainDead";

		m_pWindowTitle = new wchar_t[ CompleteTitle.str( ).size( ) + 1 ];
		wcsncpy( m_pWindowTitle, CompleteTitle.str( ).c_str( ),
			CompleteTitle.str( ).size( ) );
		m_pWindowTitle[ CompleteTitle.str( ).size( ) ] = L'\0';

		WinClass.cbSize = sizeof( WNDCLASSEX );
		WinClass.cbClsExtra = 0;
		WinClass.cbWndExtra = 0;
		WinClass.hbrBackground = BD_NULL;
		WinClass.hInstance = GetModuleHandle( BD_NULL );
		WinClass.hIcon = LoadIcon( BD_NULL, IDI_WINLOGO );
		WinClass.hIconSm = LoadIcon( BD_NULL, IDI_WINLOGO );
		WinClass.hCursor = LoadCursor( BD_NULL, IDC_ARROW );
		// ISSUE!
		// This seems terrible.  What can be done?
		// !ISSUE
		WinClass.lpfnWndProc = ( WNDPROC )WindowsWindow::WindowProc;
		WinClass.lpszClassName = m_pWindowTitle;
		WinClass.lpszMenuName = BD_NULL;
		WinClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;

		if( !RegisterClassEx( &WinClass ) )
		{
			m_Created = BD_FALSE;
			return BD_ERROR;
		}

		HWND DesktopWindow = GetDesktopWindow( );
		HDC DesktopContext = GetDC( DesktopWindow );
		DWORD Style = 0, ExStyle = 0;

		if( m_Fullscreen == BD_TRUE )
		{
			long Width = 0L, Height = 0L;
			Width = GetDeviceCaps( DesktopContext, HORZRES );
			Height = GetDeviceCaps( DesktopContext, VERTRES );

			m_WindowRect.left = 0L;
			m_WindowRect.bottom = Height;
			m_WindowRect.top = 0L;
			m_WindowRect.right = Width;

			DEVMODE ScreenSettings;
			memset( &ScreenSettings, 0, sizeof( DEVMODE ) );

			ScreenSettings.dmSize = sizeof( DEVMODE );
			ScreenSettings.dmPelsWidth = Width;
			ScreenSettings.dmPelsHeight = Height;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH |
				DM_PELSHEIGHT;

			if( ChangeDisplaySettings( &ScreenSettings, CDS_FULLSCREEN ) !=
				DISP_CHANGE_SUCCESSFUL )
			{
				return BD_ERROR;
			}

			ExStyle = WS_EX_APPWINDOW;
			Style = WS_POPUP;

			ShowCursor( FALSE );
		}
		else
		{
			BD_FLOAT32 WidthF = 0.0f, HeightF = 0.0f;
			BD_FLOAT32 XF = 0.0f, YF = 0.0f;

			WidthF = static_cast< BD_FLOAT32 >(
				GetDeviceCaps( DesktopContext, HORZRES ) );
			HeightF = static_cast< BD_FLOAT32 >(
				GetDeviceCaps( DesktopContext, VERTRES ) );

			XF = ( WidthF / 100.0f )*5.0f;
			YF = ( HeightF / 100.0f )*5.0f;
			WidthF = ( WidthF / 100.0f )*90.0f;
			HeightF = ( HeightF / 100.0f )*90.0f;

			m_WindowRect.left = static_cast< long >( XF );
			m_WindowRect.right = static_cast< long >( WidthF );
			m_WindowRect.top = static_cast< long >( YF );
			m_WindowRect.bottom = static_cast< long >( HeightF );

			ExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			Style = WS_OVERLAPPEDWINDOW;
		}

		ReleaseDC( DesktopWindow, DesktopContext );
 		AdjustWindowRectEx( &m_WindowRect, Style, FALSE, ExStyle );

		m_Window = CreateWindowEx( ExStyle, m_pWindowTitle, m_pWindowTitle,
			Style, m_WindowRect.left, m_WindowRect.top, m_WindowRect.right,
			m_WindowRect.bottom, BD_NULL, BD_NULL, GetModuleHandle( BD_NULL ),
			BD_NULL );

		DWORD Err = GetLastError( );

 		if( m_Window == BD_NULL )
		{
			m_Created = BD_FALSE;
			return BD_ERROR;
		}

		m_DeviceContext = GetDC( m_Window );

		ShowWindow( m_Window, SW_SHOW );
		SetForegroundWindow( m_Window );
		SetFocus( m_Window );

		m_Created = BD_TRUE;

		return BD_OK;
	}

	BD_UINT32 WindowsWindow::DoEvents()
	{
		MSG Mesage;
		bool Close = BD_FALSE;
		while( PeekMessage(&Mesage, NULL, NULL, NULL, PM_REMOVE))
		{
			// Disable the VK_MENU key by skipping it.
			if(Mesage.wParam == VK_MENU)
			{
				continue;
			}

			if(Mesage.message == WM_KEYDOWN)
			{
				Close = BD_TRUE;
			}

			TranslateMessage( &Mesage );
			DispatchMessage( &Mesage );
		}

		if(Close == BD_TRUE)
		{
			return BD_ERROR;
		}

		return BD_OK;
	}

	WINDATA WindowsWindow::Data( ) const
	{
		WINDATA WinData;
		memset( &WinData, 0, sizeof( WINDATA ) );
		WinData.DeviceContext = m_DeviceContext;

		return WinData;
	}

	LRESULT WindowsWindow::WindowProc( HWND p_HWND, UINT p_Message, WPARAM p_WParam,
		LPARAM p_LParam )
	{
		switch( p_Message )
		{
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
				break;
			}
		case WM_CLOSE:
			{
				PostQuitMessage( 0 );
				break;
			}
		default:
			return DefWindowProc( p_HWND, p_Message, p_WParam, p_LParam );
		}
		return 0L;
	}

}
