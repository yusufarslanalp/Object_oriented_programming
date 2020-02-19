#ifndef File_H
#define File_H

#include "Window.h"
#include <iostream>
#include <string>
#include <vector> 
#include <typeinfo>
#include <fstream>

using namespace std;

class File : public Window
{
	public:
		File():
			Window()
		{	}

		File( string new_name ): //soldaki constructor çalıştırıldığında "new_name" daında bir File objesi oluşturulur. ve bu next'i NULL olur.
			Window( new_name )
		{	}

		virtual void foo(){};

		private:

};

#endif
