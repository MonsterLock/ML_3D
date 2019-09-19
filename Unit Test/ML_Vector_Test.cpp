#include "CppUnitTest.h"

#include "../CoreLibrary/ML_Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	using namespace ML::MATH::Vector;

	TEST_CLASS( VectorTest )
	{
	public:
		TEST_METHOD( VectorConstructor )
		{
			float x = -2.0f;
			float y = 0.0f;
			float z = -4.0f;
			float w = 1.0f;

			vector v1;

			Assert::IsTrue( v1.x == 0.0f );
			Assert::IsTrue( v1.y == 0.0f );
			Assert::IsTrue( v1.z == 0.0f );
			Assert::IsTrue( v1.w == 0.0f );

			vector v2( x , y );

			Assert::IsTrue( v2.x == x );
			Assert::IsTrue( v2.y == y );
			Assert::IsTrue( v2.z == 0.0f );
			Assert::IsTrue( v2.w == 0.0f );

			vector v3( x , y , z );

			Assert::IsTrue( v3.x == x );
			Assert::IsTrue( v3.y == y );
			Assert::IsTrue( v3.z == z );
			Assert::IsTrue( v3.w == 0.0f );

			vector v4( x , y , z , w );

			Assert::IsTrue( v4.x == x );
			Assert::IsTrue( v4.y == y );
			Assert::IsTrue( v4.z == z );
			Assert::IsTrue( v4.w == w );

			vector v5( -2.0f , 0.0f , -4.0f , 1.0f );

			Assert::IsTrue( v5.x == x );
			Assert::IsTrue( v5.y == y );
			Assert::IsTrue( v5.z == z );
			Assert::IsTrue( v5.w == w );
		}
		TEST_METHOD( VectorAssignentOperator )
		{
			float x = -2.0f;
			float y = 0.0f;
			float z = -4.0f;
			float w = 1.0f;

			vector v1 = { x, y, z, w };

			Assert::IsTrue( v1.x == x );
			Assert::IsTrue( v1.y == y );
			Assert::IsTrue( v1.z == z );
			Assert::IsTrue( v1.w == w );

			vector v2 = v1;

			Assert::IsTrue( v2.x == x );
			Assert::IsTrue( v2.y == y );
			Assert::IsTrue( v2.z == z );
			Assert::IsTrue( v2.w == w );
		}
		TEST_METHOD( VectorAdditionOperators )
		{
			vector v1( 1 , -2 , -9 , 1 );
			vector v2( -9 , -8 , -6 , -8 );
			vector result1( -8 , -10 , -15 , -7 );

			vector output1 = v1 + v2;
			Assert::IsTrue( output1 == result1 );

			vector output2 = v1;
			output2 += v2;
			Assert::IsTrue( output2 == result1 );

			vector v3( 6 , -2 , 7 , 0 );
			vector v4( 8 , 1 , -2 , 0 );
			vector result2( 14 , -1 , 5 , 0 );

			vector output3 = v3 + v4;
			Assert::IsTrue( output3 == result2 );

			vector output4 = v3;
			output4 += v4;
			Assert::IsTrue( output4 == result2 );
		}
		TEST_METHOD( VectorSubtractionOperators )
		{
			vector v1( 6 , 7 , 7 , -6 );
			vector v2( -3 , -8 , -2 , -3 );
			vector result1( 9 , 15 , 9 , -3 );

			vector output1 = v1 - v2;
			Assert::IsTrue( output1 == result1 );

			vector output2 = v1;
			output2 -= v2;
			Assert::IsTrue( output2 == result1 );

			vector v3( -6 , -9 , 4 , 0 );
			vector v4( -8 , -2 , 7 , 0 );
			vector result2( 2 , -7 , -3 , 0 );

			vector output3 = v3 - v4;
			Assert::IsTrue( output3 == result2 );

			vector output4 = v3;
			output4 -= v4;
			Assert::IsTrue( output4 == result2 );
		}
		TEST_METHOD( VectorScalarMultiply )
		{
			vector v1( -9 , 3 , 4 , 5 );
			float f1 = -4;
			vector result1( 36 , -12 , -16 , -20 );

			vector output1 = v1 * f1;
			Assert::IsTrue( output1 == result1 );

			vector output2 = v1;
			output2 *= f1;
			Assert::IsTrue( output2 == result1 );

			vector v2( -4 , -2 , -4 , 8 );
			float f2 = 2;
			vector result2( -8 , -4 , -8 , 16 );

			vector output3 = v2 * f2;
			Assert::IsTrue( output3 == result2 );

			vector output4 = v2;
			output4 *= f2;
			Assert::IsTrue( output4 == result2 );

			vector v3( -4 , 1 , -6 , 7 );
			float f3 = 8;
			vector result3( -32 , 8 , -48 , 56 );

			vector output5 = v3 * f3;
			Assert::IsTrue( output5 == result3 );

			vector output6 = v3;
			output6 *= f3;
			Assert::IsTrue( output6 == result3 );
		}
		TEST_METHOD( VectorNegate )
		{
			vector v1( 8 , 5 , -6 , -5 );
			vector result1( -8 , -5 , 6 , 5 );

			vector output1( -v1 );
			Assert::IsTrue( output1 == result1 );

			vector v2( 5 , 3 , -3 , 5 );
			vector result2( -5 , -3 , 3 , -5 );

			vector output2( -v2 );
			Assert::IsTrue( output2 == result2 );
		}

		TEST_METHOD( VectorAngleBetween )
		{
			vector v1( 5 , 2 , -3 , 0 );
			vector v2( 8 , 8 , 1 , 0 );
			float result1 = 0.712104f;

			float output1 = AngleBetween( v1 , v2 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output1 , result1 ) );

			vector v3( 0 , 0 , 0 , 0 );
			vector v4( 8 , -4 , -7 , 0 );
			float result2 = 0.0f;

			float output2 = AngleBetween( v3 , v4 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output2 , result2 ) );

			vector v5( -3 , -3 , -8 , 0 );
			vector v6( 0 , 0 , 0 , 0 );
			float result3 = 0;

			float output3 = AngleBetween( v5 , v6 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output3 , result3 ) );

			vector v7( 0 , 0 , 0 , 0 );
			vector v8( 0 , 0 , 0 , 0 );
			float result4 = 0.0f;

			float output4 = AngleBetween( v7 , v8 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output4 , result4 ) );

			vector v9( 2 , -8 , -5 , -3 );
			vector v10( 4 , 4 , 3 , 1 );
			float result5 = 2.2674946f;

			float output5 = AngleBetween( v9 , v10 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output5 , result5 ) );

			vector v11( 0 , 0 , 0 , 0 );
			vector v12( -6 , -6 , 5 , -7 );
			float result6 = 0.0f;

			float output6 = AngleBetween( v11 , v12 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output6 , result6 ) );

			vector v13( -8 , 4 , 7 , -2 );
			vector v14( 0 , 0 , 0 , 0 );
			float result7 = 0.0f;

			float output7 = AngleBetween( v13 , v14 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output7 , result7 ) );
		}
		TEST_METHOD( VectorAverage )
		{
			vector v1( -4 , 5 , 3 , 2 );
			vector v2( -9 , 8 , -1 , -8 );
			vector result1( -6.5 , 6.5 , 1 , -3 );

			vector output1 = Average( v1 , v2 );
			Assert::IsTrue( output1 == result1 );

			vector v3( -1 , -1 , -6 , 0 );
			vector v4( -6 , 6 , -8 , 0 );
			vector result2( -3.5 , 2.5 , -7 , 0 );

			vector output2 = Average( v3 , v4 );
			Assert::IsTrue( output2 == result2 );

			vector v5( -6 , 3 , 8 , 0 );
			vector v6( 0 , 1 , -9 , 0 );
			vector result3( -3 , 2 , -0.5 , 0 );

			vector output3 = Average( v5 , v6 );
			Assert::IsTrue( output3 == result3 );
		}
		TEST_METHOD( VectorClampLength )
		{
			float clamp1 = 3.464101f;

			vector v1( 8 , 9 , 3 , 0 );
			v1.ClampLength( clamp1 );
			float result1 = v1.Length();

			Assert::IsTrue( ML::MATH::IsAboutEqual( result1 , clamp1 ) );

			vector v2( -8 , -9 , -3 , 0 );
			v2.ClampLength( clamp1 );
			float result2 = v2.Length();

			Assert::IsTrue( ML::MATH::IsAboutEqual( result2 , clamp1 ) );
		}
		TEST_METHOD( VectorComponent )
		{
			vector v1( -5 , 8 , 6 , 0 );
			vector v2( -3 , 2 , -6 , 0 );
			float result1 = -0.71428537f;

			float output1 = Component( v1 , v2 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output1 , result1 ) );

			vector v3( 6 , 4 , 4 , 0 );
			vector v4( 0 , 0 , 0 , 0 );
			float result2 = 0;

			float output2 = Component( v3 , v4 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output2 , result2 ) );

			vector v5( 8 , 3 , -6 , -4 );
			vector v6( 0 , 2 , 6 , -1 );
			float result3 = -4.0605173f;

			float output3 = Component( v5 , v6 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output3 , result3 ) );

			vector v7( 3 , 3 , -2 , -8 );
			vector v8( 0 , 0 , 0 , 0 );
			float result4 = 0;

			float output4 = Component( v7 , v8 );
			Assert::IsTrue( ML::MATH::IsAboutEqual( output4 , result4 ) );
		}
		TEST_METHOD( VectorCrossProduct )
		{
			vector v1( -2 , 5 , 4 , 0 );
			vector v2( -6 , 8 , 2 , 0 );
			vector result1( -22 , -20 , 14 , 1 );

			vector output1 = Cross( v1 , v2 );
			Assert::IsTrue( output1 == result1 );

			vector v3( 6 , 6 , 8 , -9 );
			vector v4( -2 , 7 , 6 , -3 );
			vector result2( -20 , -52 , 54 , 1 );

			vector output2 = Cross( v3 , v4 );
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorDistanceBetween )
		{
			vector v1( -7 , -2 , 1 , 0 );
			vector v2( -4 , 2 , 7 , 0 );
			float result1 = 7.81025f;

			float output1 = DistanceBetween( v1 , v2 );
			Assert::IsTrue( output1 == result1 );

			vector v3( -7 , -2 , 1 , 7 );
			vector v4( -4 , 2 , 7 , 8 );
			float result2 = 7.81025f;

			float output2 = DistanceBetween( v3 , v4 );
			Assert::IsFalse( output2 == result2 );

			vector v5( 0,0,0,0 );
			vector v6( 0,0,0,0 );
			float result3 = 0;

			float output3 = DistanceBetween( v5 , v6 );
			Assert::IsTrue( output3 == result3 );
		}
		TEST_METHOD( VectorDotProduct )
		{
			vector v1( -7 , -2 , 1 , -2 );
			vector v2( -4 , 2 , 7 , 5 );
			float result1 = 21.0f;

			float output1 = v1 * v2;
			Assert::IsTrue( output1 == result1 );

			vector v3( 0 , -1 , 6 , -7 );
			vector v4( -7 , 8 , 3 , -2 );
			float result2 = 24.0f;

			float output2 = v3 * v4;
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorHomogenize )
		{
			vector v1( -5, -1, 3, -3 );
			vector result1( 1.6666667f, 0.33333334f, -1, 1 );

			vector output1(Homogenize(v1));
			Assert::IsTrue( output1 == result1 );

			vector v2( 6, 7, -8, 0 );
			vector result2( 0, 0, 0, 0 );

			vector output2(Homogenize(v2));
			Assert::IsTrue( output2 == result2 );

			vector v3( -5, -1, 3, -3 );
			v3.Homogenize( );
			Assert::IsTrue( v3 == result1 );

			vector v4( 6, 7, -8, 0 );
			v4.Homogenize( );
			Assert::IsTrue( v4 == v2 );
		}
		TEST_METHOD( VectorIsExact )
		{
			vector v1( 0.7475667940f, 0.2210000239f, 0.6492298694f, 0.3385129473f );
			vector v2( 0.7475667940f, 0.2210000239f, 0.6492298694f, 0.3385129473f );
			vector v3( 0.7475f, 0.2210f, 0.6492f, 0.3385f );

			Assert::IsTrue( IsExact(v1, v2 ) );
			Assert::IsFalse( IsExact(v1, v3 ) );
		}
		TEST_METHOD( VectorLength )
		{
			vector v1( 4 , -5 , 1 , -9 );
			float result1 = 11.090536f;

			float output1 = v1.Length( );
			Assert::IsTrue( output1 == result1 );

			vector v2( -8 , -1 , -9 , -5 );
			float result2 = 13.076696f;

			float output2 = v2.Length( );
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorLengthSquare )
		{
			vector v1( -6 , 2 , -2 , 0 );
			float result1 = 44;

			float output1 = v1.LengthSq( );
			Assert::IsTrue( output1 == result1 );

			vector v2( -1 , -1 , -5 , 8 );
			float result2 = 91;

			float output2 = v2.LengthSq( );
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorLerp )
		{
			vector v1( 1 , 2 , -2 , 2 );
			vector v2( 2 , 1 , 2 , -2 );

			float lerp1 = 0.75f;
			vector result1( 1.75f , 1.25f , 1 , -1 );

			vector output1( Lerp( v1 , v2 , lerp1 ) );
			Assert::IsTrue( output1 == result1 );

			float lerp2 = -0.75f;
			vector result2( 0.25f , 2.75f , -5 , 5 );

			vector output2( Lerp( v1 , v2 , lerp2 ) );
			Assert::IsTrue( output2 == result2 );

			float lerp3 = 1.75f;
			vector result3( 2.75f , 0.25f , 5 , -5 );

			vector output3( Lerp( v1 , v2 , lerp3 ) );
			Assert::IsTrue( output3 == result3 );
		}
		TEST_METHOD( VectorMax )
		{
			vector v1( -4 , 5 , -2 , -9 );
			vector v2( -4 , 2 , -4 , 0 );
			vector result1( -4 , 5 , -2 , 0 );

			vector output1 = Max( v1 , v2 );
			Assert::IsTrue( output1 == result1 );

			vector v3( 3 , 8 , -2 , -2 );
			vector v4( -6 , 7 , -3 , 1 );
			vector result2( 3 , 8 , -2 , 1 );

			vector output2 = Max( v3 , v4 );
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorMin )
		{
			vector v1( 1 , 7 , 7 , -6 );
			vector v2( -7 , 8 , 0 , -5 );
			vector result1( -7 , 7 , 0 , -6 );

			vector output1 = Min( v1 , v2 );
			Assert::IsTrue( output1 == result1 );

			vector v3( -9 , 1 , 5 , 5 );
			vector v4( 4 , -2 , 0 , 3 );
			vector result2( -9 , -2 , 0 , 3 );

			vector output2 = Min( v3 , v4 );
			Assert::IsTrue( output2 == result2 );
		}
		TEST_METHOD( VectorNormalize )
		{
			vector v1( -9 , 1 , 0 , 5 );
			vector result1( -0.87006289f , 0.096673653f , 0 , 0.48336828f );

			v1.Normalize( );
			Assert::IsTrue( v1 == result1 );

			vector v2( -4 , -7 , -1 , 2 );
			vector result2( -0.47809145f , -0.83666003f , -0.11952286f , 0.23904572f );

			v2.Normalize( );
			Assert::IsTrue( v2 == result2 );

			vector v3( 0 , 0 , 0 , 0 );
			vector result3( 0 , 0 , 0 , 0 );

			v3.Normalize( );
			Assert::IsTrue( v3 == result3 );

		}
		TEST_METHOD( VectorProject )
		{
			vector v1( 7 , 6 , 6 , 0 );
			vector v2( 2 , 3 , 3 , 0 );
			vector result1( 4.5454545f , 6.8181815f , 6.8181815f , 0 );

			vector output1(Projection(v1, v2));
			Assert::IsTrue( output1 == result1 );

			vector v3( -4 , 0 , 6 , 0 );
			vector v4( 0 , 0 , 0 , 0 );
			vector result2( 0 , 0 , 0 , 0 );

			vector output2(Projection(v3, v4));
			Assert::IsTrue( output2 == result2 );

			vector v5( -9 , -8 , 0 , 5 );
			vector v6( 0 , 7 , -9 , -1 );
			vector result3( -0 , -3.2595417f , 4.1908393f , 0.46564883f );

			vector output3(Projection(v5, v6));
			Assert::IsTrue( output3 == result3 );

			vector v7( -2 , -5 , 3 , 7 );
			vector v8( 0 , 0 , 0 , 0 );
			vector result4( 0 , 0 , 0 , 0 );

			vector output4(Projection(v7, v8));
			Assert::IsTrue( output4 == result4 );
		}
		TEST_METHOD( VectorReflect )
		{
			vector v1( 2 , 2 , 5 , 0 );
			vector v2( 7 , -7 , -3 , 0 );
			vector result1( -3.9626169f , -0.03738296f , -4.1588783f , -0 );

			vector output1(Reflection(v1, v2));
			Assert::IsTrue( output1 == result1 );

			vector v3( 3 , -8 , 0 , 0 );
			vector v4( 0 , 0 , 0 , 0 );
			vector result2( -3, 8, -0, -0 );

			vector output2(Reflection(v3, v4));
			Assert::IsTrue( output2 == result2 );

			vector v5( -1 , 4 , -7 , -8 );
			vector v6( 5 , 2 , -7 , -1 );
			vector result3( 8.5949373f , -0.96202517f , -3.6329117f , 6.4810123f );

			vector output3(Reflection(v5, v6));
			Assert::IsTrue( output3 == result3 );

			vector v7( -4 , -4 , 7 , 6 );
			vector v8( 0 , 0 , 0 , 0 );
			vector result4( 4 , 4 , -7 , -6 );

			vector output4(Reflection(v7, v8));
			Assert::IsTrue( output4 == result4 );

			vector v9( -5 , -2 , -7 , 0 );
			vector v10( 1 , 0 , 0 , 0 );
			vector result5( -5 , 2 , 7 , -0 );

			vector output5(Reflection(v9, v10));
			Assert::IsTrue( output5 == result5 );
		}
	};
}