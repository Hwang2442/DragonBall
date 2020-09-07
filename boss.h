#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "ui.h"

enum MyBossPattern
{
	BOSS_IDLE,		// �⺻
	BOSS_BACK,		// ��
	BOSS_FRONT,		// ��
	BOSS_SPREAD,	// �Ѹ���
	BOSS_MISSILE,	// ����ź
	BOSS_RAIN,		// �ָ��ָ�
	BOSS_DEAD,		// ����
	BOSS_END,		// ����	
};

class boss : public gameNode
{
private:
	ui*			_ui;
	bullet*		_bullet;			// �Ҹ�

	image*			_img;			// �̹���
	animation*		_ani;			// �ִϸ��̼�
	string			_currentImg;	// ���� �̹���
	RECT			_rc;			// ���� ��Ʈ
	MYPOINT			_playerLoc;		// �÷��̾� ��ǥ

	MYPOINT			_location;		// ���� ����
	MYPOINT			_nextMove;		// �̵��� ���� ��ǥ

	float			_speed;			// ���� ���ǵ�	
	float			_bulletAngle;	// �Ҹ� ����

	int				_patternDelay;	// ���� ���� ������
	int				_fireDelay;		// �Ѿ� �߻� ������
	int				_lastPattern;	// ���� ���� (���� �ߺ� ����)
	float			_currentHp;		// ���� ü��
	float			_maxHp;			// �ִ� ü��
	

	bool			_isStart;		// ��ŸƮ	

	MyBossPattern	_state;			// �̹��� ������ ����
	MyBossPattern	_pattern;		// �������� ����

public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayerRect(MYPOINT playerLoc) { _playerLoc = playerLoc; }

	void patternControl();
	void stateControl();
	void setAnimation(string imageName, bool loop = false);
	void setLocation();
	
	// ��Ʈ ������
	RECT	getBossRect()			{ return _rc; }
	// ü�� ������
	float	getLife()				{ return _currentHp; }
	// ü�� ������
	void	setLife(float life)		{ _currentHp = life; if (_currentHp < 0) _currentHp = 0; }
	// ���� �Ҹ� ������
	bullet* getBullet()				{ return _bullet; }

	bool getBossEnd();	
};

