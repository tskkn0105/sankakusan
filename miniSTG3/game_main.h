#ifndef GAME_MAIN
#define GAME_MAIN
#include"DxLib.h"
#include<math.h>
#include"tweet.h"


struct speed
{
	double x;
	double y;
};

struct hantei
{
	int x1;
	int y1;
	int x2;
	int y2;
};

extern bool exitflag;
extern bool z_flag;

//ボール
const int maxball = 50;
extern int ball_kazu;
extern int ball_kazu_b;

extern int ball_pos_x[maxball];
extern int ball_pos_y[maxball];

extern int g_ball1[6];
extern int g_ball2[8];
extern int g_ball1_c78;
extern int g_ball2_c78;
extern int g_ball3;
extern int g_skyfish[2];

//曲
extern int bgm[6];
extern int melo_s;
extern int se_chance;
extern int se_change;


extern double speedn;		//ボールの速さ

extern speed vecter[maxball];	//ボールの向き

//レベル
extern int level;
extern int levelcount;
extern double levelspeed;
extern int levelcount_up;

extern bool startflag[maxball];	//最初かどうか
extern bool game_startflag;

extern bool touch_flag[maxball];	//さわったかしら
extern int ball_kazu;				//ボールの数

extern bool change_ballflag[maxball]; //ボールの色フラグ
extern bool shot_missflag[maxball];

extern int se_level;	//レベルアップ効果音
extern int se_chance;

extern int melo_s;
extern int level_melo;

//スコア
extern int score;
extern int highscore;
extern int combo;
extern int sky_combo;
extern FILE *pt;
extern int ango;

	//はじめのフラグ
extern bool game_startflag;
	//BGMフラグ
extern bool start_melo;
	//ゲームオワタフラグ
extern bool game_endflag;
	//終わりの曲フラグ
extern bool end_m_flag;

//弾
const int maxshot = 2;

extern int shot_kaisuu;
extern bool shot_used2[maxshot];//自機のところに画像を持っていく
extern bool shot_used3[maxshot];
extern bool first_shotflag;
extern bool shotflag;


extern bool startflag[maxball];

extern int jiki_x;
extern int jiki_y;

//スカイフィッシュ
extern speed sky;
extern int sky_ani;
extern int sky_count;
extern int sky_combo;
extern bool sky_used;
extern bool sky_sound;

//壁
extern int change_wall;
extern int level_wall;

//オプションのフラグ
extern bool option_flag;
extern int option_level;
extern bool c78_flag;



#endif