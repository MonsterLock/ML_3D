#pragma once
#include "ML_Vector.h"

#define ml3d_MATH_USE_LH

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
				matrix( const vector& rhs1 , const vector& rhs2 , const vector& rhs3 , const vector& rhs4 ) noexcept;
				matrix( const matrix& rhs ) noexcept;
				matrix( const float* rhs );

				bool operator==        ( const matrix& rhs );
				bool operator!=        ( const matrix& rhs );

				vector operator[]      ( const unsigned int index );
				const vector operator[]( const unsigned int index ) const;

				float operator         ()( const unsigned int row, const unsigned int column );
				const float operator   ()( const unsigned int row, const unsigned int column ) const;

				matrix& operator=      ( const matrix& rhs );
				matrix operator+       ( const matrix& rhs ) const;
				matrix& operator+=     ( const matrix& rhs );
				matrix operator-       ( ) const;
				matrix operator-       ( const matrix& rhs ) const;
				matrix& operator-=     ( const matrix& rhs );
				matrix operator*       ( const float& rhs ) const;
				matrix& operator*=     ( const float& rhs );
				matrix operator*       ( const matrix& rhs ) const;
				matrix& operator*=     ( const matrix& rhs );

				friend std::ostream& operator<<(std::ostream& os, const matrix& rhs);
			};

			extern float Determinant   ( const matrix& rhs );
			extern matrix Inverse      ( const matrix& rhs );
			extern matrix Transpose    ( const matrix& rhs );
			extern vector MatrixVector ( const matrix& lhs , const vector& rhs );
			extern vector VectorMatrix ( const vector& lhs , const matrix& rhs );

			extern matrix Scale        ( const vector& rhs );
			extern matrix Scale        ( const float& x , const float& y , const float& z );
			extern matrix ScaleX       ( const float& rhs );
			extern matrix ScaleY       ( const float& rhs );
			extern matrix ScaleZ       ( const float& rhs );

			extern matrix Translate    ( const vector& rhs );
			extern matrix Translate    ( const float& x , const float& y , const float& z );
			extern matrix TranslateX   ( const float& rhs );
			extern matrix TranslateY   ( const float& rhs );
			extern matrix TranslateZ   ( const float& rhs );

			extern matrix Rotate       ( const vector& rhs );
			extern matrix Rotate       ( const float& x , const float& y , const float& z );
			extern matrix RotateX      ( const float& rhs );
			extern matrix RotateY      ( const float& rhs );
			extern matrix RotateZ      ( const float& rhs );

			extern matrix Projection   ( const float& t_fov , const float& t_aspect_ratio , const float& t_near , const float& t_far );
			extern matrix Orthographic ( const float& t_fov , const float& t_aspect_ratio , const float& t_near , const float& t_far );

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

//std::ostream& operator<< ( std::ostream& out, const ML::MATH::Matrix::matrix rhs )
//{
//	out << rhs.row[0] << ", "
//		<< rhs.row[1] << ", "
//		<< rhs.row[2] << ", "
//		<< rhs.row[3];
//	return out;
//}

// Additional Notes:
//
//	Right-handed system:
//		Translation * Rotation * Scale
//
//
//	Left-handed system:
//		Scale * Rotation * Translation