#include <Game.hpp>
#include <Debugger.hpp>
#include <iostream>

#ifdef PLATFORM_WINDOWS
#include <WindowsWindow.hpp>
#include <WindowsRendererOGL.hpp>
#elif PLATFORM_LINUX
#include <LinuxWindow.hpp>
#include <LinuxRendererOGL.hpp>
#else
#error No platform pre-processor directive specified
#endif

#include <Random.hpp>
#include <Debugger.hpp>


namespace BD
{
	Game::~Game( )
	{
		this->Unload( );
	}

	Game::Game( ) :
		m_Loaded( BD_FALSE ),
		m_Running( BD_FALSE ),
		m_pWindow( BD_NULL ),
		m_pRenderer( BD_NULL ),

		m_pVertexShader( BD_NULL ),
		m_pFragmentShader( BD_NULL ),
		m_pShaderProgram( BD_NULL ),
		m_pVertexObject( BD_NULL ),
		m_pImage( BD_NULL ),
		m_pTexture( BD_NULL )
	{
	}

	int Game::Run( int p_Argc, char **p_ppArgv )
	{
		m_Running = false;

		// Load the game
		if( Load( ) == BD_OK )
		{
			m_Running = true;
		}

		// Main loop
		m_DeltaTimer.Start( );

		while( m_Running )
		{
			bdSleep( 0 );

			// Do events
			if( m_pWindow->DoEvents( ) != BD_OK )
			{
				break;
			}

			// Update
			m_DeltaTimer.Stop( );
			Update( m_DeltaTimer.GetTime( ) );
			m_DeltaTimer.Start( );

			// Render
			m_pRenderer->StartScene( );
			this->Render( );
			m_pRenderer->EndScene( );
		}
		

		// Unload the game
		if( Unload( ) != BD_OK )
		{
			// An error message dialog could be more useful for Windows users
#ifdef PLATFORM_WINDOWS
			::MessageBox( NULL, L"Failed to unload BrainDead",
				L"BrainDead Erorr.", MB_OK | MB_ICONEXCLAMATION );
#endif
			bdTrace( BD_NULL,
				"[BD::Game::Run] <ERROR> Failed to unload BrainDead\n" );
		}
		
		return 0;
	}

