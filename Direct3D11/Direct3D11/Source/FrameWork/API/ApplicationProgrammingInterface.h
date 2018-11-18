/*
	@file	A(pplication)P(rogramming)I(nterface).h
	@date	2018/11/17
	@author	番場 宥輝
	@brief	自作API用のインターフェイス
*/
#pragma once

/*! API用の名前空間 */
namespace API {

	__interface IAPI 
	{
		long Initialize();	/*< イニシャライズ */
		void Finalize();	/*< ファイナライズ */
	};

}