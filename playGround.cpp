#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);

	// ���
	IMAGEMANAGER->addImage("���", "image/backSpace.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/���� ȭ��.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	// ���� 1�ܰ�
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� �⺻", "image/goku/idle.bmp"			, 678, 111, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� �ڿ�", "image/goku/moveBack.bmp"		, 192, 141, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� �տ�", "image/goku/moveFront.bmp"		, 218, 135, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� ����", "image/goku/attack.bmp"		, 786, 132, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� �¸�", "image/goku/win.bmp"			, 880, 175, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� ����", "image/goku/transform.bmp"		, 564, 162, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� �ʻ�", "image/goku/energyBlast.bmp"	, 945, 124, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1�ܰ� ���� ����", "image/goku/dead.bmp"			, 459, 107, 3, 1, true, RGB(255, 0, 255));

	// ���� 2�ܰ�
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �⺻", "image/Sgoku/idle.bmp"			,  642, 165, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �ڿ�", "image/Sgoku/moveBack.bmp"		,  192, 148, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �տ�", "image/Sgoku/moveFront.bmp"	,  218, 146, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� ����", "image/Sgoku/attack.bmp"		,  786, 143, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �¸�", "image/Sgoku/win.bmp"			,  462, 163, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �ʻ�", "image/Sgoku/energyBlast.bmp"	, 1080, 139, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� ����", "image/Sgoku/dead.bmp"			,  465, 121, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� ����", "image/Sgoku/transform.bmp"	, 1440, 172, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� ���� �ñ�", "image/Sgoku/ultimate.bmp"		, 1386, 142, 9, 1, true, RGB(255, 0, 255));	

	// �Ҹ�
	IMAGEMANAGER->addFrameImage("1�ܰ� �Ҹ�"		, "image/bullet/gokuBullet.bmp"		,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�ܰ� �Ҹ�"		, "image/bullet/SgokuBullet.bmp"	,  320,  80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ� �Ҹ� 2"	, "image/bullet/enemyBullet2.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ� �Ҹ� 3"	, "image/bullet/enemyBullet3.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �Ҹ� 1"	, "image/bullet/bossBullet1.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �Ҹ� 2"	, "image/bullet/bossBullet2.bmp"	, 1600, 200, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �Ҹ� 3"	, "image/bullet/bossBullet3.bmp"	,  520, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �Ҹ� 4"	, "image/bullet/bossBullet4.bmp"	,  520, 130, 4, 1, true, RGB(255, 0, 255));

	// ��������	
	IMAGEMANAGER->addImage("1�ܰ� �������� ����", "image/bullet/gokuBlast_start.bmp"	,  62,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1�ܰ� �������� �߰�", "image/bullet/gokuBlast_mid.bmp"	,  64,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1�ܰ� �������� ����", "image/bullet/gokuBlast_end.bmp"	,  62,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2�ܰ� �������� ����", "image/bullet/SgokuBlast_start.bmp"	, 126, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2�ܰ� �������� �߰�", "image/bullet/SgokuBlast_mid.bmp"	,  64, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2�ܰ� �������� ����", "image/bullet/SgokuBlast_end.bmp"	, 126, 128, true, RGB(255, 0, 255));

	// ��
	IMAGEMANAGER->addImage("���ʹ� 1", "image/enemy/enemyType_1.bmp", 141, 145, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ʹ� 2", "image/enemy/enemyType_2.bmp", 174, 172, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ʹ� 3", "image/enemy/enemyType_3.bmp", 159, 205, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���ʹ� 1 ����", "image/enemy/enemyDead_1.bmp", 480, 132, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ� 2 ����", "image/enemy/enemyDead_2.bmp", 546, 132, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ� 3 ����", "image/enemy/enemyDead_3.bmp", 555, 147, 3, 1, true, RGB(255, 0, 255));

	// ����
	IMAGEMANAGER->addFrameImage("���� �⺻"		, "image/boss/idle.bmp"			, 1210, 201, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �տ�"		, "image/boss/moveFront.bmp"	,  296, 205,  2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �ڿ�"		, "image/boss/moveBack.bmp"		,  306, 207,  2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� ����"		, "image/boss/dead.bmp"			, 1463, 207,  7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� �¸�"		, "image/boss/win.bmp"			,  675,  20,  5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� ���� 1"	, "image/boss/bossSpread.bmp"	, 1344, 214,  8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� ���� 2"	, "image/boss/bossMissile.bmp"	, 1750, 205, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� ���� 3"	, "image/boss/bossRain.bmp"		,  972, 201,  6, 1, true, RGB(255, 0, 255));
	
	// UI	
	IMAGEMANAGER->addImage("1�ܰ� ���� UI"	, "image/ui/goku.bmp"	 , 250, 305, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2�ܰ� ���� UI"	, "image/ui/Sgoku.bmp"	 , 241, 324, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3�ܰ� ���� UI"	, "image/ui/SSgoku.bmp"	 , 284, 317, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� UI"			, "image/ui/broly.bmp"	 , 299, 338, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� ��"			, "image/ui/backBar.bmp" , 260,  38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� ��"			, "image/ui/frontBar.bmp", 260,  38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����� Ƚ��"		, "image/ui/life.bmp"	 ,  72,  72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ŷ� ���"		, "image/ui/shenron.bmp" , 377, 340, true, RGB(255, 0, 255));

	// ����Ʈ
	EFFECTMANAGER->addEffect("�⺻ �Ҹ�ȿ��", "image/effect/bulletEffect1.bmp", 384, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("���� �Ҹ�ȿ��", "image/effect/bulletEffect2.bmp", 448, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("Ư�� �Ҹ�ȿ��", "image/effect/bulletEffect3.bmp", 512, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("���� �Ҹ�ȿ��", "image/effect/bulletEffect4.bmp", 512, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("�޺� �Ҹ�ȿ��", "image/effect/bulletEffect5.bmp", 448, 64, 64, 64, 1.0f, 0.3f, 300);

	// ���� ���� ����Ʈ
	IMAGEMANAGER->addFrameImage("���� �ƿ��", "image/effect/aura.bmp", 320, 160, 2, 1, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("���� ��", "image/effect/dragon.bmp", 3127, 800, true, RGB(255, 0, 255));

	// ��ź��
	IMAGEMANAGER->addFrameImage("���� ��ź��", "image/effect/target.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));

	// ������
	IMAGEMANAGER->addFrameImage("�ƿ��", "image/item/item1.bmp", 128, 32,  4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����", "image/item/item2.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("1����", "image/item/1star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2����", "image/item/2star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3����", "image/item/3star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4����", "image/item/4star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5����", "image/item/5star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6����", "image/item/6star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7����", "image/item/7star.bmp", 32, 32, true, RGB(255, 0, 255));

	// ��Ʈ��
	IMAGEMANAGER->addImage("���� ��Ʈ��"		, "image/intro/intro.bmp"	, WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ŸƮ ����"		, "image/intro/startOff.bmp",	   357,	      58, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ŸƮ ����"		, "image/intro/startOn.bmp" ,	   357,	      58, false, RGB(255, 0, 255));	

	// ����
	IMAGEMANAGER->addImage("���� 01", "image/ending/����01.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 02", "image/ending/����02.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 03", "image/ending/����03.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 04", "image/ending/����04.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 05", "image/ending/����05.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 06", "image/ending/����06.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 07", "image/ending/����07.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 08", "image/ending/����08.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 09", "image/ending/����09.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 10", "image/ending/����10.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 11", "image/ending/����11.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 12", "image/ending/����12.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� 13", "image/ending/����13.bmp", 600, 400, false, RGB(255, 0, 255));

	// ��� ����
	SOUNDMANAGER->addSound("������", "music/�巡�ﺼZ������.mp3"	, true, true);
	SOUNDMANAGER->addSound("�÷���", "music/�����÷��̺��.ogg"	, true, true);
	SOUNDMANAGER->addSound("�ǴϽ�", "music/�巡�ﺼZ����.mp3"	, true, false);		

	// ����Ʈ
	SOUNDMANAGER->addSound("���� �浹", "music/���� �浹.wav", false, false);	

	_intro	= new gameIntro;
	_play	= new gamePlay;
	_end	= new gameEnd;

	SCENEMANAGER->addScene("��Ʈ��", _intro);
	SCENEMANAGER->addScene("�÷���", _play);
	SCENEMANAGER->addScene("����", _end);

	SCENEMANAGER->changeScene("��Ʈ��");		

	return S_OK;
}

//�޸� ����
void playGround::release()
{
}

//����
void playGround::update()
{
	gameNode::update();	

	if (_intro->getChange())
	{
		_intro->setChange(false);
		SCENEMANAGER->changeScene("�÷���");
	}
	if (_play->getGameEnd())
	{
		_play->setGameEnd(false);
		SCENEMANAGER->changeScene("����");
	}
	if (_play->getGameOver())
	{
		_play->setGameOver(false);
		SCENEMANAGER->changeScene("��Ʈ��");
	}
	if (_end->getGameEnd())
	{
		_end->setGameEnd(false);
		SCENEMANAGER->changeScene("��Ʈ��");
	}

	EFFECTMANAGER->update();
	SCENEMANAGER->update();		
}

//�׸��� ����
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=================================================		
	
	SCENEMANAGER->render();	
	EFFECTMANAGER->render();		

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}