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

	SOUNDMANAGER->stop("�ǴϽ�");
	SOUNDMANAGER->stop("������");
	SOUNDMANAGER->stop("�÷���");

	SOUNDMANAGER->play("�÷���", _volume);

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
			SOUNDMANAGER->stop("�÷���");
		}
		else
		{
			_backAlpha++;
			_volume -= 0.002f;
		}
		SOUNDMANAGER->setVolume("�÷���", _volume);
	}
	
	if (_em->getBoss()->getBossEnd())
	{
		_player->setGamePlay(ISWIN);

		if (_backAlpha >= 253)
		{
			_backAlpha = 255;
			_gameEnd = true;
			_volume = 1.0f;
			SOUNDMANAGER->stop("�÷���");
		}
		else
		{
			_backAlpha++;
			_volume -= 0.002f;
		}		
		SOUNDMANAGER->setVolume("�÷���", _volume);		
	}

	playerEnemyCollision();	
}

void gamePlay::render()
{
	IMAGEMANAGER->findImage("���")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX += 5, 0);

	for (int i = 0; i < _gokuLife; i++)
	{
		IMAGEMANAGER->findImage("����� Ƚ��")->render(getMemDC(), 10 + 75 * i, 10);
	}
	for (int i = 0; i < _getBall; i++)
	{
		IMAGEMANAGER->findImage(to_string(i + 1) + "����")->render(getMemDC(), 10 + 35 * i, 85);
	}
	if (_getBall == 7)
	{
		IMAGEMANAGER->findImage("�ŷ� ���")->alphaRender(getMemDC(), WINSIZEX / 2 - IMAGEMANAGER->findImage("�ŷ� ���")->getWidth() / 2, WINSIZEY / 2 - IMAGEMANAGER->findImage("�ŷ� ���")->getHeight() / 2, _alpha);
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

	IMAGEMANAGER->findImage("����")->alphaRender(getMemDC(), _backAlpha);	
}

