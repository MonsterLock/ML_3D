#pragma once
namespace ml3d
{
	namespace DSA
	{
		template <class Type>
		class sl_list_iter;

		template <class Type>
		class sl_list
		{
			friend class sl_list_iter<Type>;

			struct Node
			{
				Type data;
				Node* next;

				Node( const Type& new_data ) : data( new_data ) , next( nullptr ) { }
				Node( const Type& new_data, const Node* new_next ) : data( new_data ) , next( new_next ) { }
			};

			Node* m_head;
			unsigned int m_size;

		public:
			sl_list( ) : m_head( nullptr ) , m_size( 0 ) { }

			~sl_list( ) { clear( ); }

			sl_list<Type>& operator=( const sl_list<Type>& rhs )
			{
				if( this != &rhs )
				{
					clear( );

					if( rhs.m_head )
					{
						m_head = new Node( rhs.m_head->data );

						Node* current = rhs.m_head->next;
						Node* newNode = m_head;

						while( current )
						{
							newNode->next = new Node( current->data );
							newNode = newNode->next;
							current = current->next;
						}

						m_size = rhs.m_size;
					}
				}
				return *this;
			}

			sl_list( const sl_list<Type>& rhs )
			{

				m_head = nullptr;
				*this = rhs;
			}

			void push_front( const Type& new_data )
			{
				Node* new_node = new Node( new_data );
				new_node->next = m_head;
				m_head = new_node;
				m_size++;
			}

			void clear( )
			{
				while( m_head )
				{
					Node* delete_node = m_head;
					m_head = m_head->next;
					delete delete_node;
				}

				m_size = 0;
			}

			void insert( sl_list_iter<Type>& iter , const Type& new_data )
			{
				if( iter.m_current )
				{
					Node* new_node = new Node( new_data, iter.m_current );

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

			void remove( sl_list_iter<Type>& iter )
			{
				if( iter.m_current )
				{
					Node* deleteNode = iter.m_current;

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

			inline unsigned int size( ) const
			{
				return m_size;
			}

		};

		template <class Type>
		class sl_list_iter
		{
			friend class sl_list<Type>;
			typename sl_list<Type>::Node* m_current;
			typename sl_list<Type>::Node* m_previous;
			sl_list<Type>* m_list;

		public:
			sl_list_iter( sl_list<Type>& list )
			{
				m_list = &list;
				begin( );
			}

			void begin( )
			{
				m_current = pointerList->m_head;
				m_previous = nullptr;
			}

			bool end( ) const
			{
				return m_current ? false : true;
			}

			sl_list_iter<Type>& operator++( )
			{
				if( !end( ) )
				{
					m_previous = m_current;
					m_current = m_current->next;
				}
				return *this;
			}

			Type& current( ) const
			{
				return m_current->data;
			}
		};
	}
}