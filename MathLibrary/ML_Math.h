#pragma once
#include <cmath>

namespace ml3d
{
	namespace MATH
	{
		static constexpr double EPSILON = 4.94065645841247E-324;

		static constexpr double RAD = 0.01745329252;

		static constexpr double PI =
			3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

		static constexpr double TWO_PI =
			6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696;


		static constexpr float fEPSILON = 0.00001f;

		static constexpr float fRAD = 0.017453f;

		static constexpr float fPI = 3.141592f;

		static constexpr float fTWO_PI = 6.283185f;

		template <typename T>
		static constexpr auto Average( const T& a , const T& b )
		{
			return T( ( a + b ) * 0.5f );
		}

		template <typename T>
		static constexpr T Clamp( const T& value , const T& min , const T& max )
		{
			return
				value < min ?
				min : value > max ?
				max : value;
		}

		template <typename T>
		static constexpr auto Square( const T& a )
		{
			return a * a;
		}

		template <typename T>
		static constexpr auto Cube( const T& a )
		{
			return a * a * a;
		}

		template <typename T>
		static constexpr auto Lesser( const T& a , const T& b )
		{
			return a < b ? a : b;
		}

		template <typename T>
		static constexpr auto Greater( const T& a , const T& b )
		{
			return a > b ? a : b;
		}

		template<typename T>
		static constexpr bool IsAboutEqual( const T& a , const T& b )
		{
			return fabs( a - b ) < fEPSILON;
		}

		template<typename T>
		static inline const bool IsAboutZero( const T& a )
		{
			return fabs( a ) < fEPSILON;
		}

		template <typename T>
		static constexpr auto Lerp( const T& from , const T& to , const float& t )
		{
			return static_cast< T >( ( 1.0f - t ) * from + t * to );
		}

		static constexpr unsigned int Lerp32( const unsigned int& from , const unsigned int& to , const unsigned int& t )
		{
			return ( ( to - from ) * t + 255u * from ) / 255u;
		}

		template <typename T>
		static constexpr T DegToRads( T Deg )
		{
			return T( Deg * PI / 180.0f );
		}

		template <typename T>
		static constexpr T RadsToDeg( T Rad )
		{
			return T( Rad * 180.0f / PI );
		}

		static constexpr double RadWrap( const double& a )
		{
			return a + RAD < TWO_PI ?
				a + RAD : 0.0;
		}

		static constexpr double DegWrap( const double& a )
		{
			return a + a < 360.0 ?
				a + a : 0.0f;
		}

		//template <typename T>
		//static constexpr T Determinant( const T& ax , const T& ay , const T& bx , const T& by )
		//{
		//	return ax * by - ay * bx;
		//}

		//template <typename T>
		//static constexpr T Area( const T& ax , const T& ay , const T& bx , const T& by , const T& cx , const T& cy )
		//{
		//	return Determinant( bx - ax , by - ay , cx - ax , cy - ay );
		//}

		//template <typename T>
		//static constexpr bool isBoxCheck( const T& x , const T& y , const T& minX , const T& maxX , const T& minY , const T& maxY )
		//{
		//	return x >= minX && x < maxX &&
		//		y >= minY && y < maxY;
		//}
	} // end namespace MATH
} // end namespace ml3d

