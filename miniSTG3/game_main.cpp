#include "game_main.h"
#include "mymain.h"


//double start_time;
//double end_time;
//double frame_time;

extern bool exitflag;

// �v���O�����̊J�n�֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	if (strcmp(lpCmdLine, "-f") != 0) ChangeWindowMode(TRUE);
	//�^�C�g��
	SetWindowText("����-SANKAKUSANKAKKEEEE-");
	//DX���C�u�����̏���������
	if( DxLib_Init() == -1 ) return -1;
	init();
	//�`��Ώۂ𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//���C�����[�v
//	g_lasttime = GetNowCount() & INT_MAX;
	while(ProcessMessage()==0 && exitflag == false)
	{
		
//		start_time = GetNowCount();
		ClsDrawScreen();	//��ʂ�����
		mymain();//mymain.cpp���C�����[�v�̏���
//		DrawBox(0,0,150,150,GetColor(255,255,255),true);
//		LoadGraphScreen(0,0,"media\\�{�[���΂P.png",true);
//		DrawFormatString(0,450,GetColor(255,0,0),"%f FPS",frame_time);
		ScreenFlip();		//��ʂ�؂�ւ�
//		end_time = GetNowCount();
//		frame_time = end_time - start_time;
		//1���[�v�ɂ����������Ԃ��v��
//		double curtime = GetNowCount() & INT_MAX;
//		g_frametime = (double)(curtime - g_lasttime) / 1000.0f;
//		g_lasttime = curtime;
//		if (g_frametime > 0.03f) g_frametime = 0.03f;
	}
	DxLib_End() ;			// �c�w���C�u�����g�p�̏I������
	return 0 ;				// �\�t�g�̏I�� 
}



