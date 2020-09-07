#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "enemy.h"
#include "bullets.h"
#include "boss.h"

class enemyManager : public gameNode
{
private:
	bullet*			_bullet;		// 에너미 불릿
	vector<enemy*>	_vEnemy;		// 에너미 벡터
	boss*			_boss;			// 보스
	MYPOINT			_player;		// 플레이어 좌표

	bool			_isBossPhase;	// 보스 페이즈
	int				_enemyMax;		// 한 번 스폰될 때 에너미 최대	
	int				_enemyMin;		// 한 번 스폰될 때 에너미 최소
	int				_spawnCount;	// 에너미 스폰을 언제마다 할건지
	int				_spawnDelay;	// 에너미 스폰용 딜레이
	int				_bossSpawn;		// 보스 스폰 카운트

public:
	enemyManager();
	~enemyManager();

	HRESULT init(int enemyMin, int enemyMax, int spawnCount, int bossSpawnCount);
	void release();
	void update();
	void render();

	void enemySpawn();
	void enemyBulletFire();

	// 플레이어 렉트 중점 설정자
	void	setPlayerLocation(RECT playerRect);	
	// 에너미 벡터 접근자
	vector<enemy*> getEnemyVector()		{ return _vEnemy; }
	// 에너미 삭제
	void	enemyRemove(int arrNum)		{ _vEnemy[arrNum]->release(); _vEnemy.erase(_vEnemy.begin() + arrNum); }
	// 
	void	setBossPhase(bool phase)	{ _isBossPhase = phase; }
	// 보스 렉트 접근자
	RECT	getBossRect()				{ return _boss->getBossRect(); }	
	// 에너미 불릿 접근자
	bullet* getBullet()					{ return _bullet; }
	// 보스 접근자
	boss* getBoss() { return _boss; }

	bool getBossPhase() { return _isBossPhase; }
};