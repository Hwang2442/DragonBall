#pragma once
#include "gameNode.h"

class gameIntro : public gameNode
{
private:
	image*	_backGround;	// 인트로 이미지
	image*	_gameStart;		// 스타트 버튼

	bool	_startKeyDown;	// 스타트 버튼 눌렀니?
	bool	_pleaseChange;	// 게임 인트로 끝 >> 게임 플레이 시작
	
	int		_count;			// 스타트 버튼 몇 번 깜빡일지
	int		_delay;			// 딜레이용 변수

	float	_volume;		// 볼륨

	RECT	_rc;			// PtInRect() 쓸려고 만듬
	BYTE	_alpha;			// 알파블렌드 값

public:
	gameIntro();
	~gameIntro();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getChange()			{ return _pleaseChange; }
	void setChange(bool change) { _pleaseChange = change; }
};

