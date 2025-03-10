#include "Matrix.h"
#include "Transform.h"

FTransform FMatrix::GetTransform() const
{
	return FTransform(GetTranslation(), GetRotation(), GetScale());
}
