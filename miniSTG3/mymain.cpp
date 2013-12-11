#include"game_main.h"
#include"mymain.h"



//はじめのはじめ
bool logoflag;

double light = 0;
int timelogo = 0;

int file_count = 47;


//スコア
int score = 0;
int timescore = 0;
int timescore2 = 0;
int combo = 0;
int sky_combo = 10;
int count = 0;
bool syokaiflag;
int ango;



//自機
const int jikispeed = 5;
int jiki_x = 304;
int jiki_y =403;
bool change_jikiflag;
bool x_flag;
int back = 0;
int wait = 0;
bool wait_move;
int player_ani_count = 0;
int player_ani = 0;
int jiki_kaiten = 0;


//弾
int k = 0;
int shot_kaisuu;
bool shot_used[maxshot]; //タマが画面上にあるか
bool shot_used2[maxshot];//自機のところに画像を持っていく
bool shot_used3[maxshot];
bool z_flag;
bool first_shotflag = false;
bool change_shotflag[maxshot];
bool shotflag = true;

speed shot_s[maxshot];	//ショットの動き

//画像
int g_player[12];	//自機
int g_player2[12];	//自機２
int g_player_c78;
int g_player2_c78;
int g_wall;		//壁
int g_wall_soto;
int g_ball1[6];	//ボール
int g_ball2[8];
int g_ball1_c78;
int g_ball2_c78;
int g_ball3;
int g_skyfish[2];	//スカイフィッシュ
int g_shot;		//ショット
int g_shot2;
int g_back;		//背景
int g_tytle;	//タイトル
int g_tytle2;	//タイトル２
int g_coment;	//つぶやき機能付き！
int g_start;	//すたーと
int g_exit;		//イグジット
int g_out;		//爆発
int g_w[19];	//壁紙

//se
int se_shot;
int se_hit;
int se_hit2;
int se_down;
int se_level;
int se_change;
int se_hansya;
int se_combo_miss;
int se_chance;
int se_sky_shot;
int se_change_wall;

//音楽
int bgm[6];
int start_m;
int end_m;
int melo_s = 0;
int level_melo = 5;

//文字
int font_lv;
int font_score;
int font_result;


//書き込みフラグ
bool set_graph;
//はじめのフラグ
bool game_startflag;
//終了フラグ
bool exitflag;
//ファンファーレフラグ
bool start_melo;
//ゲームオワタフラグ
bool game_endflag;
//終わりの曲フラグ
bool end_m_flag;
//初期化フラグ
bool syokikaflag;
//bgm読み込みフラグ
bool loadbgm_flag;

bool change_ballflag2[maxball];

//壁紙
int change_wall = 0;
int level_wall = 3;

//c78版かどうかのフラグ
bool c78_flag = false;




