#pragma once
#include "Global.h"
#include <bitset>

#define BITON(var, offset) (var |= 1 << offset)
#define BITOFF(var, offset) (var &= ~(1 << offset))
#define BITTOGGLE(var, offset) (var ^= 1 << offset)
#define BITNEGATE(var) (var = ~var)
#define BITLSHIFT(var, offset) (var <<= offset)
#define BITRSHIFT(var, offset) (var >>= offset)
#define BITISEVEN(var) (var & 1)
#define BITTEST(var, offset) (var & (1 << offset))
#define BINTOINT(var) (0b011)

template <typename T>
static void BitSetOn( T bitSet[], UINT index )
{
	UINT bitSize = sizeof( T ) * 8u;
	bitSet[index / bitSize] |= 1 << ( index % bitSize );
}

template <typename T>
static void BitSetOff( T bitSet[], UINT index )
{
	UINT bitSize = sizeof( T ) * 8u;
	bitSet[index / bitSize] &= ~( 1 << ( index % bitSize ) );
}

template <typename T>
static bool BitCheck( T bitSet[], UINT index )
{
	UINT bitSize = sizeof( T ) * 8u;
	return ( bitSet[( index / bitSize )] & ( 1 << ( index % bitSize ) ) );
}

template <typename T>
static bool ToBit( T bitSet[], UINT size )
{
	std::wstring stream;

	for( UINT i = 0; i < size; i++ )
	{
		std::bitset< sizeof( T ) * 8u > temp( bitSet[i] );
		stream += temp.to_string<TCHAR>( 'x', 'X' );
		stream += TEXT( '-' );
	}
	//return ( bitSet[( index / bitSize )] & ( 1 << ( index % bitSize ) ) )
	OutputDebugString( stream.c_str( ) );
	return true;
}