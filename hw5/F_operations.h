#ifndef F_operation_H
#define F_operation_H

#include "Window.h"
#include "File.h"
#include "Dir.h"
#include <iostream>
#include <string>
#include <vector> 
#include <typeinfo>
#include <fstream>

using namespace std;

class F_operarions
{
	public:
		F_operarions( string new_input_file );
		int check_errors(ifstream* f);
		void read_input_file( string file_name );
		void read_command_file( string file_name );
		void token_line( string line );
		string find_root(); // input dosyasından root klasörünün ismini bulup return eden fonksiyondur.
		void create_list(Window * start);
		Window * create_path( string dir_name );
		void print_list( Window * start, string path );
		void add_path( Window * current, Window * new_path, Window * prew );
		bool is_there( string name );
		void fill_commands( string line );
		void cd_double_dot();
		void cd_slash();
		void cd_to_dir( string dir_name  );
		void process_commands();
		void add_sub_window( Window * new_window );
		void remove_hold( Dir* up_dir_of_hold, Window * hold );
		Window * copy_list( Window * start ); //Linked list'te yer alan bir Dir veya File objesinin adresini alır. Aldığı objenin devamında olan tüm sub ve
												//next objeleri recursive olarak kopyalar. Kopyalanmış Sub Linked list'in adresini return eder.

	private:
		string input_file;
		string command_file;
		string output_file;
		vector< vector< string > > window_names; //input dosyasındaki klasör ve dosyaların kaydedildiği vektördür.
		vector< vector< string > > commands;	//commands.txt dosyasındaki komutların kaydedildiği vektördür.

		Window * root; //root klasörün adresinin tutulduğu pointer'dır.
		Dir * current;	//içinde bulunulan clasörün adresinin tutulduğu pointe'dır.
		
		
};

#endif