//自機の移動
void move_myship()
{

	//パッド入力
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if(jiki_y != 403)
	{
		back++;
		if(back == 4)
		{
			jiki_y = 403;
			back = 0;
		}
	}
	if(wait_move == true)
	{
		wait++;
		if(wait == 3)	//待ちフレーム数
		{
			wait_move = false;
			wait = 0;
		}
	}
	else
	{

//		if(CheckHitKey(KEY_INPUT_LEFT))
		if(key&PAD_INPUT_LEFT)
		{
			jiki_x -= jikispeed;
			ani_syori(player_ani_count,2,player_ani,1,12);
			jiki_kaiten = -1;
/*			player_ani_count++;
			if(player_ani_count==3)
			{
				player_ani++;
				player_ani_count=0;
				if(player_ani==12)
				{
					player_ani = 0;
				}
			}
*/		}
		else
		{
			if(player_ani != 0 && jiki_kaiten==-1)
			{
				ani_syori(player_ani_count,1,player_ani,1,12);
			}
			else if(player_ani == 0)
			{
				jiki_kaiten = 0;
			}
		}

		if(key&PAD_INPUT_RIGHT)
		{
			jiki_x += jikispeed;
			ani_syori(player_ani_count,2,player_ani,-1,12);
			jiki_kaiten = 1;
/*			player_ani_count++;
			if(player_ani_count==1)
			{
				player_ani--;
				player_ani_count=0;
				if(player_ani==-1)
				{
					player_ani = 11;
				}
			}
*/		}
		else
		{
			if(player_ani != 0 && jiki_kaiten == 1)
			{
				ani_syori(player_ani_count,1,player_ani,-1,12);
			}
			else  if(player_ani == 0)
			{
				jiki_kaiten = 0;
			}
		}

				


		if(jiki_x < 44)
		{
			jiki_x = 44;
		}
		if(jiki_x > 563)
		{
			jiki_x = 563;
		}
	}

	

	if(change_jikiflag == false && c78_flag == false)
	{
		
		DrawGraph(jiki_x,jiki_y,g_player[player_ani],TRUE);
	}
	else if(change_jikiflag == true && c78_flag == false)
	{
		DrawGraph(jiki_x,jiki_y,g_player2[player_ani],TRUE);
	}
	else if(change_jikiflag == false && c78_flag == true)
	{
		
		DrawGraph(jiki_x,jiki_y,g_player_c78,TRUE);
	}
	else
	{
		DrawGraph(jiki_x,jiki_y,g_player2_c78,TRUE);
	}

}
//ボタンの判定
void botten()
{
	//パッド入力
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	
//		if(CheckHitKey(KEY_INPUT_Z))
	if(key & PAD_INPUT_A)
		{
			if(z_flag == false && k < maxshot && shot_used3[k] == false && shotflag == true)
			{
				shot_used[k] = true;	//動く
				shot_used3[k] = true;	//描画
				z_flag = true;

				k++;
			}
		}
		else
		{
			z_flag = false;

			if(k >= maxshot)
			{
				k =0;
			}
		}
//		if(CheckHitKey(KEY_INPUT_X))
	if(key & PAD_INPUT_B)
		{
			if(x_flag == false)
			{
				change_jikiflag = !change_jikiflag;

				PlaySoundMem(se_change,DX_PLAYTYPE_BACK);

				x_flag = true;
			}
		}
		else
		{
			x_flag = false;
		}
}

//ショット描画
bool drawshot()
{
	for(int i = 0;i<maxshot;i++)
	{
		if(shot_used[i] == true)
		{
			shot_s[i].x = jiki_x;
			shot_s[i].y = jiki_y;
			PlaySoundMem(se_shot,DX_PLAYTYPE_BACK);
			shot_kaisuu++;
	
			shot_used[i] = false;
			shot_used2[i] = true;
			if(change_jikiflag == false)
			{
				change_shotflag[i] = false;
			}
			else
			{
				change_shotflag[i] = true;
			}
		}
		if(shot_used2[i] == true)
		{
			shot_s[i].y -= 7;
		}
		if(shot_used3[i] == true)
		{
			if(change_shotflag[i] == false)
			{
				DrawGraph((int)shot_s[i].x,(int)shot_s[i].y,g_shot,TRUE);
			}
			else
			{
				DrawGraph((int)shot_s[i].x,(int)shot_s[i].y,g_shot2,TRUE);
			}



		}
		if(shot_s[i].y <= -26)
		{
			shot_used2[i] = false;
			shot_used3[i] = false;
			shot_s[i].y = 0;
			if(combo >= 4)
			{
				PlaySoundMem(se_combo_miss,DX_PLAYTYPE_BACK);
			}
			combo = 0;
			
		}
	}
	return true;
}

//ショットの判定
void shot_hantei()
{
	for(int i = 0;i<ball_kazu;i++)
	{
		for(int j = 0;j<maxshot;j++)
		{
			if(shot_used3[j] == true)
			{
				if(ball_pos_x[i]-16 < shot_s[j].x+28 &&
					ball_pos_y[i]-16 < shot_s[j].y+20 &&
					shot_s[j].x+5 < ball_pos_x[i]+16 &&
					shot_s[j].y+2 < ball_pos_y[i]+16)
				{
					first_shotflag = true;
					vecter[i].y = -1;
					shot_used2[j] = false;
					shot_used3[j] = false;
					if((change_ballflag[i] == false && change_shotflag[j] == true ||change_ballflag[i] == true && change_shotflag[j] == false) && shot_missflag[i] == false)
					{
						PlaySoundMem(se_hit2,DX_PLAYTYPE_BACK);
						combo += 1;
						if(combo >= 4)
						{
							score += 200+(level*80)+(combo*100);
						}
						else
						{
							score += 200+(level*80);
							//score += 1999999999;
						}
					}
					else
					{
						PlaySoundMem(se_hit,DX_PLAYTYPE_BACK);
						score += 100+(level*40);
						combo = 0;
						sky_combo = 10;
						if(level >= 10 && c78_flag == true)
						{
							shot_missflag[i] = !shot_missflag[i];
						}
					}

					change_ballflag[i] = !change_ballflag[i];
	
				}

			}
		}
	}
}
//スカイフィッシュの判定
void shot_sky()
{
	for(int i = 0;i<maxshot;i++)
	{
		if(sky.x+1 < shot_s[i].x+28 &&
			sky.y+10 < shot_s[i].y+20 &&
			shot_s[i].x+5 < sky.x+63 &&
			shot_s[i].y+2 < sky.y+22 &&
			sky_used == true &&
			shot_used3[i] == true)
		{
			first_shotflag = true;
			shot_used2[i] = false;
			shot_used3[i] = false;
			sky_used = false;
			sky.x = 640;
			sky_sound = false;
			score += 1500*(level+combo);
			StopSoundMem(se_chance);
			PlaySoundMem(se_sky_shot,DX_PLAYTYPE_BACK);
			for(int j=0;j<ball_kazu;j++)
			{
				shot_missflag[j] = false;
			}
		}
	}
}

