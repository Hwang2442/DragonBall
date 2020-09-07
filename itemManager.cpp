#include "stdafx.h"
#include "itemManager.h"

itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init(int itemMax)
{
	_itemMax = itemMax;
	_currentStar = 1;

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}
	for (int i = 0; i < _vItem.size();)
	{
		if (_vItem[i]->getItemDelete())
		{
			_vItem.erase(_vItem.begin() + i);
			break;
		}
		else
		{
			++i;
		}
	}
}

void itemManager::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

void itemManager::itemSpawn(float x, float y)
{
	int dropPer = 0;
	bool isPush = 0;

	if (_vItem.size() < _itemMax)
	{
		item* vItem = new item;

		dropPer = RND->getInt(100);

		MyItemType type = static_cast<MyItemType>(RND->getInt(3) + 1);		

		switch (type)
		{
			case AURA:
			{				
				if (dropPer < 50)
				{
					vItem->init("酒快扼", x, y, RND->getFromFloatTo(0, PI2), type, 10.0f);
					isPush = true;
				}
				break;
			}			
			case LIFE:
			{
				if (dropPer < 10)
				{
					vItem->init("积疙仿", x, y, RND->getFromFloatTo(0, PI2), type, 10.0f);
					isPush = true;
				}
				break;
			}			
			case STAR:
			{
				if (dropPer < 40 && _currentStar < 8)
				{
					vItem->init(to_string(_currentStar) + "己备", x, y, RND->getFromFloatTo(0, PI2), type, 10.0f);
					_currentStar++;
					isPush = true;
				}
				break;
			}
		}
		if(isPush) _vItem.push_back(vItem);
	}
}
