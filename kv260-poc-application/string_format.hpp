#include <memory>
#include <string>
#include <stdexcept>

template<typename ... Args>
std::string string_format( const std::string  &fmt, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, fmt.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, fmt.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}
