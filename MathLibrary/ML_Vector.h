#pragma once
#include "ML_Math.h"

namespace ml3d
{
	namespace MATH
	{
		struct vector
		{
			union
			{
				struct
				{
					float x;
					float y;
					float z;
					float w;
				};
				float e[ 4 ];
			};

			vector( ) noexcept;
			vector( const float& x , const float& y ) noexcept;
			vector( const float& x , const float& y , const float& z ) noexcept;
			vector( const float& x , const float& y , const float& z , const float& w ) noexcept;
			vector( const vector& rhs ) noexcept;

			vector& operator=( const vector& rhs );
			vector operator+( const vector& rhs ) const;
			vector& operator+=( const vector& rhs );
			vector operator-( ) const;
			vector operator-( const vector& rhs ) const;
			vector& operator-=( const vector& rhs );
			vector operator*( const float& rhs ) const;
			vector& operator*=( const float& rhs );
			vector operator/( const float& rhs ) const;
			vector& operator/=( const float& rhs );
			float operator*( const vector& rhs ) const;
			bool operator==( const vector& rhs );
			bool operator!=( const vector& rhs );
			float operator[]( const unsigned int index );
			const float operator[]( const unsigned int index ) const;

			static float AngleBetween( const vector& lhs , const vector& rhs );
			static vector Average( const vector& lhs , const vector& rhs );
			static float Component( const vector& lhs , const vector& rhs );
			static vector Cross( const vector& lhs , const vector& rhs );
			float LengthSq( ) const;
			float Length( ) const;
			static vector LerpVector( const vector& lhs , const vector& rhs , const float t );
			static vector Min( const vector& lhs , const vector& rhs );
			static vector Max( const vector& lhs , const vector& rhs );
			void Normalize( );
			static vector Normalize( const vector& rhs );
			static vector Projection( const vector& lhs , const vector& rhs );
			static vector Reflection( const vector& lhs , const vector& rhs );
		}; // end vector

		namespace Vector
		{
			static const vector Zero = { 0.0f , 0.0f , 0.0f , 0.0f };
			static const vector Back = { 0.0f , 0.0f , -1.0f , 0.0f };
			static const vector Forward = { 0.0f , 0.0f , 1.0f , 0.0f };
			static const vector Left = { -1.0f , 0.0f , 0.0f , 0.0f };
			static const vector Right = { 1.0f , 0.0f , 0.0f , 0.0f };
			static const vector Up = { 0.0f , 1.0f , 0.0f , 0.0f };
			static const vector Down = { 0.0f , -1.0f , 0.0f , 0.0f };
		} // end namespace vector

	} // end namespace MATH
} // end namespace ml3d