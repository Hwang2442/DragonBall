#pragma once
#include "gameNode.h"

enum MyItemType
{
	AURA = 1,	// �ƿ�� �Ѵ�� ��Ƽ�� ����
	LIFE,		// ���� �߰�
	STAR		// �巡�ﺼ
};

class item : public gameNode
{
private:
	MyItemType	_type;		// Ÿ��
	image*		_img;		// �̹���
	animation*	_ani;		// �ִϸ��̼�
	RECT		_rc;		// ��Ʈ
	MYPOINT		_pos;		// ��ǥ

	bool		_isDelete;	// ����?
	float		_angle;		// ����
	float		_speed;		// �ӵ�
	int			_count;		// ȭ�� ƨ�� Ƚ��

public:
	item();
	~item();

	HRESULT init(string imageName, float x, float y, float angle, MyItemType type, float speed);
	void release();
	void update();
	void render();

	void setItemDelete(bool remove) { _isDelete = remove; }
	bool getItemDelete()			{ return _isDelete; }

	MyItemType  getItemType()		{ return _type; }
	RECT		getItemRect()		{ return _rc; }
};

