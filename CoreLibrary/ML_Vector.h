/*
R.A. Bickell [https://github.com/MonsterLock]
ML_Vector.h Last Updated: 2019-09-19 03::07::51 AM
*/
#pragma once
#include "ML_Math.h"
#include <iostream>

namespace ML
{
	namespace MATH
	{
		namespace Vector
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
				vector( const float& , const float& ) noexcept;
				vector( const float& , const float& , const float& ) noexcept;
				vector( const float& , const float& , const float& , const float& ) noexcept;
				vector( const vector& ) noexcept;

				bool operator==             ( const vector& );
				bool operator!=             ( const vector& );

				float operator*             ( const vector& ) const;
				float operator[]            ( const unsigned int );
				const float operator[]      ( const unsigned int ) const;

				vector& operator=           ( const vector& );
				vector operator+            ( const vector& ) const;
				vector& operator+=          ( const vector& );
				vector operator-            ( ) const;
				vector operator-            ( const vector& ) const;
				vector& operator-=          ( const vector& );
				vector operator*            ( const float& ) const;
				vector& operator*=          ( const float& );
				vector operator/            ( const float& ) const;
				vector& operator/=          ( const float& );

				float Length                ( ) const;
				float LengthSq              ( ) const;

				void ClampLength            ( const float& );
				void Homogenize             ( );
				void Normalize              ( );

				friend std::ostream& operator<<(std::ostream& os, const vector& rhs);

			}; // end struct vector

			extern bool IsExact         ( const vector& , const vector& );

			extern float AngleBetween   ( const vector& , const vector& );
			extern float Component      ( const vector& , const vector& );
			extern float DistanceBetween( const vector& , const vector& );

			extern vector Average       ( const vector& , const vector& );
			extern vector Barycentric   ( const vector& , const vector& );
			extern vector Clamp         ( const vector&, const float& );
			extern vector Cross         ( const vector& , const vector& );
			extern vector Homogenize    ( const vector& );
			extern vector Lerp          ( const vector& , const vector& , const float );
			extern vector Max           ( const vector& , const vector& );
			extern vector Min           ( const vector& , const vector& );
			extern vector Normalize     ( const vector& );
			extern vector Projection    ( const vector& , const vector& );
			extern vector Reflection    ( const vector& , const vector& );

			static const vector Back    = { 0.0f , 0.0f , -1.0f , 0.0f };
			static const vector Down    = { 0.0f , -1.0f , 0.0f , 0.0f };
			static const vector Forward = { 0.0f , 0.0f , 1.0f , 0.0f };
			static const vector Left    = { -1.0f , 0.0f , 0.0f , 0.0f };
			static const vector Right   = { 1.0f , 0.0f , 0.0f , 0.0f };
			static const vector Up      = { 0.0f , 1.0f , 0.0f , 0.0f };
			static const vector Zero    = { 0.0f , 0.0f , 0.0f , 0.0f };
		} // end namespace vector
	} // end namespace MATH
} // end namespace ML

