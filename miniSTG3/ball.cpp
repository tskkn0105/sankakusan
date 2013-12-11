#include "game_main.h"



//ボールの座標
int ball_pos_x[maxball];
int ball_pos_y[maxball];

double speedn = 2.5;				//ボールの速さ

speed vecter[maxball];	//ボールの向き

int ball_kazu = 2;
int ball_kazu_b = 0;	//青ボールの数


bool startflag[maxball];	//最初かどうか


double kaiten[maxball];		//回転角
int ball_ani[maxball]={0};
int ball_ani_count = 0;


bool touch_flag[maxball];	//触ったかどうか

bool change_ballflag[maxball];
bool shot_missflag[maxball];

//レベル
int levelcount = 0;
int level = 1;
double levelspeed = 0.5;
int levelcount_up = 900;

void ball()
{
	ball_kazu_b = 0;
	if(option_level>level)
	{
		if((option_level-level)/10)
		{
			levelcount += 60;
		}
		levelcount += 60;
		if(levelcount%60 != 0)
		{
			levelcount -= levelcount%60;
		}
	}
	else
	{
		levelcount++;
	}
	if(levelcount >= levelcount_up)
	{
		levelcount = 0;
		level +=1;
		if(level%2 == 1)
		{
			levelspeed +=0.5;
		}
		else
		{
			ball_kazu +=1;
		}
		if(ball_kazu > maxball)
		{
			ball_kazu = maxball;
		}
		if(level < 16){	levelcount_up += 180; }
		PlaySoundMem(se_level,DX_PLAYTYPE_BACK);
	}
	//各ボールの挙動
	ball_ani_count++;
//	if(ball_ani_count == 48)
//	{
//		ball_ani_count = 0;
//	}
	for(int i =0;i < ball_kazu;i++)
	{

		if(startflag[i] == false)
		{
			if( i%2 == 1)
			{
				ball_pos_x[i] = 16;
				ball_pos_y[i] = 16;
				vecter[i].x = 1;
				vecter[i].y = 1;
				kaiten[i] = i;
				change_ballflag[i] = false;
				shot_missflag[i] = false;
			}
			if(i%2 == 0)
			{
				ball_pos_x[i] = 616;
				ball_pos_y[i] = 16;
				vecter[i].x = -1;
				vecter[i].y = 1;
				kaiten[i] = i;
				change_ballflag[i] = true;
				shot_missflag[i] = false;
			}
				startflag[i] = true;

		}

		kaiten[i] += 0.05;
		ball_pos_x[i] += (int)(speedn+levelspeed) * (int)vecter[i].x;
		ball_pos_y[i] += (int)(speedn+levelspeed) * (int)vecter[i].y;


		if(ball_pos_x[i] >= 616)
		{
			ball_pos_x[i] = 616;
			vecter[i].x = -1;
		}
		if(ball_pos_x[i] <= 24)
		{
			ball_pos_x[i] = 24;
			vecter[i].x = 1;
		}
		if(ball_pos_y[i] >= 424)
		{
			ball_pos_y[i] = 424;
			vecter[i].y = -1;
		}
		if(ball_pos_y[i] <= 24)
		{
			ball_pos_y[i] = 24;
			vecter[i].y = 1;
		}
		
		

		//描画
		if(change_ballflag[i] == false && c78_flag == false/* && shot_missflag[i] == false*/)
		{
			ball_ani[i] = ((ball_ani_count+i)%12)/2;
			DrawRotaGraph(ball_pos_x[i],ball_pos_y[i],1,kaiten[i],g_ball1[ball_ani[i]],true,false);
			ball_kazu_b++;
		}
		else if(change_ballflag[i] == true && c78_flag == false/*&& shot_missflag[i] == false*/)
		{
			ball_ani[i] = ((ball_ani_count+i)%16)/2;
			DrawRotaGraph(ball_pos_x[i],ball_pos_y[i],1,kaiten[i],g_ball2[ball_ani[i]],true,false);
		}
		else if(change_ballflag[i] == false && shot_missflag[i] == false && c78_flag == true)
		{
			DrawRotaGraph(ball_pos_x[i],ball_pos_y[i],1,kaiten[i],g_ball1_c78,true,false);
		}
		else if(change_ballflag[i] == true && shot_missflag[i] == false && c78_flag == true)
		{
			DrawRotaGraph(ball_pos_x[i],ball_pos_y[i],1,kaiten[i],g_ball2_c78,true,false);
		}
		else if(shot_missflag[i] == true && c78_flag == true)
		{
			DrawRotaGraph(ball_pos_x[i],ball_pos_y[i],1,kaiten[i],g_ball3,true,false);
		}
	}
}

void ball_hantei()
{
	for(int i = 0;i<ball_kazu;i++)
	{
		for(int j=1+i;j<ball_kazu;j++)
		{
			if(i != j)
			{
				if(ball_pos_x[i]-16 < ball_pos_x[j]+16 &&
					ball_pos_y[i]-16 < ball_pos_y[j]+16 &&
					ball_pos_x[j]-16 < ball_pos_x[i]+16 &&
					ball_pos_y[j]-16 < ball_pos_y[i]+16)
				{
					if((change_ballflag[i] == false && change_ballflag[j] == false && shot_missflag[i] == false && shot_missflag[j] == false) ||
						(change_ballflag[i] == true && change_ballflag[j] == true && shot_missflag[i] == false && shot_missflag[j] == false) ||
						(shot_missflag[i] == true && shot_missflag[j] == true))
					{
						if(abs(ball_pos_x[j]-ball_pos_x[i]) >= abs(ball_pos_y[j]-ball_pos_y[i]))
						{
							if(ball_pos_x[i] > ball_pos_x[j])
							{
								vecter[i].x = 1;
								vecter[j].x = -1;
							}
							else
							{
								vecter[i].x = -1;
								vecter[j].x = 1;
							}
						}
						if(abs(ball_pos_x[j]-ball_pos_x[i]) <= abs(ball_pos_y[j]-ball_pos_y[i]))
						{
							if(ball_pos_y[i] > ball_pos_y[j])
							{
								vecter[i].y = 1;
								vecter[j].y = -1;
							}
							else
							{
								vecter[i].y = -1;
								vecter[j].y = 1;
							}

						}
					}
				}
			}
		}
//		DrawBox(ball_pos_x[i]-16,ball_pos_y[i]-16,ball_pos_x[i]+16,ball_pos_y[i]+16,65535,false);
	}
}