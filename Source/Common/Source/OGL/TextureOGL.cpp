#include <OGL/TextureOGL.hpp>

namespace BD
{
	// Set the static s_PixelFormats values
	GLint TextureOGL::s_PixelFormats[4] = { 0, 0, GL_RGB, GL_RGBA };


	TextureOGL::TextureOGL( ) :
		m_Id(0)
	{
		m_Id = 0;
		m_Loaded = BD_FALSE;
	}

	TextureOGL::~TextureOGL ( )
	{
		// Make sure the texture is loaded.
		if(m_Loaded == BD_FALSE)
		{
			return;
		}

		// Delete the OGL texture
		glDeleteTextures(1, &m_Id);
		m_Loaded = false;
	}

	BD_UINT32 TextureOGL::Load( const Image & p_Image)
	{
		// Make sure the image class contains any data at all.
		if(p_Image.ContainsData() == BD_FALSE)
		{
			return BD_ERROR;
		}

		// Check the image BPP, we are currently just supporting 24 and 32 bit images.
		BD_UINT32 Depth = p_Image.GetDepth();
		if(Depth != 3 && Depth != 4)
		{
			return BD_ERROR;
		}

		GLint OpenGLTextureFormats[2] = { GL_RGB, GL_RGBA };
		GLint Format = OpenGLTextureFormats[Depth - 3];

		// Generate an OGL texture id.
		glGenTextures( 1, &m_Id );
		glBindTexture( GL_TEXTURE_2D, m_Id );

		glTexImage2D ( GL_TEXTURE_2D, 0, Format, p_Image.GetWidth(), p_Image.GetHeight(), 0,
			(GLenum)Format, GL_UNSIGNED_BYTE, (GLvoid *)p_Image.GetData() );

		// Unbind the texture
		glBindTexture( GL_TEXTURE_2D, 0 );
		
		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	BD_UINT32 TextureOGL::Load( BD_UINT32 p_Width, BD_UINT32 p_Height,
			const ePixelFormat p_PixelFormat, BD_BYTE * p_Data )
	{
		if( p_Data == BD_NULL )
		{
			return BD_ERROR;
		}


		GLint Format = s_PixelFormats[(int)p_PixelFormat];

		// Generate an OGL texture id.
		glGenTextures(1, &m_Id);
		glBindTexture (GL_TEXTURE_2D, m_Id);

		glTexImage2D ( GL_TEXTURE_2D, 0, Format, p_Width, p_Height, 0,
			(GLenum)Format, GL_UNSIGNED_BYTE, (GLvoid *)p_Data );

		glBindTexture(GL_TEXTURE_2D, 0);
		
		m_Loaded = BD_TRUE;
		return BD_OK;
	}

	void TextureOGL::Bind(BD_UINT32 p_Index)
	{
		// Don't bind the texture if the class isn't loaded yet.
		if(m_Loaded == BD_FALSE)
		{
			return;
		}

		bglActiveTexture(GL_TEXTURE0 + p_Index);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void TextureOGL::Unbind( )
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	BD_UINT32 TextureOGL::SetFilters( BD_UINT32 * p_pFilters )
	{
		// This code is working, but I don't know about it's efficiency...

		if( p_pFilters == BD_NULL ||
			*p_pFilters == 0 || *( p_pFilters + 1 ) == 0 )
		{
			return BD_ERROR;
		}

		// Bind the texture
		glBindTexture( GL_TEXTURE_2D, m_Id );

		// Currently max 4 filters supported.
		const BD_UINT32 MaxFilters = 4;
		GLenum  Filter = 0;
 		GLint  	Param = 0;

		for( BD_MEMSIZE i = 0; i < MaxFilters; i++ )
		{
			// Make sure the filter or param isn't 0
			if( *p_pFilters == 0 || *( p_pFilters + 1 ) == 0 )
			{
				// Break the for-loop.
				break;
			}

			// Swtich the filter type
			switch( *p_pFilters )
			{
			case BD_TEXTURE_FILTER_MAG:
				Filter = GL_TEXTURE_MAG_FILTER;
				break;
			case BD_TEXTURE_FILTER_MIN:
				Filter = GL_TEXTURE_MIN_FILTER;
				break;
			case BD_TEXTURE_FILTER_WRAP_X:
				Filter = GL_TEXTURE_WRAP_S;
				break;
			case BD_TEXTURE_FILTER_WRAP_Y:
				Filter = GL_TEXTURE_WRAP_T;
				break;
			default:
				glBindTexture( GL_TEXTURE_2D, 0 );
				return BD_ERROR;
			}

			// Swtich the filters value 
			switch( *(p_pFilters + 1) )
			{
			case BD_TEXTURE_FILTER_NEAREST:
				Param = GL_NEAREST;
				break;
			case BD_TEXTURE_FILTER_LINEAR:
				Param = GL_LINEAR;
				break;
			case BD_TEXTURE_FILTER_REPEAT:
				Param = GL_REPEAT;
				break;
			default:
				glBindTexture( GL_TEXTURE_2D, 0 );
				return BD_ERROR;
			}

			// Set the opengl texture filter.
			glTexParameteri ( GL_TEXTURE_2D, Filter, Param );

			// Increment the pointer by 2,
			p_pFilters += 2;
		}

		// Unbind the texture
		glBindTexture( GL_TEXTURE_2D, 0 );

		return BD_OK;

	}

}
