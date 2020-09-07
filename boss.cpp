#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{	
	_ui = new ui;
	_bullet = new bullet;
	_ani = new animation;

	setAnimation("���� �տ�");
	_ui->init("���� UI", RIGHTBOT);

	_location = { WINSIZEX + 500, WINSIZEY / 2 };
	_nextMove = { RND->getFromFloatTo(WINSIZEX / 2, WINSIZEX - 100), RND->getFromFloatTo(100, WINSIZEY - 100) };

	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());

	_speed = 8.0f;
	_currentHp = _maxHp = 500.0f;
	_isStart = _patternDelay = _bulletAngle = _fireDelay = 0;
	_state = BOSS_FRONT;

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	if (!_isStart) setLocation();
	else
	{
		if (_currentHp <= 0)
		{
			_state = BOSS_DEAD;
		}
		else
		{			
			patternControl();
		}		
	}
	stateControl();
	_bullet->update();
	_ui->update();
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);	

	_ui->setProgress(_currentHp, _maxHp);
}

void boss::render()
{	
	_ui->render();
	_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
	_bullet->render();	
}

void boss::patternControl()
{
	static int delay = 0;	
	int rndPattern = 0;
	delay++;
	if (delay % 200 == 0 && _pattern == BOSS_IDLE && _state == BOSS_IDLE)
	{	
		_nextMove = { RND->getFromFloatTo(WINSIZEX / 2, WINSIZEX - 100), RND->getFromFloatTo(100, WINSIZEY - 100) };
		do
		{
			rndPattern = RND->getFromIntTo(3, 6);			
		} while (rndPattern == _lastPattern);		
		_pattern = static_cast<MyBossPattern>(rndPattern);		
		delay = _fireDelay = 0;				
	}	
	switch (_pattern)
	{	
		case BOSS_IDLE:
		{
			_state = _nextMove.x < _location.x ? BOSS_FRONT : BOSS_BACK;

			if (getDistance(_nextMove.x, _nextMove.y, _location.x, _location.y) > _speed)
			{
				float moveAngle = getAngle(_location.x, _location.y, _nextMove.x, _nextMove.y);
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);
				delay = 0;				
			}
			else
			{
				_location = _nextMove;
				_state = BOSS_IDLE;				
			}
			break;
		}
		case BOSS_SPREAD: 
		{
			MYPOINT target = { WINSIZEX / 2, WINSIZEY / 2 };								// ��ǥ ��ǥ
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// ���� ��ǥ�� ��ǥ ��ǥ ��

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// �Ÿ��� ���ǵ庸�� ũ��
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// ���� ����ؼ�
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// �̵�
			}
			else
			{				
				_location = target;				// ��ǥ ����
				_state = BOSS_SPREAD;			// �ִϸ��̼� ����
				if (!_ani->isPlay())
				{				
					_fireDelay++;
					if (delay > 1000)
					{
						delay = 0;
						_lastPattern = BOSS_SPREAD;
						_pattern = BOSS_IDLE;						
					}										
					if (_fireDelay % 3 == 0)	// ���� �ֱ�
					{
						_bullet->init("���� �Ҹ� 1", _location.x, _location.y, 15.0f, _bulletAngle);	// ���� �����ؼ� ���ư�
						_bulletAngle += 0.20f;	// �ޱ� ��� �þ
						_fireDelay = 0;
					}
					for (int i = 0; i < _bullet->getVBullet().size(); i++)
					{
						if (getDistance(_bullet->getVBullet()[i].x, _bullet->getVBullet()[i].y, _location.x, _location.y) > 175)	// �Ҹ��� ������� �־�����
						{
							_bullet->setBulletSpeed(i, 2.0f);	// �ӵ��� ����
						}
					}
				}				
			}			
			break;
		}		
		case BOSS_MISSILE:
		{
			MYPOINT target = { WINSIZEX - 175, 110 };										// ����ź ���� ��ǥ
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// ���� ��ǥ�� ��ǥ ��ǥ ��

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// ���� ��ǥ�� ��ǥ ��ǥ�� �Ÿ��� ���ǵ庸�� ũ��
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// ���� ����ؼ�
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// �̵�
			}
			else
			{
				_location = target;				// ��ǥ ����
				_state = BOSS_MISSILE;			// �ִϸ��̼� ����
				if (!_ani->isPlay())
				{
					_fireDelay++;
					if (delay > 500)
					{
						delay = 0;
						_lastPattern = BOSS_MISSILE;
						_pattern = BOSS_IDLE;
					}
					if (_fireDelay % 30 == 0)	// ���� �ֱ�
					{
						_fireDelay = 0;
						float pAngle = getAngle(_location.x, _location.y, _playerLoc.x, _playerLoc.y);	// �÷��̾� ��ǥ�� ���� ������ �ٲ�
						_bullet->init("���� �Ҹ� 2", _location.x, _location.y, 10.0f, pAngle, 20);		// �Ҹ� �߻�
					}					
				}
			}			
			break;
		}		
		case BOSS_RAIN:
		{
			MYPOINT target = { WINSIZEX - 350, WINSIZEY / 2 };								// �ָ��ָ� ���� ��ǥ
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// ���� X��ǥ�� ��ǥ X��ǥ ��

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// ���� ��ǥ�� ��ǥ ��ǥ���� �Ÿ��� ���ǵ庸�� ũ��
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// ���� ����Ͽ�
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// ������ŭ �̵�
			}
			else
			{
				_location = target;						// ���� ��ǥ�� ��ǥ��ǥ�� ����
				_state = BOSS_RAIN;						// ���� �ִϸ��̼� ���
				if (!_ani->isPlay())					// �ִϸ��̼� ������
				{
					_fireDelay++;
					if (delay > 500)
					{
						delay = 0;
						_lastPattern = BOSS_RAIN;						
						_pattern = BOSS_IDLE;
					}
					if (_fireDelay % 40 == 0)			// ���� �ֱ� = 40
					{
						for (int i = 0; i < 5; i++)		// �� ���� 5�� �� ����
						{
							// �������� 0~WINSIZEX���� �������� ����
							_bullet->init("���� �Ҹ� 3", RND->getFromFloatTo(0, WINSIZEX), -30, RND->getFromFloatTo(5.0f, 10.0f), PI * 3 / 2, 30);
						}						
						_fireDelay = 0;						
					}
				}
			}
			break;
		}		
	}
	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());	// ���� ��ǥ ��� ������Ʈ
}

