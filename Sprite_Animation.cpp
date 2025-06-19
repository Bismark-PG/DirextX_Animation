/*==============================================================================

   Make Animation [Sprite_Animation.cpp]

==============================================================================*/
#include "Sprite_Animation.h"
#include "Sprite.h"
#include "Texture.h"


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
	// Initialize Animation Patterns
	for (AniPatternData& data : g_AniPattern)
	{
		data.TextureID = -1; // Initialize Texture ID
		//data.PatternMAX = 0; // Initialize Pattern Count
		//data.StartPosition = { 0, 0 }; // Initialize Start Position
		//data.PatternSize = { 0, 0 }; // Initialize Pattern Size
		//data.ISLooped = true; // Default Loop Animation
	}

	/*g_AniPattern[0].TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[0].PatternMAX = 8;
	g_AniPattern[0].PatternSize = { 32, 32 };
	g_AniPattern[0].StartPosition = { 32 * 0, 32 * 3 };
	g_AniPlay[0].PatternID = 0;

	g_AniPattern[1].TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[1].PatternMAX = 13;
	g_AniPattern[1].PatternSize = { 32, 32 };
	g_AniPattern[1].StartPosition = { 32 * 0, 32 * 1 };
	g_AniPlay[1].PatternID = 1;
	
	g_AniPattern[2].TextureID = Texture_Load(L"kokosozai.png");
	g_AniPattern[2].PatternMAX = 4;
	g_AniPattern[2].PatternSize = { 32, 32 };
	g_AniPattern[2].StartPosition = { 32 * 2, 32 * 5 };
	g_AniPattern[2].ISLooped = false; // Not Loop Animation
	g_AniPlay[2].PatternID = 2;*/

	// Set Animation Pattern ID
	g_AniPlay[0].PatternID = 0;
	g_AniPlay[1].PatternID = 1;
	g_AniPlay[2].PatternID = 2;
}

void SpriteAni_Finalize()
{

}

void SpriteAni_Update(double elapsed_time)
{
	for (int i = 0; i < 3; i++)
	{
		if (g_AniPlay[i].Accumulated_Time >= 0.1)
		{
			g_AniPlay[i].PatternNUM++;

			AniPatternData* pAniPatternData = &g_AniPattern[g_AniPlay[i].PatternID];
		
			// Set Pattern Count
			if (g_AniPlay[i].PatternNUM >= pAniPatternData->PatternMAX)
			{
				if (pAniPatternData->ISLooped)  // Loop Animation
				{
					g_AniPlay[i].PatternNUM = 0;
				}
				else // Stop Animation at Last Pattern
				{
					g_AniPlay[i].PatternNUM = pAniPatternData->PatternMAX - 1;
				}
			}
			g_AniPlay[i].Accumulated_Time -= 0.1;
		}
		g_AniPlay[i].Accumulated_Time += elapsed_time;
	}
}

void SpriteAni_Draw(int PlayID, float dx, float dy, float dw, float dh)
{
	Sprite_Draw(g_AniPattern[g_AniPlay[PlayID].PatternID].TextureID,
		dx, dy, dw, dh,
		g_AniPattern[g_AniPlay[PlayID].PatternID].StartPosition.x
		+ g_AniPattern[g_AniPlay[PlayID].PatternID].PatternSize.x
		* g_AniPlay[PlayID].PatternNUM,
		g_AniPattern[g_AniPlay[PlayID].PatternID].StartPosition.y,
		g_AniPattern[g_AniPlay[PlayID].PatternID].PatternSize.x,
		g_AniPattern[g_AniPlay[PlayID].PatternID].PatternSize.y,
		{ 1.0f, 1.0f, 1.0f, 1.0f });
}

// Read Texture And Make Texture Info
int SpriteAni_Get_Pattern_Info(int TexID, int PMax, const XMUINT2& PSize, const XMUINT2& SPosition, bool Is_Loop)
{
	for (int i = 0; i < ANI_PATTERN_MAX; i++)
	{
		if (g_AniPattern[i].TextureID >= 0) // If Set Texture ID
			continue;// If Texture ID Already Set, Continue Loop

		// If Not Set Texture ID
		g_AniPattern[i].TextureID = TexID;
		g_AniPattern[i].PatternMAX = PMax;
		g_AniPattern[i].PatternSize = PSize;
		g_AniPattern[i].StartPosition = SPosition;
		g_AniPattern[i].ISLooped = Is_Loop;

		return i; // Return Pattern ID
	}

	return -1; // If No More Space, Return -1
}