	BD_UINT32 Game::Load( )
	{
		m_Loaded = BD_FALSE;

		// Seed the random function
		bdSeedRandom( "Jimmie Bergmann" );

		// Allocate the window and the renderer
#ifdef PLATFORM_WINDOWS	
		m_pWindow = new WindowsWindow( );
		m_pRenderer = new WindowsRendererOGL( );
#elif PLATFORM_LINUX
		m_pWindow = new LinuxWindow( );
		m_pRenderer = new LinuxRendererOGL( );
#else
#error No platform pre-processor directive specified
#endif

		// Create the window
		BD_UINT32 WindowWidth = 800;
		BD_UINT32 WindowHeight = 600;
		
		if( m_pWindow->Create( WindowWidth, WindowHeight, BD_FALSE ) != BD_OK )
		{
			return BD_ERROR;
		}

		// Create the renderer and set some initial values.
		if( m_pRenderer->Create( *m_pWindow ) != BD_OK )
		{
			return BD_ERROR;
		}
		
		m_pRenderer->SetViewport( 0, 0, WindowWidth, WindowHeight );
		m_pRenderer->SetClearColor( 135 / 255.0f, 182 / 255.0f, 225 / 255.0f,
			1.0f );
		m_pRenderer->EnableTexture( );
		m_pRenderer->EnableAlpha( );
		m_pRenderer->DisableDepthTest( );
		
		// Loading the test rendering data.
		// Load the vertex object
		m_ObjectSize = 20;
		m_pVertexObject = new VertexObjectOGL( );

		BD_FLOAT32 ObjectSize = static_cast< BD_FLOAT32 >( m_ObjectSize );

		BD_FLOAT32 VertexBuffer[ 18 ] = 
		{
			0.0f,		0.0f,		0.0f,
			ObjectSize,	0.0f,		0.0f,
			ObjectSize,	ObjectSize, 0.0f,
			0.0f,		0.0f,		0.0f,
			ObjectSize, ObjectSize, 0.0f,
			0.0f,		ObjectSize, 0.0f
		};

		BD_FLOAT32 TextureBuffer[ 12 ] = 
		{
			0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
			0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f
		};
		
		BD_UINT32 VertexAttributeLocation = 0;
		BD_UINT32 TextureAttributeLocation = 0;
		if( m_pVertexObject->AddVertexBuffer( VertexBuffer, 3,
			VertexAttributeLocation )  == BD_ERROR )
		{
			return BD_ERROR;
		}

		if( m_pVertexObject->AddVertexBuffer( TextureBuffer, 2,
			TextureAttributeLocation )  == BD_ERROR )
		{
			return BD_ERROR;
		}
		if( m_pVertexObject->Load( 2, 3 ) == BD_ERROR )
		{
			return BD_ERROR;
		}

		// Load the shaders
		std::string VertexValidation = "";
		std::string FragmentValidation = "";
		m_pVertexShader = new ShaderOGL(Shader::SHADERTYPE_VERTEX);
		m_pFragmentShader = new ShaderOGL(Shader::SHADERTYPE_FRAGMENT);

		if( m_pVertexShader->Read("Data/Shader.vert") != BD_OK )
		{
			bdTrace( BD_NULL, "TESTGE\n" );
			return BD_ERROR;
		}
		if( m_pVertexShader->Compile(VertexValidation) != BD_OK )
		{
			return BD_ERROR;
		}
		if( VertexValidation.length( ) > 0)
		{
			bdTrace( BD_NULL, "Vertex shader validation:\n" );
			bdTrace( BD_NULL, "%s", VertexValidation.c_str() );
		}
		if( m_pFragmentShader->Read( "Data/Shader.frag" ) != BD_OK )
		{
			return BD_ERROR;
		}
		if( m_pFragmentShader->Compile( FragmentValidation ) != BD_OK )
		{
			return BD_ERROR;
		}
		if( FragmentValidation.length( ) > 0 )
		{
			bdTrace( BD_NULL, "Fragment shader validation:\n" );
			bdTrace( BD_NULL, "%s", FragmentValidation.c_str() );
		}
		// Load the shader program
		std::string ShaderProgramValidation = "";
		m_pShaderProgram = new ShaderProgramOGL( );
		if( m_pShaderProgram->Load( ) != BD_OK )
		{
			return BD_ERROR;
		}
		m_pShaderProgram->AttachShaders( m_pVertexShader );
		m_pShaderProgram->AttachShaders( m_pFragmentShader );

		// Let's set the attribute values before we continue the shader
		// program linking
		m_pShaderProgram->SetAttributeLocation( "Position",
			VertexAttributeLocation );
		m_pShaderProgram->SetAttributeLocation( "Texture",
			TextureAttributeLocation );


		if( m_pShaderProgram->Link( ShaderProgramValidation ) != BD_OK )
		{
			bdTrace( NULL, "Shader program shader validation:\n" );
			bdTrace( NULL, "%s", ShaderProgramValidation.data() );
			return BD_ERROR;
		}

		// Set uniforms
		m_Matrix.Orthographic( 0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f );

		m_pShaderProgram->Bind( );
		m_pShaderProgram->SetUniform1i( "ColorTexture", 0 );
		m_pShaderProgram->SetUniformMatrix4x4f( "Matrix", m_Matrix );
		m_pShaderProgram->Unbind( );


		// Load the image and texture
		m_pImage = new Image( );
		if( m_pImage->ReadFile( "Data/Snowflake.tga" ) != BD_OK )
		{
			return BD_ERROR;
		}

		m_pTexture = new TextureOGL( );
		if( m_pTexture->Load( *m_pImage ) )
		{
			return BD_ERROR;
		}


		// Add some temporary object positions
		for( BD_MEMSIZE i = 0; i < 200; i++ )
		{
			Vector3 ObjectPosition( bdRandom( 0, WindowWidth ),
				bdRandom( 0, WindowHeight ), 0 );
			m_ObjectPositions.push_back( ObjectPosition );
		}


		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	BD_UINT32 Game::Unload( )
	{
		if( m_pVertexShader )
		{
			delete m_pVertexShader;
			m_pVertexShader = BD_NULL;
		}
		if( m_pFragmentShader )
		{
			delete m_pFragmentShader;
			m_pFragmentShader = BD_NULL;
		}
		if( m_pShaderProgram )
		{
			delete m_pShaderProgram;
			m_pShaderProgram = BD_NULL;
		}

		if( m_pVertexObject )
		{
			delete m_pVertexObject;
			m_pVertexObject = BD_NULL;
		}

		if( m_pImage )
		{
			delete m_pImage;
			m_pImage = BD_NULL;
		}
		if ( m_pTexture )
		{
			delete m_pTexture;
			m_pTexture = BD_NULL;
		}

		if( m_pRenderer )
		{
			delete m_pRenderer;
			m_pRenderer = BD_NULL;
		}
		if( m_pWindow )
		{
			delete m_pWindow;
			m_pWindow = BD_NULL;
		}
		
		return BD_OK;
	}

	BD_UINT32 Game::Update( BD_FLOAT64 p_DeltaTime )
	{
		// Sink the object on the screen
		for( BD_MEMSIZE i = 0; i < m_ObjectPositions.size( ); i++ )
		{
			m_ObjectPositions[ i ][ 1 ] -= 100.0f * p_DeltaTime;

			// Is the object outside the screen? Let's put it back up again8
			if( ( m_ObjectPositions[ i ][ 1 ] + m_ObjectSize ) <= 0 )
			{
				BD_FLOAT32 HeightPositionOffset =
					( m_ObjectPositions[ i ][ 1 ] + m_ObjectSize );
				m_ObjectPositions[ i ][ 0 ] = bdRandom( 0, 800 );
				m_ObjectPositions[ i ][ 1 ] = 600 + HeightPositionOffset +
					bdRandom( 0, 30 );
			}
		}

		return BD_OK;
	}

	void Game::Render( )
	{
		m_pShaderProgram->Bind( );
		m_pTexture->Bind( 0 );

		for( BD_MEMSIZE i = 0; i < m_ObjectPositions.size( ); i++ )
		{
			m_pShaderProgram->SetUniform3f( "VertexPosition", 
				static_cast< int >( m_ObjectPositions[ i ][ 0 ] ),
				static_cast< int >( m_ObjectPositions[ i ][ 1 ] ),
				m_ObjectPositions[ i ][ 2 ] );
			m_pVertexObject->Render( VertexObject::RENDERMODE_TRIANGLES );
		}

		m_pTexture->Unbind( );
		m_pShaderProgram->Unbind( );
	}
}

