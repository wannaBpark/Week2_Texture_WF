#pragma once
#include <cstdint>

#define IS_WIDECHAR 0

// Windows.h의 TEXT를 삭제
#ifdef TEXT
    #undef TEXT
#endif

#if IS_WIDECHAR 
    #define TEXT(x) L##x
#else
    #define TEXT(x) x
#endif


// unsigned int type
typedef std::uint8_t uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;
typedef std::uint64_t uint64;

// signed int
typedef std::int8_t int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::int64_t int64;

typedef char ANSICHAR;
typedef wchar_t WIDECHAR;

#if IS_WIDECHAR
    typedef WIDECHAR TCHAR;
#else
    typedef ANSICHAR TCHAR;
#endif
