#include "stdafx.h"
#include "gameIntro.h"

gameIntro::gameIntro()
{
}

gameIntro::~gameIntro()
{
}

HRESULT gameIntro::init()
{
	_backGround = IMAGEMANAGER->findImage("게임 인트로");
	_gameStart = IMAGEMANAGER->findImage("스타트 오프");		

	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, _gameStart->getWidth(), _gameStart->getHeight());

	_startKeyDown = _pleaseChange = _count = _delay = 0;
	_alpha = 255;
	_volume = 1.0f;

	SOUNDMANAGER->stop("피니쉬");
	SOUNDMANAGER->stop("오프닝");
	SOUNDMANAGER->stop("플레이");

	SOUNDMANAGER->play("오프닝", _volume);

	return S_OK;
}

void gameIntro::release()
{
}

void gameIntro::update()
{
	if (PtInRect(&_rc, _ptMouse))
	{
		_gameStart = IMAGEMANAGER->findImage("스타트 오온");
	}
	else if(!_startKeyDown)
	{
		_gameStart = IMAGEMANAGER->findImage("스타트 오프");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_rc, _ptMouse))
	{
		_startKeyDown = true;		
		_count = 1;
	}

	if (_startKeyDown && _count % 5 != 0)
	{
		_delay++;
		if (_delay % 5 == 0)
		{
			_delay = 0;
			_alpha = 255;
			_count++;
		}
		else
		{
			_alpha = 0;
		}
	}
	if(_count % 5 == 0 && _count != 0)
	{		
		_alpha -= 2;
		_volume -= 0.008f;
		SOUNDMANAGER->setVolume("오프닝", _volume);
		
		if (_alpha <= 2)
		{
			_alpha = 0;
			_pleaseChange = true;			
			SOUNDMANAGER->stop("오프닝");
		}
	}
}

void gameIntro::render()
{

	if (_startKeyDown && _count % 5 == 0)
	{
		_backGround->alphaRender(getMemDC(), _alpha);
	}
	else
	{
		_backGround->alphaRender(getMemDC(), 255);
	}	
	_gameStart->alphaRender(getMemDC(), _rc.left, _rc.top, _alpha);
}
