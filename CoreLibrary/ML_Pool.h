#pragma once
/*
namespace ml3d
{
	template<typename T, int16_t N>
	class sorted_pool_t
	{
	public:
		// Todo: Implement the function bodies

		// Returns the number of active elements
		size_t size( )const
		{
			return active_count;
		}

		// Returns the maximum supported number of elements
		size_t capacity( )const
		{
			return sizeof( pool ) / sizeof( pool[0] );
		}

		// Returns the value at the specified index
		T& operator[]( int16_t index )
		{
			return T[index];
		}

		// Returns the value at the specified index
		const T& operator[]( int16_t index )const
		{
			return T[index];
		}

		// Returns the index of the first inactive element
		//   and updates the active count
		// Returns -1 if no inactive elements remain
		int16_t alloc( )
		{
			if( active_count == capacity( ) ) return -1;

			int16_t output = active_count;
			active_count++;
			return output;
		}

		// Moves the element at 'index' to the inactive
		// region and updates the active count
		void free( int16_t index )
		{
			// Swap the index with the active_count then decrement active_count.
			pool[index] ^= pool[active_count];
			pool[active_count] ^= pool[index];
			pool[index] ^= pool[active_count];
			active_count--;
		}

	private:

		T pool[N];

		int16_t active_count = 0;
	};

	template<typename T, int16_t N>
	class pool_t
	{
		// Todo: Implement the function bodies

		// Removes the first element from the free list and returns its index
		// Returns -1 if no free elements remain
		int16_t alloc( )
		{
			unsigned int index = free_start;
			free_start = pool[index].next;
			return index;
		}

		// Adds 'index' to the free list
		void free( int16_t index )
		{
			pool[index].next = free_start;
			free_start = index;
		}

		// Initializes the free list
		pool_t( )
		{
			for( unsigned int i = 0; i < sizeof( pool ) / sizeof( pool[0] ); i++ )
			{
				pool[i].next = i + 1;
			}
		}

		// Returns the value at the specified index
		T& operator[]( int16_t index )
		{
			return pool[index];
		}

		// Returns the value at the specified index
		const T& operator[]( int16_t index )const
		{
			return pool[index];
		}

	private:

		union element_t
		{
			T value;
			int16_t next;
		};

		element_t pool[N];

		int16_t free_start = 0;
	};
}
*/