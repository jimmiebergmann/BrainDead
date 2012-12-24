#ifndef __BRAINDEAD_TEXTURE_OGL_HPP__
#define __BRAINDEAD_TEXTURE_OGL_HPP__

#include <Texture.hpp>
#include <OGL/OpenGL.hpp>

namespace BD
{
	
	class TextureOGL : public Texture
	{

	public:

		TextureOGL( );
		virtual ~TextureOGL ( );
		virtual BD_UINT32 Load( const Image & p_Image);
		virtual BD_UINT32 Load( BD_UINT32 p_Width, BD_UINT32 p_Height,
			const ePixelFormat p_PixelFormat, BD_BYTE * p_Data );
		virtual void Bind( BD_UINT32 p_Index );
		virtual void Unbind( );

	private:

		GLuint m_Id;
		static GLint s_PixelFormats[4];

	};

}

#endif

