//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"//dxLib���g���Ƃ��͕K���K�v]

//�}�N����`
#define GAME_TITLE	"�Q�[���^�C�g��"//�Q�[���^�C�g��
#define GAME_WIDTH	1280//�Q�[����ʂ̕��i�E�B�h�X�j
#define GAME_HEIGHT 720//�Q�[����ʍ����i�n�C�g�j
#define GAME_COLOR 32//�Q�[���̐F��

#define GAME_ICON   333

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

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

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
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}