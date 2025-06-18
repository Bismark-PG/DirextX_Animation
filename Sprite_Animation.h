/*==============================================================================

   Make Animation [Sprite_Animation.h]

==============================================================================*/
#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

void SpriteAni_Initialize();
void SpriteAni_Finalize();

void SpriteAni_Update(double elapsed_time);
void SpriteAni_Draw(int playID, float dx, float dy, float dw, float dh);

#endif // SPRITE_ANIMATION_H
