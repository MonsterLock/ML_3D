#pragma once
#include "ML_Vector.h"

#define ml3d_MATH_USE_LH

namespace ml3d
{
	namespace MATH
	{
		struct matrix
		{
			union
			{
				struct
				{
					vector row1;
					vector row2;
					vector row3;
					vector row4;
				};
				float m[ 16 ];
			};

			matrix( ) noexcept;
			matrix( const vector& rhs1 , const vector& rhs2 , const vector& rhs3 , const vector& rhs4 ) noexcept;
			matrix( const matrix& rhs ) noexcept;

			matrix& operator=( const matrix& rhs );
			matrix operator-( ) const;
			matrix operator-( const matrix& rhs ) const;
			matrix& operator-=( const matrix& rhs );
			matrix operator+( const matrix& rhs ) const;
			matrix& operator+=( const matrix& rhs );
			matrix operator*( const float& rhs ) const;
			matrix& operator*=( const float& rhs );
			matrix operator*( const matrix& rhs ) const;
			matrix& operator*=( const matrix& rhs );
			bool operator==( const matrix& rhs );
			bool operator!=( const matrix& rhs );
			float operator[]( const unsigned int index );
			const float operator[]( const unsigned int index ) const;

			static matrix Translate( const vector& rhs );
			static matrix Translate( const float& x , const float& y , const float& z );
			static matrix TranslateX( const float& rhs );
			static matrix TranslateY( const float& rhs );
			static matrix TranslateZ( const float& rhs );

			static matrix Scale( const vector& rhs );
			static matrix Scale( const float& x , const float& y , const float& z );
			static matrix ScaleX( const float& rhs );
			static matrix ScaleY( const float& rhs );
			static matrix ScaleZ( const float& rhs );

			static matrix Rotate( const vector& rhs );
			static matrix Rotate( const float& x , const float& y , const float& z );
			static matrix RotateX( const float& rhs );
			static matrix RotateY( const float& rhs );
			static matrix RotateZ( const float& rhs );

			static matrix Transpose( const matrix& rhs );
			static float Determinant( const matrix& rhs );
			static matrix Inverse( const matrix& rhs );

			static vector MatrixVectorMultiplication( const matrix& lhs, const vector& rhs );
			static vector VectorMatrixMultiplication( const vector& lhs, const matrix& rhs );

			static matrix Projection( const float& t_aspect_ratio, const float& t_fov, const float& t_near, const float& t_far );
			static matrix Orthographic( const float& t_near, const float& t_far );
		};

		//namespace Matrix
		//{
		//	static const matrix Identity = { vector::Right, vector::Up, vector::Forward, { 0.0f, 0.0f, 0.0f, 1.0f } };
		//} // end namespace Matrix
	} // end namespace MATH
} // end namespace ml3d

// Additional Notes:
//
//	Right-handed system:
//		Translation * Rotation * Scale
//
//
//	Left-handed system:
//		Scale * Rotation * Translation