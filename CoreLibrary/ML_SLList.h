#pragma once
namespace ML
{
	namespace DSA
	{
		template <class Type>
		class sl_list_iter;

		template <class Type>
		class sl_list
		{
			friend class sl_list_iter<Type>;

			struct sl_node
			{
				Type data;
				sl_node* next;

				sl_node( const Type& new_data ) noexcept;
				sl_node( const Type& new_data , const sl_node* new_next ) noexcept;
			};// end struct sl_node

			sl_node* m_head;
			size_t m_size;

		public:
			sl_list( ) noexcept;
			sl_list( const sl_list<Type>& );
			~sl_list( );

			sl_list<Type>& operator=( const sl_list<Type>& );

			size_t size( ) const;

			sl_list_iter<Type> begin( );
			sl_list_iter<Type> end( );

			void push_front( const Type& );
			void clear( );
			void insert( sl_list_iter<Type>& , const Type& );
			void remove( sl_list_iter<Type>& );
		};// end class sl_list

		template <class Type>
		class sl_list_iter
		{
			friend class sl_list<Type>;

			typename sl_list<Type>::sl_node* m_current;
			typename sl_list<Type>::sl_node* m_previous;
			sl_list<Type>* m_list;

		public:
			sl_list_iter( ) noexcept;
			sl_list_iter( sl_list<Type>& list ) noexcept;

			sl_list_iter<Type>& operator++( );
			sl_list_iter<Type>& operator++( int );
			sl_list_iter<Type>& operator=( const sl_list_iter<Type>& );

			bool operator==( const sl_list_iter<Type>& );
			bool operator!=( const sl_list_iter<Type>& );

			Type& operator*( ) const;
		}; // end class sl_list_iter

		   //---------------------------------------------------- sl_node
		template<class Type>
		inline sl_list<Type>::sl_node::sl_node( const Type & new_data ) noexcept : data( new_data ) , next( nullptr ) { }

		template<class Type>
		inline sl_list<Type>::sl_node::sl_node( const Type & new_data , const sl_node * new_next ) noexcept
			: data( new_data ) , next( new_next ) { }

		//---------------------------------------------------- sl_list
		template<class Type>
		inline sl_list<Type>::sl_list( ) noexcept : m_head( nullptr ) , m_size( 0 ) { }

		template<class Type>
		inline sl_list<Type>::sl_list( const sl_list<Type>& rhs )
			: m_head( nullptr ) { *this = rhs; }

		template<class Type>
		inline sl_list<Type>::~sl_list( ) { clear( ); }

		template<class Type>
		inline sl_list<Type>& sl_list<Type>::operator=( const sl_list<Type>& rhs )
		{
			if( this != &rhs )
			{
				clear( );

				if( rhs.m_head )
				{
					m_head = new sl_node( rhs.m_head->data );

					sl_node* current = rhs.m_head->next;
					sl_node* newNode = m_head;

					while( current )
					{
						newNode->next = new sl_node( current->data );
						newNode = newNode->next;
						current = current->next;
					}

					m_size = rhs.m_size;
				}
			}
			return *this;
		}

		template<class Type>
		inline size_t sl_list<Type>::size( ) const
		{
			return m_size;
		}

		template<class Type>
		inline sl_list_iter<Type> sl_list<Type>::begin( )
		{
			return sl_list_iter<Type>( *this );
		}

		template<class Type>
		inline sl_list_iter<Type> sl_list<Type>::end( )
		{
			return sl_list_iter<Type>();
		}

		template<class Type>
		inline void sl_list<Type>::push_front( const Type & new_data )
		{
			sl_node* new_node = new sl_node( new_data );
			new_node->next = m_head;
			m_head = new_node;
			m_size++;
		}

		template<class Type>
		inline void sl_list<Type>::clear( )
		{
			while( m_head )
			{
				sl_node* delete_node = m_head;
				m_head = m_head->next;
				delete delete_node;
			}

			m_size = 0;
		}

		template<class Type>
		inline void sl_list<Type>::insert( sl_list_iter<Type>& iter , const Type & new_data )
		{
			if( iter.m_current )
			{
				sl_node* new_node = new sl_node( new_data, iter.m_current );

				if( iter.m_previous )
				{
					iter.m_previous->next = iter.m_current = new_node;
				}
				else
				{
					m_head = iter.m_current = new_node;
				}

				m_size++;
			}
		}

		template<class Type>
		inline void sl_list<Type>::remove( sl_list_iter<Type>& iter )
		{
			if( iter.m_current )
			{
				sl_node* deleteNode = iter.m_current;

				if( iter.m_previous )
				{
					iter.m_previous->next = iter.m_current = iter.m_current->next;
				}
				else
				{
					m_head = iter.m_current = iter.m_current->next;
				}

				delete deleteNode;
				m_size--;
			}
		}

		//---------------------------------------------------- sl_list_iter
		template<class Type>
		inline sl_list_iter<Type>::sl_list_iter( ) noexcept
			: m_list( nullptr ) , m_current( nullptr ) , m_previous( nullptr ) { }

		template<class Type>
		inline sl_list_iter<Type>::sl_list_iter( sl_list<Type>& list ) noexcept
			: m_list( &list ) , m_current( list.m_head ) , m_previous( nullptr ) { }

		template<class Type>
		inline sl_list_iter<Type>& sl_list_iter<Type>::operator++( )
		{
			m_previous = m_current;
			m_current = m_current->next;
			return *this;
		}

		template<class Type>
		inline sl_list_iter<Type>& sl_list_iter<Type>::operator++( int )
		{
			m_previous = m_current;
			m_current = m_current->next;
			return *this;
		}

		template<class Type>
		inline sl_list_iter<Type>& sl_list_iter<Type>::operator=( const sl_list_iter<Type>& rhs )
		{
			if( this != &rhs )
			{
				m_current = rhs.m_current;
				m_previous = rhs.m_previous;
				m_list = rhs.m_list;
			}
			return *this;
		}

		template<class Type>
		inline bool sl_list_iter<Type>::operator==( const sl_list_iter<Type>& rhs )
		{
			return m_current == rhs.m_current ? true : false;
		}

		template<class Type>
		inline bool sl_list_iter<Type>::operator!=( const sl_list_iter<Type>& rhs )
		{
			return m_current == rhs.m_current ? false : true;
		}

		template<class Type>
		inline Type & sl_list_iter<Type>::operator*( ) const
		{
			return m_current->data;
		}

}// end namespace DSA
}// end namespace ML