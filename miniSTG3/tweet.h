
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<vector>

//winsock��Visual Studio�̃o�[�W�����ŋ�����������炻��̊֌W��
#if _MSC_VER == 1500
	#ifdef _DEBUG
		#pragma comment( lib, "twit.lib" )
	#else
		#pragma comment( lib, "twit_d.lib" )
	#endif
#endif
#if _MSC_VER == 1600
	#ifdef _DEBUG
		#pragma comment( lib, "twit_2010.lib" )
	#else
		#pragma comment( lib, "twit_2010_d.lib" )
	#endif
#endif

#define DXLIBFLAG 1

/*
���������邽�߂̂��
�ŏ��ɓǂݍ��܂���
*/
void init();
/*
�ꎞ�I�ɘA�g��؂��Ă邩�ǂ���
init�Ō��Ă邩��ċN���Ƃ������Ȃ��ƃ_�������ǂ�
*/
bool TweetFlag();

/*
Twitter�ɓ��~����
text�ɂԂ₩������e������
url:http://www.amusement-makers.org/
�ȍ~�������Ă���������
(��)tweet("�Ă񂷂�","works/Sankaku/top.html");
����g����
http://www.amusement-makers.org/works/Sankaku/top.html
�ƌ����y�[�W���Ō�ɕ\�������
�_���̏��ɂ̓Q�[���̃n�b�V���^�O������Ȃ炻���������
*/
void tweet(std::string text,LPSTR url);
void tweetText(std::string edit,LPSTR url,std::string init_key,std::string init_secret);
/*
set_key,set_secret�@�Ɏ����Ŏ擾����key��secret����͂��Ă�
*/
void SetTweetText(std::string edit,std::string init_key,std::string init_secret,std::string set_key,std::string set_secret);
#if _UNICODE
//���j�R�[�h�̎�����Ȃ��Ǝg���Ȃ�������key�Ƃ�secret�Ƃ������Ȃ��Ƃ����Ȃ����炢�낢��߂�ǂ�
void tweetA(std::wstring edit);
void tweetTextA(std::string edit,std::string init_key,std::string init_secret,std::string set_key,std::string set_secret);
#endif

/*
�q�E�B���h�E������ăG�f�B�b�g�{�b�N�X�ɕ�������͂��ęꂩ����B
text�ɂԂ₩������e������
url:http://www.amusement-makers.org/
�ȍ~�������Ă���������
(��)tweet("�Ă񂷂�","works/Sankaku/top.html");
����g����
http://www.amusement-makers.org/works/Sankaku/top.html
�ƌ����y�[�W���Ō�ɕ\�������
*/
HWND ChildWindow(char* text,LPSTR url);

/*
URL�ȗ�
url�ɒZ�k������URL�����
*/
std::string bitly(char* url);
//���{��URL���܂܂�Ă�Ƃ��p
std::string bitlyW(std::string LongURL);
std::string Setbitly(char* longURL,char* user,char* apikey);

//�w�肵��URL���u���E�U���J���ĕ\��
//OpenURL("http://www.amusement-makers.org/");
//�Ƃ���
//OpenURL("./");
//�Ŋm���C���X�g�[�������f�B���N�g���J�����͂�
void OpenURL(TCHAR* url);

//�e�X�g�p�̃A�J�E���g�ɂԂ₩���邽�߂̌�
std::string GetKey();
//�e�X�g�p�̃A�J�E���g�ɂԂ₩���邽�߂̌�
std::string GetSecret();
//�l�b�g�ɂȂ����Ă邩�ǂ����̔���
bool webcop();
