#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"
#include "ui.h"

enum MyPlayerStat
{
	IDLE, BACK, FRONT,	// 기본, 뒤, 앞
	FIRE, TRANSFORM,	// 발사, 변신
	BOMB, DEAD,			// 폭탄, 웅크리기?
	ULTIMATE,	
	WIN
};

enum MyGamePlay
{
	ISSTART,	// 초기 시작
	ISIMMOT,	// 시작 시 잠깐동안 무적
	ISPLAY,		// 정말 시작 상태, 보스나 에너미한테 맞으면 죽음
	ISDEAD,		// 죽고 있는 상태
	ISINIT,		// 죽은 후 다시 초기화
	ISULTI,		// 3단계 실행중
	ISWIN
};

struct tagTarget
{
	image*		img;	// 피탄면 이미지
	animation*	ani;	// 피탄면 애니메이션
	RECT		rc;		// 피탄면 렉트
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
	image*	img;		// 드래곤 이미지
	RECT	rc;			// 드래곤 렉트
	MYPOINT	center;		// 중점	
	bool	letAttack;	// 궁극기 이펙트가 이제 나가도 되는지	
	float	speed;		// 속도	
};

class player : public gameNode
{
private:	
	bullet*		_bullet;			// 불릿
	playerBomb* _bomb;				// 폭탄
	ui*			_ui;				// UI

	image*		_img;				// 이미지
	animation*	_ani;				// 플레이어 애니메이션		
	string		_form;				// 변신 단계?
	string		_currentImg;		// 현재 이미지
	RECT		_rc;				// 충돌용 렉트
	BYTE		_alpha;				// 알파블렌딩 값
	MYPOINT		_location;			// 좌표
	tagTarget	_target;			// 피탄면 구조체
	tagAura		_aura;				// 아우라 구조체
	tagDragon	_dragon;			// 오공 3단계 궁극기 모음	

	float		_speed;				// 스피드
	float		_bulletSpeed;		// 불릿 스피드
	float		_currentGauge;		// 현재 게이지
	float		_maxGauge;			// 최대 게이지
	int			_delay;				// 주기	
	int			_startCount;		// 초기 깜빡일 카운트
	int			_startDelay;		// 초기 깜빡일 딜레이용	
	
	MyPlayerStat _playerState;		// 상태
	MyGamePlay	_gamePlay;			// 플레이 상태

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

