/*==============================================================================

   Make Animation [Sprite_Animation.cpp]

==============================================================================*/
#include "Sprite_Animation.h"
#include "Sprite.h"
#include "Texture.h"
#include "DirectXMath.h"
using namespace DirectX;

struct AniPatternData
{
	// Set Texture Manage Number
	int TextureID{ -1 };
	// Animation Pattern Count
	int PatternMAX = 0;
	// Animation Start Range
	XMUINT2 StartPosition = { 0, 0 };
	// One Pattern Width, Height
	XMUINT2 PatternSize = { 0, 0 };
	// Check Last Pattern
	bool ISLooped{ true };
};

struct AniPlayData
{
	// Animation Pattern ID
	int PatternID = -1;
	// Current Pattern Count
	int PatternNUM = 0;
	// Accumulated Time
	double Accumulated_Time = 0.0;
};

static constexpr int ANI_PATTERN_MAX = 128;
static AniPatternData g_AniPattern[ANI_PATTERN_MAX];
static constexpr int ANI_PLAY_MAX = 256;
static AniPlayData g_AniPlay[ANI_PLAY_MAX];

void SpriteAni_Initialize()
{
	// Read Texture And Make Texture Info
	// g_TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[0].TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[0].PatternMAX = 8;
	g_AniPattern[0].PatternSize = { 32, 32 };
	g_AniPattern[0].StartPosition = { 0, 96 };
	g_AniPlay[0].PatternID = 0;

	g_AniPattern[1].TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[1].PatternMAX = 13;
	g_AniPattern[1].PatternSize = { 32, 32 };
	g_AniPattern[1].StartPosition = { 0, 32 };
	g_AniPlay[1].PatternID = 1;
}

void SpriteAni_Finalize()
{

}

void SpriteAni_Update(double elapsed_time)
{
	for (int i = 0; i < 2; i++)
	{
		// Set Pattern Count
		if (g_AniPlay[i].Accumulated_Time >= 0.1)
		{
			g_AniPlay[i].PatternNUM
				= (g_AniPlay[i].PatternNUM + 1)
				% g_AniPattern[g_AniPlay[i].PatternID].PatternMAX;

			g_AniPlay[i].Accumulated_Time = 0.0;
		}
		g_AniPlay[i].Accumulated_Time += elapsed_time;
	}
}

void SpriteAni_Draw(int playID, float dx, float dy, float dw, float dh)
{
	Sprite_Draw(g_AniPattern[g_AniPlay[playID].PatternID].TextureID,
		dx, dy, dw, dh,
		g_AniPattern[g_AniPlay[playID].PatternID].StartPosition.x
		+ g_AniPattern[g_AniPlay[playID].PatternID].PatternSize.x
		* g_AniPlay[playID].PatternNUM,
		g_AniPattern[g_AniPlay[playID].PatternID].StartPosition.y,
		g_AniPattern[g_AniPlay[playID].PatternID].PatternSize.x,
		g_AniPattern[g_AniPlay[playID].PatternID].PatternSize.y,
		{ 1.0f, 1.0f, 1.0f, 1.0f });
}