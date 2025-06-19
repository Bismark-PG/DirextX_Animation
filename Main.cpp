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

//#include "polygon.h"

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
		L"consolab_ascii_512.png",
		Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
		0.f, 0.f,
		0, 0,
		0.f, 0.f);

	// Input Texture File
	int TexID_Knight = Texture_Load(L"knight_more_new.png");
	int TexID_Konbini = Texture_Load(L"konbini.png");
	int TexID_KoKo = Texture_Load(L"kokosozai.png");

	int aid_rw = SpriteAni_Get_Pattern_Info(TexID_KoKo, 13, { 32, 32 }, { 32 * 0, 32 * 0 }, true); // Loop Animation
	int aid_sm = SpriteAni_Get_Pattern_Info(TexID_KoKo, 6,  { 32, 32 }, { 32 * 0, 32 * 2 }, true); // Loop Animation
	int aid_to = SpriteAni_Get_Pattern_Info(TexID_KoKo, 4, { 32, 32 }, { 32 * 2, 32 * 5 }, false); // Do Not Loop Animation

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
				//Sprite_Draw(TexID_Konbini, 32.0f, 32.0f, { 1.f, 1.f, 1.f, 1.f });
				Sprite_Draw(TexID_Knight, .0f, .0f, 1024.f * .5f, 1536.f * .5f);
	

				SpriteAni_Draw(0, 512.f, 64.f, 256.f, 256.f);
				SpriteAni_Draw(1, 1024.f, 64.f, 256.f, 256.f);
				SpriteAni_Draw(2, 1024.f, 512.f, 256.f, 256.f);

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