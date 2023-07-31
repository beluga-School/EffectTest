#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�w�Дԍ� ���O:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;	

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
	
	//�����`
	//���W
	int posX[10];
	int posY[10];
	
	//�~�̔��a
	int radius[10];

	//�~���Ƃ̌o�ߎ���
	int timer[10];
	//���̃^�C�}�[���N����Ԃ��m�F����t���O
	bool timerActive[10];

	//���̃^�C�}�[���n�܂鎞��
	int NextStartTime[10];
	
	//�^�C�}�[���~�܂鎞��
	const int MaxTime = 300; //60�t���[���z���5�b�ԓ���

	//�~�̔��a�̍ő�l
	const int MaxRadius = 600;

	//�傫���Ȃ鑬�x
	const int RadiusSpeed = 3;

	//�����ݒ�
	for (int i = 0; i < 10; i++)
	{
		//���S�ɂȂ�悤��
		posX[i] = WIN_WIDTH / 2;
		posY[i] = WIN_HEIGHT / 2;

		//0�ŏ�����
		radius[i] = 0;
		timer[i] = 0;
		timerActive[i] = false;
	}

	//�ׂ����ݒ肷��
	NextStartTime[0] = 10;
	NextStartTime[1] = 10;
	NextStartTime[2] = 10;
	NextStartTime[3] = 30;
	NextStartTime[4] = 30;
	NextStartTime[5] = 30;
	NextStartTime[6] = 50;
	NextStartTime[7] = 10;
	NextStartTime[8] = 90;
	NextStartTime[9] = 30;

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		if (keys[KEY_INPUT_SPACE])
		{
			//�^�C�}�[��������
			for (int i = 0; i < 10; i++)
			{
				timer[i] = 0;
				timerActive[i] = false;
			}

			//�ŏ��̃^�C�}�[���N��
			timerActive[0] = true;
		}

		//�^�C�}�[�̍X�V
		for (int i = 0; i < 10; i++)
		{
			//i��0���ƍ���̂ŏ��O����
			if (i != 0)
			{
				//�ЂƂO�̌o�߂����āA���̃^�C�}�[�𓮂���
				if (timer[i - 1] > NextStartTime[i])
				{
					timerActive[i] = true;
				}
			}

			//�N�����Ă��邩���m�F����
			if (timerActive[i])
			{
				//���Ԃ��ő厞�Ԃɂ܂��B���Ă��Ȃ��Ȃ�
				if (timer[i] < MaxTime)
				{
					//1�t���[�����Ƃ�1���Z
					timer[i] += 1;
				}
			}
			//�ő厞�ԂɒB���Ă���ꍇ�͎~�܂�
		}
		
		//���a�̍X�V
		for (int i = 0; i < 10; i++)
		{
			//�o�ߎ��Ԃɍ��킹�đ傫������
			radius[i] = timer[i] * RadiusSpeed;
		}

		// �`�揈��
		
		//�`�悷�邾��
		for (int i = 0; i < 10; i++)
		{
			DrawCircle(posX[i], posY[i], radius[i], 0xffffff, false);
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();	

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}