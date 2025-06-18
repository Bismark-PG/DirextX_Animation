/*==============================================================================

   Draw Polygon [polygon.cpp]

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
#include "DirectXTex.h"
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"	
#include "debug_ostream.h"

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

void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// デバイスとデバイスコンテキストのチェック
	if (!pDevice || !pContext) {
		hal::dout << "Polygon_Initialize() : 与えられたデバイスかコンテキストが不正です" << std::endl;
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

	// Read Texture
	TexMetadata metadata;
	ScratchImage image;

	LoadFromWICFile(L"knight_more_new.png", WIC_FLAGS_NONE, &metadata, image);
	HRESULT hr = CreateShaderResourceView(g_pDevice,
		image.GetImages(), image.GetImageCount(), metadata, &g_pTexture);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Failed read texture", "ERROR", MB_OK | MB_ICONERROR);
	}
}

void Polygon_Finalize(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexBuffer);
}

void Polygon_Draw(void)
{
	// シェーダーを描画パイプラインに設定
	Shader_Begin();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	constexpr float x = 32.0f;
	constexpr float y = 32.0f;
	constexpr float w = 1024.0f / 2;
	constexpr float h = 1536.0f / 2;

	// 画面の左上から右下に向かう線分を描画する
	v[0].position = { x,     y,     0.0f };
	v[1].position = { x + w, y,     0.0f };
	v[2].position = { x,     y + h, 0.0f };
	v[3].position = { x + w, y + h, 0.0f };

	v[0].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[1].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[2].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	v[3].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	v[0].UV = { 0.0f, 0.0f };
	v[1].UV = { 1.0f, 0.0f };
	v[2].UV = { 0.0f, 1.0f };
	v[3].UV = { 1.0f, 1.0f };

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
	Shader_SetMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));

	// プリミティブトポロジ設定
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// Setting Texture
	g_pContext->PSSetShaderResources(0, 1, &g_pTexture);

	// ポリゴン描画命令発行
	g_pContext->Draw(NUM_VERTEX, 0);
}
