#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum MyRender
{
	LEFTTOP,
	LEFTBOT,
	RIGHTTOP,
	RIGHTBOT
};

class ui : public gameNode
{
private:
	progressBar*_pBar;			// 프로그레스 바
	image*		 _img;			// 이미지
	float		 _x, _y;		// 출력 좌표
	MyRender	 _renderLoc;	// 출력할 위치

public:
	ui();
	~ui();

	HRESULT init(string imageName, MyRender renderLoc);
	void release();
	void update();
	void render();

	void setProgress(int currentGauge, int maxGauge) { _pBar->setGauge(currentGauge, maxGauge); }
};

