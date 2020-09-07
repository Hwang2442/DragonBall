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

	int		_loopX;		// �̹��� ������ ��
	int		_gokuLife;	// ����� Ƚ��
	int		_count;		// �׳� ī��Ʈ
	bool	_gameEnd;	// ���� ����
	bool	_gameOver;	// ���� ����
	int		_getBall;	// ���� �巡�ﺼ � ��Ҵ���
	BYTE	_alpha;		// ���İ�
	BYTE	_backAlpha;	// �� �վ�
	float	_volume;	// �Ҹ�ũ��

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

