#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(string frontImage, string backImage, float x, float y)
{
	_x = x;
	_y = y;

	_progressBarTop = IMAGEMANAGER->findImage(frontImage);
	_progressBarBottom = IMAGEMANAGER->findImage(backImage);

	_rcProgress = RectMake(x, y, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	
	//�ڿ� �򸮴� �������� ����ũ�⸦ �������� ��´�
	_width = _progressBarBottom->getWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarTop->getWidth(),
		_progressBarBottom->getHeight());
}

void progressBar::render()
{
	_progressBarBottom->render(getMemDC(), 
		_rcProgress.left + _progressBarBottom->getWidth() / 2, _y + _progressBarBottom->getHeight() / 2, 
		0, 0, 
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight()
	);

	_progressBarTop->render(getMemDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2, _y + _progressBarBottom->getHeight() / 2,
		0, 0,
		_width, _progressBarBottom->getHeight());	
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//����� ���ϴ� �����̿���!
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}
