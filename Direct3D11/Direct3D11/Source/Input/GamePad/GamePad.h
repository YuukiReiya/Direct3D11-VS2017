/*
	@file	GamePad.h
	@brief	�Q�[���p�b�h����
	@date	2018/04/24
	@detail	XInput��p��������
			XInput�Q�l:		http://www.geocities.jp/gameprogrammingunit/xinput/index.html
			�񋓑̂̒���:	http://d.hatena.ne.jp/mclh46/20100627/1277603928
	@author	�ԏ� �G�P
*/#pragma once
#include <windows.h>
#include <Xinput.h>
#include <DirectXMath.h>

#pragma comment(lib, "XInput.lib")

/*!
	@brief	���O���
*/
namespace KeyCode {
	/*! �񋓑̃L�[�R�[�h */
	enum Button		{ A, B, X, Y, START, BACK, LB, RB, L_STICK, R_STICK, };	/*!< �{�^�� */
	enum Trigger	{ LT, RT };												/*!< �g���K�[ */
	enum JoyStick	{ LEFT, RIGHT };										/*!< �W���C�X�e�B�b�N */
	enum Arrow		{ VERTICAL, HORIZONTAL };								/*!< V:�c H:�� */
}

/*!
	@brief	�Q�[���p�b�h�N���X
	@detail	XBOX�R���g���[���[�̓��͐���N���X
*/
class GamePad {
public:
	/*! �R���g���[���[�ԍ� */
	enum Index { One, Two, Three, Four, };

	explicit GamePad();
	explicit GamePad(Index&& index);
	~GamePad();


	/*! �֐� */
	void Update();
	bool GetButton(KeyCode::Button button);
	bool GetButtonDown(KeyCode::Button button);
	bool GetButtonUp(KeyCode::Button button);
	int GetArrow(KeyCode::Arrow arrow);
	int GetArrowDown(KeyCode::Arrow arrow);
	int GetArrowUp(KeyCode::Arrow arrow);
	DirectX::XMFLOAT3 GetJoyStick(KeyCode::JoyStick joyStick);
	BYTE GetTrigger(KeyCode::Trigger trigger);
	bool GetBTrigger(KeyCode::Trigger trigger);
	void SetVibration(int leftPower, int rightPower = -1);
private:
	float InputNormalize(float input);
	float InputRound(float input);
	int VibrationConvertPower(int vibration);
	int ConvertKeyButtonCode(KeyCode::Button&& button);
	DirectX::XMINT2 ConvertKeyArrowCode(KeyCode::Arrow&& arrow);

	/*! �萔 */
	static const int c_JoyStickInputMin;
	static const int c_JoyStickInputMax;
	static const int c_JoyStickInputPrecision;
	static const int c_VibrationRange;
	static const float c_JoyStickInputDead;

	/*! �p�����[�^�[ */
	Index index;			/*!< �R���g���[���[�ԍ� */
	XINPUT_STATE now,old;	/*!< ���̓o�b�t�@ */

};