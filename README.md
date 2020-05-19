# Temporary Storage

Just a simple linear allocator. Copy and paste the files from `source` folder. Take a look at the `example` folder.

Uses `[[nodiscard]]` from C++17 which can be turned off. Uses ``auto`` from C++14, which can not be turned off. 

## Motivation

This repository is just an example implementation. Feel free to copy and change it.

Imagine calling `new` and `delete` (or `malloc` and `free`) everytime you want to allocate memory -- RIP. Why not have a constant size buffer which resets itself frequently (at the beginning of a game frame, for example)? This way you don't care about calling `delete` / `free` everywhere. 

## Usage
For working example see the `example` folder.
### Macros
You can comment them out in the header file. You can also provide your own assertion macro.
```cpp
#define CON_USE_NODISCARD        // -- uses C++17 [[nodiscard]] for getters.
#define CON_MEASURE_HIGHEST_MARK // -- tracks the highest amount of memory used. Useful for determinaing how much memory your Temporary_Storage actually need.
#define CON_ASSERT( x )          // -- it's assert( x ) by default.
```

### Basic setup
Put the instance in your `Application` class (or somwhere similar). I assume that your application allocates a chunk of memory that you later use to allocate your game objects (entities, strings...). Here is simplified example:
```cpp
class My_Application
{
public:
    My_Application();
    // main game loop, etc...
    void run();

private:
    void* all_aplication_memory;
    con::Temporary_Storage ts;
};

My_Application::My_Application()
{
    // Let's say we allocate 512 bytes of memory for our app.
    all_application_memory = std::malloc( 512 );
    // Then give a part of it (here 128 bytes) to Temporary Storage.
    ts.set_memory( all_applicaiton_memory, 128 );
    // We're making this instance of temporary storage as a global one.
    ts.set_instance( &ts );
}

void My_Application::run()
{
    // Typical game loop
    while( 1 ) {
        ts.reset();

        input();
        update();
        render();
    }
}

```

### Actual, basic usage
You just alloc, no freeing.

This `allocate( size_ )` syntax may change since calling `reinterpret_cast<>` everytime is kinda boilerplate.

```cpp
// Handy macro, not necassary but handy.
#define G_Temporary_Storage con::Temporary_Storage::get_instance()
```
When you use C library stuff you frequently deal with buffers and allocating memory for every buffer may be costly. `Temporary_Storage` just increments internal counter and returns you a pointer to memory. No free or malloc is involved:
```cpp
void print_some_stuff() 
{
    char* buffer = reintrpret_cast<char*>( G_Temporary_Storage.allocate( sizeof( char ) * 32 ) );

    snprintf( buffer, 32, "Oh, hi %s", "Mark!" );
    puts( buffer );
    // no free(buffer) call -- buffer memory will be cleared at the beginning of the next frame
}
```
### The mark
Mark is just amount of bytes used by the Storage object. You can set it to your own value, check out `example/example.cpp`.  

## Inspiration
This is a rough implementation of the idea from Jai language. You can watch Jonathan Blow video about that: [here](https://www.youtube.com/watch?v=SSVHWrYG974&t=133s).

Jai's implemenation fallbacks to `malloc` when there is not enough space avaible, this one just calls `CON_ASSERT( x )`.