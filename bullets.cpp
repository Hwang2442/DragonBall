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
	bullet.angle = angle;	// �Ű����� ������ 0

	_vBullet.push_back(bullet);

	_frame = frame;			// �Ű����� ������ 10

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	for (int i = 0; i < _vBullet.size();)
	{
		_vBullet[i].x +=  cosf(_vBullet[i].angle) * _vBullet[i].speed;	// ���� ������ŭ �̵�
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;	// ���� ������ŭ �̵�
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y, _vBullet[i].img->getFrameWidth(), _vBullet[i].img->getFrameHeight()); // ��Ʈ ����

		_vBullet[i].ani->frameUpdate(TIMEMANAGER->getElapsedTime() * _frame);	// ������ ������Ʈ

		// ȭ�� �ٱ����� ������
		if (screenOverCheck(_vBullet[i].rc))
		{
			// ����
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
	// �ش� ������ �迭 ����
	delete _vBullet[arrNum].ani;
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void bullet::setBulletSpeed(int arrNum, float speed)
{
	// �ش� ������ ���ǵ� ����
	_vBullet[arrNum].speed = speed;
}

bool bullet::screenOverCheck(RECT bulletRect)
{
	if (bulletRect.left > WINSIZEX)	return true;	// ȭ�� ���������� ������
	if (bulletRect.right < 0)		return true;	// ȭ�� �������� ������
	if (bulletRect.bottom < 0)		return true;	// ȭ�� �������� ������
	if (bulletRect.bottom > WINSIZEY)				// ȭ�� �Ʒ������� ������
	{
		// ����Ʈ ó��
		EFFECTMANAGER->play("���� �Ҹ�ȿ��", (bulletRect.left + bulletRect.right) / 2, WINSIZEY - 32);
		SOUNDMANAGER->stop("���� �浹");
		SOUNDMANAGER->play("���� �浹");
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

	tagBomb bomb[2];	// ó������ 2�� ����� ����
	
	ZeroMemory(&_bombStart, sizeof(_bombStart));
	ZeroMemory(&_bombFinal, sizeof(_bombFinal));

	_bombStart.img = IMAGEMANAGER->findImage(imageName + " ����");
	_bombStart.rc = RectMake(x, y, _bombStart.img->getWidth(), _bombStart.img->getHeight());	// ������ �÷��̾� �ٷξտ�
	_bombStart.x = (_bombStart.rc.left + _bombStart.rc.right) / 2;
	_bombStart.y = (_bombStart.rc.top + _bombStart.rc.bottom) / 2;

	for (int i = 0; i < 2; i++)
	{
		bomb[i].img = IMAGEMANAGER->findImage(imageName + " �߰�");
		bomb[i].speed = speed;
	}

	bomb[0].rc = RectMake(_bombStart.rc.right, _bombStart.rc.top, bomb[0].img->getWidth(), bomb[0].img->getHeight());	// 0�� ��ŸƮ �ٷ� �տ�
	bomb[1].rc = RectMake(bomb[0].rc.right, _bombStart.rc.top, bomb[1].img->getWidth(), bomb[1].img->getHeight());		// 1�� 0 �ٷ� �տ�
	
	for (int i = 0; i < 2; i++)
	{
		bomb[i].x = (bomb[i].rc.left + bomb[i].rc.right) / 2;
		bomb[i].y = (bomb[i].rc.top + bomb[i].rc.bottom) / 2;
		_vBombMid.push_back(bomb[i]);
	}	

	_bombFinal.img = IMAGEMANAGER->findImage(imageName + " ����");
	_bombFinal.rc = RectMake(bomb[1].rc.right, _bombStart.rc.top, _bombFinal.img->getWidth(), _bombFinal.img->getHeight());	// ���� 1 �ٷ� �տ�
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
	_bombStart.rc = RectMake(x, y, _bombStart.img->getWidth(), _bombStart.img->getHeight());	// ��ŸƮ ��ġ ����
	_bombStart.x = (_bombStart.rc.left + _bombStart.rc.right) / 2;
	_bombStart.y = (_bombStart.rc.top + _bombStart.rc.bottom) / 2;

	_vBombMid[0].rc = RectMake(_bombStart.rc.right, _bombStart.rc.top, _vBombMid[0].img->getWidth(), _vBombMid[0].img->getHeight());	// �߰� ��ġ ����
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