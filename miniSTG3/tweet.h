
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<vector>

//winsockがVisual Studioのバージョンで挙動違ったからそれの関係で
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
初期化するためのやつ
最初に読み込ませる
*/
void init();
/*
一時的に連携を切ってるかどうか
initで見てるから再起動とかさせないとダメだけども
*/
bool TweetFlag();

/*
Twitterに投降する
textにつぶやかせる内容を入れる
url:http://www.amusement-makers.org/
以降を書いてくださいな
(例)tweet("てんすう","works/Sankaku/top.html");
上を使うと
http://www.amusement-makers.org/works/Sankaku/top.html
と言うページが最後に表示される
点数の所にはゲームのハッシュタグがあるならそれも書いて
*/
void tweet(std::string text,LPSTR url);
void tweetText(std::string edit,LPSTR url,std::string init_key,std::string init_secret);
/*
set_key,set_secret　に自分で取得したkeyとsecretを入力してね
*/
void SetTweetText(std::string edit,std::string init_key,std::string init_secret,std::string set_key,std::string set_secret);
#if _UNICODE
//ユニコードの時じゃないと使えないうえにkeyとかsecretとかかかないといけないからいろいろめんどい
void tweetA(std::wstring edit);
void tweetTextA(std::string edit,std::string init_key,std::string init_secret,std::string set_key,std::string set_secret);
#endif

/*
子ウィンドウを作ってエディットボックスに文字を入力して呟かせる。
textにつぶやかせる内容を入れる
url:http://www.amusement-makers.org/
以降を書いてくださいな
(例)tweet("てんすう","works/Sankaku/top.html");
上を使うと
http://www.amusement-makers.org/works/Sankaku/top.html
と言うページが最後に表示される
*/
HWND ChildWindow(char* text,LPSTR url);

/*
URL省略
urlに短縮させるURLを入力
*/
std::string bitly(char* url);
//日本語URLが含まれてるとき用
std::string bitlyW(std::string LongURL);
std::string Setbitly(char* longURL,char* user,char* apikey);

//指定したURLをブラウザを開いて表示
//OpenURL("http://www.amusement-makers.org/");
//とかね
//OpenURL("./");
//で確かインストールしたディレクトリ開けたはず
void OpenURL(TCHAR* url);

//テスト用のアカウントにつぶやかせるための鍵
std::string GetKey();
//テスト用のアカウントにつぶやかせるための鍵
std::string GetSecret();
//ネットにつながってるかどうかの判定
bool webcop();
