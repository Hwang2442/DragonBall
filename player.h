#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"
#include "ui.h"

enum MyPlayerStat
{
	IDLE, BACK, FRONT,	// �⺻, ��, ��
	FIRE, TRANSFORM,	// �߻�, ����
	BOMB, DEAD,			// ��ź, ��ũ����?
	ULTIMATE,	
	WIN
};

enum MyGamePlay
{
	ISSTART,	// �ʱ� ����
	ISIMMOT,	// ���� �� ��񵿾� ����
	ISPLAY,		// ���� ���� ����, ������ ���ʹ����� ������ ����
	ISDEAD,		// �װ� �ִ� ����
	ISINIT,		// ���� �� �ٽ� �ʱ�ȭ
	ISULTI,		// 3�ܰ� ������
	ISWIN
};

struct tagTarget
{
	image*		img;	// ��ź�� �̹���
	animation*	ani;	// ��ź�� �ִϸ��̼�
	RECT		rc;		// ��ź�� ��Ʈ
};

struct tagAura
{
	image*		img;
	animation*	ani;
	RECT		rc;
	bool		isShield;
};

struct tagDragon
{
	image*	img;		// �巡�� �̹���
	RECT	rc;			// �巡�� ��Ʈ
	MYPOINT	center;		// ����	
	bool	letAttack;	// �ñر� ����Ʈ�� ���� ������ �Ǵ���	
	float	speed;		// �ӵ�	
};

class player : public gameNode
{
private:	
	bullet*		_bullet;			// �Ҹ�
	playerBomb* _bomb;				// ��ź
	ui*			_ui;				// UI

	image*		_img;				// �̹���
	animation*	_ani;				// �÷��̾� �ִϸ��̼�		
	string		_form;				// ���� �ܰ�?
	string		_currentImg;		// ���� �̹���
	RECT		_rc;				// �浹�� ��Ʈ
	BYTE		_alpha;				// ���ĺ��� ��
	MYPOINT		_location;			// ��ǥ
	tagTarget	_target;			// ��ź�� ����ü
	tagAura		_aura;				// �ƿ�� ����ü
	tagDragon	_dragon;			// ���� 3�ܰ� �ñر� ����	

	float		_speed;				// ���ǵ�
	float		_bulletSpeed;		// �Ҹ� ���ǵ�
	float		_currentGauge;		// ���� ������
	float		_maxGauge;			// �ִ� ������
	int			_delay;				// �ֱ�	
	int			_startCount;		// �ʱ� ������ ī��Ʈ
	int			_startDelay;		// �ʱ� ������ �����̿�	
	
	MyPlayerStat _playerState;		// ����
	MyGamePlay	_gamePlay;			// �÷��� ����

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void stateControl();
	void setAnimation(string imageName, bool loop = false);
	void startLocation();
	void ultimateAttack();

	RECT		getTargetRect()		{ return _target.rc; }
	RECT		getPlayerRect()		{ return _rc; }
	bullet*		getPlayerBullet()	{ return _bullet; }
	playerBomb* getPlayerBomb()		{ return _bomb; }

	void playerBulletDelete(int arrNum)		{ return _bullet->bulletDelete(arrNum); }	

	void setPlayerState(MyPlayerStat state) { _playerState = state; }
	void setGamePlay(MyGamePlay play) { _gamePlay = play; }
	MyGamePlay getGamePlay() { return _gamePlay; }	

	void setGauge(float gauge);
	float getGauge() { return _currentGauge; }

	void setShiled(bool shield) { _aura.isShield = shield; }

	RECT getDragonRect();
	bool getUltimate() { return _dragon.letAttack; }
};

