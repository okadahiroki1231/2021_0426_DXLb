//ヘッダーファイルの読み込み
#include "DxLib.h"//dxLibを使うときは必ず必要

#include "keyboard.h"//キーボードの処理

//マクロ定義
#define GAME_TITLE	"ゲームタイトル"//ゲームタイトル
#define GAME_WIDTH	1280//ゲーム画面の幅（ウィドス）
#define GAME_HEIGHT 720//ゲーム画面高さ（ハイト）
#define GAME_COLOR 32//ゲームの色域

#define GAME_ICON_ID 333

#define GAME_WINDOW_BAR 0

//列挙型
enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};//ゲームのシーン

//シーンを管理する変数
GAME_SCENE GameScene;//現在のゲームのシーン
GAME_SCENE OldGameScene;//前回のゲームのシーン
GAME_SCENE NextGameScene;//次のゲームのシーン

//画面の切り替え
BOOL IsFadeOut = FALSE;
BOOL IsFadeIn = FALSE;

int fadeTimeMill = 2000;//切り替えミリ秒
int fadeTimeMax = fadeTimeMill / 1000 * 60;//ミリ秒をフレーム秒に変換

//フェードアウト
int fadeOutCntInit = 0; //初期値
int fadeOutCnt = fadeOutCntInit;//フィードアウトのカウンタ
int fadeOutCntMax = fadeTimeMax; //フィードアウトのカウンタMAX

//フェードイン
int fadeInCntInit = fadeTimeMax; //初期値
int fadeInCnt = fadeInCntInit;//フィードインのカウンタ
int fadeInCntMax = fadeTimeMax; //フィードインのカウンタMAX

//プロトタイプ宣言
VOID Title(VOID);    //タイトル画面
VOID TitleProc(VOID);//タイトル画面(処理)
VOID TitleDraw(VOID);//タイトル画面(描画)

VOID Play(VOID);    //プレイ画面
VOID PlayProc(VOID);//プレイ画面(処理)
VOID PlayDraw(VOID);//プレイ画面(描画)

VOID End(VOID);    //エンド画面
VOID EndProc(VOID);//エンド画面(処理)
VOID EndDraw(VOID);//エンド画面(描画)

VOID Change(VOID);    //切り替え画面
VOID ChangeProc(VOID);//切り替え画面(処理)
VOID ChangeDraw(VOID);//切り替え画面(描画)

VOID ChangeScene(GAME_SCENE scene);//シーン切り替え


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

	SetDrawScreen(DX_SCREEN_BACK);

	//円の中心点
	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;
	//円の半径
	int radius = 50;

	//最初のシーンは、タイトル画面から
	GameScene = GAME_SCENE_TITLE;

	//無限ループ
	while (1)
	{


		//メッセージを受け取り続ける
		if (ProcessMessage() != 0) { break; }//メッセージを受け取り続ける
		if (ClearDrawScreen() != 0) { break; }//画面を消去する

		//キーボード入力の更新
		AllKeyUpdate();

		//ESCキーで強制終了
		if (KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		//以前のシーンを取得
		if (GameScene != GAME_SCENE_CHANGE)
		{
			OldGameScene = GameScene;
		}

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			Title();
			break;
		case GAME_SCENE_PLAY:
			Play();
			break;
		case GAME_SCENE_END:
			End();
			break;
		case GAME_SCENE_CHANGE:
			Change();
			break;
		default:
			break;
		}
		
	

		//シーンを切り替える
		if (OldGameScene != GameScene)
		{
			//現在のシーンが切り替え画面でないとき
			if (GameScene != GAME_SCENE_CHANGE)
			{
				NextGameScene = GameScene;//次のシーンを保存
				GameScene = GAME_SCENE_CHANGE;//画面切り替えシーンに変える
			}
		}

		//キー入力
		if (KeyDown(KEY_INPUT_UP) == TRUE)
		{
			Y--;//上に移動
		}
		if (KeyDown(KEY_INPUT_DOWN) == TRUE)
		{
			Y++;
		}
		if (KeyDown(KEY_INPUT_LEFT) == TRUE)
		{
			X--;
		}
		if (KeyDown(KEY_INPUT_RIGHT) == TRUE)
		{
			X++;
		}

		

		

		DrawCircle(X, Y, radius, GetColor(255, 255, 0), TRUE);
		
		ScreenFlip();//ダブルバッキングした画面を描画
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
	VOID ChangeScene(GAME_SCENE scene)
	{
		GameScene = scene;//シーンの切り替え
		IsFadeIn = FALSE;//フィードインしない
		IsFadeOut = TRUE;//フィードアウトする
}
///<summary>
/// タイトル画面
///</summary>
VOID Title(VOID)
{
	TitleProc();//処理
	TitleDraw();//描画

	return;
}
///
/// タイトル画面の処理
/// 
VOID TitleProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//シーン切り替え
		//次のシーンの初期化をここで行うと楽

		//プレイ画面に切り替え
		ChangeScene(GAME_SCENE_PLAY);
	}
	
	return;
}
///
///タイトル画面の描画
/// 
VOID TitleDraw(VOID)
{
	DrawString(0, 0, "タイトル画面", GetColor(0, 0, 0));
	return;

}