void boss::stateControl()
{
	switch (_state)
	{
		case BOSS_IDLE:		setAnimation("���� �⺻", true);	break;
		case BOSS_BACK:		setAnimation("���� �ڿ�");		break;		
		case BOSS_FRONT:	setAnimation("���� �տ�");		break;
		case BOSS_SPREAD:	setAnimation("���� ���� 1");		break;
		case BOSS_MISSILE:	setAnimation("���� ���� 2");		break;
		case BOSS_RAIN:		setAnimation("���� ���� 3");		break;
		case BOSS_DEAD:		
		{
			setAnimation("���� ����");
			if (!_ani->isPlay())
			{
				_state = BOSS_END;
			}
			break;
		}		
	}
}

void boss::setAnimation(string imageName, bool loop)
{
	if (!_currentImg.compare(imageName)) return;

	_currentImg = imageName;
	_img = IMAGEMANAGER->findImage(imageName);

	_rc = RectMake(_rc.left, _rc.top, _img->getFrameWidth(), _img->getFrameHeight());

	_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());

	_ani->setDefPlayFrame(false, loop);
	_ani->setFPS(1);
	_ani->start();
}

void boss::setLocation()
{
	POINT startLoc = { WINSIZEX - 250, WINSIZEY / 2 };

	float angle = getAngle(_location.x, _location.y, startLoc.x, startLoc.y);

	if (_location.x > startLoc.x)
	{
		_location.x += cosf(angle) * _speed;
		_location.y += -sinf(angle) * _speed;

		_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());
	}
	else
	{
		_state = BOSS_IDLE;
		_isStart = true;
	}
}

bool boss::getBossEnd()
{
	if (_state == BOSS_END) return true;
	else return false;	
}
