#pragma once
#include "xCore.h"


struct SimpleVertex  // 4*5 = 20바이트
{
	float x, y, z;
	float u, v;
};



class PipeLineSetup
{
public:
	ID3D11Buffer *				m_pVertextBuffer;
	ID3D11VertexShader*			m_pVertexShader;
	ID3D11PixelShader*			m_pPixelShader;
	ID3DBlob*					m_pVSBlob;
	ID3DBlob*					m_pPSBlob;
	ID3DBlob*					m_pErrorBlob;
	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11ShaderResourceView*	m_pTextureSRV;
	ID3D11SamplerState*			m_pSamplerState;
	ID3D11BlendState*			m_pAlphaBlend;

public:
	ID3D11Buffer*    m_pIndexBuffer;


public: // 래스터라이져
	D3D11_VIEWPORT		m_ViewPort;
	UINT iRectWidth;
	UINT iRectHeight;
	void For_Viewport_get_set();


	ID3D11RasterizerState* m_RasterizerState;
	void Create_RasterizerState();



public: // 깊이 스텐실 버퍼

	ID3D11Texture2D * pDSTexture;
	ID3D11DepthStencilView*		pDSV;
	void						CreateTexture2D_DepthStencilView();


	bool						m_bDepthEnable;
	ID3D11DepthStencilState*	m_pDepthStencilState;
	void						CreateDepthStencilState();




public:

	HRESULT CreateVertextBuffer(ID3D11Device* pd3dDevice, SimpleVertex* pVertexList, int iNumCount);
	HRESULT CreateVertexShader(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT CreateLayout(ID3D11Device* pd3dDevice);
	HRESULT CreatePixelShader(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile);
	HRESULT SetBlendState(ID3D11Device* pd3dDevice);
	HRESULT CreateIndexBuffer(ID3D11Device* pd3dDevice, UINT index_counts, void* index_list);


public:
	bool Init(ID3D11Device* pd3dDevice, const TCHAR* p_Texture_LoadFile, SimpleVertex* pVertexList, int iNumCount, const TCHAR* p_Vertex_shader_Name, const TCHAR* p_Pixel_shader_Name)
	{
		
		LoadTexture(g_pd3dDevice, p_Texture_LoadFile);
		SetBlendState(pd3dDevice);
		CreateVertextBuffer(g_pd3dDevice, pVertexList, iNumCount);
		CreateVertexShader(g_pd3dDevice, p_Vertex_shader_Name);
		CreateLayout(g_pd3dDevice);
		CreatePixelShader(g_pd3dDevice, p_Pixel_shader_Name);
		return true;
	}

	bool PreRender(ID3D11DeviceContext* pContext)
	{
		//


		pContext->IASetInputLayout(m_pVertexLayout);
		UINT pStrides = sizeof(SimpleVertex);
		UINT pOffsets = 0; //*** 정점버퍼의 처리는 정점1개 단위로 연산된다.

		pContext->IASetVertexBuffers(0, 1, &m_pVertextBuffer, &pStrides, &pOffsets);
		pContext->VSSetShader(m_pVertexShader, NULL, NULL);
		pContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
		pContext->PSSetShader(m_pPixelShader, NULL, NULL);//0
		pContext->PSSetSamplers(0, 1, &m_pSamplerState);


		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pContext->RSSetViewports(1, &m_ViewPort);
		pContext->RSSetState(m_RasterizerState);
		//래스터라이져 셋.

		pContext->OMSetBlendState(m_pAlphaBlend, 0, -1);
		pContext->OMSetDepthStencilState(m_pDepthStencilState, 0);
		// 깊이스텐실스테이트 셋.


		return true;
	}
	bool Render(ID3D11DeviceContext* pContext)
	{
		PreRender(pContext);
		PostRender(pContext);

		return true;
	}
	bool PostRender(ID3D11DeviceContext* pContext)
	{
		pContext->Draw(6, 0);
		return true;
	}

	bool Release()
	{
		if (m_pPixelShader != NULL)  m_pPixelShader->Release();
		if (m_pVertexShader != NULL) m_pVertexShader->Release();

		//	if (m_pPSBlob != NULL) m_pPSBlob->Release();
		if (m_pVSBlob != NULL) m_pVSBlob->Release();
		if (m_pErrorBlob != NULL)m_pErrorBlob->Release();


		if (m_pVertextBuffer != NULL) m_pVertextBuffer->Release();
		if (m_pTextureSRV != NULL)m_pTextureSRV->Release();
		if (m_pVertexLayout != NULL) m_pVertexLayout->Release();


		if (m_pAlphaBlend != NULL)m_pAlphaBlend->Release();
		if (m_pSamplerState != NULL)m_pSamplerState->Release();
		if (m_RasterizerState != NULL)m_RasterizerState->Release();
		if (m_pDepthStencilState != NULL)m_pDepthStencilState->Release();


		m_pDepthStencilState = NULL;
		m_pSamplerState = NULL;
		m_RasterizerState = NULL;
		m_pAlphaBlend = NULL;

		m_pVSBlob = NULL;
		m_pPSBlob = NULL;
		m_pErrorBlob = NULL;
		m_pVertexLayout = NULL;
		m_pTextureSRV = NULL;
		m_pVertextBuffer = NULL;

		m_pVertexShader = NULL;
		m_pPixelShader = NULL;
		m_pVertexLayout = NULL;

		return true;
	}
public:
	PipeLineSetup() {


		m_pVertextBuffer = nullptr;
		m_pVertexShader = nullptr;
		
		m_pPixelShader = nullptr;
		m_pVSBlob = nullptr;
		m_pPSBlob = nullptr;
		m_pErrorBlob = nullptr;
		m_pVertexLayout = nullptr;
		m_pTextureSRV = nullptr;

		m_pSamplerState = nullptr;
		m_pAlphaBlend = nullptr;
		m_pDepthStencilState = nullptr;
		m_RasterizerState = nullptr;
	}
	~PipeLineSetup() {}
};




HRESULT PipeLineSetup::CreateIndexBuffer(ID3D11Device* pd3dDevice, UINT index_counts, void* index_list)
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd; // 집어넣을 데이터
	ZeroMemory(&bd, sizeof(bd));
	ZeroMemory(&sd, sizeof(sd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = index_counts * sizeof(UINT);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	sd.pSysMem = &index_list;

	if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
	{
		return hr;;
	}

	return hr;
}

void	PipeLineSetup::CreateTexture2D_DepthStencilView()
{

	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = g_rtClient.right;
	DescDepth.Height = g_rtClient.bottom;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	g_pd3dDevice->CreateTexture2D(&DescDepth, NULL, &pDSTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC  dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DescDepth.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	g_pd3dDevice->CreateDepthStencilView(pDSTexture, &dsvd, &pDSV);

}


void PipeLineSetup::CreateDepthStencilState()
{
	//--------------------------------------------------------------------------------------
	// 깊이 및 스텐실 버퍼 상태객체 생성 
	//--------------------------------------------------------------------------------------		
	D3D11_DEPTH_STENCIL_DESC dsd;
	memset(&dsd, 0, sizeof(dsd));

	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS; // D3D11_COMPARISON_GREATER

										   // 솔직히 이게 뭔지 잘 모르겠어요.
	dsd.StencilEnable = TRUE;
	dsd.StencilReadMask = 0xff;
	dsd.StencilWriteMask = 0xff;

	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	// 디폴트 값
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;


	g_pd3dDevice->CreateDepthStencilState(&dsd, &m_pDepthStencilState);
}


void PipeLineSetup::For_Viewport_get_set()
{
	iRectWidth = (FLOAT)g_rtClient.right;
	iRectHeight = (FLOAT)g_rtClient.bottom;

	m_ViewPort.Width = iRectWidth;
	m_ViewPort.Height = iRectHeight;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;

}

void PipeLineSetup::Create_RasterizerState()
{
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	g_pd3dDevice->CreateRasterizerState(&rd, &m_RasterizerState);
}

HRESULT  PipeLineSetup::CreateVertextBuffer(ID3D11Device* pd3dDevice, SimpleVertex* pVertexList, int iNumCount)
{
	HRESULT hr;
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));

	pDesc.ByteWidth = sizeof(SimpleVertex)*iNumCount;

	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData, sizeof(pInitialData));

