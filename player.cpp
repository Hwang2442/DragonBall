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

	// 아우라 초기화
	_aura.img = IMAGEMANAGER->findImage("오공 아우라");
	_aura.ani->init(_aura.img->getWidth(), _aura.img->getHeight(), _aura.img->getFrameWidth(), _aura.img->getFrameHeight());
	_aura.ani->setDefPlayFrame(false, true);
	_aura.ani->setFPS(1);
	_aura.ani->start();

	// 용 초기화
	_dragon.img = IMAGEMANAGER->findImage("오공 용");	

	// 피탄면 초기화
	_target.img = IMAGEMANAGER->findImage("오공 피탄면");
	_target.ani->init(_target.img->getWidth(), _target.img->getHeight(), _target.img->getFrameWidth(), _target.img->getFrameHeight());
	_target.ani->setDefPlayFrame(false, true);
	_target.ani->setFPS(1);
	_target.ani->start();

	// 초기 단계는 1단계
	_form = "1단계 ";
	// 초기 위치 설정
	_location = { -100, WINSIZEY / 2 };
	
	// 애니메이션 설정
	setAnimation("오공 앞에", false);

	// 타겟 렉트 초기화
	_target.rc = RectMakeCenter(_location.x, _location.y, _target.img->getFrameWidth(), _target.img->getFrameHeight());

	// 아우라 렉트 초기화
	_aura.rc = RectMakeCenter(_location.x, _location.y, _aura.img->getFrameWidth(), _aura.img->getFrameHeight());

	// UI 설정
	_ui->init(_form + "오공 UI", LEFTBOT);

	// 스피드, 불릿스피드, 공격주기 외 기타 등등 초기화
	_speed = 7.0f;
	_bulletSpeed = 10.0f;
	_delay = 0;	
	_aura.isShield = true;
	_dragon.letAttack = 0;
	_startCount = 0;
	_alpha = 255;

	_currentGauge = 0;
	_maxGauge = 100.0f;

	_gamePlay = ISSTART;	// 처음이니까 스타트
	_playerState = FRONT;	// 처음은 앞으로 이동

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 현재 게임플레이 상태에 따라서
	switch (_gamePlay)
	{
		case ISSTART:	// 시작
		{
			startLocation(); // 위치 잡는다
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
		case ISPLAY: 	// 플레이
		{			
			keyControl();	// 키입력			
			break;
		}
		case ISDEAD:	// 죽었음
		{
			if (_aura.isShield)
			{
				_aura.isShield = false;
				_gamePlay = ISPLAY;
				break;
			}
			else
			{
				_playerState = DEAD;	// 죽는 모션 재생
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

	// 플레이어 상태에 따른 이미지 변경 및 애니메이션 초기화
	stateControl();	

	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());							// 플레이어 렉트 갱신
	_target.rc = RectMakeCenter(_location.x, _location.y, _target.img->getFrameWidth(), _target.img->getFrameHeight());		// 피탄면 렉트 갱신 
	_aura.rc = RectMakeCenter(_location.x, _location.y, _aura.img->getFrameWidth(), _aura.img->getFrameHeight());			// 아우라 렉트 갱신

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);			// 오공 프레임 재생
	_target.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);	// 타겟 프레임 재생
	_aura.ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);		// 오공 아우라 재생

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
		_aura.img->aniRender(getMemDC(), _aura.rc.left, _aura.rc.top, _aura.ani);		// 오공 아우라
	}		

	_img->alphaAniRender(getMemDC(), _rc.left, _rc.top, _ani, _alpha);	
	_target.img->aniRender(getMemDC(), _target.rc.left, _target.rc.top, _target.ani);	// 오공 피탄면

	_bullet->render();
	_bomb->render();	
		
	if (_dragon.letAttack)
	{
		_dragon.img->render(getMemDC(), _dragon.rc.left, _dragon.rc.top);
	}
		
}

