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
	gameIntro*	_intro;	// ��Ʈ�� ȭ��
	gamePlay*	_play;	// �÷��� ȭ��
	gameEnd*	_end;	// ���� ȭ��
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();	
};

