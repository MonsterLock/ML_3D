#pragma once
#include <cstring>

namespace ml3d
{
	namespace DSA
	{
		template <class Type>
		class array
		{
		protected:
			Type* m_data;
			unsigned int m_size;
			unsigned int m_capacity;

		public:
			array( ) : m_data( nullptr ) , m_size( 0 ) , m_capacity( 0 ) { }

			~array( ) { delete[ ] m_data; }

			array( const array<Type> &rhs ) : m_data( nullptr ) { *this = rhs; }

			array<Type> &operator=( const array<Type> &rhs )
			{
				if( this != &rhs )
				{
					m_size = rhs.m_size;
					m_capacity = rhs.m_capacity;

					delete[ ] m_data;
					m_data = new Type[ rhs.m_capacity ];

					memcpy( m_data , rhs.m_data , sizeof( Type ) * m_size );
				}

				return *this;
			}

			Type& operator[]( const unsigned int index ) { return m_data[ index ]; }

			const Type& operator[]( const unsigned int index ) const { return m_data[ index ]; }

			unsigned int size( ) const { return m_size; }

			unsigned int capacity( ) const { return m_capacity; }

			void clear( )
			{
				delete[ ] m_data;
				m_data = nullptr;
				m_size = m_capacity = 0;
			}

			void push_back( const Type& data )
			{
				if( m_size == m_capacity )
				{
					reserve( );
				}
				m_data[ m_size ] = data;
				m_size++;
			}

			void reserve( )
			{
				switch( m_capacity )
				{
					case 0: { m_capacity = 1; } break;
					default: { m_capacity *= 2; } break;
				}

				Type* temp = new Type[ m_capacity ];
				memcpy( temp , m_data , sizeof( Type ) * m_size );
				delete[ ] m_data;
				m_data = temp;
			}

			void reserve( const unsigned int& new_cap )
			{
				if( new_cap <= m_capacity ) { return; }

				m_capacity = new_cap;

				Type* temp = new Type[ m_capacity ];
				memcpy( temp , m_data , sizeof( Type ) * m_size );
				delete[ ] m_data;
				m_data = temp;
			}
		};
	}
}