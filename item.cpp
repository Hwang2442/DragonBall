#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(string imageName, float x, float y, float angle, MyItemType type, float speed)
{
	_ani = new animation;
	_img = IMAGEMANAGER->findImage(imageName);

	_pos = { x, y };

	_type = type;
	switch (_type)
	{
		case AURA: case LIFE:
		{
			_rc = RectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth(), _img->getFrameHeight());

			_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
			_ani->setDefPlayFrame(false, true);
			_ani->setFPS(1);
			_ani->start();
			break;
		}				
		case STAR:
		{
			_rc = RectMakeCenter(_pos.x, _pos.y, _img->getWidth(), _img->getHeight());
			break;
		}
		
	}

	_angle = angle;
	_speed = speed;
	_count = _isDelete = 0;	

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	_pos.move(cosf(_angle) * _speed, -sinf(_angle) * _speed);
		
	if (_rc.left < 0)			// 화면 왼쪽으로 나가면
	{
		_count++;
		_angle = PI - _angle;
		_pos.x = (_type == STAR) ? _img->getWidth() / 2 : _img->getFrameWidth() / 2;	
	}
	if (_rc.right > WINSIZEX)	// 화면 오른쪽으로 나가면
	{
		_count++;
		_angle = PI - _angle;
		_pos.x = (_type == STAR) ? WINSIZEX - _img->getWidth() / 2 : WINSIZEX - _img->getFrameWidth() / 2;
	}
	if (_rc.top < 0)			// 화면 위쪽으로 나가면
	{
		_count++;
		_angle = PI2 - _angle;
		_pos.y = (_type == STAR) ? _img->getHeight() / 2 : _img->getFrameHeight() / 2;
	}
	if (_rc.bottom > WINSIZEY)	// 화면 아래쪽으로 나가면
	{
		_count++;
		_angle = PI2 - _angle;
		_pos.y = (_type == STAR) ? WINSIZEY - _img->getHeight() / 2 : WINSIZEY - _img->getFrameHeight() / 2;
	}	
	if (_count >= 6) _isDelete = true;

	switch (_type)
	{
		case AURA: case LIFE:
		{
			_rc = RectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth(), _img->getFrameHeight());
			_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
			break;
		}		
		case STAR:
		{
			_rc = RectMakeCenter(_pos.x, _pos.y, _img->getWidth(), _img->getHeight());
			break;
		}		
	}	
}

void item::render()
{
	switch (_type)
	{
		case AURA: case LIFE:
		{
			_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
			break;
		}
		case STAR:
		{
			_img->render(getMemDC(), _rc.left, _rc.top);
			break;
		}		
	}
}
