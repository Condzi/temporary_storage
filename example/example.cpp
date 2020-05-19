#include "my_temporary_storage.hpp"

#include <iostream>

int main()
{
	void* my_program_memory = std::malloc( 512 );
	hi::Temporary_Storage temp_storage;

	temp_storage.set_instance( &temp_storage );
	// You can specify how much memory the storage can use.
	temp_storage.set_memory( my_program_memory, 256 );

	// @ToDo: maybe add allocate<T>( amount ) that does this?
	char* my_buffer = reinterpret_cast<char*>( temp_storage.allocate( sizeof( char ) * 16 ) );
	snprintf( my_buffer, 16, "Oh, Hi %s!", "Mark" );
	std::puts( my_buffer );

	// We can use it as global. Here we're setting the mark to 0 -- "freeing" the space.
	hi::Temporary_Storage::get_instance()->reset();

	my_buffer = reinterpret_cast<char*>( temp_storage.allocate( sizeof( char ) * 50 ) );

	snprintf( my_buffer, 50, "Highest mark = %i", temp_storage.get_highest_mark() );
	std::puts( my_buffer );

	std::free( my_program_memory );
}