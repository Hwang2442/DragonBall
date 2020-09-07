#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init(int enemyMin, int enemyMax, int spawnCount, int bossSpawnCount)
{
	_bullet = new bullet;
	_boss = new boss;

	_enemyMin = enemyMin;
	_enemyMax = enemyMax;
	_spawnCount = spawnCount;
	_bossSpawn = bossSpawnCount;
	_spawnDelay = 0;

	_isBossPhase = false;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	if (!_isBossPhase)
	{
		_spawnDelay++;
		if (_spawnDelay % _spawnCount == 0)
		{
			_bossSpawn--;
			enemySpawn();
		}
		if (_bossSpawn == 0)
		{
			_isBossPhase = true;
			_boss->init();
		}
	}
	else
	{
		_boss->update();
		_boss->setPlayerRect(_player);
	}

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
	}

	enemyBulletFire();
	_bullet->update();
}

void enemyManager::render()
{		
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}

	_bullet->render();
	if (_isBossPhase)
	{
		_boss->render();		
	}
}

void enemyManager::enemySpawn()
{
	int enemyCount = RND->getFromIntTo(_enemyMin, _enemyMax);

	for (int i = 0; i < enemyCount; i++)
	{
		enemy* vEnemy = new enemy;
		
		int enemyType = RND->getInt(3) + 1;		

		vEnemy->init("에너미 " + to_string(enemyType), RND->getFromFloatTo(WINSIZEX / 2 - 150, WINSIZEX - 100), RND->getFromFloatTo(100, WINSIZEY - 100), static_cast<MyEnemyType>(enemyType));

		_vEnemy.push_back(vEnemy);
	}
}

void enemyManager::enemyBulletFire()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		RECT temp = _vEnemy[i]->getRectEnemy();
		int centerX = (temp.left + temp.right) / 2;
		int centerY = (temp.top + temp.bottom) / 2;

		switch (_vEnemy[i]->getEnemyType())
		{
			case RUSH: break;
			case SHOTGUN:
			{
				if (_vEnemy[i]->bulletCountFire())
				{
					_bullet->init("에너미 불릿 2", centerX, centerY, 10.0f, PI * 2 / 3);		// 120도
					_bullet->init("에너미 불릿 2", centerX, centerY, 10.0f, PI * 5 / 6);		// 150도
					_bullet->init("에너미 불릿 2", centerX, centerY, 10.0f, PI);				// 180도
					_bullet->init("에너미 불릿 2", centerX, centerY, 10.0f, PI * 7 / 6);		// 210도
					_bullet->init("에너미 불릿 2", centerX, centerY, 10.0f, PI * 4 / 3);		// 240도
				}				
				break;
			}
			case MISSILE:
			{
				if (_vEnemy[i]->bulletCountFire())
				{					
					float angle = getAngle(centerX, centerY, _player.x, _player.y);

					_bullet->init("에너미 불릿 3", centerX, centerY, 10.0f, angle);					
				}
			}
		}
	}
}

void enemyManager::setPlayerLocation(RECT playerRect)
{
	_player.x = (playerRect.left + playerRect.right) / 2;
	_player.y = (playerRect.top + playerRect.bottom) / 2;
}
