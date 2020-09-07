#pragma once
#include "gameNode.h"

#define ENDNUM 13

class gameEnd : public gameNode
{
private:
	image*	_img[ENDNUM];	// 이미지	
	BYTE	_alpha;			// 알파블렌드
	bool	_fadeOut;		// 투명화?
	bool	_endFinish;		// 끝남
	int		_arrNum;		// 배열 카운트용

public:
	HRESULT init();
	void release();
	void update();
	void render();

	bool getGameEnd() { return _endFinish; }
	void setGameEnd(bool end) { _endFinish = end; }
};

