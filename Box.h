#pragma once
#include "Object_Handling.h"

class Box : public Object_Handling
{
public:

	bool  Set_VertexData();
	bool  Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile);

public:

	Box()	{}
	~Box() {}
};

bool  Box::Set_VertexData()
{
	m_VertexList[0].x = -0.5f; m_VertexList[0].y = 0.5f;  m_VertexList[0].z = 0.0f; m_VertexList[0].u = 0.0f;	m_VertexList[0].v = 0.0f;
	m_VertexList[1].x = 0.5f; m_VertexList[1].y = 0.5f;  m_VertexList[1].z = 0.0f; m_VertexList[1].u = 1.0f;	m_VertexList[1].v = 0.0f;
	m_VertexList[2].x = -0.5f; m_VertexList[2].y = -0.5f; m_VertexList[2].z = 0.0f; m_VertexList[2].u = 0.0f;	m_VertexList[2].v = 1.0f;
	m_VertexList[3].x = -0.5f; m_VertexList[3].y = -0.5f; m_VertexList[3].z = 0.0f; m_VertexList[3].u = 0.0f;	m_VertexList[3].v = 1.0f;
	m_VertexList[4].x = 0.5f; m_VertexList[4].y = 0.5f; m_VertexList[4].z = 0.0f; m_VertexList[4].u = 1.0f; m_VertexList[4].v = 0.0f;
	m_VertexList[5].x = 0.5f; m_VertexList[5].y = -0.5f; m_VertexList[5].z = 0.0f; m_VertexList[5].u = 1.0f;	m_VertexList[5].v = 1.0f;

	return true;
}


bool    Box::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	PipeLineSetup.LoadTexture(pd3dDevice, pTexFile);
	PipeLineSetup.SetBlendState(pd3dDevice);
	PipeLineSetup.CreateVertextBuffer(pd3dDevice, m_VertexList, 6);
	PipeLineSetup.CreateVertexShader(pd3dDevice, pVsFile);
	PipeLineSetup.CreateLayout(pd3dDevice);
	PipeLineSetup.CreatePixelShader(pd3dDevice, pPsFile);


	PipeLineSetup.For_Viewport_get_set();
	PipeLineSetup.Create_RasterizerState();
	PipeLineSetup.CreateTexture2D_DepthStencilView();
	PipeLineSetup.CreateDepthStencilState();
	return true;
}

