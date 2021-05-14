#pragma once

#include "DxLib.h"

//キーボードのヘッダファイル

//マクロ定義
#define KEY_KIND_MAX  256//取得するキーの種類

//キーボード構造体
struct KEYBOARD
{
	char TempKeyState[KEY_KIND_MAX];
	int AllKeyState[KEY_KIND_MAX];
	int OldAllKeyState[KEY_KIND_MAX];

};

//外部のグローバル変数
extern KEYBOARD keyboard;

//プロトタイプ宣言
extern VOID AllKeyUpdate(VOID);
extern BOOL KeyDown(int KEY_INPUT_);
extern BOOL KeyUp(int KEY_INPUT);
extern BOOL KeyClick(int KEY_INPUT);
extern BOOL KeyDownKeep(int KEY_INPUT_, int millSec);
