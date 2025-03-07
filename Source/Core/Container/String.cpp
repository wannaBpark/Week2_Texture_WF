#include "String.h"


FString FString::FromInt(int32 Num)
{
    return FString{std::to_string(Num)};
}
