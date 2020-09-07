#pragma once
#include "gameNode.h"

class gameIntro : public gameNode
{
private:
	image*	_backGround;	// ��Ʈ�� �̹���
	image*	_gameStart;		// ��ŸƮ ��ư

	bool	_startKeyDown;	// ��ŸƮ ��ư ������?
	bool	_pleaseChange;	// ���� ��Ʈ�� �� >> ���� �÷��� ����
	
	int		_count;			// ��ŸƮ ��ư �� �� ��������
	int		_delay;			// �����̿� ����

	float	_volume;		// ����

	RECT	_rc;			// PtInRect() ������ ����
	BYTE	_alpha;			// ���ĺ��� ��

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

