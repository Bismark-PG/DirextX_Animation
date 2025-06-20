/*==============================================================================

   Main Game [main.cpp]

==============================================================================*/
#include <sdkddkver.h>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#include "Game_Window.h"
#include "direct3d.h"
#include "shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Sprite_Animation.h"
#include "debug_text.h"
#include <sstream>
#include "system_timer.h"
#include "KoKo.h"
//#include "polygon.h"

const constexpr int SCREEN_WIDTH = 1920;
const constexpr int SCREEN_HEIGHT = 1080;

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdline, _In_ int nCmdShow)
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED); // (void)

	HWND hWnd = GameWindowCreate(hInstance);

	// Read Start Initialize Function
	SystemTimer_Initialize();
	Direct3D_Initialize(hWnd);
	Shader_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	Texture_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	Sprite_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	SpriteAni_Initialize();

	hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetContext(),
		L"Resource/consolab_ascii_512.png",
		Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
		0.f, 0.f, 0, 0, 0.f, 0.f);

	// Input Texture File
	int TexID_Ground = Texture_Load(L"Resource/Texture/pixel_ground.jpg");
	int TexID_Run01 = Texture_Load(L"Resource/Texture/runningman000.png");
	int TexID_Run02 = Texture_Load(L"Resource/Texture/runningman001.png");

	// Make Texture Animation Pattern
	// (Pattern ID, Pattern Play Time, Pattern Size (X, Y), Start Position (W, H), Loop Animation (False = NO / True = YES)
	int AID_Run01 = SpriteAni_Get_Pattern_Info(TexID_Run01,  8, 8, 0.2, { 100, 200 }, { 100 * 0, 200 * 0 }, true);
	int AID_Run02 = SpriteAni_Get_Pattern_Info(TexID_Run02,  10, 5, 0.2, { 140, 200 }, { 140 * 0, 200 * 0 }, true);

	// Create Animation Player
	int PID_08 = SpriteAni_CreatePlayer(AID_Run01);
	int PID_09 = SpriteAni_CreatePlayer(AID_Run02);

	KoKo_Initialize();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Set Frame
	double Exec_Last_Time = SystemTimer_GetTime();
	double Fps_Last_Time = Exec_Last_Time;
	double Current_Time = 0.0;
	ULONG Frame_Count = 0;
	double FPS = 0.0; // Frame Per Second

	// Make Game Loop & Message Loop
	MSG msg;

	do
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		// Set Game
		else
		{
			// Time Set
			Current_Time = SystemTimer_GetTime(); // Get System Time
			double Elapsed_Time = Current_Time - Fps_Last_Time; // Get Time For FPS

			//  Set FPS
			if (Elapsed_Time >= 1.0)
			{
				FPS = Frame_Count / Elapsed_Time;
				Fps_Last_Time = Current_Time; // Save FPS
				Frame_Count = 0; // Clear Count
			}

			// Set Elapsed Time
			Elapsed_Time = Current_Time - Exec_Last_Time;
			// If you want to limit FPS, set condition here
			if (Elapsed_Time >= (1.0 / 60.0)) // 60 FPS
			{
				Exec_Last_Time = Current_Time; // Save Last Time

				// Update Game Texture
				SpriteAni_Update(Elapsed_Time);
	
				// Draw Texture
				Direct3D_Clear();
	
				Sprite_Begin();
				
				// Show Texture (What, Where, Size)
				Sprite_Draw(TexID_Ground, .0f, .0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	
				// Show Texture Animation (What, Where, Size)
				KoKo_Draw();

				//running
				SpriteAni_Draw(PID_08, 1300.f, 450.f, 100.f * 2, 200.f * 2);
				SpriteAni_Draw(PID_09,  900.f, 450.f, 140.f * 2, 200.f * 2);

				// Show FPS
#if defined(DEBUG) || defined(_DEBUG)
				std::stringstream ss;
				ss << "FPS : " << FPS << std::endl;
				dt.SetText(ss.str().c_str(), { .5f, .8f, .3f, 1.f });

				dt.Draw();
				dt.Clear();
#endif	

				Direct3D_Present();

				Frame_Count++;
			}	
		}
	} while (msg.message != WM_QUIT);
	
	// Read End Initialize Function
	SpriteAni_Finalize();
	Sprite_Finalize();
	Texture_Finalize();
	Shader_Finalize();
	Direct3D_Finalize();

	return (int)msg.wParam;
}