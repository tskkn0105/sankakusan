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

//�{�[��
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

//��
extern int bgm[6];
extern int melo_s;
extern int se_chance;
extern int se_change;


extern double speedn;		//�{�[���̑���

extern speed vecter[maxball];	//�{�[���̌���

//���x��
extern int level;
extern int levelcount;
extern double levelspeed;
extern int levelcount_up;

extern bool startflag[maxball];	//�ŏ����ǂ���
extern bool game_startflag;

extern bool touch_flag[maxball];	//�������������
extern int ball_kazu;				//�{�[���̐�

extern bool change_ballflag[maxball]; //�{�[���̐F�t���O
extern bool shot_missflag[maxball];

extern int se_level;	//���x���A�b�v���ʉ�
extern int se_chance;

extern int melo_s;
extern int level_melo;

//�X�R�A
extern int score;
extern int highscore;
extern int combo;
extern int sky_combo;
extern FILE *pt;
extern int ango;

	//�͂��߂̃t���O
extern bool game_startflag;
	//BGM�t���O
extern bool start_melo;
	//�Q�[���I���^�t���O
extern bool game_endflag;
	//�I���̋ȃt���O
extern bool end_m_flag;

//�e
const int maxshot = 2;

extern int shot_kaisuu;
extern bool shot_used2[maxshot];//���@�̂Ƃ���ɉ摜�������Ă���
extern bool shot_used3[maxshot];
extern bool first_shotflag;
extern bool shotflag;


extern bool startflag[maxball];

extern int jiki_x;
extern int jiki_y;

//�X�J�C�t�B�b�V��
extern speed sky;
extern int sky_ani;
extern int sky_count;
extern int sky_combo;
extern bool sky_used;
extern bool sky_sound;

//��
extern int change_wall;
extern int level_wall;

//�I�v�V�����̃t���O
extern bool option_flag;
extern int option_level;
extern bool c78_flag;



#endif