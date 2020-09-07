#include "stdafx.h"
#include "gamePlay.h"

gamePlay::gamePlay()
{
}

gamePlay::~gamePlay()
{
}

HRESULT gamePlay::init()
{
	_player = new player;
	_player->init();

	_em = new enemyManager;
	_em->init(3, 4, 200, 2);

	_itemM = new itemManager;
	_itemM->init(10);
	
	_gokuLife = 5;
	_gameOver = _gameEnd = _count = _loopX = _getBall = 0;
	_alpha = _backAlpha = 0;
	_volume = 1.0f;

	SOUNDMANAGER->stop("피니쉬");
	SOUNDMANAGER->stop("오프닝");
	SOUNDMANAGER->stop("플레이");

	SOUNDMANAGER->play("플레이", _volume);

	return S_OK;
}

void gamePlay::release()
{
}

void gamePlay::update()
{
	_player->update();
	_em->update();
	_itemM->update();

	_em->setPlayerLocation(_player->getTargetRect());

	if (_player->getGamePlay() == ISINIT && _gokuLife >= 0)
	{
		_gokuLife--;
		if(_gokuLife > 0) _player->init();
	}	
	if (_gokuLife < 0)
	{		
		if (_backAlpha >= 253)
		{
			_backAlpha = 255;
			_gameOver = true;
			_volume = 1.0f;
			SOUNDMANAGER->stop("플레이");
		}
		else
		{
			_backAlpha++;
			_volume -= 0.002f;
		}
		SOUNDMANAGER->setVolume("플레이", _volume);
	}
	
	if (_em->getBoss()->getBossEnd())
	{
		_player->setGamePlay(ISWIN);

		if (_backAlpha >= 253)
		{
			_backAlpha = 255;
			_gameEnd = true;
			_volume = 1.0f;
			SOUNDMANAGER->stop("플레이");
		}
		else
		{
			_backAlpha++;
			_volume -= 0.002f;
		}		
		SOUNDMANAGER->setVolume("플레이", _volume);		
	}

	playerEnemyCollision();	
}

void gamePlay::render()
{
	IMAGEMANAGER->findImage("배경")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX += 5, 0);

	for (int i = 0; i < _gokuLife; i++)
	{
		IMAGEMANAGER->findImage("재시작 횟수")->render(getMemDC(), 10 + 75 * i, 10);
	}
	for (int i = 0; i < _getBall; i++)
	{
		IMAGEMANAGER->findImage(to_string(i + 1) + "성구")->render(getMemDC(), 10 + 35 * i, 85);
	}
	if (_getBall == 7)
	{
		IMAGEMANAGER->findImage("신룡 배경")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGEMANAGER->findImage("신룡 배경")->getWidth() / 2, WINSIZEY / 2 - IMAGEMANAGER->findImage("신룡 배경")->getHeight() / 2, _alpha);
		if (_alpha < 255 && _gokuLife > 0) 
		{
			_alpha++;
		}
		else if (_alpha >= 255)
		{
			_alpha = 255;
		}
	}
	
	_player->render();
	_em->render();
	_itemM->render();	

	IMAGEMANAGER->findImage("검정")->alphaRender(getMemDC(), _backAlpha);	
}

