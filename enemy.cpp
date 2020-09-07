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
	_imageName = imageName;						// 이미지 이름 저장하고
	_img = IMAGEMANAGER->findImage(imageName);	// 이미지 찾고

	_type = enemyType;			// 타입 지정

	_finalPosition = { x, y };	// 위치할 포지션 저장

	_rndWay = RND->getInt(2);	// 트루는 아래, 폴스는 위
	switch (_type)
	{
		case RUSH:					// 자살
		{
			// 시작 위치 설정
			_startPosition = { static_cast<float>(WINSIZEX + _img->getWidth()), _finalPosition.y };
			break;
		}		
		case SHOTGUN: case MISSILE:	// 불릿 쏘는 애
		{
			// 시작 위치 설정 -- 방향에 따라서 설정 -> 아래면 화면 위에, 위에면 화면 아래
			_startPosition = { _finalPosition.x, static_cast<float>(_rndWay ? WINSIZEY + _img->getHeight() : -_img->getHeight()) };
			break;
		}
	}
	_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());	// 렉트 갱신

	_speed = RND->getFromFloatTo(10.0f, 15.0f);			// 스피드 랜덤
	_attackRandom = RND->getFromIntTo(50, 150);			// 공격 주기도 랜덤

	_life = 5.0f;	// 이만큼 때려야 죽음
	_isDead = _isStart = _isDelete = _attackCount = 0;	// 초기화

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	if (!_isStart)
	{
		_attackCount = 1;	// 공격 하면 안댐
		switch (_type)
		{
			case RUSH:
			{
				_isStart = true;	// 자살하는 애는 바로 시작
				break;
			}			
			case SHOTGUN: case MISSILE:
			{
				float angle = getAngle(_startPosition.x, _startPosition.y, _finalPosition.x, _finalPosition.y);		// 목표좌표와 현재좌표 각도
				_startPosition.move(cosf(angle) * _speed, -sinf(angle) * _speed);	// 각도만큼 이동

				_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());		

				if (getDistance(_startPosition.x, _startPosition.y, _finalPosition.x, _finalPosition.y) < _speed)	// 거리가 스피드보다 작으면
				{
					_startPosition = _finalPosition;	// 좌표 고정
					_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());
					_isStart = true;	// 시작
				}
			}
		}
	}
	else
	{
		if (_type == RUSH)	// 달린다
		{
			if(!_isDead) _startPosition.move(-_speed, 0);	// 그냥 간다
			_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getWidth(), _img->getHeight());

			if (_rc.right < 0)	// 화면 끝까지 가면
			{
				_life = 0;		// 죽음
			}
		}
	}	

	if (_life <= 0 && !_isDead)	// 피는 없는데 아직 안죽었다면
	{
		_isDead = true;	// 죽음
		_img = IMAGEMANAGER->findImage(_imageName + " 죽음");	// 이미지 찾고
		_rc = RectMakeCenter(_startPosition.x, _startPosition.y, _img->getFrameWidth(), _img->getFrameHeight());	// 렉트 갱신
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());				// 애니메이션 초기화
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(1);
		_ani->start();
	}

	if (_isDead)
	{
		_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
		if (!_ani->isPlay())	// 죽는 모션 끝났으면
		{
			_isDelete = true;	// 삭제해도 된다
		}
	}	
}

void enemy::render()
{
	//Rectangle(getMemDC(), _rc);
	switch (_isDead)
	{
		case false: _img->render(getMemDC(), _rc.left, _rc.top);			break;	// 그냥 출력
		case true:	_img->aniRender(getMemDC(), _rc.left, _rc.top, _ani);	break;	// 프레임 출력
	}
}

bool enemy::bulletCountFire()
{
	if (_isDead) return false;	// 죽었으면 발사금지

	_attackCount++;
	if (_attackCount % _attackRandom == 0)	// 공격
	{
		_attackRandom = RND->getFromIntTo(50, 150);	// 공격 주기 랜덤 지정
		_attackCount = 0;

		return true;
	}

	return false;
}
