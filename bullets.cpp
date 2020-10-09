#include "stdafx.h"
#include "bullets.h"

bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(string imageName, float x, float y, float speed, float angle, int frame)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));

	bullet.img = IMAGEMANAGER->findImage(imageName);

	bullet.ani = new animation;
	bullet.ani->init(bullet.img->getWidth(), bullet.img->getHeight(), bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	bullet.ani->setDefPlayFrame(false, true);
	bullet.ani->setFPS(1);
	bullet.ani->start();

	bullet.x = x;
	bullet.y = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	bullet.speed = speed;
	bullet.angle = angle;	// 매개변수 없으면 0

	_vBullet.push_back(bullet);

	_frame = frame;			// 매개변수 없으면 10

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	for (int i = 0; i < _vBullet.size();)
	{
		_vBullet[i].x +=  cosf(_vBullet[i].angle) * _vBullet[i].speed;	// 중점 각도만큼 이동
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;	// 중점 각도만큼 이동
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y, _vBullet[i].img->getFrameWidth(), _vBullet[i].img->getFrameHeight()); // 렉트 갱신

		_vBullet[i].ani->frameUpdate(TIMEMANAGER->getElapsedTime() * _frame);	// 프레입 업데이트

		// 화면 바깥으로 나가면
		if (screenOverCheck(_vBullet[i].rc))
		{
			// 삭제
			delete _vBullet[i].ani;
			_vBullet.erase(_vBullet.begin() + i);
		}
		else
		{
			i++;
		}
	}	
}

void bullet::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].img->aniRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].ani);		
	}	
}

