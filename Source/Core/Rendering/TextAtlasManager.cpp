#include "TextAtlasManager.h"
#include "Debug/DebugConsole.h"

UTextAtlasManager::UTextAtlasManager()
	: AtlasWidth(0), AtlasHeight(0), Columns(0), Rows(0),
	MarginX(0), MarginY(0)
{

}

void UTextAtlasManager::SetAtlasManager(int InWidth, int InHeight, int InColumns, int InRows, int InMarginX, int InMarginY)
{
	SetAtlasSize(InWidth, InHeight);
	SetGridLayout(InColumns, InRows);
	SetMargin(InMarginX, InMarginY);
}

void UTextAtlasManager::SetAtlasSize(int InWidth, int InHeight)
{
	AtlasWidth = InWidth;
	AtlasHeight = InHeight;
}

void UTextAtlasManager::SetGridLayout(int InColumns, int InRows)
{
	Columns = InColumns;
	Rows = InRows;
}

void UTextAtlasManager::SetMargin(int InMarginX, int InMarginY)
{
	MarginX = InMarginX;
	MarginY = InMarginY;
}

UVRect UTextAtlasManager::GetCharUV(char character) const
{
    UVRect rect = { 0.f, 0.f, 0.f, 0.f };
    if (character > Columns * Rows - 1 || Columns <= 0 || Rows <= 0 || AtlasWidth <= 0 || AtlasHeight <= 0)
        UE_LOG("TextAtlasManager GetCharUV Error!");
        return rect; // 잘못된 입력이면 기본값 반환

    int index = character; //  현재 준비된 TextAtlas는 char을 바로 사용 가능

    // 효과적으로 사용 가능한 영역에서 각 셀의 크기 계산
    int availableWidth = AtlasWidth - (Columns - 1) * MarginX;
    int availableHeight = AtlasHeight - (Rows - 1) * MarginY;
    int cellWidth = availableWidth / Columns;
    int cellHeight = availableHeight / Rows;

    int col = index % Columns;
    int row = index / Columns;
    if (row >= Rows)
        UE_LOG("TextAtlasManager GetCharUV Error row!");
        return rect;

    // 각 셀의 시작 좌표 (픽셀 단위)
    int x = col * (cellWidth + MarginX);
    int y = row * (cellHeight + MarginY);

    // 정규화된 UV 좌표 계산 (0.0 ~ 1.0)
    rect.u0 = static_cast<float>(x) / AtlasWidth;
    rect.v0 = static_cast<float>(y) / AtlasHeight;
    rect.u1 = static_cast<float>(x + cellWidth) / AtlasWidth;
    rect.v1 = static_cast<float>(y + cellHeight) / AtlasHeight;

    return rect;
}
