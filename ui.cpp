#include "stdafx.h"
#include "ui.h"

ui::ui()
{
}

ui::~ui()
{
}

HRESULT ui::init(string imageName, MyRender renderLoc)
{
	_pBar = new progressBar;
	_img = IMAGEMANAGER->findImage(imageName);

	_renderLoc = renderLoc;

	switch (_renderLoc)
	{
		case LEFTTOP:
		{
			_x = 0;
			_y = 0;
			_pBar->init("���� ��", "���� ��", _x, _y + _img->getHeight());
			break;
		}		
		case LEFTBOT:
		{
			_x = 0;
			_y = WINSIZEY - _img->getHeight();
			_pBar->init("���� ��", "���� ��", _x, WINSIZEY - IMAGEMANAGER->findImage("���� ��")->getHeight() * 2);
			break;
		}		
		case RIGHTTOP:
		{
			_x = WINSIZEX - _img->getWidth();
			_y = 0;
			_pBar->init("���� ��", "���� ��", WINSIZEX - IMAGEMANAGER->findImage("���� ��")->getWidth(), _y + _img->getHeight() * 2);
			break;
		}		
		case RIGHTBOT:
		{
			_x = WINSIZEX - _img->getWidth();
			_y = WINSIZEY - _img->getHeight();
			_pBar->init("���� ��", "���� ��", WINSIZEX - IMAGEMANAGER->findImage("���� ��")->getWidth(), WINSIZEY - IMAGEMANAGER->findImage("���� ��")->getHeight() * 2);
			break;
		}		
	}

	return S_OK;
}

void ui::release()
{
}

void ui::update()
{
	_pBar->update();
}

void ui::render()
{	
	_img->alphaRender(getMemDC(), _x, _y, 255);
	_pBar->render();
}