//自機の当たり判定
void jiki_hantei()
{
#ifdef _DEBUG
	
	DrawBox(jiki_x+8,jiki_y+20,jiki_x+25,jiki_y+33,GetColor(255,255,255),true);
#endif

	for(int i = 0;i<ball_kazu;i++)
	{
		if(ball_pos_x[i]-16 <jiki_x+25 &&
			ball_pos_y[i]-16 < jiki_y+33 &&
			jiki_x+8 < ball_pos_x[i]+16 &&
			jiki_y+20 < ball_pos_y[i]+16)
		{
			shotflag = false;
		}
		else
		{
			count++;
			if(count == ball_kazu)
			{
				shotflag = true;
			}
		}
		if(ball_pos_x[i]-15 <jiki_x+27 &&
			ball_pos_y[i]-15 < jiki_y+33 &&
			jiki_x+6 < ball_pos_x[i]+15 &&
			jiki_y+6 < ball_pos_y[i]+15 ||
			(CheckHitKey(KEY_INPUT_ESCAPE)))
		{

			if(((change_jikiflag == false && change_ballflag[i] == false) || 
				(change_jikiflag == true && change_ballflag[i] == true) || (shot_missflag[i] == true && c78_flag == true)) &&
				change_ballflag2[i] == false && touch_flag[i] == false &&
				ball_pos_x[i]-10 <jiki_x+25 &&
				ball_pos_y[i]-10 < jiki_y+33 &&
				jiki_x+8 < ball_pos_x[i]+10 &&
				jiki_y+20 < ball_pos_y[i]+10 ||
				(CheckHitKey(KEY_INPUT_ESCAPE) &&
				game_endflag == false))
			{
				//げーむおーばーになる
				DrawGraph(jiki_x,jiki_y,g_out,true);
				PlaySoundMem(se_down,DX_PLAYTYPE_NORMAL);
				StopSoundMem(bgm[melo_s]);
				StopSoundMem(se_chance);
				game_endflag = true;
			}
			if(((change_jikiflag == false && change_ballflag[i] == true) ||
				(change_jikiflag == true && change_ballflag[i] == false))&& 
				change_ballflag2[i] == false && touch_flag[i] == false /* && shot_missflag[i] == false */ &&
				(CheckHitKey(KEY_INPUT_ESCAPE) == 0))
			{
				//反射する

//				if(abs(ball_pos_x[i]-jiki_x) >= abs(ball_pos_y[i]-jiki_y))
//				{
					if(jiki_x+16 > ball_pos_x[i])
					{
						vecter[i].x = -1;
						jiki_x += 3;
					}
					else
					{
						vecter[i].x = 1;
						jiki_x -= 3;
					}
//				}
//				if(abs(ball_pos_x[i]-jiki_x) <= abs(ball_pos_y[i]-jiki_y))
//				{
						vecter[i].y = -1;
						jiki_y +=4;
//				}
				wait_move = true;
				touch_flag[i] = true;
				change_ballflag2[i] = true;
				if(change_jikiflag == false)
				{
					score += (ball_kazu - ball_kazu_b+level)*100;
				}
				else
				{
					score += (ball_kazu_b+level)*100;
					
				}
				levelcount += 30;
				if(c78_flag == false){ combo++; }
			}
			timescore = 0;
			timescore2 = 0;

		}
		else
		{
			if(change_ballflag2[i] == true)
			{
				change_ballflag[i] = !change_ballflag[i];
				PlaySoundMem(se_hansya,DX_PLAYTYPE_BACK);
				change_ballflag2[i] = false;
			}
			count++;
			if(count == ball_kazu)
			{
				timescore++;
				if(timescore >= 1200-level*60)
				{
					timescore2++;
					if(timescore2 == 12)
					{
						score += level;
						timescore2 = 0;
					}
				}
				shotflag = true;
			}

			touch_flag[i] = false;
		}
	}
	count = 0;
}
void gamestart()
{
	shot_used2[0] = false;
	shot_used3[0] = false;
	shot_used2[1] = false;
	shot_used3[1] = false;
	game_startflag = true;
	if(loadbgm_flag == false)
	{
		PlaySoundMem(start_m,DX_PLAYTYPE_BACK);
		bgm[0] = LoadSoundMem("media\\bgm2.ogg");
		bgm[1] = LoadSoundMem("media\\bgm3.ogg");
		bgm[3] = LoadSoundMem("media\\bgm4.ogg");
		bgm[5] = LoadSoundMem("media\\bgm5.ogg");
		bgm[2] = LoadSoundMem("media\\bgm6.ogg");
		bgm[4] = LoadSoundMem("media\\bgm7.ogg");
		WaitTimer(2000);
		loadbgm_flag = true;
	}
	else
	{
		PlaySoundMem(start_m,DX_PLAYTYPE_NORMAL);
	}
	jiki_x = 304;
}

