/*
R.A. Bickell [https://github.com/MonsterLock]
ML_BitManip.h Last Updated: 2019-09-19 03::36::45 AM
*/
#pragma once

namespace ML
{
	namespace BIT
	{
		template <typename T>
		static const size_t BitSize( )
		{
			return sizeof( T ) * 8;
		}

		template <typename T>
		static void On( T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			var[offset / bitSize] |= 1 << ( offset % bitSize );
		}

		template <typename T>
		static void Off( T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			var[offset / bitSize] &= ~( 1 << ( offset % bitSize ) );
		}

		template <typename T>
		static const bool IsOn( const T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			return ( var[( offset / bitSize )] & ( 1 << ( offset % bitSize ) ) );
		}

		template <typename T>
		static const size_t GetBitsOn( const T& var )
		{
			if( !( var ) ) return 0;
			else return ( ( var ) & 1 ) + SizeOfOn( var >> 1 );
		}

		template <typename T>
		static void Toggle( T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			( var[( offset / bitSize )] ^= ( 1 << ( offset % bitSize ) ) );
		}

		template <typename T>
		static void Negate( T* var )
		{
			size_t bitSize = BitSize<T>( );
			( *var = ~( *var ) );
		}

		template <typename T>
		static void LeftShift( T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			( *var <<= ( offset % bitSize ) );
		}

		template <typename T>
		static void RightShift( T* var, const size_t offset )
		{
			size_t bitSize = BitSize<T>( );
			( *var >>= ( offset % bitSize ) );
		}

		template <typename T>
		static const bool IsEven( const T* var )
		{
			return ( *var & 1 ) ? false : true;
		}

		static const size_t Sq( const size_t offset )
		{
			return 1 << offset;
		}
	} // end namespace BIT
} // end namespace ML

