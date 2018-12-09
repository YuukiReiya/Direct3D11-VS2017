/*
	@file	Camera.h
	@date	2018/04/22
	@author	�ԏ� �G�P
	@brief	�J����
	@detail	�V���O���g��
*/
#pragma once
#include <DirectXMath.h>
#include "../Singleton/Singleton.h"

/****************************************/
/*			�J�����̕`���(v)			*/
/*		NearClip <= v < FarClip			*/
/*	Ex)									*/
/*	NearClip = 0.1f, FarClip = 100.0f	*/
/*	�`�悳���I�u�W�F�N�g�̓J�����̎�	*/
/*	�_+NearClip����J�����̎��_+FarClip */
/*	�͈̔͂Ɏ��܂��Ă�����̂�`�悷��	*/
/****************************************/

class Camera
	:public Singleton<Camera>
{
public:

	/*!
		@brief	�f�X�g���N�^
	*/
	~Camera();

	/*!
		@fn			�C�j�V�����C�Y
		@brief		������
		@param[in]	���_
		@param[in]	�����_
		@param[in]	������x�N�g��
	*/
	void Initialize(
		DirectX::XMFLOAT3 eyePt,
		DirectX::XMFLOAT3 lookPt = { 0.0f,0.0f,0.0f },
		DirectX::XMFLOAT3 upVec = c_UpVector
	);

	static const double		c_Pi;				/*!< �~������ */
	static const float		c_FieldOfView;		/*!< ��p */
	static const float		c_NearClip;			/*!< �f�t�H���g�N���b�s���O����:�� */
	static const float		c_FarClip;			/*!< �f�t�H���g�N���b�s���O����:�� */
	static const DirectX::XMFLOAT3 c_UpVector;	/*!< �f�t�H���g�̏�����x�N�g�� */

	/*!
		@fn		�r���[�s��̃Q�b�^�[
		@brief	�r���[�s��̎擾
		@return	�r���[�s��
	*/
	DirectX::XMMATRIX GetViewMatrix()const { return m_ViewMat; }

	/*!
		@fn		�v���W�F�N�V�����s��̃Q�b�^�[
		@brief	�v���W�F�N�V�����s��̎擾
		@return	�v���W�F�N�V�����s��
	*/
	DirectX::XMMATRIX GetProjMatrix()const { return m_ProjMat; }

	/*!
		@fn		���_�ʒu�̃Q�b�^�[
		@brief	���_�ʒu�̎擾
		@return	���_�ʒu
	*/
	DirectX::XMFLOAT3 GetEyePt()const;

	/*!
		@fn		�����_�̃Q�b�^�[
		@brief	�����_�̎擾
		@return	�����_
	*/
	DirectX::XMFLOAT3 GetLookAtPt()const;

	/*!
		@fn			FOV�̃Z�b�g
		@brief		����p�̐ݒ�
		@param[in]	FOV�̐ݒ�l
	*/
	void SetFieldOfView(float fov)	{ m_FieldOfView = fov; }

	/*!
		@fn			�ߋ����N���b�v�̃Z�b�g
		@brief		�N���b�v����:�߂̐ݒ�
		@param[in]	�ߋ����N���b�v�̐ݒ�l
	*/
	void SetNearClip(float nearClip){ m_NearClip = nearClip; }

	/*!
		@fn			�������N���b�v�̃Z�b�g
		@brief		�N���b�v����:���̐ݒ�
		@param[in]	�������N���b�v�̐ݒ�l
	*/
	void SetFarClip(float farClip)	{ m_FarClip = farClip; }

private:
	/*!
		@brief	�R���X�g���N�^
	*/
	Camera();

	/*!
		@brief	�V���O���g���f�U�C���p�^�[���̃e���v���[�g�p��
	*/
	friend class Singleton<Camera>;

	/*! �ϐ� */
	float m_FieldOfView;			/*!< ����p */
	float m_NearClip;				/*!< �f�t�H���g�̃N���b�s���O����:�� */
	float m_FarClip;				/*!< �f�t�H���g�̃N���b�s���O����:�� */
	DirectX::XMVECTOR m_EyePt;		/*!< ���_�ʒu */
	DirectX::XMVECTOR m_LookAtPt;	/*!< �����_ */
	DirectX::XMVECTOR m_UpVec;		/*!< ������x�N�g�� */
	DirectX::XMMATRIX m_ViewMat;	/*!< �r���[�s�� */
	DirectX::XMMATRIX m_ProjMat;	/*!< �v���W�F�N�V�����s�� */
};

