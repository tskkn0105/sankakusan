#include "game_main.h"
#include "mymain.h"

int g_pause;
bool pause_flag;
bool option_flag = false;
const int option_max = 5;
int string_c[option_max];
const int white = GetColor(255,255,255);
const int gray = GetColor(100,100,100);
int c_title = 0;
int c_level = 0;
int point;
int option_level = 0;
bool down_flag;
bool up_flag;
int left_count;
bool left_flag;
bool right_flag;
int right_count;
char* c78_mode;
char c78_mode1[] = "ON";
char c78_mode2[] = "OFF";
//bool 2player_flag; //2p使用フラグ


void get_option()
{
	int key = GetJoypadInputState(DX_INPUT_PAD1);

	if(CheckHitKey(KEY_INPUT_1) || key & PAD_INPUT_START)
	{
		if(pause_flag == false)
		{
			if(option_flag == false)
			{
				g_pause = MakeGraph(640,480);
				GetDrawScreenGraph(0,0,640,480,g_pause);
				point = 0;
				option_level = level;
			}
			option_flag = !option_flag;
			pause_flag = true;
		}
	}
	else
	{
		pause_flag = false;
	}

	

}

void option()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if(option_flag == true)
	{
		SetDrawBright(120,120,120);
		DrawGraph(0,0,g_pause,false);
		SetDrawBright(255,255,255);
//オプション画面の操作
		if(key & PAD_INPUT_DOWN)
		{
			if(down_flag == false)
			{
				point += 1;
				down_flag = true;
			}
		}
		else
		{
			down_flag = false;
		}

		if(key & PAD_INPUT_UP)
		{
			if(up_flag == false)
			{
				point -= 1;
				up_flag = true;
			}
		}
		else
		{
			up_flag = false;
		}
		if(point<0)
		{
			point = 0;
		}
		else if(point>option_max-1)
		{
			point = option_max-1;
		}

		for(int i=0;i<option_max;i++)
		{
			if(i==point)
			{
				string_c[i] = white;
			}
			else
			{
				string_c[i] = gray;
			}
		}


		if((key & PAD_INPUT_A) == 0)
		{
			z_flag = false;
		}

//レベルをいじくるところ
		if(key & PAD_INPUT_LEFT)
		{
			left_count++;
			if(point == 1 && option_level > level && (left_flag == false || left_count == 40))
			{
				option_level -= 1;
				left_flag = true;
				if(left_count == 40)
				{
					left_count = 32;
				}
			}

		}
		else
		{
			left_flag = false;
			left_count = 0;
		}
		if(key & PAD_INPUT_RIGHT)
		{
			right_count++;
			if(point == 1 && option_level < 40 &&(right_flag == false || right_count ==40))
			{
				option_level += 1;
				right_flag = true;
				if(right_count == 40)
				{
					right_count = 32;
				}
			}
		}
		else
		{
			right_flag = false;
			right_count = 0;
		}
//ゲームに戻る
		if(key & PAD_INPUT_A && (point == 0 || point == 1))
		{
			option_flag = !option_flag;
			pause_flag = true;
			z_flag = true;
			if(point == 1 && game_startflag == false)
			{
				gamestart();
			}
		}

//c78モードフラグ
		if(key & PAD_INPUT_A && point == 2 && game_startflag == false)
		{
			if(z_flag == false)
			{
				c78_flag = !c78_flag;
				z_flag = true;
				PlaySoundMem(se_change,DX_PLAYTYPE_BACK);
			}
		}
		
		if(c78_flag == true)
		{
			c78_mode = &c78_mode1[0];
		}
		else
		{
			c78_mode = &c78_mode2[0];
		}


//タイトルに戻る
		if(key & PAD_INPUT_A && point == 3)
		{
			option_flag = !option_flag;
			pause_flag = true;
			StopSoundMem(bgm[melo_s]);
			StopSoundMem(se_chance);
			game_endflag = true;
		}

//ゲームをやめる
		if(key & PAD_INPUT_A && point == 4)
		{
			exitflag = true;
		}

		
		



		DrawString(50,50,"ゲームに戻る",string_c[0]);
		DrawFormatString(50,80,string_c[1],"レベル  < %d >",option_level);
		DrawFormatString(50,110,string_c[2],"c78モード　%s",c78_mode);
		DrawString(50,140,"タイトルに戻る",string_c[3]);
		DrawString(50,170,"ゲームをやめる",string_c[4]);

	}

}