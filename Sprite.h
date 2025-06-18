/*==============================================================================

	Draw Sprite [Sprite.h]

==============================================================================*/
#ifndef SPRITE_H
#define SPRITE_H

#include <d3d11.h>
#include <DirectXMath.h>

void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Sprite_Finalize(void);

void Sprite_Begin();

// Show All Texture
void Sprite_Draw(int Tex_ID, float dx, float dy,
				 const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }); // White Color

// Show All Texture (Can Change Size)
void Sprite_Draw(int Tex_ID, float dx, float dy, float dw, float dh,
				 const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

// Cut UV
void Sprite_Draw(int Tex_ID, float dx, float dy,
				 int px, int py, int pw, int ph,  // Cut UV Range (Pixel Range)
				 const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

// Cut UV (Change Texture Size)
void Sprite_Draw(int Tex_ID, float dx, float dy, float dw, float dh,
			     int px, int py, int pw, int ph, // Cut UV Range (Pixel Range)
				 const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

void Sprite_Draw(float dx, float dy, float dw, float dh);

#endif // SPRITE_H