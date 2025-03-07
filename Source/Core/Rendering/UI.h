#pragma once
#include "URenderer.h"


class URenderer;

class UI
{
public:
    void Initialize(HWND hWnd, URenderer Renderer);
    void Update();
    void Shutdown();
};
