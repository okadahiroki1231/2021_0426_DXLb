//ヘッダーファイルの読み込み
#include "DxLib.h"//dxLibを使うときは必ず必要]

//マクロ定義
#define GAME_TITLE	"ゲームタイトル"//ゲームタイトル
#define GAME_WIDTH	1280//ゲーム画面の幅（ウィドス）
#define GAME_HEIGHT 720//ゲーム画面高さ（ハイト）
#define GAME_COLOR 32//ゲームの色域

#define GAME_ICON   333

// プログラムは WinMain から始まります
//windowsのプログラミング方法　＝　（WinAPI)で動いている！
//DxLibは、DireectXという、ゲームプログラミングを簡単に使える仕組み
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText(GAME_TITLE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	SetBackgroundColor(255, 255, 255);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	while (1)
	{
		//何かしらのキーが押されたとき
		if (CheckHitKeyAll() != 0)
		{
			break;
		}

		//メッセージを受け取り続ける
		if (ProcessMessage() != 0)//-1の時は、エラーやウィンドウが閉じられた
		{
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}