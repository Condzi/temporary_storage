#pragma once

#include "../source/temporary_storage.hpp"

// You can create a handy macro like that. Just remember to initialize the 
// storage using ::set_instance( ptr )! 
// #define G_Temporary_Storage con::Temporary_Storage::get_instance()

namespace hi
{
using con::Temporary_Storage;
}