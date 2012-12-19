#ifndef __BRAINDEAD_DATATYPES_WINDOWS_X86_64_HPP__
#define __BRAINDEAD_DATATYPES_WINDOWS_X86_64_HPP__

#include <wchar.h>

typedef unsigned char		BD_UCHAR8;
typedef signed char			BD_SCHAR8;
typedef wchar_t				BD_CHAR16;
typedef unsigned char		BD_UINT8;
typedef signed char			BD_SINT8;
typedef unsigned short int	BD_UINT16;
typedef signed short int	BD_SINT16;
typedef unsigned int		BD_UINT32;
typedef signed int			BD_SINT32;
typedef unsigned __int64	BD_UINT64;
typedef signed __int64		BD_SINT64;

#define BD_LITTLE_ENDIAN	1
#define BD_BIG_ENDIAN		0

#define BD_32BIT	0
#define BD_64BIT	1

#endif

