//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"//dxLib���g���Ƃ��͕K���K�v]

//�}�N����`
#define GAME_TITLE	"�Q�[���^�C�g��"//�Q�[���^�C�g��
#define GAME_WIDTH	1280//�Q�[����ʂ̕��i�E�B�h�X�j
#define GAME_HEIGHT 720//�Q�[����ʍ����i�n�C�g�j
#define GAME_COLOR 32//�Q�[���̐F��

#define GAME_ICON_ID 333

#define GAME_WINDOW_BAR 0

// �v���O������ WinMain ����n�܂�܂�
//windows�̃v���O���~���O���@�@���@�iWinAPI)�œ����Ă���I
//DxLib�́ADireectX�Ƃ����A�Q�[���v���O���~���O���ȒP�Ɏg����d�g��
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

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;

	int width = 32;
	int height = 32;

	//�~�̔��a�����߂�
	int radius = 100;

	int Speed = 1;
	int XSpeed = Speed;
	int YSpeed = Speed;

	SetDrawScreen(DX_SCREEN_BACK);

	while (1)
	{
		//��������̃L�[�������ꂽ�Ƃ�
		if (CheckHitKeyAll() != 0)
		{
			break;
		}

		//���b�Z�[�W���󂯎�葱����
		if (ProcessMessage() != 0)//-1�̎��́A�G���[��E�B���h�E������ꂽ
		{
			//break;
		}

		if (ClearDrawScreen() != 0) { break; }


		/*DrawBox(
			X, Y, X+ width,Y+height,
			GetColor(255, 0, 0),
			TRUE
		);*/
		//�~��`��
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}