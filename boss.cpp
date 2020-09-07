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

	setAnimation("보스 앞에");
	_ui->init("보스 UI", RIGHTBOT);

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
			MYPOINT target = { WINSIZEX / 2, WINSIZEY / 2 };								// 목표 좌표
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// 현재 좌표와 목표 좌표 비교

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// 거리가 스피드보다 크면
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// 각도 계산해서
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// 이동
			}
			else
			{				
				_location = target;				// 좌표 고정
				_state = BOSS_SPREAD;			// 애니메이션 지정
				if (!_ani->isPlay())
				{				
					_fireDelay++;
					if (delay > 1000)
					{
						delay = 0;
						_lastPattern = BOSS_SPREAD;
						_pattern = BOSS_IDLE;						
					}										
					if (_fireDelay % 3 == 0)	// 공격 주기
					{
						_bullet->init("보스 불릿 1", _location.x, _location.y, 15.0f, _bulletAngle);	// 각도 지정해서 날아감
						_bulletAngle += 0.20f;	// 앵글 계속 늘어남
						_fireDelay = 0;
					}
					for (int i = 0; i < _bullet->getVBullet().size(); i++)
					{
						if (getDistance(_bullet->getVBullet()[i].x, _bullet->getVBullet()[i].y, _location.x, _location.y) > 175)	// 불릿이 어느정도 멀어지면
						{
							_bullet->setBulletSpeed(i, 2.0f);	// 속도를 낮춤
						}
					}
				}				
			}			
			break;
		}		
		case BOSS_MISSILE:
		{
			MYPOINT target = { WINSIZEX - 175, 110 };										// 유도탄 패턴 좌표
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// 현재 좌표와 목표 좌표 비교

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// 현재 좌표와 목표 좌표의 거리가 스피드보다 크면
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// 각도 계산해서
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// 이동
			}
			else
			{
				_location = target;				// 좌표 고정
				_state = BOSS_MISSILE;			// 애니메이션 지정
				if (!_ani->isPlay())
				{
					_fireDelay++;
					if (delay > 500)
					{
						delay = 0;
						_lastPattern = BOSS_MISSILE;
						_pattern = BOSS_IDLE;
					}
					if (_fireDelay % 30 == 0)	// 공격 주기
					{
						_fireDelay = 0;
						float pAngle = getAngle(_location.x, _location.y, _playerLoc.x, _playerLoc.y);	// 플레이어 좌표에 따라 각도가 바뀜
						_bullet->init("보스 불릿 2", _location.x, _location.y, 10.0f, pAngle, 20);		// 불릿 발사
					}					
				}
			}			
			break;
		}		
		case BOSS_RAIN:
		{
			MYPOINT target = { WINSIZEX - 350, WINSIZEY / 2 };								// 주륵주륵 패턴 좌표
			_state = target.x < _location.x ? BOSS_FRONT : BOSS_BACK;						// 현재 X좌표와 목표 X좌표 비교

			if (getDistance(target.x, target.y, _location.x, _location.y) > _speed)			// 현재 좌표와 목표 좌표간의 거리가 스피드보다 크면
			{
				float moveAngle = getAngle(_location.x, _location.y, target.x, target.y);	// 각도 계산하여
				_location.move(cosf(moveAngle) * _speed, -sinf(moveAngle) * _speed);		// 각도만큼 이동
			}
			else
			{
				_location = target;						// 보스 좌표는 목표좌표로 고정
				_state = BOSS_RAIN;						// 보스 애니메이션 재생
				if (!_ani->isPlay())					// 애니메이션 끝나면
				{
					_fireDelay++;
					if (delay > 500)
					{
						delay = 0;
						_lastPattern = BOSS_RAIN;						
						_pattern = BOSS_IDLE;
					}
					if (_fireDelay % 40 == 0)			// 공격 주기 = 40
					{
						for (int i = 0; i < 5; i++)		// 한 번에 5개 씩 떨굼
						{
							// 직각으로 0~WINSIZEX까지 랜덤으로 떨굼
							_bullet->init("보스 불릿 3", RND->getFromFloatTo(0, WINSIZEX), -30, RND->getFromFloatTo(5.0f, 10.0f), PI * 3 / 2, 30);
						}						
						_fireDelay = 0;						
					}
				}
			}
			break;
		}		
	}
	_rc = RectMakeCenter(_location.x, _location.y, _img->getFrameWidth(), _img->getFrameHeight());	// 보스 좌표 계속 업데이트
}

void boss::stateControl()
{
	switch (_state)
	{
		case BOSS_IDLE:		setAnimation("보스 기본", true);	break;
		case BOSS_BACK:		setAnimation("보스 뒤에");		break;		
		case BOSS_FRONT:	setAnimation("보스 앞에");		break;
		case BOSS_SPREAD:	setAnimation("보스 패턴 1");		break;
		case BOSS_MISSILE:	setAnimation("보스 패턴 2");		break;
		case BOSS_RAIN:		setAnimation("보스 패턴 3");		break;
		case BOSS_DEAD:		
		{
			setAnimation("보스 죽음");
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
