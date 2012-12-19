#ifndef __BRAINDEAD_OPENGL_RENDERER_HPP__
#define __BRAINDEAD_OPENGL_RENDERER_HPP__

#include <windows.h>

class OpenGLRenderer
{

public:

	~OpenGLRenderer();
	OpenGLRenderer();
	int Create(Window & window);
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

	HGLRC m_pContext;
	HDC * m_pHDC;


};

#endif
