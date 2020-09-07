#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	ZeroMemory(&_target, sizeof(_target));
	ZeroMemory(&_aura, sizeof(_aura));	

	_ui			= new ui;	
	_bullet		= new bullet;
	_bomb		= new playerBomb;
	_ani		= new animation;
	_target.ani = new animation;
	_aura.ani	= new animation;	

	// �ƿ�� �ʱ�ȭ
	_aura.img = IMAGEMANAGER->findImage("���� �ƿ��");
	_aura.ani->init(_aura.img->getWidth(), _aura.img->getHeight(), _aura.img->getFrameWidth(), _aura.img->getFrameHeight());
	_aura.ani->setDefPlayFrame(false, true);
	_aura.ani->setFPS(1);
	_aura.ani->start();

	// �� �ʱ�ȭ
	_dragon.img = IMAGEMANAGER->findImage("���� ��");	

	// ��ź�� �ʱ�ȭ
	_target.img = IMAGEMANAGER->findImage("���� ��ź��");
	_target.ani->init(_target.img->getWidth(), _target.img->getHeight(), _target.img->getFrameWidth(), _target.img->getFrameHeight());
	_target.ani->setDefPlayFrame(false, true);
	_target.ani->setFPS(1);
	_target.ani->start();

	// �ʱ� �ܰ�� 1�ܰ�
	_form = "1�ܰ� ";
	// �ʱ� ��ġ ����
	_location = { -100, WINSIZEY / 2 };
	
	// �ִϸ��̼� ����
	setAnimation("���� �տ�", false);

	// Ÿ�� ��Ʈ �ʱ�ȭ
	_target.rc = RectMakeCenter(_location.x, _location.y, _target.img->getFrameWidth(), _target.img->getFrameHeight());

	// �ƿ�� ��Ʈ �ʱ�ȭ
	_aura.rc = RectMakeCenter(_location.x, _location.y, _aura.img->getFrameWidth(), _aura.img->getFrameHeight());

	// UI ����
	_ui->init(_form + "���� UI", LEFTBOT);

	// ���ǵ�, �Ҹ����ǵ�, �����ֱ� �� ��Ÿ ��� �ʱ�ȭ
	_speed = 7.0f;
	_bulletSpeed = 10.0f;
	_delay = 0;	
	_aura.isShield = true;
	_dragon.letAttack = 0;
	_startCount = 0;
	_alpha = 255;

	_currentGauge = 0;
	_maxGauge = 100.0f;

	_gamePlay = ISSTART;	// ó���̴ϱ� ��ŸƮ
	_playerState = FRONT;	// ó���� ������ �̵�

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// ���� �����÷��� ���¿� ����
	switch (_gamePlay)
	{
		case ISSTART:	// ����
		{
			startLocation(); // ��ġ ��´�
			break;
		}		
		case ISIMMOT:
		{
			if (_startCount < 15)
			{
				_startDelay++;
				if (_startDelay % 10 == 0) 
				{
					_startCount++;
					_alpha = 255; _startDelay = 0;
				}
				else _alpha = 100;
			}
			else _gamePlay = ISPLAY;
		}
		case ISPLAY: 	// �÷���
		{			
			keyControl();	// Ű�Է�			
			break;
		}
		case ISDEAD:	// �׾���
		{
			if (_aura.isShield)
			{
				_aura.isShield = false;
				_gamePlay = ISPLAY;
				break;
			}
			else
			{
				_playerState = DEAD;	// �״� ��� ���
			}			
			break;
		}	
		case ISULTI:
		{
			ultimateAttack();
			break;
		}
		case ISWIN:
		{
			_playerState = WIN;
			_alpha = 255;
			break;
		}
	}	

	// �÷��̾� ���¿� ���� �̹��� ���� �� �ִϸ��̼� �ʱ�ȭ
	stateControl();	

	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());							// �÷��̾� ��Ʈ ����
	_target.rc = RectMakeCenter(_location.x, _location.y, _target.img->getFrameWidth(), _target.img->getFrameHeight());		// ��ź�� ��Ʈ ���� 
	_aura.rc = RectMakeCenter(_location.x, _location.y, _aura.img->getFrameWidth(), _aura.img->getFrameHeight());			// �ƿ�� ��Ʈ ����

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);			// ���� ������ ���
	_target.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);	// Ÿ�� ������ ���
	_aura.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);		// ���� �ƿ�� ���

	_bullet->update();
	_bomb->update();
	
	_ui->update();			
	_ui->setProgress(_currentGauge, _maxGauge);
}