///<summary>
/// プレイ画面
///</summary>
VOID Play(VOID)
{
	PlayProc();//処理
	PlayDraw();//描画

	return;
}
///
/// プレイ画面の処理
/// 
VOID PlayProc(VOID)
{

	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//シーン切り替え
		//次のシーンの初期化をここで行うと楽

		//エンド画面に切り替え
		ChangeScene(GAME_SCENE_END);
	}
	return;
}
///
///プレイ画面の描画
/// 
VOID PlayDraw(VOID)
{
	DrawString(0, 0, "プレイ画面", GetColor(0, 0, 0));
	return;
}


///<summary>
/// エンド画面
///</summary>
VOID End(VOID)
{
	EndProc();//処理
	EndDraw();//描画

	return;
}
///
/// エンド画面の処理
/// 
VOID EndProc(VOID)
{

	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//シーン切り替え
		//次のシーンの初期化をここで行うと楽

		//タイトル画面に切り替え
		ChangeScene(GAME_SCENE_TITLE);
	}
	return;
}
///
///エンド画面の描画
/// 
VOID EndDraw(VOID)
{
	DrawString(0, 0, "エンド画面", GetColor(0, 0, 0));
	return;
}


///<summary>
/// 切り替え画面
///</summary>
VOID Change(VOID)
{
	ChangeProc();//処理
	ChangeDraw();//描画

	return;
}
///
/// 切り替え画面の処理
/// 
VOID ChangeProc(VOID)
{
	if (IsFadeIn == TRUE)
	{
		if (fadeInCnt > fadeInCntMax)
		{
			fadeInCnt--;
		}
		else
		{
			fadeInCnt = fadeInCntInit;
			IsFadeIn = FALSE;
		}
	}

	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt > fadeOutCntMax)
		{
			fadeOutCnt--;
		}
		else
		{
			fadeOutCnt = fadeOutCntInit;
			IsFadeOut = FALSE;
		}
	}
	if (IsFadeIn == FALSE && IsFadeOut == FALSE)
	{
		GameScene = NextGameScene;
		OldGameScene = GameScene;
	}
	return;
}
///
///切り替え画面の描画
/// 
VOID ChangeDraw(VOID)
{
	//以前のシーンを描画
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		TitleDraw();//タイトル画面の描画
		break;
	case GAME_SCENE_PLAY:
		PlayDraw();//プレイ画面の描画
		break;
	case GAME_SCENE_END:
		EndDraw();//エンド画面の描画
		break;
	default:
		break;
	}

	if (IsFadeIn == TRUE)
	{
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, ((float)fadeInCnt / fadeInCntMax) * 255);
	}

	if (IsFadeOut == TRUE)

	{
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, ((float)fadeOutCnt / fadeOutCntMax) * 255);
	}


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);//0～255
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "切り替え画面", GetColor(0, 0, 0));
	return;
}

