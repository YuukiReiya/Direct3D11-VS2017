/*
	@file	A(pplication)P(rogramming)I(nterface).h
	@date	2018/11/17
	@author	�ԏ� �G�P
	@brief	����API�p�̃C���^�[�t�F�C�X
*/
#pragma once

/*! API�p�̖��O��� */
namespace API {

	__interface IAPI 
	{
		long Initialize();	/*< �C�j�V�����C�Y */
		void Finalize();	/*< �t�@�C�i���C�Y */
	};

}