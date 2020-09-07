#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _L, _T; // ī�޶� LEFT, TOP ���� ��ǥ�̸� �̸� �������� �׷���
	float _x, _y; // ī�޶� ���� ��ǥ
	float _width, _height; // ī�޶� �ʺ�, ���� ��

	// �⺻��
	float _originMinL, _originMaxL;
	float _originMinT, _originMaxT;
	float _originMinX, _originMaxX;
	float _originMinY, _originMaxY;

	// zoom���� ���� ����� ����
	float _minL, _maxL; // Left ��ǥ�� ������ ����
	float _minT, _maxT; // Top ��ǥ�� ������ ����
	float _minX, _maxX; // x ��ǥ�� ������ ����
	float _minY, _maxY; // y ��ǥ�� ������ ����

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	void setConfig(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT);
	void setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY);
	float getL();
	float getT();
	float getX();
	float getY();
	void setL(float newL);
	void setT(float newT);
	void setX(float newX);
	void setY(float newY);
	void movePivot(float offsetX, float offsetY);

	float getRelativeL(float left);
	LONG getRelativeL(LONG left);
	float getRelativeT(float top);
	LONG getRelativeT(LONG top);

	float getAbsoluteL(float left);
	LONG getAbsoluteL(LONG left);
	float getAbsoluteT(float top);
	LONG getAbsoluteT(LONG top);

	void rectangle(HDC hdc, TTYONE_UTIL::MYRECT rect);
	void rectangle(HDC hdc, RECT rect);
	void ellipse(HDC hdc, TTYONE_UTIL::MYRECT rect);
	void ellipse(HDC hdc, RECT rect);

	void render(HDC hdc, image* img);
	void render(HDC hdc, image* img, float destX, float destY);
	void render(HDC hdc, image* img, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void render(HDC hdc, HDC originDC, float destX, float destY, float width, float height, bool trans, COLORREF rgb);
	void loopRender(HDC hdc, image* img, RECT lpRect, int offsetX, int offsetY);

	void frameRender(HDC hdc, image* img, float destX, float destY);
	void frameRender(HDC hdc, image* img, float destX, float destY, int frameX, int frameY);
	void frameRender(HDC hdc, image* img, float destX, float destY, int frameX, int frameY, bool leftRightInverse);


	void aniRender(HDC hdc, image* img, int destX, int destY, animation* ani, bool leftRightInverse);

	void zoom(HDC hdc, float ratio);
};

