/*
R.A. Bickell [https://github.com/MonsterLock]
ML_ArrayList.h Last Updated: 2019-09-19 06::38::45 AM
*/
#pragma once
#include <algorithm>

namespace ML
{
	namespace DSA
	{
		template <class T>
		class array_list
		{
		protected:
			T*     m_data;
			size_t m_size;
			size_t m_capacity;

		public:
			array_list              ( ) noexcept;
			array_list              ( const array_list<T> &rhs ) noexcept;
			~array_list             ( );

			array_list<T> &operator=( const array_list<T> &rhs );
			T& operator[]           ( const size_t index );
			const T& operator[]     ( const size_t index ) const;

			size_t size             ( ) const;
			size_t capacity         ( ) const;

			void clear              ( );
			void push_back          ( const T& data );
			void reserve            ( );
			void reserve            ( const size_t& new_cap );
		}; // end class array_list

		template<typename T>
		inline array_list<T>::array_list( ) noexcept : m_data( nullptr ) , m_size( 0 ) , m_capacity( 0 ) { }

		template<class T>
		inline array_list<T>::array_list( const array_list<T>& rhs ) noexcept
			: m_data( nullptr ) , m_size( 0 ) , m_capacity( 0 ) { *this = rhs; }

		template<class T>
		inline array_list<T>::~array_list( ) { delete[ ] m_data; }

		template<class T>
		inline array_list<T>& array_list<T>::operator=( const array_list<T>& rhs )
		{
			if( this != &rhs )
			{
				m_size = rhs.m_size;
				m_capacity = rhs.m_capacity;

				delete[ ] m_data;
				m_data = new T[ rhs.m_capacity ];

				std::copy( rhs.m_data , rhs.m_data + m_size , m_data );
			}

			return *this;
		}
		template<class T>
		inline T & array_list<T>::operator[]( const size_t index ) { return m_data[ index ]; }

		template<class T>
		inline const T & array_list<T>::operator[]( const size_t index ) const { return m_data[ index ]; }

		template<class T>
		inline size_t array_list<T>::size( ) const { return m_size; }

		template<class T>
		inline size_t array_list<T>::capacity( ) const { return m_capacity; }

		template<class T>
		inline void array_list<T>::clear( )
		{
			delete[ ] m_data;
			m_data = nullptr;
			m_size = m_capacity = 0;
		}

		template<class T>
		inline void array_list<T>::push_back( const T & data )
		{
			if( m_size == m_capacity )
			{
				reserve( );
			}
			m_data[ m_size ] = data;
			m_size++;
		}

		template<class T>
		inline void array_list<T>::reserve( )
		{
			switch( m_capacity )
			{
				case 0: { m_capacity = 1; } break;
				default: { m_capacity *= 2; } break;
			}

			T* temp = new T[ m_capacity ];
			std::copy( m_data , m_data + m_size , temp );
			delete[ ] m_data;
			m_data = temp;
		}

		template<class T>
		inline void array_list<T>::reserve( const size_t & new_cap )
		{
			if( new_cap <= m_capacity ) { return; }

			m_capacity = new_cap;

			T* temp = new T[ m_capacity ];
			std::copy( m_data , m_data + m_size , temp );
			delete[ ] m_data;
			m_data = temp;
		}
	} // end namespace DSA
} // end namespace ML

// Feature(s)
//