//ゲーム開始画面
void start_menu()
{
	if(change_jikiflag == false)
	{
		DrawGraph(120,80,g_tytle,true);
	}
	else
	{
		DrawGraph(120,80,g_tytle2,true);
	}
	DrawGraph(130,240,g_coment,true);//つぶやき機能付き
	DrawGraph(80,270,g_start,true);
	DrawGraph(464,270,g_exit,true);

	for(int i = 0;i<maxshot;i++)
	{
		if(shot_used3[i] == true)
		{
			if(80 < shot_s[i].x+33 && 270 < shot_s[i].y+33 && shot_s[i].x < 176 && shot_s[i].y < 334)
			{
				
				gamestart();
			}
			if(464 < shot_s[i].x+33 && 270 < shot_s[i].y+33 && shot_s[i].x < 560 && shot_s[i].y < 334)
			{
				
				shot_used2[i] = false;
				shot_used3[i] = false;
				PlaySoundMem(se_combo_miss,DX_PLAYTYPE_NORMAL);
				exitflag = true;
				

			}
		}
	}

}
//リザルト画面
void gameover()
{
	DrawFormatStringToHandle(80,100,GetColor(255,100,255),font_result,"Your score:  %d  ",score);
	DrawFormatStringToHandle(100,350,GetColor(255,100,255),font_result,"Please Enter Key…");
	
	if(TweetFlag())
	{ DrawFormatStringToHandle(100,450,GetColor(255,100,255),font_result,"Xキーでつぶやく"); }
//	if(first_shotflag == false)
//	{
//		DrawFormatStringToHandle(100,200,GetColor(255,100,255),font_result,"Non Shooter!");
//	}
	
	char c_score[50];

	wsprintf(c_score,"スコアは %d 点です。　",score);

	if(end_m_flag == false)
	{
		PlaySoundMem(end_m,DX_PLAYTYPE_BACK);
		end_m_flag = true;
	}
	if(CheckHitKey(KEY_INPUT_RETURN))
	{
		syokikaflag = true;
	}
	if(TweetFlag()==true && CheckHitKey(KEY_INPUT_X)==1)
	{
		SetUseIMEFlag(true);
		ChildWindow(c_score,"works/Sankaku/top.html");
		syokikaflag = true;
	}
	fopen_s(&pt,"high.dat","w");
	ango = highscore^0x9fb26ac;
	fprintf(pt,"%d",ango);
	fclose(pt);

}
//ロゴ画面
void logo()
{

	//パッド入力
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	SetDrawBright((int)light,(int)light,(int)light);
	DrawGraph(0,0,g_back,FALSE);

	timelogo++;

//	if(CheckHitKey(KEY_INPUT_RETURN) || CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_X))
	if(key&PAD_INPUT_A || key&PAD_INPUT_B || CheckHitKey(KEY_INPUT_RETURN))
	{
		timelogo += 480;
	}


	if(timelogo >= 300)
	{
		light -= 4;
		if(light <= -240)
		{
			logoflag = true;
			light = 255;
			SetDrawBright((int)light,(int)light,(int)light);
		}
	}
	else
	{
		light += 2.5;
		if(light > 255)
		{
			light = 255;
		}
	}
}

