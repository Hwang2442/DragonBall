#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "itemManager.h"

class gamePlay : public gameNode
{
private:
	player*			_player;
	enemyManager*	_em;
	itemManager*	_itemM;

	int		_loopX;		// 이미지 루프할 값
	int		_gokuLife;	// 재시작 횟수
	int		_count;		// 그냥 카운트
	bool	_gameEnd;	// 게임 종료
	bool	_gameOver;	// 게임 오버
	int		_getBall;	// 현재 드래곤볼 몇개 모았는지
	BYTE	_alpha;		// 알파값
	BYTE	_backAlpha;	// 백 앞아
	float	_volume;	// 소리크기

public:
	gamePlay();
	~gamePlay();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void playerEnemyCollision();

	bool getGameEnd() { return _gameEnd; }
	void setGameEnd(bool end) { _gameEnd = end; }

	bool getGameOver() { return _gameOver; }
	void setGameOver(bool over) { _gameOver = over; }
};

