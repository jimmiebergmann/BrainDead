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

		// !!! TEMPORARY!
		// Filters
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST/*GL_FilerModesMag[m_filterMode]*/ );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST/*GL_FilerModesMin[m_filterMode]*/ );


		glTexImage2D ( GL_TEXTURE_2D, 0, Format, p_Image.GetWidth(), p_Image.GetHeight(), 0,
			(GLenum)Format, GL_UNSIGNED_BYTE, (GLvoid *)p_Image.GetData() );

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
	
}