void player::render()
{		
	_ui->render();

	if (_aura.isShield)
	{
		_aura.img->aniRender(getMemDC(), _aura.rc.left, _aura.rc.top, _aura.ani);		// ���� �ƿ��
	}		

	_img->alphaAniRender(getMemDC(), _rc.left, _rc.top, _ani, _alpha);	
	_target.img->aniRender(getMemDC(), _target.rc.left, _target.rc.top, _target.ani);	// ���� ��ź��

	_bullet->render();
	_bomb->render();	
		
	if (_dragon.letAttack)
	{
		_dragon.img->render(getMemDC(), _dragon.rc.left, _dragon.rc.top);
	}
		
}

void player::keyControl()
{	
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp('X'))	// �����̵� ���� or �������̵� ���� or ���� ����
	{
		_playerState = IDLE;		// �⺻ ����
	}	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX && _playerState != BACK)
	{
		_playerState = FRONT;
		_location.move(_speed, 0);	// ������ �̵�
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _playerState != FRONT)
	{
		_playerState = BACK;
		_location.move(-_speed, 0);	// ���� �̵�
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
	{
		_location.move(0, _speed);	// �Ʒ��� �̵�
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_location.move(0, -_speed);	// ���� �̵�
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		_playerState = FIRE;		// ����
		_delay++;
		if (!(_delay % 10))	// ���� �ֱ�
		{			
			_delay = 0;
			_bullet->init(_form + "�Ҹ�", _rc.right + 15, _rc.top + 25, _bulletSpeed);	// �߻�߻�			
		}
	}
	if (KEYMANAGER->isOnceKeyDown('C') && (!_form.compare("1�ܰ� ")) && _currentGauge >= _maxGauge)
	{		
		_playerState = TRANSFORM;	// �ʻ��̾���!!
	}
	if (KEYMANAGER->isStayKeyDown('V'))
	{
		_playerState = BOMB;		// ��������!!
		if (_currentGauge == 0)		// �߻��ϴٰ� �������� �� ��������
		{
			_bomb->bombFinish();	// ������ ��������
		}
	}
	if (KEYMANAGER->isOnceKeyDown('B') && (!_form.compare("2�ܰ� ")) && _currentGauge == _maxGauge)
	{
		_gamePlay = ISULTI;		
		_currentGauge = 0;
	}
	if (KEYMANAGER->isOnceKeyUp('V'))
	{
		_playerState = IDLE;		// �������� ����� �⺻���� ��ȯ	
		_bomb->bombFinish();		// �������� ����
	}			
}

void player::stateControl()
{
	switch (_playerState)
	{
		case IDLE:		setAnimation("���� �⺻", true);		break;	// �⺻ ���´� ���� ����
		case BACK:		setAnimation("���� �ڿ�");			break;
		case FRONT:		setAnimation("���� �տ�");			break;	
		case FIRE:		setAnimation("���� ����", true);		break;	// ���� ���µ� ���� ����		
		case TRANSFORM:
		{			
			setAnimation("���� ����");
			if (!_ani->isPlay())		// ���� ��� �����
			{
				_currentGauge = 0;
				_form = "2�ܰ� ";		// 2�ܰ�� ����
				_ui->init(_form + "���� UI", LEFTBOT);
				_aura.isShield = true;
				_playerState = IDLE;	// �ٽ� �⺻���·� ���ư�
				_bulletSpeed *= 2;		// �Ҹ� ���ǵ� ����
			}
			break;
		}
		case BOMB:
		{
			setAnimation("���� �ʻ�");				// �������� ���			
			if (!_ani->isPlay())					// ��� ���� ��
			{
				_currentGauge--;
				if (_currentGauge < 0) { _currentGauge = 0; break; }

				float top = !_form.compare("1�ܰ�_") ? _rc.top : _rc.top - 10;	// ���� ���� �ܰ迡 ���� ��ġ ����
				_bomb->init(_form + "��������", _rc.right, top, 30.0);			// �������� �ʱ�ȭ
				_bomb->bombFire(_rc.right, top);	// �������İ� �÷��̾ ����ٴ�
			}
			break;
		}
		case DEAD:
		{
			setAnimation("���� ����");	// �״� ��� ���
			if (!(_ani->isPlay()))		// �ִϸ��̼��� ������
			{				
				_gamePlay = ISINIT;
			}
			break;
		}
		case ULTIMATE:
		{			
			if (!(_ani->isPlay()))
			{
				_aura.isShield = true;
				_ui->init("3�ܰ� ���� UI", LEFTBOT);
				setAnimation("���� �ñ�");
				
				_dragon.letAttack = true;
			}			
			break;
		}
		case WIN:
		{
			setAnimation("���� �¸�");
			break;
		}
	}
}

