#include "Sprite_Animation.h"
#include "Sprite.h"
#include "Texture.h"

const constexpr int SCREEN_WIDTH = 1920;
const constexpr int SCREEN_HEIGHT = 1080;

void Ground_Initialize();
void White_Draw();

int Ground_Draw();
int Ground_Blur();
int Top_View_Ground();
int FGround_Move();

int Polygon_Ground_Draw();
void Polygon_Ground();
int Grass_Draw();
int Cloud_Draw_1();
int Cloud_Draw_2();
int Mountain_Draw_1();
int Mountain_Draw_2();

int Polygon_Ground_Move();
void Polygon_Grass_Move();
void Polygon_Mountain_Move1();
void Polygon_Mountain_Move2();
void Polygon_Cloud_Move1();
void Polygon_Cloud_Move2();

int PGround_Blur();
void Black_Blur();
void PGround();