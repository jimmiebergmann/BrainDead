#include <Image.hpp>
#include <fstream>


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
	}

	BD_UINT32 Image::ReadFile( const char *p_pFileName )
	{

		return BD_ERROR;
	}

	BD_UINT32 Image::AddData( BD_BYTE * p_pData, BD_UINT32 p_Width,
		BD_UINT32 p_Height,BD_UINT32 p_Depth )
	{

		return BD_ERROR;
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

	BD_BOOL Image::HaveData( ) const
	{
		return (m_pData != BD_NULL);
	}


}