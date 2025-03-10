#include "Core/HAL/PlatformType.h"
#include "Core/Rendering/URenderer.h"
#include "Picker.h"

#include "Core/Input/PlayerInput.h"
#include "Static/FEditorManager.h"

FVector4 APicker::EncodeUUID(unsigned int UUID)
{
    float a = (UUID >> 24) & 0xff;
    float b = (UUID >> 16) & 0xff;
    float g = (UUID >> 8) & 0xff;
    float r = UUID & 0xff;
	
    FVector4 color = {r, g, b, a};
    
    return color;
}

int APicker::DecodeUUID(FVector4 color)
{
    return (static_cast<unsigned int>(color.W)<<24) | (static_cast<unsigned int>(color.Z)<<16) | (static_cast<unsigned int>(color.Y)<<8) | (static_cast<unsigned int>(color.X));
}

void APicker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    

}

void APicker::LateTick(float DeltaTime)
{
    AActor::LateTick(DeltaTime);

    if(APlayerInput::Get().GetMouseDown(false))
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(UEngine::Get().GetWindowHandle(), &pt);
    		
        FVector4 color = UEngine::Get().GetRenderer()->GetPixel(FVector(pt.x, pt.y, 0));

        uint32_t UUID = DecodeUUID(color);

        //TODO: UUID로 픽한 애 변경 아마 FEditorManager에서 처리할듯
        
        std::cout<<UUID << "\n";
        // UE_LOG("%d\n", UUID);
    }
}
