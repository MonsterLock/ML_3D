#include "CppUnitTest.h"

#include "../MathLibrary/ML_Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using namespace ml3d::MATH::Matrix;

	TEST_CLASS( MatrixTest )
	{
		static constexpr float zero_f[ 16 ] = { 0.0f };

		static constexpr float identity_f[ 16 ] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		static constexpr float test_f[ 16 ] = {
			-2.0f, 0.0f, -4.0f, 1.0f,
			-2.0f, 0.0f, -4.0f, 1.0f,
			-2.0f, 0.0f, -4.0f, 1.0f,
			-2.0f, 0.0f, -4.0f, 1.0f
		};

	public:
		TEST_METHOD( MatrixConstructor )
		{
			matrix m1;

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m1.m[ i ] == zero_f[ i ] );
			}

			static const vector test_row1( 1.0f , 0.0f , 0.0f , 0.0f );
			static const vector test_row2( 0.0f , 1.0f , 0.0f , 0.0f );
			static const vector test_row3( 0.0f , 0.0f , 1.0f , 0.0f );
			static const vector test_row4( 0.0f , 0.0f , 0.0f , 1.0f );

			matrix m2( test_row1 , test_row2 , test_row3 , test_row4 );

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m2.m[ i ] == identity_f[ i ] );
			}

			matrix m3( m2 );

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m3.m[ i ] == identity_f[ i ] );
			}

			matrix m4( test_f );

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m4.m[ i ] == test_f[ i ] );
			}
		}
		TEST_METHOD( MatrixAssignmentOperator )
		{
			matrix m1;
			m1 = identity_f;

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m1.m[ i ] == identity_f[ i ] );
			}

			matrix m2;
			m2 = m1;

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m2.m[ i ] == identity_f[ i ] );
			}

			static const vector test_row1( 1.0f , 0.0f , 0.0f , 0.0f );
			static const vector test_row2( 0.0f , 1.0f , 0.0f , 0.0f );
			static const vector test_row3( 0.0f , 0.0f , 1.0f , 0.0f );
			static const vector test_row4( 0.0f , 0.0f , 0.0f , 1.0f );

			matrix m3;
			m3 = { test_row1 , test_row2 , test_row3 , test_row4 };

			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m3.m[ i ] == identity_f[ i ] );
			}
		}
		TEST_METHOD( MatrixEqualityOperator )
		{
			matrix m1( identity_f );
			matrix m2( identity_f );
			matrix m3( test_f );

			Assert::IsTrue( m1 == m2 );
			Assert::IsTrue( m1 != m3 );
			Assert::IsTrue( m2 != m3 );
			Assert::IsFalse( m2 == m3 );
		}
		TEST_METHOD( MatrixIndexOperator )
		{
			matrix m1( test_f );

			for( unsigned int i = 0; i < 4; i++ )
			{
				for( unsigned int j = 0; j < 4; j++ )
				{
					Assert::IsTrue( m1[ i ][ j ] == test_f[ i * 4 + j ] );
				}
			}
		}
		TEST_METHOD( MatrixZero )
		{
			matrix m1( ZeroMatrix );
			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m1.m[ i ] == zero_f[ i ] );
			}
		}
		TEST_METHOD( MatrixIdentity )
		{
			matrix m1( IdentityMatrix );
			for( size_t i = 0; i < 16; i++ )
			{
				Assert::IsTrue( m1.m[ i ] == identity_f[ i ] );
			}
		}
		TEST_METHOD( MatrixAdditionOperator )
		{
			matrix m1a(
				{ -6 , -5 , 8 , -6 } ,
				{ -6 , -5 , -2 , 6 } ,
				{ 3 , -3 , 5 , 4 } ,
				{ -5 , -5 , 3 , -4 }
			);

			matrix m1b(
				{ 0, 3, 7, 5 } ,
				{ -8, 7, 2, -7 } ,
				{ 3, -8, 7, -7 } ,
				{ -7, -5, -6, 2 }
			);

			matrix result1(
				{ -6, -2, 15, -1 } ,
				{ -14, 2, 0, -1 } ,
				{ 6, -11, 12, -3 } ,
				{ -12, -10, -3, -2 }
			);

			matrix output1a( m1a + m1b );
			Assert::IsTrue( output1a == result1 );

			matrix output1b( m1a );
			output1b += m1b;
			Assert::IsTrue( output1b == result1 );

			matrix m2a(
				{ 6, -3, 0, 2 } ,
				{ -4, -5, -6, -3 } ,
				{ -3, 1, -6, 2 } ,
				{ -2, -7, -9, 3 }
			);

			matrix m2b(
				{ -4, -7, -5, -1 } ,
				{ 0, 4, -8, -1 } ,
				{ -6, -6, 6, 5 } ,
				{ 1, -9, -6, -7 }
			);

			matrix result2(
				{ 2, -10, -5, 1 } ,
				{ -4, -1, -14, -4 } ,
				{ -9, -5, 0, 7 } ,
				{ -1, -16, -15, -4 }
			);

			matrix output2a( m2a + m2b );
			Assert::IsTrue( output2a == result2 );

			matrix output2b( m2a );
			output2b += m2b;
			Assert::IsTrue( output2b == result2 );
		}
		TEST_METHOD( MatrixSubtractionOperator )
		{
			matrix m1a(
				{ 5, -5, -6, 0 } ,
				{ -4, -3, -8, -9 } ,
				{ -6, 5, 4, -2 } ,
				{ 2, 3, 4, 5 }
			);

			matrix m1b(
				{ -7, -7, 7, -9 } ,
				{ -7, 7, 4, 4 } ,
				{ 8, 8, -2, 8 } ,
				{ 7, -4, 1, 3 }
			);

			matrix result1(
				{ 12, 2, -13, 9 } ,
				{ 3, -10, -12, -13 } ,
				{ -14, -3, 6, -10 } ,
				{ -5, 7, 3, 2 }
			);

			matrix output1a( m1a - m1b );
			Assert::IsTrue( output1a == result1 );

			matrix output1b( m1a );
			output1b -= m1b;
			Assert::IsTrue( output1b == result1 );

			matrix m2a(
				{ -3, 7, -8, 5 } ,
				{ 4, -9, 8, -6 } ,
				{ 2, -7, -3, 0 } ,
				{ 2, 8, 5, -6 }
			);

			matrix m2b(
				{ 2, -8, 7, 8 } ,
				{ -9, 0, 2, -6 } ,
				{ -6, 0, 8, -6 } ,
				{ 3, -2, 4, -9 }
			);

			matrix result2(
				{ -5, 15, -15, -3 } ,
				{ 13, -9, 6, 0 } ,
				{ 8, -7, -11, 6 } ,
				{ -1, 10, 1, 3 }
			);

			matrix output2a( m2a - m2b );
			Assert::IsTrue( output2a == result2 );

			matrix output2b( m2a );
			output2b -= m2b;
			Assert::IsTrue( output2b == result2 );
		}
		TEST_METHOD( MatrixNegate )
		{
			matrix m1a(
				{ -3, -5, -6, -5 } ,
				{ 2, 5, 5, 0 } ,
				{ 7, -5, -3, 4 } ,
				{ -5, -2, 8, 2 }
			);

			matrix result1(
				{ 3, 5, 6, 5 } ,
				{ -2, -5, -5, -0 } ,
				{ -7, 5, 3, -4 } ,
				{ 5, 2, -8, -2 }
			);

			matrix output1a( -m1a );
			Assert::IsTrue( output1a == result1 );

			matrix m2a(
				{ 7, 0, -2, -1 } ,
				{ -7, -8, -5, 2 } ,
				{ -9, 8, 8, -2 } ,
				{ -3, -6, -5, 5 }
			);

			matrix result2(
				{ -7, -0, 2, 1 } ,
				{ 7, 8, 5, -2 } ,
				{ 9, -8, -8, 2 } ,
				{ 3, 6, 5, -5 }
			);

			matrix output2a( -m2a );
			Assert::IsTrue( output2a == result2 );
		}
		TEST_METHOD( MatrixMultiplication )
		{
			matrix m1a(
				{ -6, 0, 4, -8 } ,
				{ -9, -2, -7, -5 } ,
				{ 3, 1, -7, -1 } ,
				{ 7, -4, -5, -3 }
			);

			matrix m1b(
				{ -3, -9, 1, 0 } ,
				{ -2, 8, -7, -6 } ,
				{ -7, -7, 7, -8 } ,
				{ 3, 6, -5, 6 }
			);

			matrix result1(
				{ -34, -22, 62, -80 } ,
				{ 65, 84, -19, 38 } ,
				{ 35, 24, -48, 44 } ,
				{ 13, -78, 15, 46 }
			);

			matrix output1a( m1a * m1b );
			Assert::IsTrue( output1a == result1 );

			matrix output1b( m1a );
			output1b *= m1b;
			Assert::IsTrue( output1b == result1 );

			matrix m2a(
				{ -8, 0, -2, 4 } ,
				{ -1, 1, 4, -1 } ,
				{ 1, -2, -8, 8 } ,
				{ -1, 8, -2, 2 }
			);

			matrix m2b(
				{ -2, 5, 4, 3 } ,
				{ -9, -5, 2, -5 } ,
				{ -7, 1, 1, -2 } ,
				{ 0, 2, -2, -9 }
			);

			matrix result2(
				{ 30, -34, -42, -56 } ,
				{ -35, -8, 4, -7 } ,
				{ 72, 23, -24, -43 } ,
				{ -56, -43, 6, -57 }
			);

			matrix output2a( m2a * m2b );
			Assert::IsTrue( output2a == result2 );

			matrix output2b( m2a );
			output2b *= m2b;
			Assert::IsTrue( output2b == result2 );

			matrix m3a(
				{ -1, -8, -1, -1 } ,
				{ -5, -2, -8, 1 } ,
				{ 7, 2, -2, -2 } ,
				{ -3, -8, -7, -5 }
			);

			matrix m3b(
				{ -3, -4, 3, 8 } ,
				{ 1, 0, -3, 1 } ,
				{ -9, -1, -4, -7 } ,
				{ 5, -2, 8, -6 }
			);

			matrix result3(
				{ -1, 7, 17, -3 } ,
				{ 90, 26, 31, 8 } ,
				{ -11, -22, 7, 84 } ,
				{ 39, 29, 3, 47 }
			);

			matrix output3a( m3a * m3b );
			Assert::IsTrue( output3a == result3 );

			matrix output3b( m3a );
			output3b *= m3b;
			Assert::IsTrue( output3b == result3 );
		}
		TEST_METHOD( MatrixScalarMultiplication )
		{
			matrix m1a(
				{ -2, -6, 8, -2 } ,
				{ -5, -9, -9, 2 } ,
				{ -1, 0, 3, 2 } ,
				{ -9, -2, -5, 6 }
			);

			float m1b = 4.0f;

			matrix result1(
				{ -8, -24, 32, -8 } ,
				{ -20, -36, -36, 8 } ,
				{ -4, 0, 12, 8 } ,
				{ -36, -8, -20, 24 }
			);

			matrix output1a( m1a * m1b );
			Assert::IsTrue( output1a == result1 );

			matrix output1b( m1a );
			output1b *= m1b;
			Assert::IsTrue( output1b == result1 );

			matrix m2a(
				{ -5, 5, 2, -6 } ,
				{ 5, 8, -5, -4 } ,
				{ 0, -4, 8, 1 } ,
				{ 5, -2, 1, -6 }
			);

			float m2b = 3.0f;

			matrix result2(
				{ -15, 15, 6, -18 } ,
				{ 15, 24, -15, -12 } ,
				{ 0, -12, 24, 3 } ,
				{ 15, -6, 3, -18 }
			);

			matrix output2a( m2a * m2b );
			Assert::IsTrue( output2a == result2 );

			matrix output2b( m2a );
			output2b *= m2b;
			Assert::IsTrue( output2b == result2 );
		}
		TEST_METHOD( MatrixDeterminant )
		{
			matrix m1a(
				{ -4, 8, -7, 4 } ,
				{ 7, 4, 5, 0 } ,
				{ 6, -8, -9, 2 } ,
				{ -3, -5, 7, -9 }
			);

			float result1 = -6318.0f;

			float output1a( Determinant( m1a ) );
			Assert::IsTrue( output1a == result1 );

			matrix m2a(
				{ 6, 3, -8, -1 } ,
				{ 2, -1, 6, -7 } ,
				{ -6, 1, 3, -4 } ,
				{ -9, -6, 1, 3 }
			);

			float result2 = 2888.0f;

			float output2a( Determinant( m2a ) );
			Assert::IsTrue( output2a == result2 );

			matrix m3a(
				{ -9, 6, 0, 0 } ,
				{ -9, 8, -7, -5 } ,
				{ -5, 0, 2, 3 } ,
				{ 1, 2, 1, 2 }
			);

			float result3 = 516.0f;

			float output3a( Determinant( m3a ) );
			Assert::IsTrue( output3a == result3 );

			matrix m4a(
				{ 1, 2, 3, 4 } ,
				{ 2, 3, 4, 5 } ,
				{ 3, 4, 5, 6 } ,
				{ 4, 5, 6, 7 }
			);

			float result4 = 0.0f;

			float output4a( Determinant( m4a ) );
			Assert::IsTrue( output4a == result4 );
		}
		TEST_METHOD( MatrixInverse )
		{
			matrix m1a(
				{ 1.0f, 0.0f, 0.0f, 0.0f } ,
				{ 0.0f, 0.309f, 0.951f, 0.0f } ,
				{ 0.0f, -0.951f, 0.309f, 0.0f } ,
				{ 7.0f, -2.282f, 9.153f, 1.0f }
			);

			matrix result1(
				{ 1.0f, 0.0f, 0.0f, 0.0f } ,
				{ 0.0f, 0.309036f, -0.951112f, 0.0f } ,
				{ 0.0f, 0.951112f, 0.309036f, 0.0f } ,
				{ -7.0f, -8.00030f, -4.999048f, 1.0f }
			);

			matrix output1a( Inverse( m1a ) );

			Assert::IsTrue( output1a == result1 );

			matrix m2a(
				{ -4, -6, -1, 4 } ,
				{ 8, -8, 6, 1 } ,
				{ 6, 4, 1, -9 } ,
				{ 5, -5, -4, -1 }
			);

			matrix result2(
				{ -0.189216f ,   0.0421569f,  -0.0892157f,   0.0882353f } ,
				{ -0.18268f  ,  -0.0232026f,  -0.0826797f,  -0.00980392f } ,
				{ 0.0424837f,   0.0751634f,   0.0424837f,  -0.137255f } ,
				{ -0.202614f ,   0.0261438f,  -0.202614f ,   0.0392157f } );

			matrix output2a( Inverse( m2a ) );
			Assert::IsTrue( output2a == result2 );

			matrix m3a(
				{ 5, -1, 3, 7 } ,
				{ -3, 7, 2, -5 } ,
				{ 0, 7, 5, 7 } ,
				{ -5, 6, -2, 0 }
			);

			matrix result3(
				{ 0.57265f ,   0.279202f ,  -0.373219f  ,  0.205128f } ,
				{ 0.337607f ,   0.19943f ,  -0.195157f  ,  0.217949f } ,
				{ -0.418803f ,  -0.0997151f,   0.347578f  , -0.358974f } ,
				{ -0.0384615f ,  -0.128205f ,   0.0897436f ,  0.0384615f } );

			matrix output3a( Inverse( m3a ) );
			Assert::IsTrue( output3a == result3 );

			matrix m4a(
				{ 2, -8, -3, 1 } ,
				{ -4, -7, 3, -1 } ,
				{ 3, 8, -2, 7 } ,
				{ 6, 1, 2, -3 }
			);

			matrix result4(
				{ 0.0584039f,   0.00490415f,   0.0468123f  ,  0.127062f } ,
				{ -0.0744539f,  -0.0673206f ,  -0.00624164f , -0.0169416f } ,
				{ -0.0838163f,   0.229603f  ,   0.100758f   ,  0.130629f } ,
				{ 0.0361123f,   0.140437f  ,   0.158716f   ,  0.00222916f } );

			matrix output4a( Inverse( m4a ) );
			Assert::IsTrue( output4a == result4 );

			matrix m5a(
				{ 1, 2, 3, 4 } ,
				{ 2, 3, 4, 5 } ,
				{ 3, 4, 5, 6 } ,
				{ 4, 5, 6, 7 }
			);

			matrix result5(
				{ 1, 2, 3, 4 } ,
				{ 2, 3, 4, 5 } ,
				{ 3, 4, 5, 6 } ,
				{ 4, 5, 6, 7 }
			);

			matrix output5a( Inverse( m5a ) );
			Assert::IsTrue( output5a == result5 );
		}
		TEST_METHOD( MatrixTranspose )
		{
			matrix m1a(
				{ -4, -5, 7, -9 } ,
				{ -6, -1, -3, 3 } ,
				{ 7, 7, -8, 5 } ,
				{ -5, -8, -8, 8 }
			);

			matrix result1(
				{ -4, -6, 7, -5 } ,
				{ -5, -1, 7, -8 } ,
				{ 7, -3, -8, -8 } ,
				{ -9, 3, 5, 8 }
			);

			matrix output1a( Transpose( m1a ) );
			Assert::IsTrue( output1a == result1 );

			matrix m2a(
				{ -8, -7, 1, -2 } ,
				{ 2, -2, -4, -8 } ,
				{ -3, 4, -5, -5 } ,
				{ -1, -5, 2, 3 }
			);

			matrix result2(
				{ -8, 2, -3, -1 } ,
				{ -7, -2, 4, -5 } ,
				{ 1, -4, -5, 2 } ,
				{ -2, -8, -5, 3 }
			);

			matrix output2a( Transpose( m2a ) );
			Assert::IsTrue( output2a == result2 );
		}
		TEST_METHOD( MatrixMatrixVectorMultiplication )
		{
			matrix m1a(
				{ 0, -1, 1, 6 } ,
				{ -4, -7, -9, -5 } ,
				{ -6, -3, 0, 7 } ,
				{ 4, -1, -4, 5 }
			);

			vector m1b( 7 , 8 , -4 , 5 );

			vector result1( 18 , -73 , -31 , 61 );

			vector output1a( MatrixVector( m1a , m1b ) );
			Assert::IsTrue( output1a == result1 );

			matrix m2a(
				{ -6, -4, -7, -7 } ,
				{ -8, 8, 4, 3 } ,
				{ 7, 4, 5, -5 } ,
				{ -1, 8, -2, 1 }
			);

			vector m2b( 4 , 3 , -5 , -6 );

			vector result2( 41 , -46 , 45 , 24 );

			vector output2a( MatrixVector( m2a , m2b ) );
			Assert::IsTrue( output2a == result2 );
		}
		TEST_METHOD( MatrixVectorMatrixMultiplication )
		{
			vector m1a( 8 , -5 , 6 , 1 );

			matrix m1b(
				{ -3, 6, -4, 0 } ,
				{ 2, 1, -6, -7 } ,
				{ 3, 1, 7, 2 } ,
				{ 6, -3, 3, -1 } );

			vector result1( -10 , 46 , 43 , 46 );

			vector output1a( VectorMatrix( m1a , m1b ) );
			Assert::IsTrue( output1a == result1 );

			vector m2a( 7 , -8 , 2 , -4 );

			matrix m2b(
				{ -6, 5, -2, -3 } ,
				{ -2, 2, 7, -4 } ,
				{ -7, -5, -4, 2 } ,
				{ -9, 6, -7, -5 } );

			vector result2( -4 , -15 , -50 , 35 );

			vector output2a( VectorMatrix( m2a , m2b ) );
			Assert::IsTrue( output2a == result2 );
		}
		TEST_METHOD( MatrixScaling )
		{
			vector test1( -7.0f , 2.0f , 4.0f );
			matrix result1X(
				{ test1.x, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1X( ScaleX( test1.x ) );
			Assert::IsTrue( m1X == result1X );

			matrix result1Y(
				{ 1, 0, 0, 0 } ,
				{ 0, test1.y, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1Y( ScaleY( test1.y ) );
			Assert::IsTrue( m1Y == result1Y );

			matrix result1Z(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, test1.z, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1Z( ScaleZ( test1.z ) );
			Assert::IsTrue( m1Z == result1Z );

			matrix result1XYZ(
				{ test1.x, 0, 0, 0 } ,
				{ 0, test1.y, 0, 0 } ,
				{ 0, 0, test1.z, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1XYZ( Scale( test1.x , test1.y , test1.z ) );
			Assert::IsTrue( m1XYZ == result1XYZ );

			matrix m1XYZb( Scale( test1 ) );
			Assert::IsTrue( m1XYZb == result1XYZ );

			vector test2( 4.0f , 1.0f , -2.0f );

			matrix result2X(
				{ test2.x, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m2X( ScaleX( test2.x ) );
			Assert::IsTrue( m2X == result2X );

			matrix result2Y(
				{ 1, 0, 0, 0 } ,
				{ 0, test2.y, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );
			matrix m2Y( ScaleY( test2.y ) );
			Assert::IsTrue( m2Y == result2Y );

			matrix result2Z(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, test2.z, 0 } ,
				{ 0, 0, 0, 1 } );
			matrix m2Z( ScaleZ( test2.z ) );
			Assert::IsTrue( m2Z == result2Z );

			matrix result2XYZ(
				{ test2.x, 0, 0, 0 } ,
				{ 0, test2.y, 0, 0 } ,
				{ 0, 0, test2.z, 0 } ,
				{ 0, 0, 0, 1 } );
			matrix m2XYZ( Scale( test2.x , test2.y , test2.z ) );
			Assert::IsTrue( m2XYZ == result2XYZ );

			matrix m2XYZb( Scale( test2 ) );
			Assert::IsTrue( m2XYZb == result2XYZ );
		}
		TEST_METHOD( MatrixTranslation )
		{
			vector test1( -8.0f , 1.0f , 4.0f );
			matrix result1X(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ test1.x, 0, 0, 1 } );

			matrix m1X( TranslateX( test1.x ) );
			Assert::IsTrue( m1X == result1X );

			matrix result1Y(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, test1.y, 0, 1 } );

			matrix m1Y( TranslateY( test1.y ) );
			Assert::IsTrue( m1Y == result1Y );

			matrix result1Z(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, test1.z, 1 } );

			matrix m1Z( TranslateZ( test1.z ) );
			Assert::IsTrue( m1Z == result1Z );

			matrix result1XYZ(
				{ 1, 0, 0, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ test1.x, test1.y, test1.z, 1 } );

			matrix m1XYZ( Translate( test1.x , test1.y , test1.z ) );
			Assert::IsTrue( m1XYZ == result1XYZ );

			matrix m1XYZb( Translate( test1 ) );
			Assert::IsTrue( m1XYZb == result1XYZ );
		}
		TEST_METHOD( MatrixRotation )
		{
			vector test1( 2.302319492303f , 0.576237888384f , 0.3779737388f );
			matrix result1X(
				{ 1, 0, 0, 0 } ,
				{ 0, -0.66800249f, 0.74415904f, 0 } ,
				{ 0, -0.74415904f, -0.66800249f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1X( RotateX( test1.x ) );
			Assert::IsTrue( m1X == result1X );

			matrix result1Y(
				{ 0.83851874f, 0, -0.54487276f, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0.54487276f, 0, 0.83851874f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1Y( RotateY( test1.y ) );
			Assert::IsTrue( m1Y == result1Y );

			matrix result1Z(
				{ 0.92941445f, 0.36903772f, 0, 0 } ,
				{ -0.36903772f, 0.92941445f, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m1Z( RotateZ( test1.z ) );
			Assert::IsTrue( m1Z == result1Z );

			matrix result1XYZ( result1X * result1Y * result1Z );

			matrix m1XYZa( Rotate( test1.x , test1.y , test1.z ) );
			Assert::IsTrue( m1XYZa == result1XYZ );

			matrix m1XYZb( Rotate( test1 ) );
			Assert::IsTrue( m1XYZb == result1XYZ );

			vector test2( 5.77261209831f , 2.8702061722f , 1.36656144074f );
			matrix result2X(
				{ 1, 0, 0, 0 } ,
				{ 0, 0.87246221f, -0.48868158f, 0 } ,
				{ 0, 0.48868158f, 0.87246221f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m2X( RotateX( test2.x ) );
			Assert::IsTrue( m2X == result2X );

			matrix result2Y(
				{ -0.96339959f, 0, -0.26806954f, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ 0.26806954f, 0, -0.96339959f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m2Y( RotateY( test2.y ) );
			Assert::IsTrue( m2Y == result2Y );

			matrix result2Z(
				{ 0.20281908f, 0.97921622f, 0, 0 } ,
				{ -0.97921622f, 0.20281908f, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m2Z( RotateZ( test2.z ) );
			Assert::IsTrue( m2Z == result2Z );

			matrix result2XYZ( result2X * result2Y * result2Z );

			matrix m2XYZ( Rotate( test2.x , test2.y , test2.z ) );
			Assert::IsTrue( m2XYZ == result2XYZ );

			matrix m2XYZb( Rotate( test2 ) );
			Assert::IsTrue( m2XYZb == result2XYZ );

			vector test3( 2.8604585083f , 4.3467529741f , 5.46108287f );
			matrix result3X(
				{ 1, 0 , 0 , 0 } ,
				{ 0, -0.96074069f, 0.27744788f, 0 } ,
				{ 0, -0.27744788f, -0.96074069f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m3X( RotateX( test3.x ) );
			Assert::IsTrue( m3X == result3X );

			matrix result3Y(
				{ -0.35754675f, 0, 0.93389523f, 0 } ,
				{ 0, 1, 0, 0 } ,
				{ -0.93389523f, 0, -0.35754675f, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m3Y( RotateY( test3.y ) );
			Assert::IsTrue( m3Y == result3Y );

			matrix result3Z(
				{ 0.68067944f, -0.73258144f, 0, 0 } ,
				{ 0.73258144f, 0.68067944f, 0, 0 } ,
				{ 0, 0, 1, 0 } ,
				{ 0, 0, 0, 1 } );

			matrix m3Z( RotateZ( test3.z ) );
			Assert::IsTrue( m3Z == result3Z );

			matrix result3XYZ(result3X * result3Y * result3Z );

			matrix m3XYZ( Rotate( test3.x , test3.y , test3.z ) );
			Assert::IsTrue( m3XYZ == result3XYZ );

			matrix m3XYZb( Rotate( test3 ) );
			Assert::IsTrue( m3XYZb == result3XYZ );
		}
		TEST_METHOD( MatrixOrthographic )
		{
			matrix result1(
				{ 0.200000f, 0, 0, 0 } ,
				{ 0, 0.200000f, 0, 0 } ,
				{ 0, 0, 0.101010f, 0.0f } ,
				{ 0, 0, -0.010101, 1.0f } );

			float width = 10.000000f;
			float height = 10.000000f;
			float t_near = 0.100000f;
			float t_far = 10.000000f;

			matrix m1a( Orthographic( width, height , t_near , t_far ) );

			Assert::IsTrue( m1a == result1 );

			matrix result2(
				{ 0.001042f, 0, 0, 0 } ,
				{ 0, 0.001892f, 0, 0 } ,
				{ 0, 0, 0.001000f, 0.0f } ,
				{ 0, 0, -0.000100f, 1.0f } );

			width = 1920.000000f;
			height = 1057.000000f;
			t_near = 0.100000f;
			t_far = 1000.000000f;

			matrix m2a( Orthographic( width, height , t_near , t_far ) );

			Assert::IsTrue( m2a == result2 );
		}
		TEST_METHOD( MatrixProjection )
		{
			float fieldOfView = ml3d::MATH::fPI * 0.4f;
			float aspectRatio = 10.0f / 10.0f;
			float t_near = 0.1f;
			float t_far = 10.0f;

			matrix result1(
				{ 1.376382f, 0, 0, 0 } ,
				{ 0, 1.376382f, 0, 0 } ,
				{ 0, 0, 1.010101f, 1 } ,
				{ 0, 0, -0.101010, 0 } );

			matrix m1a( Projection( fieldOfView, aspectRatio , t_near , t_far ) );

			Assert::IsTrue( m1a == result1 );

			matrix result2(
				{ 0.757727f, 0, 0, 0 } ,
				{ 0, 1.376382f, 0, 0 } ,
				{ 0, 0, 1.000100f, 1 } ,
				{ 0, 0, -0.100010f, 0 } );

			fieldOfView = ml3d::MATH::fPI * 0.4f;
			aspectRatio = 1920.0f / 1057.0f;
			t_near = 0.1f;
			t_far = 1000.0f;

			matrix m2a( Projection( fieldOfView, aspectRatio , t_near , t_far ) );

			Assert::IsTrue( m2a == result2 );
		}
	};
}

//Matrix_Create_Rotation_X( F 131.91319 ) = M{ 1, 0, 0, 0 } ,
//{ 0, -0.66800249, -0.74415904, 0 } ,
//{ 0, 0.74415904, -0.66800249, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Y( F 33.015999 ) = M{ 0.83851874, 0, 0.54487276, 0 } ,
//{ 0, 1, 0, 0 } ,
//{ -0.54487276, 0, 0.83851874, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Z( F 21.6563 ) = M{ 0.92941445, -0.36903772, 0, 0 } ,
//{ 0.36903772, 0.92941445, 0, 0 } ,
//{ 0, 0, 1, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_X( F 330.74631 ) = M{ 1, 0, 0, 0 } ,
//{ 0, 0.87246221, 0.48868158, 0 } ,
//{ 0, -0.48868158, 0.87246221, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Y( F 164.4507 ) = M{ -0.96339959, 0, 0.26806954, 0 } ,
//{ 0, 1, 0, 0 } ,
//{ -0.26806954, 0, -0.96339959, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Z( F 78.298203 ) = M{ 0.20281908, -0.97921622, 0, 0 } ,
//{ 0.97921622, 0.20281908, 0, 0 } ,
//{ 0, 0, 1, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_X( F 163.8922 ) = M{ 1, 0, 0, 0 } ,
//{ 0, -0.96074069, -0.27744788, 0 } ,
//{ 0, 0.27744788, -0.96074069, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Y( F 249.0506 ) = M{ -0.35754675, 0, -0.93389523, 0 } ,
//{ 0, 1, 0, 0 } ,
//{ 0.93389523, 0, -0.35754675, 0 } ,
//{ 0, 0, 0, 1 }

//	Matrix_Create_Rotation_Z( F 312.897 ) = M{ 0.68067944, 0.73258144, 0, 0 } ,
//{ -0.73258144, 0.68067944, 0, 0 } ,
//{ 0, 0, 1, 0 } ,
//{ 0, 0, 0, 1 }