void player::setAnimation(string imageName, bool loop)
{
	if (!_currentImg.compare(imageName)) return;		// ���� �̹����� ���ٸ� ����

	_currentImg = imageName;
	_img = IMAGEMANAGER->findImage(_form + imageName);	// �̹��� ã���ְ�

	// ��Ʈ ����
	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());	

	// �ִϸ��̼� �ʱ�ȭ
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
	_ani->setDefPlayFrame(false, loop);
	_ani->setFPS(1);
	_ani->start();
}

void player::startLocation()
{
	MYPOINT start = { 150, WINSIZEY / 2 };		// ó�� ���۽� ��ǥ ��ǥ
	
	if (getDistance(_location.x, _location.y, start.x, start.y) > _speed)
	{
		float angle = getAngle(_location.x, _location.y, start.x, start.y);
		_location.move(cosf(angle) * _speed, -sinf(angle) * _speed);		
	}
	else
	{
		_location = start;
		_playerState = IDLE;
		_gamePlay = ISIMMOT;
	}

	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());		
}

void player::ultimateAttack()
{
	MYPOINT attackLoc = { 200.0f, WINSIZEY / 2 };

	if (!_dragon.letAttack)
	{
		if (_playerState != ULTIMATE)
		{
			_playerState = _location.x < attackLoc.x ? FRONT : BACK;
			float angle = getAngle(_location.x, _location.y, attackLoc.x, attackLoc.y);
			_location.move(cosf(angle) * _speed, -sinf(angle) * _speed);
		}
		if (getDistance(_location.x, _location.y, attackLoc.x, attackLoc.y) < _speed)
		{
			_location = attackLoc;
			_playerState = ULTIMATE;
			_dragon.center = { (_dragon.img->getWidth()) * -1.0f, WINSIZEY / 2 };
			_dragon.rc = RectMakeCenter(_dragon.center.x, _dragon.center.y, _dragon.img->getWidth(), _dragon.img->getHeight());
			_dragon.speed = 45.0f;		
			setAnimation("���� ����");
		}
	}
	else
	{
		_dragon.center.move(_dragon.speed, 0);
		_dragon.rc = RectMakeCenter(_dragon.center.x, _dragon.center.y, _dragon.img->getWidth(), _dragon.img->getHeight());
		if (_dragon.rc.right > 0)
		{
			for (int i = 0; i < 10; i++)
			{
				EFFECTMANAGER->play("Ư�� �Ҹ�ȿ��", RND->getFromFloatTo(_dragon.rc.left, _dragon.rc.right), RND->getFromFloatTo(0, WINSIZEY));
			}
		}		
		if (_dragon.rc.left > WINSIZEX)
		{
			_ui->init(_form + "���� UI", LEFTBOT);
			_startCount = 0;
			_gamePlay = ISIMMOT;
			_dragon.letAttack = false;		
			_playerState = IDLE;
		}
	}	
}

void player::setGauge(float gauge)
{
	_currentGauge = gauge;
	if (_currentGauge > _maxGauge) _currentGauge = _maxGauge;	
}

RECT player::getDragonRect()
{
	RECT temp = { 0, 0, 0, 0 };
	if (_dragon.letAttack)
	{
		temp = _dragon.rc;
	}
	return temp;
}
