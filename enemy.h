#pragma once
#include "stdafx.h"
#include "gameNode.h"

enum MyEnemyType
{
	RUSH = 1,	// X�� ����
	SHOTGUN,	// 5�� �߻�
	MISSILE		// ����ź �߻�
};

class enemy : public gameNode
{
private:
	image*		_img;			// �̹���
	animation*	_ani;			// �ִϸ��̼�
	RECT		_rc;			// �浹�� ��Ʈ
	string		_imageName;			

	MYPOINT		_finalPosition;	// ȭ�� ���� �ڸ����� ��ġ
	MYPOINT		_startPosition;	// ȭ�� �ٱ����� ������ ��ǥ

	MyEnemyType _type;			// �� Ÿ��
	int			_attackRandom;	// ���� �ֱ�
	int			_attackCount;	// ���� ����
	float		_life;			// �� �� ������ �״���

	bool		_isDead;		// �׾�����
	bool		_isDelete;		// �����ص� �Ǵ���
	bool		_isStart;		// ������ �����ص� �Ǵ���
	bool		_rndWay;		// ó�� �̵� ���� (�Ʒ� : true, �� : false)
	float		_speed;			// �ӵ�

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