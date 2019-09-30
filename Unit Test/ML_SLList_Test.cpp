///*
//R.A. Bickell [https://github.com/MonsterLock]
//ML_ArrayList_Test.cpp Last Updated: 2019-09-19 07::09::07 AM
//*/
//#include "CppUnitTest.h"
//
//#include "../CoreLibrary/ML_SLList.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTest
//{
//	using namespace ML::DSA;
//
//	TEST_CLASS( SLListTest )
//	{
//		struct test_value
//		{
//			enum
//			{
//				A = 'A', B, C, D, E, F, G, SIZE
//			};
//		};
//
//		struct test_capacity
//		{
//			enum
//			{
//				FIRST = 1,
//				SECOND = 2,
//				THIRD = 4,
//				FOURTH = 8,
//				FIFTH = 16,
//				SIXTH = 32,
//				SEVENTH = 64,
//				EIGHTH = 128,
//				NINTH = 256,
//				TENTH = 512
//			};
//		};
//
//	public:
//		TEST_METHOD( ArrayListPushBack )
//		{
//			array_list<size_t> test_array;
//
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array.push_back( i );
//			}
//
//			Assert::IsTrue( test_array.size( ) == 7 );
//
//			for( size_t i = 0; i < test_array.size( ); i++ )
//			{
//				Assert::IsTrue( test_array[i] == test_value::A + i );
//			}
//		}
//		TEST_METHOD( ArrayListReserve )
//		{
//			array_list<size_t> test_array;
//
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array.push_back( i );
//			}
//			Assert::IsTrue( test_array.capacity( ) == test_capacity::FOURTH );
//
//			test_array.reserve( 2 );
//
//			Assert::IsTrue( test_array.capacity( ) == test_capacity::FOURTH );
//
//			for( size_t i = 0; i < test_array.size( ); i++ )
//			{
//				Assert::IsTrue( test_array[i] == test_value::A + i );
//			}
//
//			test_array.reserve( 10 );
//
//			Assert::IsTrue( test_array.capacity( ) == 10 );
//
//			for( size_t i = 0; i < test_array.size( ); i++ )
//			{
//				Assert::IsTrue( test_array[i] == test_value::A + i );
//			}
//
//			test_array.push_back( 'H' );
//			test_array.push_back( 'I' );
//			test_array.push_back( 'J' );
//			test_array.push_back( 'K' );
//
//			Assert::IsTrue( test_array.capacity( ) == 20 );
//
//			for( size_t i = 0; i < test_array.size( ); i++ )
//			{
//				Assert::IsTrue( test_array[i] == test_value::A + i );
//			}
//		}
//		TEST_METHOD( ArrayListClear )
//		{
//			array_list<size_t> test_array;
//
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array.push_back( i );
//			}
//
//			test_array.clear( );
//
//			Assert::IsTrue( test_array.size() == 0 );
//			Assert::IsTrue( test_array.capacity() == 0 );
//			Assert::IsTrue( &test_array[0] == nullptr );
//
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array.push_back( i );
//			}
//
//			Assert::IsTrue( test_array.size( ) == 7 );
//			Assert::IsTrue( test_array.capacity( ) == test_capacity::FOURTH );
//
//			for( size_t i = 0; i < test_array.size( ); i++ )
//			{
//				Assert::IsTrue( test_array[i] == test_value::A + i );
//			}
//
//			test_array.clear( );
//			Assert::IsTrue( test_array.size() == 0 );
//			Assert::IsTrue( test_array.capacity() == 0 );
//			Assert::IsTrue( &test_array[0] == nullptr );
//		}
//		TEST_METHOD( ArrayListMemory )
//		{
//			array_list<size_t> test_array;
//
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array.push_back( i );
//			}
//
//			array_list<size_t> test_array2( test_array );
//
//			Assert::IsTrue( test_array2.capacity( ) == test_capacity::FOURTH );
//			Assert::IsTrue( test_array2.size( ) == 7 );
//
//			for( size_t i = 0; i < test_array2.size( ); i++ )
//			{
//				Assert::IsTrue( test_array2[i] == test_value::A + i );
//			}
//
//			array_list<size_t> test_array3;
//			for( size_t i = test_value::A; i < test_value::SIZE; i++ )
//			{
//				test_array3.push_back( i+5 );
//			}
//
//			test_array3 = test_array;
//
//			Assert::IsTrue( test_array3.capacity( ) == test_capacity::FOURTH );
//			Assert::IsTrue( test_array3.size( ) == 7 );
//
//			for( size_t i = 0; i < test_array3.size( ); i++ )
//			{
//				Assert::IsTrue( test_array3[i] == test_value::A + i );
//			}
//		}
//	};
//}