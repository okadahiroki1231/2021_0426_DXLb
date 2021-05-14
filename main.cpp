//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"//dxLib���g���Ƃ��͕K���K�v

#include "keyboard.h"//�L�[�{�[�h�̏���

//�}�N����`
#define GAME_TITLE	"�Q�[���^�C�g��"//�Q�[���^�C�g��
#define GAME_WIDTH	1280//�Q�[����ʂ̕��i�E�B�h�X�j
#define GAME_HEIGHT 720//�Q�[����ʍ����i�n�C�g�j
#define GAME_COLOR 32//�Q�[���̐F��

#define GAME_ICON_ID 333

#define GAME_WINDOW_BAR 0

//�񋓌^
enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};//�Q�[���̃V�[��

//�V�[�����Ǘ�����ϐ�
GAME_SCENE GameScene;//���݂̃Q�[���̃V�[��
GAME_SCENE OldGameScene;//�O��̃Q�[���̃V�[��
GAME_SCENE NextGameScene;//���̃Q�[���̃V�[��

//��ʂ̐؂�ւ�
BOOL IsFadeOut = FALSE;
BOOL IsFadeIn = FALSE;

int fadeTimeMill = 2000;//�؂�ւ��~���b
int fadeTimeMax = fadeTimeMill / 1000 * 60;//�~���b���t���[���b�ɕϊ�

//�t�F�[�h�A�E�g
int fadeOutCntInit = 0; //�����l
int fadeOutCnt = fadeOutCntInit;//�t�B�[�h�A�E�g�̃J�E���^
int fadeOutCntMax = fadeTimeMax; //�t�B�[�h�A�E�g�̃J�E���^MAX

//�t�F�[�h�C��
int fadeInCntInit = fadeTimeMax; //�����l
int fadeInCnt = fadeInCntInit;//�t�B�[�h�C���̃J�E���^
int fadeInCntMax = fadeTimeMax; //�t�B�[�h�C���̃J�E���^MAX

//�v���g�^�C�v�錾
VOID Title(VOID);    //�^�C�g�����
VOID TitleProc(VOID);//�^�C�g�����(����)
VOID TitleDraw(VOID);//�^�C�g�����(�`��)

VOID Play(VOID);    //�v���C���
VOID PlayProc(VOID);//�v���C���(����)
VOID PlayDraw(VOID);//�v���C���(�`��)

VOID End(VOID);    //�G���h���
VOID EndProc(VOID);//�G���h���(����)
VOID EndDraw(VOID);//�G���h���(�`��)

VOID Change(VOID);    //�؂�ւ����
VOID ChangeProc(VOID);//�؂�ւ����(����)
VOID ChangeDraw(VOID);//�؂�ւ����(�`��)

VOID ChangeScene(GAME_SCENE scene);//�V�[���؂�ւ�


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

	SetDrawScreen(DX_SCREEN_BACK);

	//�~�̒��S�_
	int X = GAME_WIDTH / 2;
	int Y = GAME_HEIGHT / 2;
	//�~�̔��a
	int radius = 50;

	//�ŏ��̃V�[���́A�^�C�g����ʂ���
	GameScene = GAME_SCENE_TITLE;

	//�������[�v
	while (1)
	{


		//���b�Z�[�W���󂯎�葱����
		if (ProcessMessage() != 0) { break; }//���b�Z�[�W���󂯎�葱����
		if (ClearDrawScreen() != 0) { break; }//��ʂ���������

		//�L�[�{�[�h���͂̍X�V
		AllKeyUpdate();

		//ESC�L�[�ŋ����I��
		if (KeyClick(KEY_INPUT_ESCAPE) == TRUE) { break; }

		//�ȑO�̃V�[�����擾
		if (GameScene != GAME_SCENE_CHANGE)
		{
			OldGameScene = GameScene;
		}

		//�V�[�����Ƃɏ������s��
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
		
	

		//�V�[����؂�ւ���
		if (OldGameScene != GameScene)
		{
			//���݂̃V�[�����؂�ւ���ʂłȂ��Ƃ�
			if (GameScene != GAME_SCENE_CHANGE)
			{
				NextGameScene = GameScene;//���̃V�[����ۑ�
				GameScene = GAME_SCENE_CHANGE;//��ʐ؂�ւ��V�[���ɕς���
			}
		}

		//�L�[����
		if (KeyDown(KEY_INPUT_UP) == TRUE)
		{
			Y--;//��Ɉړ�
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
		
		ScreenFlip();//�_�u���o�b�L���O������ʂ�`��
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
	VOID ChangeScene(GAME_SCENE scene)
	{
		GameScene = scene;//�V�[���̐؂�ւ�
		IsFadeIn = FALSE;//�t�B�[�h�C�����Ȃ�
		IsFadeOut = TRUE;//�t�B�[�h�A�E�g����
}
///<summary>
/// �^�C�g�����
///</summary>
VOID Title(VOID)
{
	TitleProc();//����
	TitleDraw();//�`��

	return;
}
///
/// �^�C�g����ʂ̏���
/// 
VOID TitleProc(VOID)
{
	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//�V�[���؂�ւ�
		//���̃V�[���̏������������ōs���Ɗy

		//�v���C��ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_PLAY);
	}
	
	return;
}
///
///�^�C�g����ʂ̕`��
/// 
VOID TitleDraw(VOID)
{
	DrawString(0, 0, "�^�C�g�����", GetColor(0, 0, 0));
	return;

}

///<summary>
/// �v���C���
///</summary>
VOID Play(VOID)
{
	PlayProc();//����
	PlayDraw();//�`��

	return;
}
///
/// �v���C��ʂ̏���
/// 
VOID PlayProc(VOID)
{

	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//�V�[���؂�ւ�
		//���̃V�[���̏������������ōs���Ɗy

		//�G���h��ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_END);
	}
	return;
}
///
///�v���C��ʂ̕`��
/// 
VOID PlayDraw(VOID)
{
	DrawString(0, 0, "�v���C���", GetColor(0, 0, 0));
	return;
}


///<summary>
/// �G���h���
///</summary>
VOID End(VOID)
{
	EndProc();//����
	EndDraw();//�`��

	return;
}
///
/// �G���h��ʂ̏���
/// 
VOID EndProc(VOID)
{

	if (KeyClick(KEY_INPUT_RETURN) == TRUE)
	{
		//�V�[���؂�ւ�
		//���̃V�[���̏������������ōs���Ɗy

		//�^�C�g����ʂɐ؂�ւ�
		ChangeScene(GAME_SCENE_TITLE);
	}
	return;
}
///
///�G���h��ʂ̕`��
/// 
VOID EndDraw(VOID)
{
	DrawString(0, 0, "�G���h���", GetColor(0, 0, 0));
	return;
}


///<summary>
/// �؂�ւ����
///</summary>
VOID Change(VOID)
{
	ChangeProc();//����
	ChangeDraw();//�`��

	return;
}
///
/// �؂�ւ���ʂ̏���
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
///�؂�ւ���ʂ̕`��
/// 
VOID ChangeDraw(VOID)
{
	//�ȑO�̃V�[����`��
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		TitleDraw();//�^�C�g����ʂ̕`��
		break;
	case GAME_SCENE_PLAY:
		PlayDraw();//�v���C��ʂ̕`��
		break;
	case GAME_SCENE_END:
		EndDraw();//�G���h��ʂ̕`��
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


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);//0�`255
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "�؂�ւ����", GetColor(0, 0, 0));
	return;
}

