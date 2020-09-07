#pragma once
#include "gameNode.h"
#include <vector>

// �������� �� �÷��̾� �Ѿ� ����ü
struct tagBullet
{
	image*		img;	// �Ѿ˿� �� �̹���
	animation*	ani;	// �Ѿ˿� �� �ִϸ��̼�
	RECT		rc;		// �Ѿ˿� �� ��Ʈ
	float		x, y;	// ���� x, y
	float		speed;	// ���ǵ�
	float		angle;	// ����
};

// �������� �� �Ѿ� Ŭ����
class bullet : public gameNode
{
private:
	vector<tagBullet>	_vBullet;	// �Ҹ� ����
	int					_frame;		// ����� ������

public:
	bullet();
	~bullet();

	virtual HRESULT init(string imageName, float x, float y, float speed, float angle = 0, int frame = 10);
	virtual void release();
	virtual void update();
	virtual void render();
	
	// �Ҹ� ����
	void	bulletDelete	(int arrNum);
	// �Ҹ� ���ǵ� ������
	void	setBulletSpeed	(int arrNum, float speed);
	// ȭ�� �ٱ����� �������� Ȯ��
	bool	screenOverCheck	(RECT bulletRect);	

	// �Ҹ� ������
	vector<tagBullet>	getVBullet() { return _vBullet; }
};

// �������Ŀ� ����� ����ü
struct tagBomb
{
	image*	img;	// �̹���
	RECT	rc;		// ��Ʈ
	float	x, y;	// ����
	float	speed;	// ���ǵ�
};

class playerBomb : public gameNode
{
private:
	bool			_isFire;		// �߻� ��
	tagBomb			_bombStart;		// ���� 
	tagBomb			_bombFinal;		// ��
	vector<tagBomb> _vBombMid;		// �߰�

public:
	playerBomb();
	~playerBomb();

	virtual HRESULT init(string imageName, float x, float y, float speed = 30.0f);
	virtual void release();
	virtual void update();
	virtual void render();

	// �������� ��ġ ������Ʈ
	void bombFire(float x, float y);
	// �������� ����
	void bombMove();
	// �������� �߻� ����
	void bombFinish();

	// �������� ��Ʈ ������
	RECT getBombRect();
};