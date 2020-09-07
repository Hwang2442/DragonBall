#include "stdafx.h"
#include "gameEnd.h"

HRESULT gameEnd::init()
{
	for (int i = 0; i < ENDNUM; i++)
	{
		char str[20];
		sprintf_s(str, "���� %02d", i + 1);	
		_img[i] = IMAGEMANAGER->findImage(str);
	}

	_alpha = _endFinish = _fadeOut = _arrNum = 0;

	SOUNDMANAGER->stop("�ǴϽ�");
	SOUNDMANAGER->stop("������");
	SOUNDMANAGER->stop("�÷���");
	
	SOUNDMANAGER->play("�ǴϽ�");

	return S_OK;
}

void gameEnd::release()
{
}

void gameEnd::update()
{
	if (!_endFinish)
	{
		switch (_fadeOut)
		{
			case 0:	// ���� ��������
			{
				if(_alpha < 255) _alpha++;
				else
				{
					_alpha = 255;
					_fadeOut = true;
				}
				break;
			}
			case 1:	// ���� ��������
			{
				_alpha--;
				if (_alpha <= 0)
				{					
					if (_arrNum < ENDNUM - 1)
					{
						_arrNum++;
					}
					else
					{
						_endFinish = true;
					}
					_fadeOut = false;
				}
				break;
			}
		}
	}	
}

void gameEnd::render()
{
	_img[_arrNum]->alphaRender(getMemDC(), WINSIZEX / 2 - _img[_arrNum]->getWidth() / 2, WINSIZEY / 2 - _img[_arrNum]->getHeight() / 2, _alpha);
}
