#include <Game.hpp>
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

namespace BD
{
	Game::~Game()
	{
	}

	Game::Game() :
		m_Loaded(BD_FALSE),
		m_Running(BD_FALSE),
		m_pWindow(BD_NULL),
		m_pRenderer(BD_NULL),

		m_pVertexShader(BD_NULL),
		m_pFragmentShader(BD_NULL),
		m_pShaderProgram(BD_NULL),

		m_pImage(BD_NULL)
	{
	}

	int Game::Run(int argc, char ** argv)
	{
		m_Running = false;

		// Load the game
		if(Load() == BD_OK)
		{
			m_Running = true;
		}

		// Main loop
		while(m_Running)
		{
			if(m_pWindow->DoEvents() != BD_OK)
			{
				break;
			}

			m_pRenderer->StartScene();

			// Draw things here

			m_pRenderer->EndScene();

		}
		

		// Unload the game
		if(Unload() != BD_OK)
		{
#ifdef PLATFORm_pWindowS
			::MessageBox(NULL, L"Failed to unload BrainDead", L"BrainDead Erorr.", MB_OK | MB_ICONEXCLAMATION);
#elif PLATFORM_LINUX
			std::cout << "Error: Failed to unload BrainDead." << std::endl;
#endif
		}
		
		return 0;
	}

	BD_UINT32 Game::Load()
	{
		m_Loaded = false;

#ifdef PLATFORM_WINDOWS	
		m_pWindow = new WindowsWindow();
		m_pRenderer = new WindowsRendererOGL();
#elif PLATFORM_LINUX
		m_pWindow = new LinuxWindow();
		m_pRenderer = new LinuxRendererOGL();
#else
#error No platform pre-processor directive specified
#endif


		// Load the test image
		m_pImage = new Image();
		if(m_pImage->ReadFile("Data/TGA_Test.tga") != BD_OK)
		{
			return BD_ERROR;
		}


		// Create the window
		if(m_pWindow->Create( 800, 600, false ) != BD_OK)
		{
			return BD_ERROR;
		}
		if(m_pRenderer->Create(*m_pWindow) != BD_OK)
		{
			return BD_ERROR;
		}

		// Output debug information about the renderer
		// Renderer::eRendererType RendererType = m_Renderer.GetRendererType();



		// Test shaders
		std::string VertexValidation = "";
		std::string FragmentValidation = "";
		m_pVertexShader = new ShaderOGL(Shader::SHADERTYPE_VERTEX);
		m_pFragmentShader = new ShaderOGL(Shader::SHADERTYPE_FRAGMENT);

		if(m_pVertexShader->Read("Data/Shader.vert") != BD_OK)
		{
			return BD_ERROR;
		}
		if(m_pVertexShader->Load(VertexValidation) != BD_OK)
		{
			return BD_ERROR;
		}

		if(m_pFragmentShader->Read("Data/Shader.frag") != BD_OK)
		{
			return BD_ERROR;
		}
		if(m_pFragmentShader->Load(FragmentValidation) != BD_OK)
		{
			return BD_ERROR;
		}

		// Load the shader program
		std::string ShaderProgramValidation = "";
		m_pShaderProgram = new ShaderProgramOGL();
		if(m_pShaderProgram->Compile(m_pVertexShader, m_pFragmentShader, ShaderProgramValidation) == BD_ERROR)
		{
			return BD_ERROR;
		}




		m_Loaded = true;
		return BD_OK;
	}

	BD_UINT32 Game::Unload()
	{
		if(m_pWindow)
		{
			delete m_pWindow;
			m_pWindow = BD_NULL;
		}

		if(m_pRenderer)
		{
			delete m_pRenderer;
			m_pRenderer = BD_NULL;
		}

		// Shader test
		if(m_pVertexShader)
		{
			delete m_pVertexShader;
			m_pVertexShader = BD_NULL;
		}

		if(m_pFragmentShader)
		{
			delete m_pFragmentShader;
			m_pFragmentShader = BD_NULL;
		}

		// Image test
		if(m_pImage)
		{
			delete m_pImage;
			m_pImage = BD_NULL;
		}
		
		
		return BD_OK;
	}


}