//背景
void wall()
{
	if(level == level_wall)
	{
		if(change_wall == (timescore + shot_kaisuu)%19)
		{
			timescore++;
		}
		change_wall = (timescore + shot_kaisuu)%19;
		level_wall += 3;
		PlaySoundMem(se_change_wall,DX_PLAYTYPE_BACK);
	}

	DrawGraph(0,0,g_w[change_wall],false);
}

//データの読み込み
int load_files()
{

	switch(file_count)
	{
	case 1:
		LoadDivGraph("media\\player3D.png",12,12,1,33,33,g_player);
		g_player_c78 = LoadGraph("media\\player2.png");
		file_count--;
		return 0;
	case 2:
		LoadDivGraph("media\\player3D_b.png",12,12,1,33,33,g_player2);
		g_player2_c78 = LoadGraph("media\\player2_b.png");
		file_count--;
		return 0;
	case 3:
		g_wall = LoadGraph("media\\waku.png");
		g_wall_soto = LoadGraph("media\\waku_soto.png");
		
		file_count--;
		return 0;
	case 4:
		LoadDivGraph("media\\ball_b_fullcolor.png",6,6,1,32,32,g_ball1);
		g_ball1_c78 = LoadGraph("media\\ball1_32.png");
		file_count--;
		return 0;
	case 5:
		LoadDivGraph("media\\ball_g_fullcolor.png",8,8,1,32,32,g_ball2);
		g_ball2_c78 = LoadGraph("media\\ball2_32.png");
		file_count--;
		return 0;
	case 6:
		g_ball3 = LoadGraph("media\\ball3_32.png");
		file_count--;
		return 0;
	case 7:
		LoadDivGraph("media\\skyfish2.png",2,2,1,64,32,g_skyfish);
		file_count--;
		return 0;
	case 8:
		g_shot = LoadGraph("media\\player_weapon_g.png");
		file_count--;
		return 0;
	case 9:
		g_shot2 = LoadGraph("media\\player_weapon_b.png");
		file_count--;
		return 0;
	case 47:
		g_back = LoadGraph("media\\AM640480.png");
		file_count--;
		return 0;
	case 11:
		g_tytle = LoadGraph("media\\tytle_g.png");
		g_coment = LoadGraph("media\\coment.png");
		file_count--;
		return 0;
	case 12:
		g_tytle2 = LoadGraph("media\\tytle_b.png");
		file_count--;
		return 0;
	case 13:
		g_start = LoadGraph("media\\start.png");
		file_count--;
		return 0;
	case 14:
		g_exit = LoadGraph("media\\exit.png");
		file_count--;
		return 0;
	case 15:
		g_out = LoadGraph("media\\out.png");
		file_count--;
		return 0;
	case 16:
		g_w[0] = LoadGraph("media\\den1.jpg");
		g_w[15]= LoadGraph("media\\den16.jpg");
		file_count--;
		return 0;
	case 17:
		g_w[1] = LoadGraph("media\\den2.jpg");
		g_w[16]= LoadGraph("media\\den17.jpg");
		file_count--;
		return 0;
	case 18:
		g_w[2] = LoadGraph("media\\den3.jpg");
		g_w[17]= LoadGraph("media\\den18.jpg");
		file_count--;
		return 0;
	case 19:
		g_w[3] = LoadGraph("media\\den4.jpg");
		g_w[18]= LoadGraph("media\\den19.jpg");
		file_count--;
		return 0;
	case 20:
		g_w[4] = LoadGraph("media\\den5.jpg");
		file_count--;
		return 0;
	case 21:
		g_w[5] = LoadGraph("media\\den6.jpg");
		file_count--;
		return 0;
	case 22:
		g_w[6] = LoadGraph("media\\den7.jpg");
		file_count--;
		return 0;
	case 23:
		g_w[7] = LoadGraph("media\\den8.jpg");
		file_count--;
		return 0;
	case 24:
		g_w[8] = LoadGraph("media\\den9.jpg");
		file_count--;
		return 0;
	case 25:
		g_w[9] = LoadGraph("media\\den10.jpg");
		file_count--;
		return 0;
	case 26:
		g_w[10] = LoadGraph("media\\den11.jpg");
		file_count--;
		return 0;
	case 27:
		g_w[11] = LoadGraph("media\\den12.jpg");
		file_count--;
		return 0;
	case 28:
		g_w[12] = LoadGraph("media\\den13.jpg");
		file_count--;
		return 0;
	case 29:
		g_w[13] = LoadGraph("media\\den14.jpg");
		file_count--;
		return 0;
	case 30:
		g_w[14] = LoadGraph("media\\den15.jpg");
		file_count--;
		return 0;

	case 31:
		se_shot = LoadSoundMem("media\\se_shot.ogg");
		file_count--;
		return 0;
	case 32:
		se_hit = LoadSoundMem("media\\se_hit.ogg");
		file_count--;
		return 0;
	case 33:
		se_hit2 = LoadSoundMem("media\\se_hit2.ogg");
		file_count--;
		return 0;
	case 34:
		se_down = LoadSoundMem("media\\se_down.ogg");
		file_count--;
		return 0;
	case 35:
		se_level = LoadSoundMem("media\\level.ogg");
		file_count--;
		return 0;
	case 36:
		se_change = LoadSoundMem("media\\change.ogg");
		file_count--;
		return 0;
	case 37:
		se_hansya = LoadSoundMem("media\\hansya.ogg");
		file_count--;
		return 0;
	case 38:
		se_combo_miss = LoadSoundMem("media\\combo_miss.ogg");
		file_count--;
		return 0;
	case 39:
		se_chance = LoadSoundMem("media\\chance.ogg");
		file_count--;
		return 0;
	case 40:
		se_sky_shot = LoadSoundMem("media\\sky_shot.ogg");
		file_count--;
		return 0;
	case 10:
		se_change_wall = LoadSoundMem("media\\change_wall.ogg");
		file_count--;
		return 0;


	case 42:
	//	bgm[0] = LoadSoundMem("media\\bgm2.ogg");
		file_count--;
		return 0;
	case 43:
	//	bgm[1] = LoadSoundMem("media\\bgm3.ogg");
		file_count--;
		return 0;
	case 44:
	//	bgm[2] = LoadSoundMem("media\\bgm4.ogg");
		file_count--;
		return 0;
	case 45:
	//	bgm[3] = LoadSoundMem("media\\bgm5.ogg");
		file_count--;
		return 0;
	case 46:
		start_m = LoadSoundMem("media\\start_melo.ogg");
		file_count--;
		return 0;
	case 41:
		end_m = LoadSoundMem("media\\end_melo.ogg");
		font_lv = CreateFontToHandle(NULL,25,5);
		font_score = CreateFontToHandle(NULL,16,2);
		font_result = CreateFontToHandle(NULL,20,4);
		file_count--;
		return 0;
	case 0:
		set_graph = true;
		return 0;
	}



/*		g_player = LoadGraph("media\\player2.png");
		g_player2 = LoadGraph("media\\player2_b.png");
		g_wall = LoadGraph("media\\waku.png");
		g_ball1 = LoadGraph("media\\ball1_32.png");
		g_ball2 = LoadGraph("media\\ball2_32.png");
		g_ball3 = LoadGraph("media\\ball3_32.png");
		LoadDivGraph("media\\skyfish2.png",2,2,1,64,32,g_skyfish);
		g_shot = LoadGraph("media\\player_weapon_g.png");
		g_shot2 = LoadGraph("media\\player_weapon_b.png");
		g_back = LoadGraph("media\\AM640480.png");
		g_tytle = LoadGraph("media\\tytle_g.png");
		g_tytle2 = LoadGraph("media\\tytle_b.png");
		g_start = LoadGraph("media\\start.png");
		g_exit = LoadGraph("media\\exit.png");
		g_out = LoadGraph("media\\out.png");
		g_w[0] = LoadGraph("media\\iro1.png");
		g_w[1] = LoadGraph("media\\iro2.png");
		g_w[2] = LoadGraph("media\\iro3.png");
		g_w[3] = LoadGraph("media\\iro4.png");
		g_w[4] = LoadGraph("media\\iro5.png");
		g_w[5] = LoadGraph("media\\iro6.png");
		g_w[6] = LoadGraph("media\\iro7.png");
		g_w[7] = LoadGraph("media\\iro8.png");
		g_w[8] = LoadGraph("media\\iro9.png");
		g_w[9] = LoadGraph("media\\iro10.png");
		g_w[10] = LoadGraph("media\\iro11.png");
		g_w[11] = LoadGraph("media\\iro12.png");
		g_w[12] = LoadGraph("media\\iro13.png");
		g_w[13] = LoadGraph("media\\iro14.png");
		g_w[14] = LoadGraph("media\\iro15.png");

		se_shot = LoadSoundMem("media\\se_shot.ogg");
		if(se_shot == -1) return -1;
		se_hit = LoadSoundMem("media\\se_hit.ogg");
		se_hit2 = LoadSoundMem("media\\se_hit2.ogg");
		se_down = LoadSoundMem("media\\se_down.ogg");
		se_level = LoadSoundMem("media\\level.ogg");
		se_change = LoadSoundMem("media\\change.ogg");
		se_hansya = LoadSoundMem("media\\hansya.ogg");
		se_combo_miss = LoadSoundMem("media\\combo_miss.ogg");
		se_chance = LoadSoundMem("media\\chance.ogg");
		se_sky_shot = LoadSoundMem("media\\sky_shot.ogg");
		se_change_wall = LoadSoundMem("media\\change_wall.ogg");


		bgm[0] = LoadSoundMem("media\\bgm2.ogg");
		bgm[1] = LoadSoundMem("media\\bgm3.ogg");
		bgm[2] = LoadSoundMem("media\\bgm4.ogg");
		bgm[3] = LoadSoundMem("media\\bgm5.ogg");
		start_m = LoadSoundMem("media\\start_melo.ogg");
		end_m = LoadSoundMem("media\\end_melo.ogg");

		font_lv = CreateFontToHandle(NULL,25,5);
		font_score = CreateFontToHandle(NULL,16,2);
		font_result = CreateFontToHandle(NULL,20,4);


		set_graph = true;
*/
	return 0;
}



