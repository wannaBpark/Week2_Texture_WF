#include "String.h"


FString FString::FromInt(int32 Num)
{
#if IS_WIDECHAR
    return FString{std::to_wstring(Num)};
#else
    return FString{std::to_string(Num)};
#endif
}
