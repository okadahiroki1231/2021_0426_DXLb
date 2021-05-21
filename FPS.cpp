//FPSのソースファイル

//ヘッダファイル読み込み
#include "DxLib.h"
#include "FPS.h"

//グローバル変数
FPS fps; //FPSの管理

///
///FPS値を計測し、値を更新する
/// 
/// 
VOID FPSUpdate(VOID)
{
	//一番最初の処理
	if (fps.IsInitFlg == FALSE)
	{
		//測定開始時刻をマイクロ秒単位で取得
		fps.StartTime = GetNowHiPerformanceCount();//windowsが起動してから経過した時間

		fps.IsInitFlg = TRUE; //フラグを立てる

	}

	//現在の時刻をマイクロ秒単位で取得
	fps.NowTime = GetNowHiPerformanceCount();

	//前回取得した時間からの経過時間を秒（少数)に変換してからセット
	fps.DeltaTime = (fps.NowTime - fps.OldTime) / 1000000.0f;

	//今回取得した時間を保存
	fps.OldTime = fps.NowTime;

	//1フレーム目～FPS設定値とまでカウントアップ
	if (fps.Count < fps.SamplcRate)
	{
		//カウンタを増やす
		fps.Count++;
	}
	else
	{
		//FPS設定値のフレームで、平均FPSを計算

		//現在の時刻から、0フレーム目時間を引き、FPSの数値で割る
		//現在の平均FPS値が出る
		fps.DrawValuc = 1000000.f / ((fps.NowTime - fps.StartTime) / (float)fps.SamplcRate);

		//測定開始時刻をマイクロ秒単位で取得
		fps.StartTime = GetNowHiPerformanceCount();//Windowsが起動してから経過した時間

		//カウンタ初期化
		fps.Count = 1;

	}

	return;
}
///
///平均FPS値を描画する
/// 
/// 
VOID FPSDraw(VOID)
{
	//文字列を描画
	DrawFormatString(0, 20, GetColor(0, 0, 0), "FPS:%.lf", fps.DrawValuc);

	return;
}

///
///FPSで処理を待つ
/// 
/// 
VOID FPSWait(VOID)
{
	//現在の時刻ー最初の時刻で、現在かかっている時刻を取得する
	LONGLONG resultTime = fps.NowTime - fps.StartTime;

	//待つべきミリ秒数　(1秒/FPS値 * 現在のフレーム数）から、現在かかっている時刻を引く
	int waitTime = 1000000.0f / fps.Value * fps.Count - resultTime;

	//マイクロ秒からミリ秒に変換
	waitTime /= 1000.0f;
	//処理が早かったら処理を待つ
	if (waitTime > 0)
	{
		WaitTimer(waitTime); //引数ミリ秒待つ
	}

	//垂直同期をOFFにしているか？
	if (GetWaitVSyncFlag() == FALSE)
	{

		//FPS最大値ではないとき
		if (fps.Value < GAME_FPS_MAX)
		{

			//１秒毎のFPS値よりも、待つ時間が小さいときは、もっとFPS値をあげてもいい
			//待つ時間　10ミリ　＜＝　1秒/60FPS　＝　16.6666ミリ　もう少し早くできる
			if (waitTime > 0
				&& waitTime <= 1000.0f / fps.Value)
			{
				fps.Count++;
			}
			else
			{
				//FPS値が追いついておらず、遅いときはFPS値をさげる
				if (fps.Value > GAME_FPS_MIN)
				{
					fps.Value--;
				}
			}
		}
	}
	return;
}