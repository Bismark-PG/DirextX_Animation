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
#include "Run.h"
#include "Background.h"
#include "HAL.h"

int Game_State = 0;
//Hal, Run, Ground State
int H_State = -1, R_State = -1, G_State = -1;
int B_State = -1; // Blur State

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

	int HAL = Texture_Load(L"Resource/Texture/HAL.jpg");

	hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetContext(),
		L"Resource/consolab_ascii_512.png",
		Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
		0.f, 0.f, 0, 0, 0.f, 0.f);

	// Initialize Game
	HAL_Initialize();
	Ground_Initialize();
	Run_Initialize();

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

				White_Draw();

				switch (Game_State)
				{
				case 0:
					H_State = HAL_Blur();
					if (H_State == 1 && G_State == 1 && R_State == 2)
						B_State = 1;

					if (B_State == 1)
						Ground_Blur();
					else
					{
						if (H_State == 1) // If Blur is Complete
						{
							R_State = Run_To_Middle_Draw();
						}
						if (H_State == 1 && R_State == 1) // If Run is Complete
						{
							G_State = Ground_Draw();
							HAL_Move();

							if (G_State == 0)
								Run_To_Middle_Draw();
							else if (G_State == 1)
								R_State = Run_To_Left();
						}
					}
					break;
				case 1:
					break;
				}
				

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