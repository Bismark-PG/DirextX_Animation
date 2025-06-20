/*==============================================================================

	Draw Sprite [Sprite.cpp]

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"	
#include "debug_ostream.h"
#include "Sprite.h"
#include "Texture.h"

static constexpr int NUM_VERTEX = 4; // 頂点数

static ID3D11Buffer* g_pVertexBuffer = nullptr; // 頂点バッファ
static ID3D11ShaderResourceView* g_pTexture = nullptr;

// 注意！初期化で外部から設定されるもの。Release不要。
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


// 頂点構造体
struct Vertex
{
	XMFLOAT3 position; // 頂点座標
	XMFLOAT4 color;
	XMFLOAT2 UV;
};

void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// デバイスとデバイスコンテキストのチェック
	if (!pDevice || !pContext) {
		hal::dout << "Sprite_Initialize() : 与えられたデバイスかコンテキストが不正です" << std::endl;
		return;
	}

	// デバイスとデバイスコンテキストの保存
	g_pDevice = pDevice;
	g_pContext = pContext;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);

	/*// Read Texture
	TexMetadata metadata;
	ScratchImage image;

	LoadFromWICFile(L"knight_more_new.png", WIC_FLAGS_NONE, &metadata, image);
	HRESULT hr = CreateShaderResourceView(g_pDevice,
		image.GetImages(), image.GetImageCount(), metadata, &g_pTexture);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Failed read texture", "ERROR", MB_OK | MB_ICONERROR);
	}*/
}

void Sprite_Finalize(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexBuffer);
}

void Sprite_Begin()
{
	// 頂点シェーダーに変換行列を設定
	// Make Camera (Zoom In or Out, More etc...)
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();
	Shader_SetMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
}

// Show All Texture
void Sprite_Draw(int Tex_ID, float dx, float dy, const DirectX::XMFLOAT4& color)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	unsigned int dw = Texture_Width(Tex_ID);
	unsigned int dh = Texture_Height(Tex_ID);

	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { dx,		dy,      0.0f };
	v[1].position = { dx + dw,	dy,      0.0f };
	v[2].position = { dx,		dy + dh, 0.0f };
	v[3].position = { dx + dw,	dy + dh, 0.0f };

	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	//	U = Width	||   V = Height
	v[0].UV = { 0.0f, 0.0f };
	v[1].UV = { 1.0f, 0.0f };
	v[2].UV = { 0.0f, 1.0f };
	v[3].UV = { 1.0f, 1.0f };

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	Texture_SetTexture(Tex_ID);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}

// Show All Texture (Can Change Size)
void Sprite_Draw(int Tex_ID, float dx, float dy, float dw, float dh, const DirectX::XMFLOAT4& color)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { dx,		dy,      0.0f };
	v[1].position = { dx + dw,	dy,      0.0f };
	v[2].position = { dx,		dy + dh, 0.0f };
	v[3].position = { dx + dw,	dy + dh, 0.0f };

	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	//	U = Width	||   V = Height
	v[0].UV = { 0.0f, 0.0f };
	v[1].UV = { 1.0f, 0.0f };
	v[2].UV = { 0.0f, 1.0f };
	v[3].UV = { 1.0f, 1.0f };

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	Texture_SetTexture(Tex_ID);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}

// Cut UV
void Sprite_Draw(int Tex_ID, float dx, float dy,
				 int px, int py, int pw, int ph, const DirectX::XMFLOAT4& color)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み

	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { dx,		dy,      0.0f };
	v[1].position = { dx + pw,	dy,      0.0f };
	v[2].position = { dx,		dy + ph, 0.0f };
	v[3].position = { dx + pw,	dy + ph, 0.0f };

	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	// Get Texture Size
	float tw = (float)Texture_Width(Tex_ID);
	float th = (float)Texture_Height(Tex_ID);

	// Set UV Size
	float U0 = px / tw;
	float U1 = (px + pw) / th;
	float V0 = py / tw;
	float V1 = (py + ph) / th;

	// Cut Texture With Using UV Tool
	//	U = Width	||   V = Height
	v[0].UV = { U0, V0 };
	v[1].UV = { U1, V0 };
	v[2].UV = { U0, V1 };
	v[3].UV = { U1, V1 };

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	Texture_SetTexture(Tex_ID);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}

// Cut UV (Change Texture Size)
void Sprite_Draw(int Tex_ID, float dx, float dy, float dw, float dh,
				 int px, int py, int pw, int ph, const DirectX::XMFLOAT4& color)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み

	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { dx,		dy,      0.0f }; // 左上
	v[1].position = { dx + dw,	dy,      0.0f }; // 右上
	v[2].position = { dx,		dy + dh, 0.0f }; // 左下
	v[3].position = { dx + dw,	dy + dh, 0.0f }; // 右下

	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	// Get Texture Size
	float tw = (float)Texture_Width(Tex_ID);
	float th = (float)Texture_Height(Tex_ID);

	// Set UV Size
	float U0 = px		 / tw; 
	float U1 = (px + pw) / tw;
	float V0 = py		 / th;
	float V1 = (py + ph) / th;

	// Cut Texture With Using UV Tool
	//	U = Width	||   V = Height
	v[0].UV = { U0, V0 };
	v[1].UV = { U1, V0 };
	v[2].UV = { U0, V1 };
	v[3].UV = { U1, V1 };

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	Texture_SetTexture(Tex_ID);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(float dx, float dy, float dw, float dh)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	// const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	// const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();
	// constexpr float w = 1024.0f / 2;
	// constexpr float h = 1536.0f / 2;

	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { dx,		dy,      0.0f };
	v[1].position = { dx + dw,	dy,      0.0f };
	v[2].position = { dx,		dy + dh, 0.0f };
	v[3].position = { dx + dw,	dy + dh, 0.0f };

	v[0].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[1].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[2].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[3].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// Make Texture Speed
	// static float a = 0.0f;

	//	U = Width	||   V = Height
	v[0].UV = { 0.0f, 0.0f };
	v[1].UV = { 1.0f, 0.0f };
	v[2].UV = { 0.0f, 1.0f };
	v[3].UV = { 1.0f, 1.0f };

	// Make 5 Square
	/*v[4].position = {SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, 0.0f};
	v[5].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.1f, 0.0f };
	v[6].position = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.3f, 0.0f };
	v[7].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f };

	v[4].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[5].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[6].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[7].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	v[8].position = { SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.3f, 0.0f };

	v[9].position = { SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.4f, 0.0f };
	v[10].position = { SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.6f, 0.0f };
	v[11].position = { SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.4f, 0.0f };
	v[12].position = { SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.6f, 0.0f };

	v[9].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[10].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[11].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[12].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	v[13].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.6f, 0.0f };

	v[14].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.7f, 0.0f };
	v[15].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.9f, 0.0f };
	v[16].position = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.7f, 0.0f };
	v[17].position = { SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.9f, 0.0f };

	v[14].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[15].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[16].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[17].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	v[18].position = { SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.3f, 0.0f };

	v[19].position = { SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.3f, 0.0f };
	v[20].position = { SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.3f, 0.0f };
	v[21].position = { SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.1f, 0.0f };
	v[22].position = { SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.1f, 0.0f };

	v[19].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[20].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[21].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[22].color = { 1.0f, 1.0f, 1.0f, 1.0f };*/

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// 頂点シェーダーに変換行列を設定
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();
	Shader_SetMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	// g_pContext->PSSetShaderResources(0, 1, &g_pTexture);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}