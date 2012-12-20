#ifndef __BRAINDEAD_OPENGL_RENDERER_HPP__
#define __BRAINDEAD_OPENGL_RENDERER_HPP__

#include <DataTypes.hpp>
#include <Window/Window.hpp>


namespace BD
{
	class OpenGLRenderer
	{

	public:

		enum eRendererType
		{
			RENDERERTYPE_NONE = 0,
			RENDERERTYPE_OPENGL3 = 1,
			RENDERERTYPE_OPENGL2 = 2
		};

		~OpenGLRenderer();
		OpenGLRenderer();
		BD_UINT32 Create(Window & p_window);
		void StartScene();
		void EndScene();
		void SetClearColor(const BD_FLOAT32 r, const BD_FLOAT32 g, const BD_FLOAT32 b, const BD_FLOAT32 a);
		void SetClearDepth(BD_FLOAT32 depth);
		void SetViewport(const BD_UINT32 lx, const BD_UINT32 ly,const BD_UINT32 hx, const BD_UINT32 hy); // Lower and higher coordinates
		void SetLineWidth(const BD_FLOAT32 width);
		void ClearColor();
		void ClearDepth();
		void EnableTexture();
		void DisableTexture();
		void EnableAlpha();
		void DisableAlpha();
		void EnableDepthTest();
		void DisableDepthTest();
		void EnableSmoothLines();
		void DisableSmoothLines();
		
	private:

		HGLRC m_Context;
		HDC * m_pHDC;
		eRendererType m_eRenderType;


	};

}

#endif