void bullet::bulletDelete(int arrNum)
{	
	// 해당 숫자의 배열 삭제
	delete _vBullet[arrNum].ani;
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void bullet::setBulletSpeed(int arrNum, float speed)
{
	// 해당 숫자의 스피드 변경
	_vBullet[arrNum].speed = speed;
}

bool bullet::screenOverCheck(RECT bulletRect)
{
	if (bulletRect.left > WINSIZEX)	return true;	// 화면 오른쪽으로 나가면
	if (bulletRect.right < 0)		return true;	// 화면 왼쪽으로 나가면
	if (bulletRect.bottom < 0)		return true;	// 화면 위쪽으로 나가면
	if (bulletRect.bottom > WINSIZEY)				// 화면 아래쪽으로 나가면
	{
		// 이펙트 처리
		EFFECTMANAGER->play("지면 불릿효과", (bulletRect.left + bulletRect.right) / 2, WINSIZEY - 32);
		SOUNDMANAGER->stop("지면 충돌");
		SOUNDMANAGER->play("지면 충돌");
		return true;
	}

	return false;
}

playerBomb::playerBomb()
{
}

playerBomb::~playerBomb()
{
}

HRESULT playerBomb::init(string imageName, float x, float y, float speed)
{
	if (_isFire) return S_OK;

	tagBomb bomb[2];	// 처음에는 2개 만들고 시작
	
	ZeroMemory(&_bombStart, sizeof(_bombStart));
	ZeroMemory(&_bombFinal, sizeof(_bombFinal));

	_bombStart.img = IMAGEMANAGER->findImage(imageName + " 시작");
	_bombStart.rc = RectMake(x, y, _bombStart.img->getWidth(), _bombStart.img->getHeight());	// 시작은 플레이어 바로앞에
	_bombStart.x = (_bombStart.rc.left + _bombStart.rc.right) / 2;
	_bombStart.y = (_bombStart.rc.top + _bombStart.rc.bottom) / 2;

	for (int i = 0; i < 2; i++)
	{
		bomb[i].img = IMAGEMANAGER->findImage(imageName + " 중간");
		bomb[i].speed = speed;
	}

	bomb[0].rc = RectMake(_bombStart.rc.right, _bombStart.rc.top, bomb[0].img->getWidth(), bomb[0].img->getHeight());	// 0은 스타트 바로 앞에
	bomb[1].rc = RectMake(bomb[0].rc.right, _bombStart.rc.top, bomb[1].img->getWidth(), bomb[1].img->getHeight());		// 1은 0 바로 앞에
	
	for (int i = 0; i < 2; i++)
	{
		bomb[i].x = (bomb[i].rc.left + bomb[i].rc.right) / 2;
		bomb[i].y = (bomb[i].rc.top + bomb[i].rc.bottom) / 2;
		_vBombMid.push_back(bomb[i]);
	}	

	_bombFinal.img = IMAGEMANAGER->findImage(imageName + " 끝점");
	_bombFinal.rc = RectMake(bomb[1].rc.right, _bombStart.rc.top, _bombFinal.img->getWidth(), _bombFinal.img->getHeight());	// 끝은 1 바로 앞에
	_bombFinal.x = (_bombFinal.rc.left + _bombFinal.rc.right) / 2;
	_bombFinal.y = (_bombFinal.rc.top + _bombFinal.rc.bottom) / 2;
	_bombFinal.speed = speed;

	_isFire = true;
	
	return S_OK;
}

void playerBomb::release()
{
}

void playerBomb::update()
{
	bombMove();
}

void playerBomb::render()
{	
	if (_vBombMid.size())
	{		
		for (int i = 0; i < _vBombMid.size(); i++)
		{
			_vBombMid[i].img->render(getMemDC(), _vBombMid[i].rc.left, _vBombMid[i].rc.top);
			if(_isFire) 
				_bombStart.img->render(getMemDC(), _bombStart.rc.left, _bombStart.rc.top);
			_bombFinal.img->render(getMemDC(), _bombFinal.rc.left, _bombFinal.rc.top);
		}		
	}	
}

void playerBomb::bombFire(float x, float y)
{
	_bombStart.rc = RectMake(x, y, _bombStart.img->getWidth(), _bombStart.img->getHeight());	// 스타트 위치 조정
	_bombStart.x = (_bombStart.rc.left + _bombStart.rc.right) / 2;
	_bombStart.y = (_bombStart.rc.top + _bombStart.rc.bottom) / 2;

	_vBombMid[0].rc = RectMake(_bombStart.rc.right, _bombStart.rc.top, _vBombMid[0].img->getWidth(), _vBombMid[0].img->getHeight());	// 중간 위치 조정
	_vBombMid[0].x = (_vBombMid[0].rc.left + _vBombMid[0].rc.right) / 2;
	_vBombMid[0].y = (_vBombMid[0].rc.top + _vBombMid[0].rc.bottom) / 2;

	for (int i = 1; i < _vBombMid.size(); i++)
	{
		_vBombMid[i].rc = RectMake(_vBombMid[i - 1].rc.right, _bombStart.rc.top, _vBombMid[i].img->getWidth(), _vBombMid[i].img->getHeight());
		_vBombMid[i].x = (_vBombMid[i].rc.left + _vBombMid[i].rc.right) / 2;
		_vBombMid[i].y = (_vBombMid[i].rc.top + _vBombMid[i].rc.bottom) / 2;
	}
}

void playerBomb::bombMove()
{
	if (_isFire)
	{
		if (_bombFinal.rc.left < WINSIZEX)
		{
			_bombFinal.x += _bombFinal.speed;
			_bombFinal.rc = RectMakeCenter(_bombFinal.x, _bombStart.y, _bombFinal.img->getWidth(), _bombFinal.img->getHeight());						
		}						
		if (_bombFinal.rc.left - _vBombMid[_vBombMid.size() - 1].rc.right >= 0)
		{
			tagBomb bomb;
			ZeroMemory(&bomb, sizeof(bomb));

			bomb.img = _vBombMid[0].img;
			bomb.rc = RectMake(_vBombMid[_vBombMid.size() - 1].rc.right, _bombStart.rc.top, bomb.img->getWidth(), bomb.img->getHeight());
			bomb.x = (bomb.rc.left + bomb.rc.right) / 2;
			bomb.y = (bomb.rc.top + bomb.rc.bottom) / 2;
			bomb.speed = _vBombMid[0].speed;

			_vBombMid.push_back(bomb);
		}
	}
	else
	{
		if (_vBombMid.size())
		{
			_bombFinal.x += _bombFinal.speed;
			_bombFinal.rc = RectMakeCenter(_bombFinal.x, _bombStart.y, _bombFinal.img->getWidth(), _bombFinal.img->getHeight());

			for (int i = 0; i < _vBombMid.size(); i++)
			{
				_vBombMid[i].x += _vBombMid[i].speed;
				_vBombMid[i].rc = RectMakeCenter(_vBombMid[i].x, _bombStart.y, _vBombMid[i].img->getWidth(), _vBombMid[i].img->getHeight());

				if (_vBombMid[i].rc.left > WINSIZEX)
				{
					_vBombMid.erase(_vBombMid.begin() + i);
				}
			}
		}
	}
}

void playerBomb::bombFinish()
{
	_isFire = false;
}

RECT playerBomb::getBombRect()
{
	RECT temp = { 0, 0, 0, 0 };
	if (_vBombMid.size() > 0)
	{
		temp = RectMake(_vBombMid[0].rc.left, _vBombMid[0].rc.top, _bombFinal.rc.right - _vBombMid[0].rc.left, _vBombMid[0].img->getHeight());
	}	

	return temp;
}