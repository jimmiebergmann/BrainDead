#include <Image.hpp>
#include <fstream>
#include <System.hpp>
#include <Debugger.hpp>
#include <cstring>


namespace BD
{

	Image::Image( ) :
		m_pData(BD_NULL),
		m_Width(0),
		m_Height(0),
		m_Depth(0)
	{
	}

	Image::~Image( )
	{
		DeallocateData( );
	}

	BD_UINT32 Image::ReadFile( char *p_pFileName )
	{
		char * pFileExtension = new char[ 4 ];
		GetFileExtension( p_pFileName, pFileExtension, 4 );

		if( strcmp( pFileExtension, "TGA" ) == 0 )
		{
			delete [ ] pFileExtension;
			pFileExtension = BD_NULL;

			return ReadTGA(p_pFileName);
		}

		delete [ ] pFileExtension;
		pFileExtension = BD_NULL;

		return BD_ERROR;
	}

	BD_UINT32 Image::AddData( BD_BYTE * p_pData, BD_UINT32 p_Width,
		BD_UINT32 p_Height,BD_UINT32 p_Depth )
	{
		// Make sure the data pointer isn't NULL
		if(p_pData == BD_NULL)
		{
			return BD_ERROR;
		}

		// Also, we don't accept the width/height/depth to be equal to zero.
		if(p_Width == 0 || p_Height == 0 || p_Depth == 0)
		{
			return BD_ERROR;
		}

		// Set the image data
		m_pData = p_pData;
		m_Width = p_Width;
		m_Height = p_Height;
		m_Depth = p_Depth;

		return BD_OK;
	}

	void Image::DeallocateData( )
	{
		if(m_pData != BD_NULL)
		{
			delete [ ] m_pData;
			m_pData = BD_NULL;
		}
	}

	BD_BYTE * Image::GetData( ) const
	{
		return m_pData;
	}

	BD_UINT32 Image::GetWidth( ) const
	{
		return m_Width;
	}

	BD_UINT32 Image::GetHeight( ) const
	{
		return m_Height;
	}

	BD_UINT32 Image::GetDepth( ) const
	{
		return m_Depth;
	}

	BD_UINT32 Image::GetSize( ) const
	{
		return (m_Width * m_Height * m_Depth);
	}

	BD_BOOL Image::ContainsData( ) const
	{
		return (m_pData != BD_NULL);
	}

	BD_UINT32 Image::ReadTGA( const char *p_pFileName )
	{
		// Open the file
		std::ifstream File(p_pFileName, std::ios::binary);
		if(File.is_open() == false)
		{
			return BD_ERROR;
		}

		// Start to read the header data
		unsigned char Type[4];
		unsigned char Info[6];
		File.read((char*)Type, sizeof(unsigned char) * 3);

		// Seek to the position of the info data
		File.seekg(12);

		// Read the info data
		File.read((char*)Info, sizeof(unsigned char) * 6); 

		// Check if the image is either a color or greyscale image
		// 2 == color, 3 == greyscale
		if( (Type[1] != 0 || Type[2] != 2) && Type[2] != 3 )
		{
			File.close();
			return BD_ERROR;
		}

		// Use the Info to calculate the size of the image
		m_Width = Info[0] + ( Info[1] * 256 );
		m_Height = Info[2] + ( Info[3] * 256 );
		m_Depth = Info[4] / 8;

		// Make sure the image is a 24 or 32 bit image
		if(m_Depth != 3 && m_Depth != 4)
		{
			File.close();
			return BD_ERROR;
		}

		// Deallocate the old image data
		DeallocateData();
		
		// Get the full size of the image data and allocate memory for the data
		BD_UINT32 ImageSize = GetSize();
		m_pData = new BD_BYTE[ImageSize];

		// Read the image data
		File.read((char*)m_pData, sizeof(BD_BYTE) * ImageSize);

		// TGA is stored as BGR or BGRA, we have to swap the bytes
		if(m_Depth == 3)
		{
			BGR_To_RGB();
		}
		else if(m_Depth == 4)
		{
			BGRA_To_RGBA();
		}

		// Close the file since we are done.
		File.close();
		return BD_OK;
	}

	void Image::BGR_To_RGB( )
	{
		// Make sure we have any data to swap
		if(ContainsData() == BD_FALSE)
		{
			return;
		}

		BD_UINT32 Size = GetSize();
		BD_BYTE TemporaryByte = 0;

		// Loop through the data we want to swap
		for (int i = 0; i < Size; i += 3 )
		{
			TemporaryByte = m_pData[i];
			m_pData[i] = m_pData[i + 2];
			m_pData[i + 2] = TemporaryByte;
		}

	}

	void Image::BGRA_To_RGBA( )
	{
		// Make sure we have any data to swap
		if(ContainsData() == BD_FALSE)
		{
			return;
		}

		BD_UINT32 Size = GetSize();
		BD_BYTE TemporaryByte = 0;

		// Loop through the data we want to swap
		for (int i = 0; i < Size; i += 4 )
		{
			TemporaryByte = m_pData[i];
			m_pData[i] = m_pData[i + 2];
			m_pData[i + 2] = TemporaryByte;
		}
	}

}
