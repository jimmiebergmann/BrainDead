#ifndef __BRAINDEAD_GAME_HPP__
#define __BRAINDEAD_GAME_HPP__

#include <DataTypes.hpp>
#include <System.hpp>
#include <Renderer.hpp>
#include <OGL/ShaderOGL.hpp>
#include <OGL/ShaderProgramOGL.hpp>
#include <Image.hpp>
#include <OGL/TextureOGL.hpp>
#include <OGL/VertexObjectOGL.hpp>
#include <Matrix4x4.hpp>
#include <Vector3.hpp>
#include <Timer.hpp>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace BD
{
	class Game
	{

	public:
		
		~Game();
		Game();
		int Run( int argc, char ** argv );
		
	private:

		BD_UINT32 Load( );
		BD_UINT32 Unload( );
		BD_UINT32 Update( BD_FLOAT64 p_DeltaTime );
		void Render( );

		BD_BOOL m_Loaded;
		BD_BOOL m_Running;
		Window * m_pWindow;
		Renderer * m_pRenderer;

		// Test rendering.
		Timer m_DeltaTimer;
		Shader * m_pVertexShader;
		Shader * m_pFragmentShader;
		ShaderProgram * m_pShaderProgram;
		Matrix4x4 m_Matrix;
		VertexObject * m_pVertexObject;
		Image * m_pImage;
		Texture * m_pTexture;
		BD_UINT32 m_ObjectSize;
		std::vector<Vector3> m_ObjectPositions; // Vector2 clas here instead, yes please

	};

}

#endif
