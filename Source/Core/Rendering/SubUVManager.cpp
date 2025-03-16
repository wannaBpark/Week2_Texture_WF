#include "SubUVManager.h"
#include "Core/Math/Vector.h"
#include "Debug/DebugConsole.h"

USubUVManager::USubUVManager()
{
}

void USubUVManager::Initialize(int InWidth, int InHeight, int InColumns, int InRows, int InTotalFrames)
{
    SetTextureSize(InWidth, InHeight);
    SetGridLayout(InColumns, InRows);
    SetTotalFrames(InTotalFrames);
}

void USubUVManager::SetTextureSize(int InWidth, int InHeight)
{
    AtlasWidth = InWidth;
    AtlasHeight = InHeight;
    CalculateCellSize();
}

void USubUVManager::SetGridLayout(int InColumns, int InRows)
{
    Columns = InColumns;
    Rows = InRows;
    CalculateCellSize();
}

void USubUVManager::SetTotalFrames(int InTotalFrames)
{
    TotalFrames = InTotalFrames;
}

void USubUVManager::CalculateCellSize()
{
    if (Columns > 0 && Rows > 0)
    {
        CellWidth = 1.0f / Columns;
        CellHeight = 1.0f / Rows;
    }
}

FVector4 USubUVManager::GetFrameUV(int FrameIndex)
{
    FVector4 UVRect = { 0.f, 0.f, 0.f, 0.f };

    /*if (FrameIndex >= TotalFrames || FrameIndex < 0 || Columns <= 0 || Rows <= 0)
    {
        UE_LOG("SubUVManager GetFrameUV Error!");
        return UVRect;
    }
    */

    int col = (FrameIndex % TotalFrames) % Columns ;
    int row = (FrameIndex % TotalFrames)/Columns;

    if (row >= Rows)
    {
        UE_LOG("SubUVManager GetFrameUV Error: Row out of range!");
        return UVRect;
    }

    // UV 계산
    UVRect.X = static_cast<float>(CellWidth) / static_cast<float>(AtlasWidth);
    UVRect.Y = static_cast<float>(CellHeight) / static_cast<float>(AtlasHeight);
    UVRect.Z = col * static_cast<float>(CellWidth) / static_cast<float>(AtlasWidth);
    UVRect.W = row * static_cast<float>(CellHeight) / static_cast<float>(AtlasHeight);

    return UVRect;
}
