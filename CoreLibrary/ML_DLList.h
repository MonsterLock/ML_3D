#pragma once

namespace ML
{
	namespace DSA
	{
		template <class Type>
		class dl_list_iter;

		template<typename Type>
		class dl_list
		{

			friend class dl_list_iter<Type>;

			struct dl_node
			{
				Type data;
				dl_node *next;
				dl_node *prev;

				dl_node( const Type& new_data )
					: data( new_data ) , next( nullptr ) , prev( nullptr )
				{
				}
			};// end struct dl_node

			dl_node* m_head;
			dl_node* m_tail;
			size_t m_size;

		public:
			dl_list( ) : m_head( nullptr ) , m_tail( nullptr ) , m_size( 0 ) { }
			dl_list( const dl_list<Type>& that ) : m_head( nullptr ) , m_tail( nullptr ) , m_size( 0 ) { *this = that; }
			~dl_list( ) { clear( ); }

			dl_list<Type>& operator=( const dl_list<Type>& that )
			{
				if( this != &that )
				{
					clear( );

					if( that.m_head )
					{
						m_head = m_tail = new dl_node( that.m_head->data );
						dl_node* current = that.m_head->next;
						dl_node* new_node = m_head;

						while( current )
						{
							new_node = m_tail = new_node->next = new dl_node( current->data );
							current = current->next;
						}
						m_size = that.m_size;
					}
				}
				return *this;
			}

			void push_front( const Type& v )
			{
				dl_node* new_node = new dl_node( v );

				switch( this->m_size )
				{
					case 0:
					{
						m_tail = m_head = new_node;
					}
					break;
					default:
					{
						m_head->prev = new_node;
						new_node->next = m_head;
						m_head = new_node;
					}
					break;
				}

				m_size++;
			}

			void addTail( const Type& v )
			{
				dl_node* new_node = new dl_node( v );

				switch( this->m_size )
				{
					case 0:
					{
						m_tail = m_head = new_node;
					}
					break;
					default:
					{
						m_tail->next = new_node;
						new_node->prev = m_tail;
						m_tail = new_node;
					}
					break;
				}

				m_size++;
			}

			void clear( )
			{
				while( m_head )
				{
					dl_node* deleteNode = m_head;
					m_head = m_head->next;
					delete deleteNode;
				}
				m_head = m_tail = nullptr;
				m_size = 0;
			}

			void insert( dl_list_iter<Type>& index , const Type& v )
			{
				if( !index.currentNode )
				{
					return;
				}

				if( m_head == index.currentNode )
				{
					push_front( v );
				}
				else
				{
					dl_node* newNode = new dl_node( v );

					index.previousNode->next = newNode;
					index.currentNode->prev = newNode;
					newNode->next = index.currentNode;
					newNode->prev = index.previousNode;
					index.currentNode = newNode;

					m_size++;
				}
			}

			void remove( dl_list_iter<Type>& index )
			{
				if( !index.currentNode )
				{
					return;
				}

				switch( this->m_size )
				{
					case 0: return;
					case 1:
					{
						clear( );
						index.currentNode = nullptr;
						index.previousNode = nullptr;
					}
					break;
					default:
					{
						dl_node* deleteNode = index.currentNode;

						if( m_head == index.currentNode )
						{
							m_head = index.currentNode = index.currentNode->next;
							m_head->prev = index.previousNode;
							delete deleteNode;
						}
						else if( m_tail == index.currentNode )
						{
							m_tail = index.previousNode;
							index.previousNode->next = index.currentNode = nullptr;
							delete deleteNode;
						}
						else
						{
							index.previousNode->next = index.currentNode = index.currentNode->next;
							index.currentNode->prev = index.previousNode;
							delete deleteNode;
						}
						m_size--;
					}
					break;
				}
			}

		};//end class dl_list

		template <class Type>
		class dl_list_iter
		{
			friend class dl_list<Type>;
			typename dl_list<Type>::dl_node* currentNode;
			typename dl_list<Type>::dl_node* previousNode;
			dl_list<Type>* pointerList;

		public:
			dl_list_iter( dl_list<Type>& listToIterate )
			{
				pointerList = &listToIterate;
				beginHead( );
			}

			void beginHead( )
			{
				currentNode = pointerList->m_head;
				previousNode = nullptr;
			}

			void beginTail( )
			{
				currentNode = pointerList->m_tail;
				if( pointerList->m_tail )
				{
					previousNode = pointerList->m_tail->prev;
				}
			}

			bool end( ) const
			{
				if( currentNode )
				{
					return false;
				}
				else return true;
			}

			dl_list_iter<Type>& operator++( )
			{
				if( currentNode )
				{
					previousNode = currentNode;
					currentNode = currentNode->next;
				}
				return *this;
			}

			dl_list_iter<Type>& operator--( )
			{
				if( currentNode )
				{
					currentNode = previousNode;
					if( currentNode )
					{
						previousNode = currentNode->prev;
					}
				}
				return *this;
			}

			Type& current( ) const
			{
				return currentNode->data;
			}

		};//
	}// end namespace DSA
}// end namespace ML