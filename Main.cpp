/*==============================================================================

   Main Game [main.cpp]

==============================================================================*/
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
#include "Run.h"
#include "Background.h"
#include "HAL.h"

int Game_State = 0;
//Hal, Run, Ground State
int H_State = -1, R_State = -1, G_State = -1;
int B_State = -1; // Blur State
//Pixel, Front Run State
int PG_State = -1, FR_State = -1;
//Polygon State
int PGM_State = -1, PoG_State;
int PRun_State = -1;
//Grass, Cloud, Mountain State
int GS = -1, CS1 = -1, CS2 = -1, MS1 = -1, MS2 = -1;
int GM = -1, PGBS = -1, PGBDS = -1;

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
	double FPS = 0.0; // Frame Per SecondState

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
					{
						G_State = Ground_Blur();

						if (G_State == 2)
							Game_State = 1;
					}
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
					if (FR_State == 1)
						Game_State = 2;
					PG_State = Top_View_Ground();
					if (PG_State == 1)
						FR_State = Run_To_Front();
					break;
				case 2:
					if (PoG_State == 1)
						Game_State = 3;
					PGM_State = FGround_Move();
					PoG_State = Polygon_Ground_Draw();
					break;
				case 3:
					Polygon_Ground();
					PRun_State = Run_Poly();
					if (PRun_State == 1)
						Game_State = 4;
					break;
				case 4:
					MS2 = Mountain_Draw_2();
					MS1 = Mountain_Draw_1();
					Polygon_Ground();
					GS = Grass_Draw();
					CS1 = Cloud_Draw_1();
					CS2 = Cloud_Draw_2();
					Run_Poly();
					if (GS == 1 && CS1 == 1 && CS2 == 1 && MS1 == 1 && MS2 == 1)
						Game_State = 5;
					break;
				case 5:
					if (PGBS == 1)
						Game_State = 6;
					else
					{
						Polygon_Mountain_Move2();
						Polygon_Mountain_Move1();
						GM = Polygon_Ground_Move();
						Polygon_Grass_Move();
						Polygon_Cloud_Move1();
						Polygon_Cloud_Move2();
						if (GM == 3)
						{
							PGBS = PGround_Blur();
							Run_Middle_Human();
						}
						else if (GM == 2)
							Run_Middle_Human();
						else if (GM == 1)
							Run_Middle();
						else if (GM != 1 && GM != 2)
							Run_Poly_Middle();
						break;
					}
				case 6:
					PGround();
					PGBDS = PGround_Blur();
					Run_Middle_Human();
					if (PGBDS == 1)
						Black_Blur();
					break;
				}
				
				// Show FPS
#if defined(DEBUG) || defined(_DEBUG)
				std::stringstream ss;
				ss << "FPS : " << Game_State << std::endl;
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