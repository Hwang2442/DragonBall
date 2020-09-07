#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "enemy.h"
#include "bullets.h"
#include "boss.h"

class enemyManager : public gameNode
{
private:
	bullet*			_bullet;		// ���ʹ� �Ҹ�
	vector<enemy*>	_vEnemy;		// ���ʹ� ����
	boss*			_boss;			// ����
	MYPOINT			_player;		// �÷��̾� ��ǥ

	bool			_isBossPhase;	// ���� ������
	int				_enemyMax;		// �� �� ������ �� ���ʹ� �ִ�	
	int				_enemyMin;		// �� �� ������ �� ���ʹ� �ּ�
	int				_spawnCount;	// ���ʹ� ������ �������� �Ұ���
	int				_spawnDelay;	// ���ʹ� ������ ������
	int				_bossSpawn;		// ���� ���� ī��Ʈ

public:
	enemyManager();
	~enemyManager();

	HRESULT init(int enemyMin, int enemyMax, int spawnCount, int bossSpawnCount);
	void release();
	void update();
	void render();

	void enemySpawn();
	void enemyBulletFire();

	// �÷��̾� ��Ʈ ���� ������
	void	setPlayerLocation(RECT playerRect);	
	// ���ʹ� ���� ������
	vector<enemy*> getEnemyVector()		{ return _vEnemy; }
	// ���ʹ� ����
	void	enemyRemove(int arrNum)		{ _vEnemy[arrNum]->release(); _vEnemy.erase(_vEnemy.begin() + arrNum); }
	// 
	void	setBossPhase(bool phase)	{ _isBossPhase = phase; }
	// ���� ��Ʈ ������
	RECT	getBossRect()				{ return _boss->getBossRect(); }	
	// ���ʹ� �Ҹ� ������
	bullet* getBullet()					{ return _bullet; }
	// ���� ������
	boss* getBoss() { return _boss; }

	bool getBossPhase() { return _isBossPhase; }
};