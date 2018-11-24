#include "Plane.h"



int end_decision;

enum TSceneState
{
	GAME_SCENE_LOBBY = 0,
	GAME_SCENE_PLAY = 1,
	GAME_SCENE_END = 2,
};

class TScene
{
public:
	int		m_iSceneID;
	bool	m_bNextSceneStart;

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }

public:
	TScene()
	{
		m_bNextSceneStart = false;
	}
	virtual ~TScene() {}
};



class TSceneLobby : public TScene
{
public:
	
	Plane					UI_BUTTON;

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneLobby();
	virtual ~TSceneLobby();
};

bool	TSceneLobby::Init()
{
	
	UI_BUTTON.Set_VertexData();
	UI_BUTTON.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../love.jpg");
	return true;
};

 
bool	TSceneLobby::Frame()
{
	



	

	return true;
};


bool	TSceneLobby::Render()
{


	
	UI_BUTTON.Render(g_pContext);
	

	return true;
};

bool	TSceneLobby::Release()
{
	
	
	return true;
};
TSceneLobby::TSceneLobby()
{
	m_iSceneID = GAME_SCENE_LOBBY;
	m_bNextSceneStart = false;
}
TSceneLobby::~TSceneLobby()
{

}

















class TSceneGame : public TScene
{
public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

public:

	TSceneGame();
	virtual ~TSceneGame();
};



TSceneGame::TSceneGame()
{
	m_iSceneID = GAME_SCENE_PLAY;
	m_bNextSceneStart = false;
}

bool   TSceneGame::Init()
{

	return true;
};

bool    TSceneGame::Frame()
{

	return true;
}

bool   TSceneGame::Render()
{

	return true;
}

bool    TSceneGame::Release()
{
	return true;
}

TSceneGame::~TSceneGame()
{
}



class TSceneEnd : public TScene
{

public:

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:

	TSceneEnd();
	virtual ~TSceneEnd();
};




bool	TSceneEnd::Init()
{



	return true;
};
bool	TSceneEnd::Frame()
{


	return true;
};

bool	TSceneEnd::Render()
{

	return true;
};

bool	TSceneEnd::Release()
{
	return true;
};

TSceneEnd::TSceneEnd()
{
	m_iSceneID = GAME_SCENE_END;
	m_bNextSceneStart = false;
}

TSceneEnd::~TSceneEnd()
{}

