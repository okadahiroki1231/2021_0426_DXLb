//FPS�̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"
#include "FPS.h"

//�O���[�o���ϐ�
FPS fps; //FPS�̊Ǘ�

///
///FPS�l���v�����A�l���X�V����
/// 
/// 
VOID FPSUpdate(VOID)
{
	//��ԍŏ��̏���
	if (fps.IsInitFlg == FALSE)
	{
		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.StartTime = GetNowHiPerformanceCount();//windows���N�����Ă���o�߂�������

		fps.IsInitFlg = TRUE; //�t���O�𗧂Ă�

	}

	//���݂̎������}�C�N���b�P�ʂŎ擾
	fps.NowTime = GetNowHiPerformanceCount();

	//�O��擾�������Ԃ���̌o�ߎ��Ԃ�b�i����)�ɕϊ����Ă���Z�b�g
	fps.DeltaTime = (fps.NowTime - fps.OldTime) / 1000000.0f;

	//����擾�������Ԃ�ۑ�
	fps.OldTime = fps.NowTime;

	//1�t���[���ځ`FPS�ݒ�l�Ƃ܂ŃJ�E���g�A�b�v
	if (fps.Count < fps.SamplcRate)
	{
		//�J�E���^�𑝂₷
		fps.Count++;
	}
	else
	{
		//FPS�ݒ�l�̃t���[���ŁA����FPS���v�Z

		//���݂̎�������A0�t���[���ڎ��Ԃ������AFPS�̐��l�Ŋ���
		//���݂̕���FPS�l���o��
		fps.DrawValuc = 1000000.f / ((fps.NowTime - fps.StartTime) / (float)fps.SamplcRate);

		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.StartTime = GetNowHiPerformanceCount();//Windows���N�����Ă���o�߂�������

		//�J�E���^������
		fps.Count = 1;

	}

	return;
}
///
///����FPS�l��`�悷��
/// 
/// 
VOID FPSDraw(VOID)
{
	//�������`��
	DrawFormatString(0, 20, GetColor(0, 0, 0), "FPS:%.lf", fps.DrawValuc);

	return;
}

///
///FPS�ŏ�����҂�
/// 
/// 
VOID FPSWait(VOID)
{
	//���݂̎����[�ŏ��̎����ŁA���݂������Ă��鎞�����擾����
	LONGLONG resultTime = fps.NowTime - fps.StartTime;

	//�҂ׂ��~���b���@(1�b/FPS�l * ���݂̃t���[�����j����A���݂������Ă��鎞��������
	int waitTime = 1000000.0f / fps.Value * fps.Count - resultTime;

	//�}�C�N���b����~���b�ɕϊ�
	waitTime /= 1000.0f;
	//���������������珈����҂�
	if (waitTime > 0)
	{
		WaitTimer(waitTime); //�����~���b�҂�
	}

	//����������OFF�ɂ��Ă��邩�H
	if (GetWaitVSyncFlag() == FALSE)
	{

		//FPS�ő�l�ł͂Ȃ��Ƃ�
		if (fps.Value < GAME_FPS_MAX)
		{

			//�P�b����FPS�l�����A�҂��Ԃ��������Ƃ��́A������FPS�l�������Ă�����
			//�҂��ԁ@10�~���@�����@1�b/60FPS�@���@16.6666�~���@�������������ł���
			if (waitTime > 0
				&& waitTime <= 1000.0f / fps.Value)
			{
				fps.Count++;
			}
			else
			{
				//FPS�l���ǂ����Ă��炸�A�x���Ƃ���FPS�l��������
				if (fps.Value > GAME_FPS_MIN)
				{
					fps.Value--;
				}
			}
		}
	}
	return;
}