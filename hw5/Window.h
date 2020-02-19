#ifndef Window_H
#define Window_H

#include <iostream>
#include <string>
#include <vector> 
#include <typeinfo>
#include <fstream>

using namespace std;

/*
Bu class Dir ve File Class'larının base class'ıdır.

*/
class Window
{
	public:
		Window():
			next_window( NULL )
		{	}

		Window( string new_name ):
			name( new_name ), next_window( NULL )
		{	}

		string get_name()const{ return name; } // get_name() bir accessor fonksiyonu olduğu için const olarak tanımlanmıştır.
		Window * get_next_window()const{ return next_window; } //get_next_window() bir accessor fonksiyonu olduğu için const olarak tanımlanmıştır.
		void set_next_window( Window * new_adress ){ next_window = new_adress; }

		virtual void foo(){};

	private:
		string name;
		Window * next_window; //File ve Dir class'ları için next objesinin adresi tutulur. *next_window base class tipinde olduğu için: *next_window hem
								//File hemde Dir objesinin adreslerini tutabilir.  

};

#endif
