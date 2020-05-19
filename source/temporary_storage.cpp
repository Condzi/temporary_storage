#include "temporary_storage.hpp"

namespace con
{
void Temporary_Storage::set_instance( Temporary_Storage* instance_ )
{
	instance = instance_;
}

auto Temporary_Storage::get_instance() -> Temporary_Storage*
{
	return instance;
}

void Temporary_Storage::set_memory( void* mem, int32_t size_ )
{
	CON_ASSERT( mem != nullptr );
	CON_ASSERT( size_ > 0 );

	data = mem;
	size = size_;
	mark = 0;
#ifdef CON_MEASURE_HIGHEST_MARK 
	highest_mark = 0;
#endif
}

void Temporary_Storage::set_mark( int32_t new_mark )
{
	CON_ASSERT( new_mark >= 0 );

	mark = new_mark;
}

void Temporary_Storage::reset()
{
	mark = 0;
}

auto Temporary_Storage::allocate( int32_t size_ ) -> void*
{
	using byte = uint8_t;

	// @ToDo: Add CON_SMALL_ASSERT for stuff like bounds checking?
	CON_ASSERT( size_ );
	CON_ASSERT( mark + size_ < size );

	void* requested_memory = ( reinterpret_cast<byte*>( data ) + mark );
	mark += size_;

#ifdef CON_MEASURE_HIGHEST_MARK
	if ( mark > highest_mark ) {
		highest_mark = mark;
	}
#endif

	return requested_memory;
}

auto Temporary_Storage::get_current_mark() -> int32_t
{
	return mark;
}

auto Temporary_Storage::get_highest_mark() -> int32_t
{
#ifdef CON_MEASURE_HIGHEST_MARK
	return highest_mark;
#else
	return -1;
#endif
}

auto Temporary_Storage::get_size() -> int32_t
{
	return size;
}

auto Temporary_Storage::get_raw_data() -> void*
{
	return data;
}
}