void gamePlay::playerEnemyCollision()
{
	// 플레이어 불릿과 에너미 충돌 처리
	for (int i = 0; i < _player->getPlayerBullet()->getVBullet().size(); )	// 플레이어 불릿
	{
		bool isDelete = false;
		RECT temp;
		for (int j = 0; j < _em->getEnemyVector().size(); j++)	// 에너미
		{
			if (IntersectRect(&temp, &_player->getPlayerBullet()->getVBullet()[i].rc, &_em->getEnemyVector()[j]->getRectEnemy()))	// 플레이어 불릿과 에너미 충돌
			{
				if (_em->getEnemyVector()[j]->getEnemyLife() <= 0) break;	// 이미 죽은 건 넘김

				_player->getPlayerBullet()->bulletDelete(i);				// 불릿 삭제
				_player->setGauge(_player->getGauge() + 5);					// 게이지 증가

				_em->getEnemyVector()[j]->setEnemyLife(_em->getEnemyVector()[j]->getEnemyLife() - 1);				// 에너미 체력 - 1

				EFFECTMANAGER->play("기본 불릿효과", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// 이펙트 효과
				SOUNDMANAGER->stop("지면 충돌");
				SOUNDMANAGER->play("지면 충돌");
				isDelete = true;

				break;
			}
		}
		if (!isDelete)
		{
			i++;
		}
	}
	// 에너지파 충돌 && 궁극기 충돌
	for (int i = 0; i < _em->getEnemyVector().size();)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getPlayerBomb()->getBombRect(), &_em->getEnemyVector()[i]->getRectEnemy()))	// 에너지파와 에너미 충돌
		{
			if (_em->getEnemyVector()[i]->getEnemyLife() <= 0) break;	// 이미 죽은 건 넘김

			_em->getEnemyVector()[i]->setEnemyLife(_em->getEnemyVector()[i]->getEnemyLife() - 0.5f);			// 에너미 생명 줄이고

			EFFECTMANAGER->play("특수 불릿효과", 
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().left, _em->getEnemyVector()[i]->getRectEnemy().right),
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().top, _em->getEnemyVector()[i]->getRectEnemy().bottom)
			);		// 이펙트 효과					
		}				
		else
		{
			++i;
		}
	}
	for (int i = 0; i < _em->getEnemyVector().size(); i++)
	{
		if (_player->getDragonRect().left > WINSIZEX / 2 - 100)
		{
			_em->getEnemyVector()[i]->setEnemyLife(0.0f);
			

			EFFECTMANAGER->play("특수 불릿효과",
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().left, _em->getEnemyVector()[i]->getRectEnemy().right),
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().top, _em->getEnemyVector()[i]->getRectEnemy().bottom)
			);		// 이펙트 효과		
		}		
	}
	// 에너미 삭제 확인
	for (int i = 0; i < _em->getEnemyVector().size();)	// 에너미
	{
		if (_em->getEnemyVector()[i]->getEnemyDelete())	// 에너미 삭제 플래그가 참이면
		{
			RECT temp = _em->getEnemyVector()[i]->getRectEnemy();

			_itemM->itemSpawn((temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);

			_em->enemyRemove(i);	// 삭제			
			break;
		}
		else
		{
			++i;
		}
	}	
	// 플레이어 에너미 불릿 충돌
	for (int i = 0; i < _em->getBullet()->getVBullet().size();)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getTargetRect(), &_em->getBullet()->getVBullet()[i].rc) && _player->getGamePlay() == ISPLAY)
		{
			_em->getBullet()->bulletDelete(i);
			_player->setGamePlay(ISDEAD);

			EFFECTMANAGER->play("기본 불릿효과", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// 이펙트 효과			
			break;
		}
		else
		{
			++i;
		}
	}
	for (int i = 0; i < _em->getEnemyVector().size();)
	{
		RECT temp;
		if (_em->getEnemyVector()[i]->getEnemyType() == RUSH && IntersectRect(&temp, &_player->getTargetRect(), &_em->getEnemyVector()[i]->getRectEnemy())
			&& _player->getGamePlay() == ISPLAY)
		{
			_em->getEnemyVector()[i]->setEnemyLife(0);
			_player->setGamePlay(ISDEAD);

			EFFECTMANAGER->play("기본 불릿효과", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// 이펙트 효과			
			break;
		}
		else
		{
			++i;
		}
	}

	// 보스 충돌 관련
	if (_em->getBossPhase())
	{
		// 에너지파 보스 충돌
		RECT temp;
		if (IntersectRect(&temp, &_player->getPlayerBomb()->getBombRect(), &_em->getBossRect()))
		{
			if (_em->getBoss()->getLife() > 0)
			{
				_em->getBoss()->setLife(_em->getBoss()->getLife() - 0.5f);

				EFFECTMANAGER->play("특수 불릿효과",
					RND->getFromFloatTo(_em->getBossRect().left, _em->getBossRect().right),
					RND->getFromFloatTo(_em->getBossRect().top, _em->getBossRect().bottom)
				);		// 이펙트 효과				
			}
		}
		if (IntersectRect(&temp, &_player->getDragonRect(), &_em->getBossRect()))
		{
			if (_em->getBoss()->getLife() > 0)
			{
				_em->getBoss()->setLife(_em->getBoss()->getLife() - 1.5f);

				EFFECTMANAGER->play("특수 불릿효과",
					RND->getFromFloatTo(_em->getBossRect().left, _em->getBossRect().right),
					RND->getFromFloatTo(_em->getBossRect().top, _em->getBossRect().bottom)
				);		// 이펙트 효과				
			}
		}
		// 플레이어 보스 불릿 충돌
		for (int i = 0; i < _em->getBoss()->getBullet()->getVBullet().size();)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getTargetRect(), &_em->getBoss()->getBullet()->getVBullet()[i].rc) && _player->getGamePlay() == ISPLAY)
			{
				_em->getBoss()->getBullet()->bulletDelete(i);
				_player->setGamePlay(ISDEAD);

				EFFECTMANAGER->play("기본 불릿효과", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// 이펙트 효과				
				break;
			}
			else
			{
				++i;
			}
		}
		// 보스 피격 충돌
		for (int i = 0; i < _player->getPlayerBullet()->getVBullet().size();)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getPlayerBullet()->getVBullet()[i].rc, &_em->getBossRect()))
			{
				if (_em->getBoss()->getLife() <= 0) break;

				_player->getPlayerBullet()->bulletDelete(i);

				_player->setGauge(_player->getGauge() + 5);

				_em->getBoss()->setLife(_em->getBoss()->getLife() - 1.0f);

				EFFECTMANAGER->play("기본 불릿효과", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// 이펙트 효과
				SOUNDMANAGER->stop("지면 충돌");
				SOUNDMANAGER->play("지면 충돌");
				break;
			}
			else
			{
				++i;
			}
		}
	}	
	
	// 플레이어 아이템 충돌
	for (int i = 0; i < _itemM->getVitem().size();)
	{
		if (isCollision(_player->getPlayerRect(), _itemM->getVitem()[i]->getItemRect()))
		{
			switch (_itemM->getVitem()[i]->getItemType())
			{
				case AURA:
				{
					_player->setShiled(true);
					break;
				}			
				case LIFE:
				{
					_gokuLife++;
					break;
				}
				case STAR:
				{
					_getBall++;
					break;
				}
			}			
			_itemM->itemDelete(i);
			break;
		}
		else
		{
			++i;
		}
	}
}