	pInitialData.pSysMem = pVertexList;

	if (FAILED(hr = pd3dDevice->CreateBuffer(
		&pDesc,
		&pInitialData,
		&m_pVertextBuffer)))
	{
		return hr;
	}

	return hr;
}
HRESULT PipeLineSetup::CreateVertexShader(ID3D11Device* pd3dDevice, const TCHAR* pszFileName)
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(pszFileName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &m_pVSBlob, &m_pErrorBlob, NULL);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());
		return false;
	}

	//4)정점쉐이더 생성
	// 정점버퍼의 정점을 실제 처리하는 곳-->정점쉐이더

	if (FAILED(hr = g_pd3dDevice->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		return hr;
	}
	return hr;
}
HRESULT PipeLineSetup::CreatePixelShader(ID3D11Device* pd3dDevice, const TCHAR* pszFileName)
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(pszFileName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &m_pPSBlob, &m_pErrorBlob, NULL);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());
		return false;
	}

	if (FAILED(hr = g_pd3dDevice->CreatePixelShader(
		m_pPSBlob->GetBufferPointer(),
		m_pPSBlob->GetBufferSize(), NULL, &m_pPixelShader)))
	{
		m_pPSBlob->Release();
		return NULL;
	}
	m_pPSBlob->Release();
	return hr;
}

HRESULT PipeLineSetup::CreateLayout(ID3D11Device* pd3dDevice)
{
	HRESULT hr;
	if (m_pVSBlob == NULL) return	E_FAIL;
	//6)레이아웃 설정

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	int iNumElement = sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	if (FAILED(hr = g_pd3dDevice->CreateInputLayout(
		ied, iNumElement,
		m_pVSBlob->GetBufferPointer(),
		m_pVSBlob->GetBufferSize(),
		&m_pVertexLayout)))
	{
		return hr;
	}
	return hr;
}

HRESULT PipeLineSetup::LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile)
{
	HRESULT hr;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, pLoadFile, NULL, NULL, &m_pTextureSRV, NULL)))
	{
		return hr;
	}
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_pd3dDevice->CreateSamplerState(&sd, &m_pSamplerState);
	return hr;
}

HRESULT PipeLineSetup::SetBlendState(ID3D11Device* pd3dDevice)
{
	HRESULT hr = S_OK;
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.RenderTarget[0].BlendEnable = true;
	//FinalColor = destColor * DescBlend + srcColor * SrcBlend;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//FinalAlpha = destAlpha * DescBlendAlpha + srcAlpha * SrcBlendAlpha;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = g_pd3dDevice->CreateBlendState(&bd, (ID3D11BlendState **)&m_pAlphaBlend);
	return hr;
}
