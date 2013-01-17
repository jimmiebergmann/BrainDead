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
#include <Level.hpp>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace BD
{
	class Game
	{

	public:
		
		~Game( );
		Game( );
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

		Timer m_DeltaTimer;
		Level * m_pLevel;

	/*	Shader * m_pVertexShader;
		Shader * m_pFragmentShader;
		ShaderProgram * m_pShaderProgram;
		Matrix4x4 m_Matrix;
		VertexObject * m_pVertexObject;
		Image * m_pImage;
		Texture * m_pTexture;
		BD_UINT32 m_ObjectSize;
*/


		// TODO!
		// Vector2 class here instead, yes please
		//std::vector<Vector3> m_ObjectPositions;
		// !TODO

	};

}

#endif
