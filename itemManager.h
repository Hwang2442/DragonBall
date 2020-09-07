#pragma once
#include "gameNode.h"
#include "item.h"

class itemManager : public gameNode
{
private:
	vector<item*> _vItem;

	int _itemMax;
	int _currentStar;

public:
	itemManager();
	~itemManager();

	HRESULT init(int itemMax);
	void release();
	void update();
	void render();

	void itemSpawn(float x, float y);

	void itemDelete(int arrNum) { _vItem.erase(_vItem.begin() + arrNum); }

	vector<item*> getVitem() { return _vItem; }

};

