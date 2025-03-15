#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct UVRect
{
	float u0, v0;
	float u1, v1;
};

class UTextAtlasManager
{
public:
	UTextAtlasManager();

	void SetAtlasManager(int InWidth, int InHeight, int InColumns, int InRows, int InMarginX, int InMarginY);

	void SetAtlasSize(int InWidth, int InHeight);
	void SetGridLayout(int InColumns, int InRows);
	void SetMargin(int InMarginX, int InMarginY);

	UVRect GetCharUV(char character) const;

private:
	int AtlasWidth;
	int AtlasHeight;
	int Columns;
	int Rows;
	int MarginX;
	int MarginY;
};
