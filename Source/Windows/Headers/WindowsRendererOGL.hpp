#ifndef __BRAINDEAD_WINDOWS_RENDERER_OGL_HPP__
#define __BRAINDEAD_WINDOWS_RENDERER_OGL_HPP__

#include <Renderer.hpp>
#include <WindowsWindow.hpp>

namespace BD
{
	class WindowsRendererOGL : public Renderer
	{

	public:

		virtual ~WindowsRendererOGL( );
		WindowsRendererOGL( );
		virtual BD_UINT32 Create( const Window & p_Window);
		virtual void StartScene() ;
		virtual void EndScene();
		virtual void SetClearColor(const BD_FLOAT32 r, const BD_FLOAT32 g, const BD_FLOAT32 b, const BD_FLOAT32 a);
		virtual void SetClearDepth(BD_FLOAT32 depth);
		virtual void SetViewport(const BD_UINT32 lx, const BD_UINT32 ly,const BD_UINT32 hx, const BD_UINT32 hy); // Lower and higher coordinates
		virtual void SetLineWidth(const BD_FLOAT32 width);
		virtual void ClearColor();
		virtual void ClearDepth();
		virtual void EnableTexture();
		virtual void DisableTexture();
		virtual void EnableAlpha();
		virtual void DisableAlpha();
		virtual void EnableDepthTest();
		virtual void DisableDepthTest();
		virtual void EnableSmoothLines();
		virtual void DisableSmoothLines();
		virtual BD_BOOL IsCreated( ) const { return m_Created; }
		virtual eRendererType GetRendererType( ) const { return m_eRendererType; }
		
	private:

		BD_BOOL m_Created;
		HGLRC m_Context;
		HDC m_HDC;
		eRendererType m_eRendererType;

	};

}

#endif
