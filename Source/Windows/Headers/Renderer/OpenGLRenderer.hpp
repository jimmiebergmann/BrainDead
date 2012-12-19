#ifndef __BRAINDEAD_OPENGL_RENDERER_HPP__
#define __BRAINDEAD_OPENGL_RENDERER_HPP__

#include <Window/Window.hpp>

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
<<<<<<< HEAD
	int Create(Window & p_window);
=======
//	int Create(Window & window);
>>>>>>> 7656c21ed3eac87e2ad54430c83915cab53c09b2
	void StartScene();
	void EndScene();
	void SetClearColor(const float r, const float g, const float b, const float a);
	void SetClearDepth(float depth);
	void SetViewport(const int lx, const int ly,const int hx, const int hy); // Lower and higher coordinates
	void SetLineWidth(const float width);
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

#endif
