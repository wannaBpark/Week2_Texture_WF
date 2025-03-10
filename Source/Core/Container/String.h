#pragma once

#include <string>
#include "ContainerAllocator.h"
#include "Core/HAL/PlatformType.h"

/*
# TCHAR가 ANSICHAR인 경우
1. const ANSICHAR* 로 FString 생성
2. std::string에서 FString 생성

# TCHAR가 WIDECHAR인 경우
1. const ANSICHAR* 로 FString 생성
1. const WIDECHAR* 로 FString 생성
2. std::wstring에서 FString 생성
3. std::string에서 FString 생성
*/

enum : int8 { INDEX_NONE = -1 };

/** Determines case sensitivity options for string comparisons. */
namespace ESearchCase
{
enum Type : uint8
{
    /** Case sensitive. Upper/lower casing must match for strings to be considered equal. */
    CaseSensitive,

    /** Ignore case. Upper/lower casing does not matter when making a comparison. */
    IgnoreCase,
};
};

/** Determines search direction for string operations. */
namespace ESearchDir
{
enum Type : uint8
{
    /** Search from the start, moving forward through the string. */
    FromStart,

    /** Search from the end, moving backward through the string. */
    FromEnd,
};
}

class FString
{
private:
    using BaseStringType = std::basic_string<
        TCHAR,
        std::char_traits<TCHAR>,
        FDefaultAllocator<TCHAR>
    >;

    BaseStringType PrivateString;

public:
    FString() {}

#if IS_WIDECHAR
private:
    static std::wstring ConvertWideChar(const ANSICHAR* NarrowStr);

public:
    FString(const std::wstring& InString) : PrivateString(InString) {}
    FString(const std::string& InString) : PrivateString(ConvertWideChar(InString.c_str())) {}
    FString(const WIDECHAR* InString) : PrivateString(InString) {}
    FString(const ANSICHAR* InString) : PrivateString(ConvertWideChar(InString)) {}
#else
public:
    FString(const std::string& InString) : PrivateString(InString) {}
    FString(const ANSICHAR* InString) : PrivateString(InString) {}
#endif

    static FString FromInt(int32 Num);
    static FString SanitizeFloat(float InFloat);

public:
    int32 Len() const { return static_cast<int32>(PrivateString.length()); }
    bool IsEmpty() const;
    bool Equals(const FString& Other, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const;
    bool Contains(const FString& SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase, ESearchDir::Type SearchDir = ESearchDir::FromStart) const;
    int32 Find(const FString& SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase, ESearchDir::Type SearchDir = ESearchDir::FromStart, int32 StartPosition = -1) const;

public:
    /** TCHAR* 로 반환하는 연산자 */
    const TCHAR* operator*() const
    {
        return PrivateString.c_str();
    }
};
