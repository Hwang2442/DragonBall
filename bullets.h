#pragma once
#include "gameNode.h"
#include <vector>

// 공용으로 쓸 플레이어 총알 구조체
struct tagBullet
{
	image*		img;	// 총알에 쓸 이미지
	animation*	ani;	// 총알에 쓸 애니메이션
	RECT		rc;		// 총알에 쓸 렉트
	float		x, y;	// 중점 x, y
	float		speed;	// 스피드
	float		angle;	// 각도
};

// 공용으로 쓸 총알 클래스
class bullet : public gameNode
{
private:
	vector<tagBullet>	_vBullet;	// 불릿 벡터
	int					_frame;		// 재생할 프레임

public:
	bullet();
	~bullet();

	virtual HRESULT init(string imageName, float x, float y, float speed, float angle = 0, int frame = 10);
	virtual void release();
	virtual void update();
	virtual void render();
	
	// 불릿 삭제
	void	bulletDelete	(int arrNum);
	// 불릿 스피드 설정자
	void	setBulletSpeed	(int arrNum, float speed);
	// 화면 바깥으로 나갔는지 확인
	bool	screenOverCheck	(RECT bulletRect);	

	// 불릿 접근자
	vector<tagBullet>	getVBullet() { return _vBullet; }
};

// 에너지파에 사용할 구조체
struct tagBomb
{
	image*	img;	// 이미지
	RECT	rc;		// 렉트
	float	x, y;	// 중점
	float	speed;	// 스피드
};

class playerBomb : public gameNode
{
private:
	bool			_isFire;		// 발사 중
	tagBomb			_bombStart;		// 시작 
	tagBomb			_bombFinal;		// 끝
	vector<tagBomb> _vBombMid;		// 중간

public:
	playerBomb();
	~playerBomb();

	virtual HRESULT init(string imageName, float x, float y, float speed = 30.0f);
	virtual void release();
	virtual void update();
	virtual void render();

	// 에너지파 위치 업데이트
	void bombFire(float x, float y);
	// 에너지파 무빙
	void bombMove();
	// 에너지파 발사 종료
	void bombFinish();

	// 에너지파 렉트 접근자
	RECT getBombRect();
};