#pragma once
#include "ML_ArrayList.h"

namespace ML
{
	namespace DSA
	{
		template <class T>
		class BinaryHeap : protected array_list<T>
		{
			void swap( size_t lhs , size_t rhs )
			{
				this->array[ lhs ] ^= this->array[ rhs ] ^= this->array[ lhs ] ^= this->array[ rhs ];
			}

			size_t GetParent( size_t index )
			{
				return ( index - 1 ) * 0.5f;
			}

			size_t GetFirst( size_t index )
			{
				return index * 2 + 1;
			}

			void bubble_down( size_t root )
			{
				size_t rank = GetFirst( root );

				if( rank >= this->m_size )
				{
					return;
				}

				size_t next_rank = rank + 1;

				if( next_rank < this->m_size &&
					this->array[ next_rank ] < this->array[ rank ] )
				{
					rank = next_rank;
				}

				if( this->array[ rank ] < this->array[ root ] )
				{
					swap( rank , root );
					bubble_down( rank );
				}
			}

		public:

			void clear( )
			{
				array_list<T>::clear( );
			}

			unsigned int size( )
			{
				return this->m_size;
			}

			void push_heap( const T& new_data )
			{
				this->append( v );
				sort_heap( );
			}

			void pop_heap( )
			{
				switch( this->m_size )
				{
					case 0: break;
					case 1: { clear( ); } break;
					default:
					{
						swap( 0 , this->m_size - 1 );
						this->m_size--;
						bubble_down( 0 );
					}
				}
			}

			T front( )
			{
				return *this->m_data;
			}

			T dequeue( )
			{
				switch( this->m_size )
				{
					case 0: { return T( ); } break;
					case 1:
					{
						T temp = *this->array;
						clear( );
						return temp;
					}
					break;
					default:
					{
						T temp = *this->array;

						size_t last_child = this->m_size - 1;
						swap( 0 , last_child );

						this->array[ 0 ] = this->array[ lastIndex ];
						this->array[ lastIndex ] = 0;
						this->m_size--;

						bubble_down( 0 );

						return temp;
					}
				}
			}

			T& operator[]( int index )
			{
				return this->array[ index ];
			}

			void sort_heap( )
			{
				switch( this->m_size )
				{
					case 0:
					case 1: break;
					default:
					{
						for( int i = this->m_size - 1; i >= 0; --i )
						{
							bubble_down( i );
						}
					}
					break;
				}
			}
		};
	}// end namespace DSA
}// end namespace ML