void gamePlay::playerEnemyCollision()
{
	// �÷��̾� �Ҹ��� ���ʹ� �浹 ó��
	for (int i = 0; i < _player->getPlayerBullet()->getVBullet().size(); )	// �÷��̾� �Ҹ�
	{
		bool isDelete = false;
		RECT temp;
		for (int j = 0; j < _em->getEnemyVector().size(); j++)	// ���ʹ�
		{
			if (IntersectRect(&temp, &_player->getPlayerBullet()->getVBullet()[i].rc, &_em->getEnemyVector()[j]->getRectEnemy()))	// �÷��̾� �Ҹ��� ���ʹ� �浹
			{
				if (_em->getEnemyVector()[j]->getEnemyLife() <= 0) break;	// �̹� ���� �� �ѱ�

				_player->getPlayerBullet()->bulletDelete(i);				// �Ҹ� ����
				_player->setGauge(_player->getGauge() + 5);					// ������ ����

				_em->getEnemyVector()[j]->setEnemyLife(_em->getEnemyVector()[j]->getEnemyLife() - 1);				// ���ʹ� ü�� - 1

				EFFECTMANAGER->play("�⺻ �Ҹ�ȿ��", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// ����Ʈ ȿ��
				SOUNDMANAGER->stop("���� �浹");
				SOUNDMANAGER->play("���� �浹");
				isDelete = true;

				break;
			}
		}
		if (!isDelete)
		{
			i++;
		}
	}
	// �������� �浹 && �ñر� �浹
	for (int i = 0; i < _em->getEnemyVector().size();)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getPlayerBomb()->getBombRect(), &_em->getEnemyVector()[i]->getRectEnemy()))	// �������Ŀ� ���ʹ� �浹
		{
			if (_em->getEnemyVector()[i]->getEnemyLife() <= 0) break;	// �̹� ���� �� �ѱ�

			_em->getEnemyVector()[i]->setEnemyLife(_em->getEnemyVector()[i]->getEnemyLife() - 0.5f);			// ���ʹ� ���� ���̰�

			EFFECTMANAGER->play("Ư�� �Ҹ�ȿ��", 
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().left, _em->getEnemyVector()[i]->getRectEnemy().right),
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().top, _em->getEnemyVector()[i]->getRectEnemy().bottom)
			);		// ����Ʈ ȿ��					
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
			

			EFFECTMANAGER->play("Ư�� �Ҹ�ȿ��",
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().left, _em->getEnemyVector()[i]->getRectEnemy().right),
				RND->getFromFloatTo(_em->getEnemyVector()[i]->getRectEnemy().top, _em->getEnemyVector()[i]->getRectEnemy().bottom)
			);		// ����Ʈ ȿ��		
		}		
	}
	// ���ʹ� ���� Ȯ��
	for (int i = 0; i < _em->getEnemyVector().size();)	// ���ʹ�
	{
		if (_em->getEnemyVector()[i]->getEnemyDelete())	// ���ʹ� ���� �÷��װ� ���̸�
		{
			RECT temp = _em->getEnemyVector()[i]->getRectEnemy();

			_itemM->itemSpawn((temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);

			_em->enemyRemove(i);	// ����			
			break;
		}
		else
		{
			++i;
		}
	}	
	// �÷��̾� ���ʹ� �Ҹ� �浹
	for (int i = 0; i < _em->getBullet()->getVBullet().size();)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player->getTargetRect(), &_em->getBullet()->getVBullet()[i].rc) && _player->getGamePlay() == ISPLAY)
		{
			_em->getBullet()->bulletDelete(i);
			_player->setGamePlay(ISDEAD);

			EFFECTMANAGER->play("�⺻ �Ҹ�ȿ��", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// ����Ʈ ȿ��			
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

			EFFECTMANAGER->play("�⺻ �Ҹ�ȿ��", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// ����Ʈ ȿ��			
			break;
		}
		else
		{
			++i;
		}
	}

	// ���� �浹 ����
	if (_em->getBossPhase())
	{
		// �������� ���� �浹
		RECT temp;
		if (IntersectRect(&temp, &_player->getPlayerBomb()->getBombRect(), &_em->getBossRect()))
		{
			if (_em->getBoss()->getLife() > 0)
			{
				_em->getBoss()->setLife(_em->getBoss()->getLife() - 0.5f);

				EFFECTMANAGER->play("Ư�� �Ҹ�ȿ��",
					RND->getFromFloatTo(_em->getBossRect().left, _em->getBossRect().right),
					RND->getFromFloatTo(_em->getBossRect().top, _em->getBossRect().bottom)
				);		// ����Ʈ ȿ��				
			}
		}
		if (IntersectRect(&temp, &_player->getDragonRect(), &_em->getBossRect()))
		{
			if (_em->getBoss()->getLife() > 0)
			{
				_em->getBoss()->setLife(_em->getBoss()->getLife() - 1.5f);

				EFFECTMANAGER->play("Ư�� �Ҹ�ȿ��",
					RND->getFromFloatTo(_em->getBossRect().left, _em->getBossRect().right),
					RND->getFromFloatTo(_em->getBossRect().top, _em->getBossRect().bottom)
				);		// ����Ʈ ȿ��				
			}
		}
		// �÷��̾� ���� �Ҹ� �浹
		for (int i = 0; i < _em->getBoss()->getBullet()->getVBullet().size();)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getTargetRect(), &_em->getBoss()->getBullet()->getVBullet()[i].rc) && _player->getGamePlay() == ISPLAY)
			{
				_em->getBoss()->getBullet()->bulletDelete(i);
				_player->setGamePlay(ISDEAD);

				EFFECTMANAGER->play("�⺻ �Ҹ�ȿ��", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// ����Ʈ ȿ��				
				break;
			}
			else
			{
				++i;
			}
		}
		// ���� �ǰ� �浹
		for (int i = 0; i < _player->getPlayerBullet()->getVBullet().size();)
		{
			RECT temp;
			if (IntersectRect(&temp, &_player->getPlayerBullet()->getVBullet()[i].rc, &_em->getBossRect()))
			{
				if (_em->getBoss()->getLife() <= 0) break;

				_player->getPlayerBullet()->bulletDelete(i);

				_player->setGauge(_player->getGauge() + 5);

				_em->getBoss()->setLife(_em->getBoss()->getLife() - 1.0f);

				EFFECTMANAGER->play("�⺻ �Ҹ�ȿ��", (temp.left + temp.right) / 2, (temp.top + temp.bottom) / 2);		// ����Ʈ ȿ��
				SOUNDMANAGER->stop("���� �浹");
				SOUNDMANAGER->play("���� �浹");
				break;
			}
			else
			{
				++i;
			}
		}
	}	
	
	// �÷��̾� ������ �浹
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