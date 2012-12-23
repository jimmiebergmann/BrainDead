#ifndef __BRAINDEAD_IMAGE_HPP__
#define __BRAINDEAD_IMAGE_HPP__

#include <DataTypes.hpp>

namespace BD
{

	class Image
	{

	public:

		Image( );
		~Image( );
		BD_UINT32 ReadFile( const char *p_pFileName ); // Read data from a file.
		BD_UINT32 AddData( BD_BYTE * p_pData, const BD_UINT32 p_Width,
			const BD_UINT32 p_Height, const BD_UINT32 p_Depth ); // Add raw data by hand (Not from a file)
		void DeallocateData( );
		BD_BYTE * GetData( ) const;
		BD_UINT32 GetWidth( ) const;
		BD_UINT32 GetHeight( ) const;
		BD_UINT32 GetDepth( ) const;
		BD_UINT32 GetSize( ) const; // (Width * Height * Depth)
		BD_BOOL HaveData( ) const; // Does the Image class have any data?

	private:

		BD_UINT32 ReadTGA( const char *p_pFileName );
		void BGR_To_RGB( );
		void BGRA_To_RGBA( );

		BD_BYTE * m_pData;
		BD_UINT32 m_Width;
		BD_UINT32 m_Height;
		BD_UINT32 m_Depth;

	};

}

#endif