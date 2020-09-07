#pragma once
#include "gameNode.h"

#define ENDNUM 13

class gameEnd : public gameNode
{
private:
	image*	_img[ENDNUM];	// �̹���	
	BYTE	_alpha;			// ���ĺ���
	bool	_fadeOut;		// ����ȭ?
	bool	_endFinish;		// ����
	int		_arrNum;		// �迭 ī��Ʈ��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	bool getGameEnd() { return _endFinish; }
	void setGameEnd(bool end) { _endFinish = end; }
};

