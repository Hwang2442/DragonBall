#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "ui.h"

enum MyBossPattern
{
	BOSS_IDLE,		// 기본
	BOSS_BACK,		// 뒤
	BOSS_FRONT,		// 앞
	BOSS_SPREAD,	// 뿌리개
	BOSS_MISSILE,	// 유도탄
	BOSS_RAIN,		// 주륵주륵
	BOSS_DEAD,		// 죽음
	BOSS_END,		// 끝남	
};

class boss : public gameNode
{
private:
	ui*			_ui;
	bullet*		_bullet;			// 불릿

	image*			_img;			// 이미지
	animation*		_ani;			// 애니메이션
	string			_currentImg;	// 현재 이미지
	RECT			_rc;			// 보스 렉트
	MYPOINT			_playerLoc;		// 플레이어 좌표

	MYPOINT			_location;		// 보스 중점
	MYPOINT			_nextMove;		// 이동할 다음 좌표

	float			_speed;			// 보스 스피드	
	float			_bulletAngle;	// 불릿 각도

	int				_patternDelay;	// 패턴 변경 딜레이
	int				_fireDelay;		// 총알 발사 딜레이
	int				_lastPattern;	// 이전 패턴 (패턴 중복 방지)
	float			_currentHp;		// 현재 체력
	float			_maxHp;			// 최대 체력
	

	bool			_isStart;		// 스타트	

	MyBossPattern	_state;			// 이미지 설정할 상태
	MyBossPattern	_pattern;		// 공격패턴 정의

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
	
	// 렉트 접근자
	RECT	getBossRect()			{ return _rc; }
	// 체력 접근자
	float	getLife()				{ return _currentHp; }
	// 체력 설정자
	void	setLife(float life)		{ _currentHp = life; if (_currentHp < 0) _currentHp = 0; }
	// 보스 불릿 접근자
	bullet* getBullet()				{ return _bullet; }

	bool getBossEnd();	
};

