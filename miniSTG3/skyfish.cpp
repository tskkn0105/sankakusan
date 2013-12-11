#include"game_main.h"

speed sky = {640,16};
int sky_ani = 0;
int sky_count = 0;
bool sky_used;
bool sky_sound;
bool sky_hanten;


void skyfish()
{
	if(sky_used == true)
	{
		if(sky_hanten == false)
		{
			sky.x -= 3+(level/10);
		}
		else
		{
			sky.x += 3+(level/10);
		}
		sky_count++;	//アニメーション
		if(sky_count == 30)
		{
			sky_ani++;
			if(sky_ani == 2)
			{
				sky_ani = 0;
			}
			sky_count = 0;
			if(sky_sound == false)
			{
				PlaySoundMem(se_chance,DX_PLAYTYPE_BACK);
				sky_sound = true;
			}
		}
		if(sky.x < -70 || sky.x > 640)
		{
			sky_used = false;
			sky_sound = false;
			StopSoundMem(se_chance);
		}

		if(sky_hanten == false)
		{
			DrawGraph((int)sky.x,(int)sky.y,g_skyfish[sky_ani],true);
		}
		else
		{
			DrawTurnGraph((int)sky.x,(int)sky.y,g_skyfish[sky_ani],true);
		}
	}


}

void sky_jouken()
{
	if(combo == sky_combo && ball_kazu == ball_kazu_b*2)
	{
		if(shot_kaisuu%2 == 0)
		{
			sky.x = 640;
			sky_hanten = false;
		}
		else
		{
			sky.x = -70;
			sky_hanten = true;
		}
		sky_used = true;
		levelcount += 100;
		sky_combo += 10;
	}
}

