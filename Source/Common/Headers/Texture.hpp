#ifndef __BRAINDEAD_TEXTURE_HPP__
#define __BRAINDEAD_TEXTURE_HPP__

#include <DataTypes.hpp>
#include <Image.hpp>

namespace BD
{
	// Texture filter
	const BD_UINT32 BD_TEXTURE_FILTER_MAG = 1;
	const BD_UINT32 BD_TEXTURE_FILTER_MIN = 2;
	const BD_UINT32 BD_TEXTURE_FILTER_WRAP_X = 3;
	const BD_UINT32 BD_TEXTURE_FILTER_WRAP_Y = 4;

	const BD_UINT32 BD_TEXTURE_FILTER_NEAREST = 5;
	const BD_UINT32 BD_TEXTURE_FILTER_LINEAR = 6;
	const BD_UINT32 BD_TEXTURE_FILTER_REPEAT = 7;

	class Texture 
	{

	public:

		enum ePixelFormat
		{
			PIXEL_FORMAT_NONE = 0,
			//PIXEL_FORMAT_GREY = 1, // Not supported yet.
			PIXEL_FORMAT_RGB = 2,
			PIXEL_FORMAT_RGBA = 3,
		};

		virtual ~Texture( ) { }
		virtual BD_UINT32 Load( const Image & p_Image) = 0;
		virtual BD_UINT32 Load( BD_UINT32 p_Width, BD_UINT32 p_Height,
			const ePixelFormat p_PixelFormat, BD_BYTE * p_Data ) = 0;
		virtual void Bind( BD_UINT32 p_Index ) = 0;
		virtual void Unbind( ) = 0;
		virtual BD_UINT32 SetFilters( BD_UINT32 * p_pFilters ) = 0;
		// Filter functions
		// ...

		BD_INLINE BD_BOOL IsLoaded( ) { return m_Loaded; };

	protected:

		BD_BOOL m_Loaded;

	};

}

#endif
