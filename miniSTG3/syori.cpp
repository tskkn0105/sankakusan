#include "game_main.h"

FILE *pt;
int highscore = 0;

void syokika()
{

	score = 0;
	combo = 0;

	//���@
	jiki_x = 304;
//	hantei_count = 0;

	first_shotflag = false;

	speedn = 2.5;
	ball_kazu = 2;

	//���x��
	levelcount = 0;
	level = 1;
	option_level = 1;
	levelspeed = 0.5;
	levelcount_up = 900;

	for(int i=0;i<maxball;i++)
	{
		startflag[i] = false;	//�{�[���ŏ����ǂ���
		if(i<maxshot)
		{
			shot_used2[i] = false;//���@�̂Ƃ���ɉ摜�������Ă���
			shot_used3[i] = false;
		}
	}
	shotflag = true;

	sky_used = false;
	sky.x = 640;
	sky_sound = false;
	sky_combo = 10;
	StopSoundMem(se_chance);


	//�͂��߂̃t���O
	game_startflag = false;
	//BGM�t���O
	start_melo = false;
	//�Q�[���I���^�t���O
	game_endflag = false;
	//�I���̋ȃt���O
	end_m_flag = false;

	//�Ȃ̑����Ƃ�
	level_melo = 5;
	melo_s = 0;

	//��
	level_wall = 3;
	change_wall += 1;
	if(change_wall >= 14)
	{
		change_wall = 0;
	}


}

void highscore_syori()
{
	if(fopen_s(&pt,"high.dat","r") != 0)
	{
		fopen_s(&pt,"high.dat","w");
		highscore = 1000;
		ango = highscore^0x9fb26ac;
		fprintf(pt,"%d",ango);

	}
	else
	{
		fscanf_s(pt,"%d",&ango);
		highscore = ango^0x9fb26ac;
	}
	fclose(pt);
}

