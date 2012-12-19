#ifndef __BRAINDEAD_DATATYPES_HPP__
#define __BRAINDEAD_DATATYPES_HPP__

#ifdef PLATFORM_WINDOWS_X86_32
#include <DataTypes_Windows_x86_32.hpp>
#elif PLATFORM_WINDOWS_X86_64
#include <DataTypes_Windows_x86_64.hpp>
#elif PLATFORM_LINUX_X86_32
#include <DataTypes_Linux_x86_32.hpp>
#elif PLATFORM_LINUX_X86_64
#include <DataTypes_Linux_x86_64.hpp>
#else
#error No platform specified
#endif

#include <Compiler.hpp>

// Extra data types building off of those defined in the platform-specific
// headers
typedef BD_UCHAR8 BD_BYTE;
typedef BD_UINT32 BD_BOOL;

// Standard types unified under the grand unification datatype theorem
typedef size_t	BD_MEMSIZE;
typedef float	BD_FLOAT32;
typedef double	BD_FLOAT64;

#define BD_TRUE		1
#define BD_FALSE	0

// Return codes (expand as necessary)
const BD_UINT32	BD_OK				= 0x00000000;
const BD_UINT32	BD_ERROR_GRAPHICS	= 0x00000001;
const BD_UINT32	BD_ERROR			= 0xFFFFFFFF;
const BD_UINT32	BD_FAIL				= BD_ERROR;

#if ( BD_32BIT == 1 )
const BD_MEMSIZE BD_ENUM_PAD = 0x7FFFFFFF;
#elif ( BD_64BIT == 1 )
const BD_MEMSIZE BD_ENUM_PAD = 0x7FFFFFFFFFFFFFFF;
#else
#error No bit size set
#endif

const BD_UINT32 BD_TIME_INFINITE = 0xFFFFFFFF;
const BD_UINT32 BD_IEEE754_INFINITE32 = 0x7F800000;

const BD_FLOAT32 BD_EPSILON = 1.0e-6f;
const BD_FLOAT32 BD_HALFEPSILON = 1.0e-3f;

#endif

