/*
R.A. Bickell [https://github.com/MonsterLock]
ML_Mattrix.h Last Updated: 2019-09-19 03::07::51 AM
*/
#pragma once
#include "ML_Vector.h"

namespace ML
{
	namespace MATH
	{
		namespace Matrix
		{
			using namespace Vector;

			struct matrix
			{
				union
				{
					struct
					{
						vector row[4];
					};
					float m[ 16 ];
				};

				matrix( ) noexcept;
				matrix( const vector& , const vector& , const vector& , const vector& ) noexcept;
				matrix( const matrix& ) noexcept;
				matrix( const float* );

				bool operator==        ( const matrix& );
				bool operator!=        ( const matrix& );

				vector operator[]      ( const unsigned int );
				const vector operator[]( const unsigned int ) const;

				float operator         ()( const unsigned int, const unsigned int );
				const float operator   ()( const unsigned int, const unsigned int ) const;

				matrix& operator=      ( const matrix& );
				matrix operator+       ( const matrix& ) const;
				matrix& operator+=     ( const matrix& );
				matrix operator-       ( ) const;
				matrix operator-       ( const matrix& ) const;
				matrix& operator-=     ( const matrix& );
				matrix operator*       ( const float& ) const;
				matrix& operator*=     ( const float& );
				matrix operator*       ( const matrix& ) const;
				matrix& operator*=     ( const matrix& );

				friend std::ostream& operator<<( std::ostream& os, const matrix& );
			};

			extern float Determinant   ( const matrix& );
			extern matrix Inverse      ( const matrix& );
			extern matrix Transpose    ( const matrix& );
			extern vector MatrixVector ( const matrix& , const vector& );
			extern vector VectorMatrix ( const vector& , const matrix& );

			extern matrix Scale        ( const vector& );
			extern matrix Scale        ( const float& , const float& , const float& );
			extern matrix ScaleX       ( const float& );
			extern matrix ScaleY       ( const float& );
			extern matrix ScaleZ       ( const float& );

			extern matrix Translate    ( const vector& );
			extern matrix Translate    ( const float& , const float& , const float& );
			extern matrix TranslateX   ( const float& );
			extern matrix TranslateY   ( const float& );
			extern matrix TranslateZ   ( const float& );

			extern matrix Rotate       ( const vector& );
			extern matrix Rotate       ( const float& , const float& , const float& );
			extern matrix RotateX      ( const float& );
			extern matrix RotateY      ( const float& );
			extern matrix RotateZ      ( const float& );

			extern matrix Projection   ( const float& , const float& , const float& , const float& );
			extern matrix Orthographic ( const float& , const float& , const float& , const float& );

			static const matrix ZeroMatrix(
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			);

			static const matrix IdentityMatrix(
				{ 1.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			);


		} // end namespace Matrix

	} // end namespace MATH
} // end namespace ML

// Feature: Implement LookAt and TurnTo.

// Additional Notes:
//
//	Right-handed system:
//		Translation * Rotation * Scale
//
//
//	Left-handed system:
//		Scale * Rotation * Translation