#include "my_temporary_storage.hpp"

#include <cstdlib>
#include <cstdio>

// Prints out passed number using temporary storage as buffer
inline void dummy_log( char const* fmt, int x )
{
	char* buff = reinterpret_cast<char*>( G_Temporary_Storage->allocate( sizeof( char ) * 32 ) );
	
	snprintf( buff, 32, fmt, x );
	puts( buff );
}


int main()
{
	void* my_program_memory = std::malloc( 512 );
	// This should be alive during entire program lifetime because it's
	// a global. You can have multiple Temporary Storage objects, but the
	// global one is only one. 
	hi::Temporary_Storage temp_storage;

	temp_storage.set_instance( &temp_storage );
	// You can specify how much memory the storage can use.
	temp_storage.set_memory( my_program_memory, 256 );


	dummy_log( "%i) Log.", 1 );
	dummy_log( "%i) Log.", 2 );
	dummy_log( "%i) Log.", 3 );
	dummy_log( "%i) Log.", 4 );
	// Put this in your game loop.
	temp_storage.reset();
	dummy_log( "Highest mem usage = %i", temp_storage.get_highest_mark() );
	

	// Let's say we know that we don't care about memory allocated here. We can save
	// space by saving current mark value (which is just basically amount of bytes used)
	// and setting it again after making a call to 'allocate' (which happens in dummy_log).
	int32_t saved_mark = temp_storage.get_current_mark();
	dummy_log( "Current mark = %i", saved_mark );
	dummy_log( "%ind call here...", 2 );
	temp_storage.set_mark( saved_mark );
	// should be the same as before the two dummy_log calls above.
	dummy_log( "Current mark = %i.", temp_storage.get_current_mark() );


	std::free( my_program_memory );
}