#pragma once
#include "stdafx.h"
#include "gameNode.h"

enum MyEnemyType
{
	RUSH = 1,	// X축 돌진
	SHOTGUN,	// 5발 발사
	MISSILE		// 유도탄 발사
};

class enemy : public gameNode
{
private:
	image*		_img;			// 이미지
	animation*	_ani;			// 애니메이션
	RECT		_rc;			// 충돌용 렉트
	string		_imageName;			

	MYPOINT		_finalPosition;	// 화면 내에 자리잡을 위치
	MYPOINT		_startPosition;	// 화면 바깥에서 시작할 좌표

	MyEnemyType _type;			// 적 타입
	int			_attackRandom;	// 공격 주기
	int			_attackCount;	// 공격 세팅
	float		_life;			// 몇 번 때려야 죽는지

	bool		_isDead;		// 죽었는지
	bool		_isDelete;		// 삭제해도 되는지
	bool		_isStart;		// 공격을 시작해도 되는지
	bool		_rndWay;		// 처음 이동 방향 (아래 : true, 위 : false)
	float		_speed;			// 속도

public:
	enemy();
	~enemy();

	HRESULT init(string imageName, float x, float y, MyEnemyType enemyType);
	void release();
	void update();
	void render();

	bool bulletCountFire();

	MyEnemyType getEnemyType()			{ return _type; }
	RECT		getRectEnemy()			{ return _rc; }
	float		getEnemyLife()			{ return _life; }
	void		setEnemyLife(float life){ _life = life; }

	bool		getEnemyDelete()		{ return _isDelete; }
	
};