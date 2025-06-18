/*==============================================================================

   Management Texture [Texture.cpp]

==============================================================================*/
#include "Texture.h"
#include "direct3d.h"
#include <string>
#include "DirectXTex.h"
using namespace DirectX;

// Max Manage Texture Count
static constexpr int TEXTURE_MAX = 256;

struct Texture
{
	std::wstring filename;
	ID3D11ShaderResourceView* pTexture;
	unsigned int width;
	unsigned int height;
};

static Texture g_Textures[TEXTURE_MAX]{};
static int g_SetTextureIndex = -1;

// 注意！初期化で外部から設定されるもの。Release不要。
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

// Reset Management Texture
void Texture_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	for (Texture& t : g_Textures)
	{
		t.pTexture = nullptr;
	}

	g_SetTextureIndex = -1;

	// デバイスとデバイスコンテキストの保存
	g_pDevice = pDevice;
	g_pContext = pContext;
}

void Texture_Finalize(void)
{
	Texture_ALLRelease();
}

int Texture_Load(const wchar_t* FileName)
{
	// If Now Reading Texture is Read Already
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// Filename Checking
		if (g_Textures[i].filename == FileName)
		{
			return i;
		}
	}

	// Find Empty Space
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Textures[i].pTexture)
			continue; // If Using >> Continue

		// Read Texture
		TexMetadata metadata;
		ScratchImage image;

		HRESULT hr = LoadFromWICFile(FileName, WIC_FLAGS_NONE, &metadata, image);

		// If Can`t Read File
		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"Failed read texture", FileName, MB_OK | MB_ICONERROR);
			return -1;
		}
		
		// Get File Info
		g_Textures[i].filename = FileName;
		g_Textures[i].width = (unsigned int)metadata.width;
		g_Textures[i].height = (unsigned int)metadata.height;

		hr = CreateShaderResourceView(g_pDevice,
			image.GetImages(), image.GetImageCount(), metadata, &g_Textures[i].pTexture);

		return i;
	}
	return -1;
}

void Texture_ALLRelease()
{
	for (Texture& t : g_Textures)
	{
		t.filename.clear();
		SAFE_RELEASE(t.pTexture);
	}
}

void Texture_SetTexture(int TexID)
{
	// Safe Triger
	if (TexID < 0)
		return;

	// If Now Reading Texture is Read Already
	if (g_SetTextureIndex == TexID)
		return;

	g_SetTextureIndex = TexID;

	// Setting Texture
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[TexID].pTexture);
}

unsigned int Texture_Width(int TexID)
{
	// Safe Triger
	if (TexID < 0)
		return 0;

	return g_Textures[TexID].width;
}

unsigned int Texture_Height(int TexID)
{
	// Safe Triger
	if (TexID < 0)
		return 0;

	return g_Textures[TexID].height;
}
