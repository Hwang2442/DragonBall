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
	progressBar*_pBar;			// ���α׷��� ��
	image*		 _img;			// �̹���
	float		 _x, _y;		// ��� ��ǥ
	MyRender	 _renderLoc;	// ����� ��ġ

public:
	ui();
	~ui();

	HRESULT init(string imageName, MyRender renderLoc);
	void release();
	void update();
	void render();

	void setProgress(int currentGauge, int maxGauge) { _pBar->setGauge(currentGauge, maxGauge); }
};

