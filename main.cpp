#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>

#include "Core/Rendering/UI.h"
#include "ImGui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Core/Math/Vector.h"
#include "Primitive/PrimitiveVertices.h"


enum class EPrimitiveType : UINT8
{
	EPT_Triangle,
	EPT_Cube,
	EPT_Sphere,
	EPT_Max,
};

class UBall
{
public:
	FVector Location;
	FVector Velocity;
	float Radius;
	float Mass;

	float Friction = 0.01f;      // 마찰 계수
	float BounceFactor = 0.85f;  // 반발 계수

	bool bApplyGravity = false;
	static float Gravity;

public:
	UBall()
		: Location{
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			0.0f
		}
		, Velocity{
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			0.0f
		}
		, Radius{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.15f + 0.05f }
		, Mass { (4.0f / 3.0f) * 3.141592f * powf(Radius, 3) * 1000.0f }
	{
	}

	static bool CheckCollision(const UBall& A, const UBall& B)
	{
		const float Distance = (A.Location - B.Location).Length();
		return Distance <= (A.Radius + B.Radius);
	}

	void Update(float DeltaTime)
	{
		if (!bApplyGravity)
		{
			Location += Velocity * DeltaTime;
		}

		// Add Velocity
		if (Location.X - Radius < -1.0f)
		{
			Location.X = -1.0f + Radius;
			HandleWallCollision(FVector(1, 0, 0));
		}
		else if (Location.X + Radius > 1.0f)
		{
			Location.X = 1.0f - Radius;
			HandleWallCollision(FVector(-1, 0, 0));
		}

		if (Location.Y - Radius < -1.0f)
		{
			Location.Y = -1.0f + Radius;
			HandleWallCollision(FVector(0, 1, 0));
		}
		else if (Location.Y + Radius > 1.0f)
		{
			Location.Y = 1.0f - Radius;
			HandleWallCollision(FVector(0, -1, 0));
		}
	}

	void FixedUpdate(float FixedTime)
	{
		if (!bApplyGravity) return;

		Location += Velocity * FixedTime;
		Velocity.Y += Gravity * FixedTime;
	}

	void Render(const URenderer& Renderer) const
	{
		Renderer.UpdateConstant(Location, Radius);
	}

	void HandleWallCollision(const FVector& WallNormal)
	{
		// 속도를 벽면에 수직인 성분과 평행한 성분으로 분해
		FVector VelocityNormal = WallNormal * FVector::DotProduct(Velocity, WallNormal);
		const FVector VelocityTangent = Velocity - VelocityNormal;

		// 수직 속도 성분에 반발 계수를 적용하여 반사
		VelocityNormal = -VelocityNormal * BounceFactor;

		// 반사된 수직 속도와 마찰이 적용된 평행 속도를 합하여 최종 속도 계산
		Velocity = VelocityNormal + VelocityTangent * (1.0f - Friction);
	}

	void HandleBallCollision(UBall& OtherBall)
	{
		// 충돌 법선 벡터와 상대속도 계산
		const FVector Normal = (OtherBall.Location - Location).GetSafeNormal();
		const FVector RelativeVelocity = OtherBall.Velocity - Velocity;

		const float VelocityAlongNormal = FVector::DotProduct(RelativeVelocity, Normal);

		// 이미 서로 멀어지고 있는 경우 무시
		if (VelocityAlongNormal > 0) return;

		// 충격량 계산
		const float e = min(BounceFactor, OtherBall.BounceFactor);  // 반발 계수를 둘중 더 작은걸로 설정
		float j = -(1 + e) * VelocityAlongNormal;
		j /= 1 / Mass + 1 / OtherBall.Mass;

		// 속도 업데이트
		const FVector Impulse = Normal * j;
		Velocity -= Impulse / Mass;
		OtherBall.Velocity += Impulse / OtherBall.Mass;

		// 마찰 적용
		FVector Tangent = RelativeVelocity - Normal * VelocityAlongNormal;
		if (Tangent.LengthSquared() > 0.0001f)  // 탄젠트의 길이가 매우 작으면 건너뛰기
		{
			Tangent = Tangent.GetSafeNormal();

			// 탄젠트 충격량 계산
			float JT = -FVector::DotProduct(RelativeVelocity, Tangent);  // 접선 방향 상대 속도에 기반한 충격량 크기
			JT /= 1 / Mass + 1 / OtherBall.Mass;                               // 두 물체의 유효 질량

			const float MuT = min(Friction, OtherBall.Friction);
			FVector FrictionImpulse;
			if (fabsf(JT) < j * MuT)
			{
				// 실제 마찰력 사용
				FrictionImpulse = Tangent * JT;
			}
			else
			{
				// 한계치를 초과시 j * MuT로 제한
				FrictionImpulse = Tangent * -j * MuT;
			}

			// 마찰력 적용
			Velocity -= FrictionImpulse / Mass;
			OtherBall.Velocity += FrictionImpulse / OtherBall.Mass;
		}

		// 겹침 해결
		const float Penetration = Radius + OtherBall.Radius - (OtherBall.Location - Location).Length();
		const FVector Correction = Normal * Penetration / (Mass + OtherBall.Mass) * 0.8f;
		Location -= Correction * Mass;
		OtherBall.Location += Correction * OtherBall.Mass;
	}
};

