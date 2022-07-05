#include "framework.h"
#include "CSceneManager.h"
#include "CTitle.h"
#include "CScene_Tool.h"
#include "CGameObject.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStageBoss.h"

CSceneManager::CSceneManager()
{
	// 씬 목록 초기화
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// 씬 목록 삭제
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::TITLEUP] = new CTitle;
	m_arrScene[(size_t)GROUP_SCENE::TITLEUP]->SetName(L"TitleUp");

	m_arrScene[(size_t)GROUP_SCENE::TITLE] = new CTitle;
	m_arrScene[(size_t)GROUP_SCENE::TITLE]->SetName(L"Title");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_01] = new CStage01;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_01]->SetName(L"Stage01");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_02] = new CStage02;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_02]->SetName(L"Stage02");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS] = new CStageBoss;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS]->SetName(L"StageBoss");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS] = new CStageBoss;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS]->SetName(L"HappyEnding");

	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS] = new CStageBoss;
	m_arrScene[(size_t)GROUP_SCENE::STAGE_BOSS]->SetName(L"BadEnding");

	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	// TODO : 나중에 타이틀로 변경
	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::TITLE];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
