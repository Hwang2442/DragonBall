#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);

	// 배경
	IMAGEMANAGER->addImage("배경", "image/backSpace.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("검정", "image/검은 화면.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	// 오공 1단계
	IMAGEMANAGER->addFrameImage("1단계 오공 기본", "image/goku/idle.bmp"			, 678, 111, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 뒤에", "image/goku/moveBack.bmp"		, 192, 141, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 앞에", "image/goku/moveFront.bmp"		, 218, 135, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 공격", "image/goku/attack.bmp"		, 786, 132, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 승리", "image/goku/win.bmp"			, 880, 175, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 변신", "image/goku/transform.bmp"		, 564, 162, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 필살", "image/goku/energyBlast.bmp"	, 945, 124, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("1단계 오공 죽음", "image/goku/dead.bmp"			, 459, 107, 3, 1, true, RGB(255, 0, 255));

	// 오공 2단계
	IMAGEMANAGER->addFrameImage("2단계 오공 기본", "image/Sgoku/idle.bmp"			,  642, 165, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 뒤에", "image/Sgoku/moveBack.bmp"		,  192, 148, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 앞에", "image/Sgoku/moveFront.bmp"	,  218, 146, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 공격", "image/Sgoku/attack.bmp"		,  786, 143, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 승리", "image/Sgoku/win.bmp"			,  462, 163, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 필살", "image/Sgoku/energyBlast.bmp"	, 1080, 139, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 죽음", "image/Sgoku/dead.bmp"			,  465, 121, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 변신", "image/Sgoku/transform.bmp"	, 1440, 172, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 오공 궁극", "image/Sgoku/ultimate.bmp"		, 1386, 142, 9, 1, true, RGB(255, 0, 255));	

	// 불릿
	IMAGEMANAGER->addFrameImage("1단계 불릿"		, "image/bullet/gokuBullet.bmp"		,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2단계 불릿"		, "image/bullet/SgokuBullet.bmp"	,  320,  80, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미 불릿 2"	, "image/bullet/enemyBullet2.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미 불릿 3"	, "image/bullet/enemyBullet3.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 불릿 1"	, "image/bullet/bossBullet1.bmp"	,  256,  64, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 불릿 2"	, "image/bullet/bossBullet2.bmp"	, 1600, 200, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 불릿 3"	, "image/bullet/bossBullet3.bmp"	,  520, 130, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 불릿 4"	, "image/bullet/bossBullet4.bmp"	,  520, 130, 4, 1, true, RGB(255, 0, 255));

	// 에너지파	
	IMAGEMANAGER->addImage("1단계 에너지파 시작", "image/bullet/gokuBlast_start.bmp"	,  62,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1단계 에너지파 중간", "image/bullet/gokuBlast_mid.bmp"	,  64,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1단계 에너지파 끝점", "image/bullet/gokuBlast_end.bmp"	,  62,  64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2단계 에너지파 시작", "image/bullet/SgokuBlast_start.bmp"	, 126, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2단계 에너지파 중간", "image/bullet/SgokuBlast_mid.bmp"	,  64, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2단계 에너지파 끝점", "image/bullet/SgokuBlast_end.bmp"	, 126, 128, true, RGB(255, 0, 255));

	// 적
	IMAGEMANAGER->addImage("에너미 1", "image/enemy/enemyType_1.bmp", 141, 145, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("에너미 2", "image/enemy/enemyType_2.bmp", 174, 172, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("에너미 3", "image/enemy/enemyType_3.bmp", 159, 205, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("에너미 1 죽음", "image/enemy/enemyDead_1.bmp", 480, 132, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미 2 죽음", "image/enemy/enemyDead_2.bmp", 546, 132, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미 3 죽음", "image/enemy/enemyDead_3.bmp", 555, 147, 3, 1, true, RGB(255, 0, 255));

	// 보스
	IMAGEMANAGER->addFrameImage("보스 기본"		, "image/boss/idle.bmp"			, 1210, 201, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 앞에"		, "image/boss/moveFront.bmp"	,  296, 205,  2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 뒤에"		, "image/boss/moveBack.bmp"		,  306, 207,  2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 죽음"		, "image/boss/dead.bmp"			, 1463, 207,  7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 승리"		, "image/boss/win.bmp"			,  675,  20,  5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 패턴 1"	, "image/boss/bossSpread.bmp"	, 1344, 214,  8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 패턴 2"	, "image/boss/bossMissile.bmp"	, 1750, 205, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스 패턴 3"	, "image/boss/bossRain.bmp"		,  972, 201,  6, 1, true, RGB(255, 0, 255));
	
	// UI	
	IMAGEMANAGER->addImage("1단계 오공 UI"	, "image/ui/goku.bmp"	 , 250, 305, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2단계 오공 UI"	, "image/ui/Sgoku.bmp"	 , 241, 324, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3단계 오공 UI"	, "image/ui/SSgoku.bmp"	 , 284, 317, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스 UI"			, "image/ui/broly.bmp"	 , 299, 338, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("막대 뒤"			, "image/ui/backBar.bmp" , 260,  38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("막대 앞"			, "image/ui/frontBar.bmp", 260,  38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("재시작 횟수"		, "image/ui/life.bmp"	 ,  72,  72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신룡 배경"		, "image/ui/shenron.bmp" , 377, 340, true, RGB(255, 0, 255));

	// 이펙트
	EFFECTMANAGER->addEffect("기본 불릿효과", "image/effect/bulletEffect1.bmp", 384, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("지면 불릿효과", "image/effect/bulletEffect2.bmp", 448, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("특수 불릿효과", "image/effect/bulletEffect3.bmp", 512, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("보스 불릿효과", "image/effect/bulletEffect4.bmp", 512, 64, 64, 64, 1.0f, 0.3f, 300);
	EFFECTMANAGER->addEffect("달빛 불릿효과", "image/effect/bulletEffect5.bmp", 448, 64, 64, 64, 1.0f, 0.3f, 300);

	// 오공 전용 이펙트
	IMAGEMANAGER->addFrameImage("오공 아우라", "image/effect/aura.bmp", 320, 160, 2, 1, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addImage("오공 용", "image/effect/dragon.bmp", 3127, 800, true, RGB(255, 0, 255));

	// 피탄면
	IMAGEMANAGER->addFrameImage("오공 피탄면", "image/effect/target.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));

	// 아이템
	IMAGEMANAGER->addFrameImage("아우라", "image/item/item1.bmp", 128, 32,  4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("생명력", "image/item/item2.bmp", 640, 64, 10, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("1성구", "image/item/1star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2성구", "image/item/2star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3성구", "image/item/3star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4성구", "image/item/4star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5성구", "image/item/5star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6성구", "image/item/6star.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7성구", "image/item/7star.bmp", 32, 32, true, RGB(255, 0, 255));

	// 인트로
	IMAGEMANAGER->addImage("게임 인트로"		, "image/intro/intro.bmp"	, WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스타트 오프"		, "image/intro/startOff.bmp",	   357,	      58, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스타트 오온"		, "image/intro/startOn.bmp" ,	   357,	      58, false, RGB(255, 0, 255));	

	// 엔딩
	IMAGEMANAGER->addImage("엔딩 01", "image/ending/엔딩01.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 02", "image/ending/엔딩02.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 03", "image/ending/엔딩03.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 04", "image/ending/엔딩04.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 05", "image/ending/엔딩05.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 06", "image/ending/엔딩06.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 07", "image/ending/엔딩07.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 08", "image/ending/엔딩08.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 09", "image/ending/엔딩09.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 10", "image/ending/엔딩10.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 11", "image/ending/엔딩11.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 12", "image/ending/엔딩12.bmp", 800, 400, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩 13", "image/ending/엔딩13.bmp", 600, 400, false, RGB(255, 0, 255));

	// 브금 사운드
	SOUNDMANAGER->addSound("오프닝", "music/드래곤볼Z오프닝.mp3"	, true, true);
	SOUNDMANAGER->addSound("플레이", "music/게임플레이브금.ogg"	, true, true);
	SOUNDMANAGER->addSound("피니쉬", "music/드래곤볼Z엔딩.mp3"	, true, false);		

	// 이펙트
	SOUNDMANAGER->addSound("지면 충돌", "music/지면 충돌.wav", false, false);	

	_intro	= new gameIntro;
	_play	= new gamePlay;
	_end	= new gameEnd;

	SCENEMANAGER->addScene("인트로", _intro);
	SCENEMANAGER->addScene("플레이", _play);
	SCENEMANAGER->addScene("엔딩", _end);

	SCENEMANAGER->changeScene("인트로");		

	return S_OK;
}

//메모리 해제
void playGround::release()
{
}

//연산
void playGround::update()
{
	gameNode::update();	

	if (_intro->getChange())
	{
		_intro->setChange(false);
		SCENEMANAGER->changeScene("플레이");
	}
	if (_play->getGameEnd())
	{
		_play->setGameEnd(false);
		SCENEMANAGER->changeScene("엔딩");
	}
	if (_play->getGameOver())
	{
		_play->setGameOver(false);
		SCENEMANAGER->changeScene("인트로");
	}
	if (_end->getGameEnd())
	{
		_end->setGameEnd(false);
		SCENEMANAGER->changeScene("인트로");
	}

	EFFECTMANAGER->update();
	SCENEMANAGER->update();		
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=================================================		
	
	SCENEMANAGER->render();	
	EFFECTMANAGER->render();		

	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}