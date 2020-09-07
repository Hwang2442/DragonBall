#pragma once
#include "gameNode.h"

enum MyItemType
{
	AURA = 1,	// 아우라 한대는 버티게 해줌
	LIFE,		// 생명 추가
	STAR		// 드래곤볼
};

class item : public gameNode
{
private:
	MyItemType	_type;		// 타입
	image*		_img;		// 이미지
	animation*	_ani;		// 애니메이션
	RECT		_rc;		// 렉트
	MYPOINT		_pos;		// 좌표

	bool		_isDelete;	// 삭제?
	float		_angle;		// 각도
	float		_speed;		// 속도
	int			_count;		// 화면 튕긴 횟수

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

