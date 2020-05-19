#pragma once

#include <cinttypes>
// Suit this for your need. (You can also define CON_ASSERT)
#define CON_USE_NODISCARD
#define CON_MEASURE_HIGHEST_MARK

#ifdef CON_USE_NODISCARD
#define CON_NODISCARD [[nodiscard]]
#else
#define CON_NODISCARD 
#endif

#ifndef CON_ASSERT
#include <cassert>
#define CON_ASSERT( x ) assert( x )
#endif

namespace con
{
class Temporary_Storage final
{
public:
	static void set_instance( Temporary_Storage* instance_ );
	CON_NODISCARD static auto get_instance() -> Temporary_Storage*;

	// also resets highest_mark
	void set_memory( void* mem, int32_t size_ );
	void set_mark( int32_t new_mark );

	void reset();

	CON_NODISCARD auto allocate( int32_t size ) -> void*;
	CON_NODISCARD auto get_current_mark()		-> int32_t;
	CON_NODISCARD auto get_highest_mark()		-> int32_t;
	CON_NODISCARD auto get_size()				-> int32_t;
	CON_NODISCARD auto get_raw_data()			-> void*;

private:
	// @ToDo: Maybe not everyone want to use singleton pattern, consider adding a macro?
	static inline Temporary_Storage* instance = nullptr;

	void* data = nullptr;
	int32_t size = -1;
	int32_t mark = -1;
#ifdef CON_MEASURE_HIGHEST_MARK
	int32_t highest_mark = -1;
#endif // CON_MEASURE_HIGHEST_MARK
};
}

