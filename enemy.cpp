#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(string imageName, float x, float y, MyEnemyType enemyType)
{
	_ani = new animation;
	_imageName = imageName;						// �̹��� �̸� �����ϰ�
	_img = IMAGEMANAGER->findImage(imageName);	// �̹��� ã��

	_type = enemyType;			// Ÿ�� ����

	_finalPosition = { x, y };	// ��ġ�� ������ ����

	_rndWay = RND->getInt(2);	// Ʈ��� �Ʒ�, ������ ��
	switch (_type)
	{
		case RUSH:					// �ڻ�
		{
			// ���� ��ġ ����
			_startPosition = { static_cast<float>(WINSIZEX + _img->getWidth()), _finalPosition.y };
			break;
		}		
		case SHOTGUN: case MISSILE:	// �Ҹ� ��� ��
		{
			// ���� ��ġ ���� -- ���⿡ ���� ���� -> �Ʒ��� ȭ�� ����, ������ ȭ�� �Ʒ�
			_startPosition = { _finalPosition.x, static_cast<float>(_rndWay ? WINSIZEY + _img->getHeight() : -_img->getHeight()) };
			break;
		}
	}
	_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());	// ��Ʈ ����

	_speed = RND->getFromFloatTo(10.0f, 15.0f);			// ���ǵ� ����
	_attackRandom = RND->getFromIntTo(50, 150);			// ���� �ֱ⵵ ����

	_life = 5.0f;	// �̸�ŭ ������ ����
	_isDead = _isStart = _isDelete = _attackCount = 0;	// �ʱ�ȭ

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	if (!_isStart)
	{
		_attackCount = 1;	// ���� �ϸ� �ȴ�
		switch (_type)
		{
			case RUSH:
			{
				_isStart = true;	// �ڻ��ϴ� �ִ� �ٷ� ����
				break;
			}			
			case SHOTGUN: case MISSILE:
			{
				float angle = getAngle(_startPosition.x, _startPosition.y, _finalPosition.x, _finalPosition.y);		// ��ǥ��ǥ�� ������ǥ ����
				_startPosition.move(cosf(angle) * _speed, -sinf(angle) * _speed);	// ������ŭ �̵�

				_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());		

				if (getDistance(_startPosition.x, _startPosition.y, _finalPosition.x, _finalPosition.y) < _speed)	// �Ÿ��� ���ǵ庸�� ������
				{
					_startPosition = _finalPosition;	// ��ǥ ����
					_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());
					_isStart = true;	// ����
				}
			}
		}
	}
	else
	{
		if (_type == RUSH)	// �޸���
		{
			if(!_isDead) _startPosition.move(-_speed, 0);	// �׳� ����
			_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());

			if (_rc.right < 0)	// ȭ�� ������ ����
			{
				_life = 0;		// ����
			}
		}
	}	

	if (_life <= 0 && !_isDead)	// �Ǵ� ���µ� ���� ���׾��ٸ�
	{
		_isDead = true;	// ����
		_img = IMAGEMANAGER->findImage(_imageName + " ����");	// �̹��� ã��
		_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getFrameWidth(), _img->getFrameHeight());	// ��Ʈ ����
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());				// �ִϸ��̼� �ʱ�ȭ
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(1);
		_ani->start();
	}

	if (_isDead)
	{
		_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
		if (!_ani->isPlay())	// �״� ��� ��������
		{
			_isDelete = true;	// �����ص� �ȴ�
		}
	}	
}

void enemy::render()
{
	//Rectangle(getMemDC(), _rc);
	switch (_isDead)
	{
		case false: _img->render(getMemDC(), _rc.left, _rc.top);			break;	// �׳� ���
		case true:	_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);	break;	// ������ ���
	}
}

bool enemy::bulletCountFire()
{
	if (_isDead) return false;	// �׾����� �߻����

	_attackCount++;
	if (_attackCount % _attackRandom == 0)	// ����
	{
		_attackRandom = RND->getFromIntTo(50, 150);	// ���� �ֱ� ���� ����
		_attackCount = 0;

		return true;
	}

	return false;
}
