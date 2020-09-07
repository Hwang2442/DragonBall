#pragma once
#include "gameNode.h"
#include "gameIntro.h"
#include "gamePlay.h"
#include "gameEnd.h"
#include "player.h"
#include "enemyManager.h"
#include "itemManager.h"

class playGround : public gameNode
{
private:	
	gameIntro*	_intro;	// 인트로 화면
	gamePlay*	_play;	// 플레이 화면
	gameEnd*	_end;	// 엔딩 화면
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();	
};