void player::keyControl()
{	
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp('X'))	// 왼쪽이동 종료 or 오른쪽이동 종료 or 공격 종료
	{
		_playerState = IDLE;		// 기본 상태
	}	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX && _playerState != BACK)
	{
		_playerState = FRONT;
		_location.move(_speed, 0);	// 오른쪽 이동
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _playerState != FRONT)
	{
		_playerState = BACK;
		_location.move(-_speed, 0);	// 왼쪽 이동
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
	{
		_location.move(0, _speed);	// 아래로 이동
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_location.move(0, -_speed);	// 위로 이동
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		_playerState = FIRE;		// 공격
		_delay++;
		if (!(_delay % 10))	// 공격 주기
		{			
			_delay = 0;
			_bullet->init(_form + "불릿", _rc.right + 15, _rc.top + 25, _bulletSpeed);	// 발사발사			
		}
	}
	if (KEYMANAGER->isOnceKeyDown('C') && (!_form.compare("1단계 ")) && _currentGauge >= _maxGauge)
	{		
		_playerState = TRANSFORM;	// 초사이어인!!
	}
	if (KEYMANAGER->isStayKeyDown('V'))
	{
		_playerState = BOMB;		// 에너지파!!
		if (_currentGauge == 0)		// 발사하다가 게이지가 다 떨어지면
		{
			_bomb->bombFinish();	// 강제로 끝나버림
		}
	}
	if (KEYMANAGER->isOnceKeyDown('B') && (!_form.compare("2단계 ")) && _currentGauge == _maxGauge)
	{
		_gamePlay = ISULTI;		
		_currentGauge = 0;
	}
	if (KEYMANAGER->isOnceKeyUp('V'))
	{
		_playerState = IDLE;		// 에너지파 종료시 기본으로 변환	
		_bomb->bombFinish();		// 에너지파 종료
	}			
}

void player::stateControl()
{
	switch (_playerState)
	{
		case IDLE:		setAnimation("오공 기본", true);		break;	// 기본 상태는 무한 루프
		case BACK:		setAnimation("오공 뒤에");			break;
		case FRONT:		setAnimation("오공 앞에");			break;	
		case FIRE:		setAnimation("오공 공격", true);		break;	// 공격 상태도 무한 루프		
		case TRANSFORM:
		{			
			setAnimation("오공 변신");
			if (!_ani->isPlay())		// 변신 모션 종료시
			{
				_currentGauge = 0;
				_form = "2단계 ";		// 2단계로 변경
				_ui->init(_form + "오공 UI", LEFTBOT);
				_aura.isShield = true;
				_playerState = IDLE;	// 다시 기본상태로 돌아감
				_bulletSpeed *= 2;		// 불릿 스피드 증가
			}
			break;
		}
		case BOMB:
		{
			setAnimation("오공 필살");				// 에너지파 모션			
			if (!_ani->isPlay())					// 모션 종료 시
			{
				_currentGauge--;
				if (_currentGauge < 0) { _currentGauge = 0; break; }

				float top = !_form.compare("1단계_") ? _rc.top : _rc.top - 10;	// 현재 변신 단계에 따라서 위치 조정
				_bomb->init(_form + "에너지파", _rc.right, top, 30.0);			// 에너지파 초기화
				_bomb->bombFire(_rc.right, top);	// 에너지파가 플레이어를 따라다님
			}
			break;
		}
		case DEAD:
		{
			setAnimation("오공 죽음");	// 죽는 모션 재생
			if (!(_ani->isPlay()))		// 애니메이션이 끝나면
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
				_ui->init("3단계 오공 UI", LEFTBOT);
				setAnimation("오공 궁극");
				
				_dragon.letAttack = true;
			}			
			break;
		}
		case WIN:
		{
			setAnimation("오공 승리");
			break;
		}
	}
}

void player::setAnimation(string imageName, bool loop)
{
	if (!_currentImg.compare(imageName)) return;		// 현재 이미지와 같다면 리턴

	_currentImg = imageName;
	_img = IMAGEMANAGER->findImage(_form + imageName);	// 이미지 찾아주고

	// 렉트 갱신
	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());	

	// 애니메이션 초기화
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
	_ani->setDefPlayFrame(false, loop);
	_ani->setFPS(1);
	_ani->start();
}

void player::startLocation()
{
	MYPOINT start = { 150, WINSIZEY / 2 };		// 처음 시작시 목표 좌표
	
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
			setAnimation("오공 변신");
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
				EFFECTMANAGER->play("특수 불릿효과", RND->getFromFloatTo(_dragon.rc.left, _dragon.rc.right), RND->getFromFloatTo(0, WINSIZEY));
			}
		}		
		if (_dragon.rc.left > WINSIZEX)
		{
			_ui->init(_form + "오공 UI", LEFTBOT);
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
