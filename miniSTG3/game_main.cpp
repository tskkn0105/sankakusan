#include "game_main.h"
#include "mymain.h"


//double start_time;
//double end_time;
//double frame_time;

extern bool exitflag;

// プログラムの開始関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	if (strcmp(lpCmdLine, "-f") != 0) ChangeWindowMode(TRUE);
	//タイトル
	SetWindowText("△△-SANKAKUSANKAKKEEEE-");
	//DXライブラリの初期化処理
	if( DxLib_Init() == -1 ) return -1;
	init();
	//描画対象を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	//メインループ
//	g_lasttime = GetNowCount() & INT_MAX;
	while(ProcessMessage()==0 && exitflag == false)
	{
		
//		start_time = GetNowCount();
		ClsDrawScreen();	//画面を消去
		mymain();//mymain.cppメインループの処理
//		DrawBox(0,0,150,150,GetColor(255,255,255),true);
//		LoadGraphScreen(0,0,"media\\ボール緑１.png",true);
//		DrawFormatString(0,450,GetColor(255,0,0),"%f FPS",frame_time);
		ScreenFlip();		//画面を切り替え
//		end_time = GetNowCount();
//		frame_time = end_time - start_time;
		//1ループにかかった時間を計測
//		double curtime = GetNowCount() & INT_MAX;
//		g_frametime = (double)(curtime - g_lasttime) / 1000.0f;
//		g_lasttime = curtime;
//		if (g_frametime > 0.03f) g_frametime = 0.03f;
	}
	DxLib_End() ;			// ＤＸライブラリ使用の終了処理
	return 0 ;				// ソフトの終了 
}



