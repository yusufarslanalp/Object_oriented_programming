#ifndef Dir_H
#define Dir_H

#include "Window.h"
#include <iostream>
#include <string>
#include <vector> 
#include <typeinfo>
#include <fstream>

using namespace std;

class Dir : public Window
{
	public:
		Dir():
			Window(), sub_window( NULL )
		{	}

		Dir( string new_name ):
			Window( new_name ), sub_window( NULL )
		{	}

		Window * get_sub_window()const{ return sub_window; } // get_sub_window() bir accessor fonksiyonu olduğu için const olarak tanımlanmıştır.
		void set_sub_window( Window * new_adress ){ sub_window = new_adress; }

		void set_prew_dir_adress( Dir * adress ){ prew_dir_adress = adress; }
		Dir * get_prew_dir_adress()const { return prew_dir_adress; } // get_prew_dir_adress() bir accessor fonksiyonu olduğu için const olarak tanımlanmıştır.

		virtual void foo(){};

	private:
		Window * sub_window; // Bu adress değişkeni bir alt klasördeki Window'un adresini tutar. *sub_window base class tipinde olduğu için:
								//Bir Dir adreside File adreside tutabilir.
		Dir * prew_dir_adress;	//cd.. komutunda bir önceki adresin konumuna rahatlıkla ulaşabilmek için tüm Dir objeleri bir üst klasörün adresini saklamaktadır.
};

#endif