float UBall::Gravity = -9.8f;


// ImGui WndProc 정의
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 각종 윈도우 관련 메시지(이벤트)를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ImGui의 메시지를 처리
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    {
        return true;
    }

    switch (uMsg)
    {
    // 창이 제거될 때 (창 닫기, Alt+F4 등)
    case WM_DESTROY:
        PostQuitMessage(0); // 프로그램 종료
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
#pragma region Init Window
    // 사용 안하는 파라미터들
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    // 윈도우 클래스 이름 및 타이틀 이름
    constexpr WCHAR WndClassName[] = L"DX11 Test Window Class";
    constexpr WCHAR WndTitle[] = L"DX11 Test Window";

    // 윈도우 클래스 등록
    WNDCLASS WndClass = {0, WndProc, 0, 0, hInstance, nullptr, nullptr, nullptr, nullptr, WndClassName};
    RegisterClass(&WndClass);

    // 1024 x 1024로 윈도우 생성
    const HWND hWnd = CreateWindowEx(
        0, WndClassName, WndTitle,
        WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1024, 1024,
        nullptr, nullptr, hInstance, nullptr
    );
#pragma endregion Init Window

#pragma region Init Renderer & ImGui
    // 렌더러 초기화
    URenderer Renderer;
    Renderer.Create(hWnd);
    Renderer.CreateShader();
    Renderer.CreateConstantBuffer();

	UI ui;
	ui.Initialize(hWnd, Renderer);
	
#pragma endregion Init Renderer & ImGui

#pragma region Create Vertex Buffer
	int NumOfVertices = sizeof(SphereVertices) / sizeof(FVertexSimple);
	ID3D11Buffer* VertexBufferSphere = Renderer.CreateVertexBuffer(SphereVertices, sizeof(SphereVertices));
#pragma endregion Create Vertex Buffer

    // FPS 제한
    constexpr int TargetFPS = 60;
    constexpr double TargetDeltaTime = 1000.0f / TargetFPS; // 1 FPS의 목표 시간 (ms)

    // 고성능 타이머 초기화
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);

    LARGE_INTEGER StartTime;
    QueryPerformanceCounter(&StartTime);

    float Accumulator = 0.0; // Fixed Update에 사용되는 값
    constexpr float FixedTimeStep = 1.0f / TargetFPS;

	// UBalls 배열
	int ArrSize = 1;
	int ArrCap = 4;
	UBall** Balls = new UBall*[ArrCap];
	Balls[0] = new UBall;
	

    // Main Loop
    bool bIsExit = false;
    while (bIsExit == false)
    {
        // DeltaTime 계산 (초 단위)
        const LARGE_INTEGER EndTime = StartTime;
        QueryPerformanceCounter(&StartTime);

        const float DeltaTime =
            static_cast<float>(StartTime.QuadPart - EndTime.QuadPart) / static_cast<float>(Frequency.QuadPart);

        // 누적 시간 추가
        Accumulator += DeltaTime;

        // 메시지(이벤트) 처리
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키 입력 메시지를 번역
            TranslateMessage(&msg);

            // 메시지를 등록한 Proc에 전달
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                bIsExit = true;
                break;
            }
        }


		// Update 로직
		for (int i = 0; i < ArrSize; ++i)
		{
			Balls[i]->Update(DeltaTime);
		}


    	// FixedTimeStep 만큼 업데이트
    	while (Accumulator >= FixedTimeStep)
    	{
    		for (int i = 0; i < ArrSize; ++i)
    		{
				Balls[i]->FixedUpdate(FixedTimeStep);
    		}

    		// 공 충돌 처리
    		for (int i = 0; i < ArrSize; ++i)
    		{
    			for (int j = i + 1; j < ArrSize; ++j)
    			{
    				if (UBall::CheckCollision(*Balls[i], *Balls[j]))
    				{
    					Balls[i]->HandleBallCollision(*Balls[j]);
    				}
    			}
    		}

    		Accumulator -= FixedTimeStep;
    	}

        // 렌더링 준비 작업
        Renderer.Prepare();
        Renderer.PrepareShader();

    	for (int i = 0; i < ArrSize; ++i)
    	{
    		Balls[i]->Render(Renderer);
    		Renderer.RenderPrimitive(VertexBufferSphere, NumOfVertices);
    	}

    	ui.Update();

        // 현재 화면에 보여지는 버퍼와 그리기 작업을 위한 버퍼를 서로 교환
        Renderer.SwapBuffer();


        // FPS 제한
        double ElapsedTime;
        do
        {
            Sleep(0);

            LARGE_INTEGER CurrentTime;
            QueryPerformanceCounter(&CurrentTime);

            ElapsedTime = static_cast<double>(CurrentTime.QuadPart - StartTime.QuadPart) * 1000.0 / static_cast<double>(Frequency.QuadPart);
        } while (ElapsedTime < TargetDeltaTime);
    }

	delete[] Balls;

	ui.Shutdown();

    Renderer.ReleaseConstantBuffer();
    Renderer.ReleaseShader();
    Renderer.Release();

    return 0;
}
