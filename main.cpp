//ヘッダーファイルの読み込み
#include "DxLib.h"//dxLibを使うときは必ず必要]

//マクロ定義
#define GAME_TITLE	"ゲームタイトル"//ゲームタイトル
#define GAME_WIDTH	1280//ゲーム画面の幅（ウィドス）
#define GAME_HEIGHT 720//ゲーム画面高さ（ハイト）
#define GAME_COLOR 32//ゲームの色域

#define GAME_ICON_ID 333

#define GAME_WINDOW_BAR 0

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
	SetWindowIconID(GAME_ICON_ID);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetWaitVSyncFlag(TRUE);
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;

	int width = 32;
	int height = 32;

	//円の半径を決める
	int radius = 100;

	int Speed = 1;
	int XSpeed = Speed;
	int YSpeed = Speed;

	SetDrawScreen(DX_SCREEN_BACK);

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
			//break;
		}

		if (ClearDrawScreen() != 0) { break; }


		/*DrawBox(
			X, Y, X+ width,Y+height,
			GetColor(255, 0, 0),
			TRUE
		);*/
		//円を描画
		DrawCircle(
			X, Y, radius,
			GetColor(0, 255, 0),
			FALSE, 5
		);
		X += XSpeed;
		Y += YSpeed;

		if (X - radius < 0 || X + radius > GAME_WIDTH)
		{
			XSpeed = -XSpeed;

			if (XSpeed > 0) { XSpeed += 2;}
			else if (XSpeed < 0) {
				XSpeed -= 2;
			}
		}
		if (Y - radius < 0 || Y + radius > GAME_HEIGHT)
		{
			YSpeed = -YSpeed;

			if (YSpeed > 0) { YSpeed += 2; }
			else if (YSpeed < 0) {
				YSpeed -= 2;
			}
		}
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}