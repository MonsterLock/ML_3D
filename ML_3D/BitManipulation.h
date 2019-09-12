#pragma once
#include "Global.h"
#include <bitset>

#define BINTOINT(var) (0b011)

namespace BitM
{
	template <typename T>
	static UINT GetBitSetSize( )
	{
		return sizeof( T ) * 8u;
	}

	template <typename T>
	static void BitOn( T& var, const UINT offset )
	{
		( var |= 1 << offset );
	}

	template <typename T>
	static void BitOff( T& var, const UINT offset )
	{
		( var &= ~( 1 << offset ) );
	}

	template <typename T>
	static void BitToggle( T& var, const UINT offset )
	{
		( var ^= 1 << offset );
	}

	template <typename T>
	static void BitNegate( T& var )
	{
		( var = ~var );
	}

	template <typename T>
	static void BitLeftShift( T& var, const UINT offset )
	{
		( var <<= offset );
	}

	template <typename T>
	static void BitRightShift( T& var, const UINT offset )
	{
		( var >>= offset );
	}

	template <typename T>
	static bool BitIsEven( const T& var )
	{
		return ( var & 1 ) ? true : false;
	}

	static bool BitIsOn( int var, const UINT offset )
	{
		return ( var & ( 1 << offset ) ) ? true : false;
	}

	template <typename T>
	static void BitSetOn( T var[], const UINT offset )
	{
		UINT bitSize = GetBitSetSize<T>( );
		var[offset / bitSize] |= 1 << ( offset % bitSize );
	}

	template <typename T>
	static void BitSetOff( T var[], const UINT offset )
	{
		UINT bitSize = GetBitSetSize<T>( );
		var[offset / bitSize] &= ~( 1 << ( offset % bitSize ) );
	}

	template <typename T>
	static bool BitSetIsOn( const T var[], const UINT offset )
	{
		UINT bitSize = GetBitSetSize<T>( );
		return ( var[( offset / bitSize )] & ( 1 << ( offset % bitSize ) ) );
	}

	template <typename T>
	static std::wstring PrintBitStream( T var[], UINT size )
	{
		std::wstring out;

		for( UINT i = 0; i < size; i++ )
		{
			std::bitset< sizeof( T ) * 8u > temp( var[i] );
			out += temp.to_string<TCHAR>( '.', '1' );
			out += TEXT( "\n" );
		}

		return out;
	}
}