//メインループ
void mymain()
{

	if(syokaiflag == false)
	{
		highscore_syori();
		syokaiflag = true;
	}
	if(set_graph == false)
	{
		load_files();
	}
	if(logoflag == false && file_count <41)
	{
		logo();
	}
	else if(file_count == 0)
	{
		option();

		if(option_flag == false)
		{
			if(syokikaflag == true)
			{
				syokika();
				syokikaflag = false;
			}


			if(game_endflag == false)
			{
				if(game_startflag == true)
				{
					wall();
				}
				

				if(game_startflag == false)
				{
					StopSoundMem(end_m);
					start_menu();
				}
				DrawGraph(0,0,g_wall,TRUE);
				move_myship();
				botten();
				drawshot();
				if(game_startflag == true)
				{
					ball();
					ball_hantei();
					shot_hantei();
					jiki_hantei();
					sky_jouken();
					skyfish();
					shot_sky();
					
					
					if(level == level_melo)
					{
						start_melo = false;
						level_melo += 5;
						if(melo_s == 1)
						{
							melo_s+=2;
						}
						if(melo_s == 2)
						{
							melo_s+=2;
						}
						if(melo_s == 0)
						{
							melo_s += shot_kaisuu%2+1;
						}
						if(melo_s > 5)
						{
							start_melo = true;
							melo_s = 5;
						}
					}

					if(start_melo == false)
					{
						
						StopSoundMem(bgm[0]);
						StopSoundMem(bgm[1]);
						StopSoundMem(bgm[2]);
						StopSoundMem(bgm[3]);
						StopSoundMem(bgm[4]);
						PlaySoundMem(bgm[melo_s],DX_PLAYTYPE_LOOP);
						start_melo = true;
					}
				}

				DrawGraph(0,0,g_wall_soto,TRUE);

				if(score >= 1999999999)
				{
					score = 1999999999;
				}
				if(score >= highscore)
				{
					highscore = score;
				}
				DrawFormatStringToHandle(200,463,GetColor(255,100,255),font_score,"HIGHSCORE: %d",highscore);
				DrawFormatStringToHandle(200,447,GetColor(255,100,255),font_score,"    SCORE: %d",score);
				DrawFormatStringToHandle(24,454,GetColor(255,122,0),font_lv,"Lv. %d",level);
				if(combo >= 4)
				{
					DrawFormatStringToHandle(500,454,GetColor(122,122,255),font_lv,"%d HIT!",combo);
				}
			}
			else if(game_endflag == true)
			{
				gameover();

			}
		}
		get_option();
	}

}