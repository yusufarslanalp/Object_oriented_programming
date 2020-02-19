using namespace std;

#include "F_operations.h"

F_operarions::F_operarions( string new_input_file ):
			input_file( new_input_file )
		{
			string s;
			Dir *  temp;
			Dir *  path2;
			read_input_file( input_file );
			
			root = new Dir( Dir( find_root() ) );
			current = (Dir *)root;
			current -> set_prew_dir_adress( NULL );

			while( window_names.size() != 0 )
			{
				create_list( root );
			}

			read_command_file( "commands.txt" );
			process_commands();
			print_list( root, s );
		}



Window *
F_operarions::copy_list( Window * start )
{
	Window * copy;

	if( start == NULL ) return NULL;

	if(dynamic_cast<Dir*>(start) != NULL)
	{
		copy = new 	Dir( Dir( start -> get_name() ) );
		((Dir*)copy) -> set_sub_window( copy_list( ((Dir*)start) -> get_sub_window()) );
		copy -> set_next_window( copy_list( start -> get_next_window() ) );	
	}

	else
	{
		copy = new 	File( File( start -> get_name() ) );
		copy -> set_next_window( copy_list( start -> get_next_window() ) );	
	}

	return copy;
}




void
F_operarions::remove_hold( Dir* up_dir_of_hold, Window * hold ) 
{
	Window * iter;

	if( up_dir_of_hold -> get_sub_window() == hold )
	{
		up_dir_of_hold -> set_sub_window( hold -> get_next_window() );
	}

	else
	{
		iter = up_dir_of_hold -> get_sub_window();
		while(1)
		{
			if( iter -> get_next_window() == hold )
			{
				iter -> set_next_window( hold -> get_next_window() );
				break;
			}
		}
	}
	hold -> set_next_window( NULL );
}




void
F_operarions::add_sub_window( Window * new_window )
{
	Dir * iter;

	if( current -> get_sub_window() == NULL )
	{
		current -> set_sub_window( new_window );
	}

	else
	{
		iter = (Dir*)( current -> get_sub_window() )  ;

		while( 1 )
		{
			if( iter -> get_next_window() == NULL )
			{
				iter -> set_next_window( new_window );
				break;	
			}
			iter = (Dir*)( iter -> get_next_window() );
		}
	}
}


void
F_operarions::process_commands()
{
	int i,k;
	Dir * backup;
	Dir * up_dir_of_hold = current;
	Window * hold; // hold taşınacak dosya veya klasörün adresidir.
	Window * new_list;
	Dir * iter;
	Window * save_next;
	int place_of_switch;

	for( i = 0; i < commands.size(); i++ )
	{
		if( commands[i][0] == "cd" )
		{
			
			cd_to_dir( commands[i][1] );
		}

		else if( commands[i][0] == "cd.." )
		{
			cd_double_dot();
		}

		else if( commands[i][0] == "cd/" )
		{
			cd_slash();
		}

		else if( commands[i][0] == "move" )
		{
			backup = current;

			for( k = 0; k < commands[i].size(); k++ )
			{
				if( commands[i][k] == "switch" )
				{
					place_of_switch = k;
					break;
				}
			}		

			for( k = 1; k < place_of_switch ; k++ )
			{
				up_dir_of_hold = current;
				cd_to_dir( commands[i][k] );
			}

			hold = (Window *)current; // hold taşınacak dosya veya klasörün adresidir.
			current = backup;

			//cout << current -> get_name() << endl; ///////////
			for( k = place_of_switch +1; k < commands[i].size(); k++ )
			{
				cd_to_dir( commands[i][k] );
			}

			if( dynamic_cast<Dir*>(hold) != NULL ) ((Dir*)hold) -> set_prew_dir_adress( current );

			add_sub_window( hold );

			remove_hold( up_dir_of_hold, hold );
			current = backup;
		}

		else if( commands[i][0] == "copy" )
		{
			backup = current;

			for( k = 0; k < commands[i].size(); k++ )
			{
				if( commands[i][k] == "switch" )
				{
					place_of_switch = k;
					break;
				}
			}		

			for( k = 1; k < place_of_switch ; k++ )
			{
				up_dir_of_hold = current;
				cd_to_dir( commands[i][k] );
			}

			hold = (Window *)current; // hold copyalanacak dosya veya klasörün adresidir.
			current = backup;

			//cout << current -> get_name() << endl; ///////////
			for( k = place_of_switch +1; k < commands[i].size(); k++ )
			{
				cd_to_dir( commands[i][k] );
			}

			if( dynamic_cast<Dir*>(hold) != NULL ) ((Dir*)hold) -> set_prew_dir_adress( current );

			save_next = hold -> get_next_window();
			hold -> set_next_window( NULL );		
			new_list = copy_list( hold );
			hold -> set_next_window( save_next );
			add_sub_window( new_list );
			current = backup;
		}
	}
}

void
F_operarions::cd_double_dot()
{
	if( current -> get_prew_dir_adress() != NULL )
	{
		current = current -> get_prew_dir_adress();
	}
}

void
F_operarions::cd_slash()
{
	current = (Dir *)root;
}




void
F_operarions::cd_to_dir( string dir_name )
{
	Dir* temp;
	Window * w1;

	temp = (Dir *)(current -> get_sub_window());
	while( true )
	{
		if( temp -> get_name() == dir_name )
		{
			w1 = ( Window * )temp;
			current = ( Dir * )w1;
			break;
		}
		temp = ( Dir * )( temp -> get_next_window() );
		if( temp == NULL )
		{
			cout << "error" << endl;
			break;
		}
	}

}

bool
F_operarions::is_there( string name )
{
	int i;
	for( i = 0; i < window_names.size(); i++  )
	{
		if( window_names[i][0] == name ) return true;
	}
	return false;
}


int
F_operarions::check_errors(ifstream* f)
{
	int stop = 0;
	if (f->eof()) {
		stop = 0;
	}
	if (f->fail()) {
		stop = 1;
	}
	if (f->bad()) {
		stop = 1;
	}
	return stop;
}

void
F_operarions::read_input_file( string file_name )
{
	const char * char_ptr_file_name = file_name.c_str();
	string line;
	ifstream cin_from_file;
	cin_from_file.open( char_ptr_file_name );
	if (cin_from_file.is_open())
	{
		while(1)
		{
			getline(cin_from_file, line);
			if (check_errors(&cin_from_file))
			{
				break;
			}
			token_line( line );
		}
	}
}


void
F_operarions::read_command_file( string file_name )
{
	const char * char_ptr_file_name = file_name.c_str();
	string line;
	ifstream cin_from_file;
	cin_from_file.open( char_ptr_file_name );
	if (cin_from_file.is_open())
	{
		while(1)
		{
			getline(cin_from_file, line);
			if (check_errors(&cin_from_file))
			{
				break;
			}
			fill_commands( line );
		}
	}
}



void
F_operarions::fill_commands( string line )
{
	string token;
	string temp;
	commands.push_back( vector< string >() );

	token = line.substr( 0, line.find( " " ) );

	if( token == "cd" )
	{
		commands[ commands.size() ].push_back( token );
		line.erase( 0, line.find( " " ) + 1 );
		commands[ commands.size() -1 ].push_back( line );

	}

	else if( token == "cd.." )
	{
		commands[ commands.size() -1 ].push_back( token );
	}

	else if( token == "cd/" )
	{
		commands[ commands.size() ].push_back( token );
	}

	else if( token == "move" )
	{
		//cout << "geldi" << endl;
		commands[ commands.size() -1 ].push_back( token );
		line.erase( 0, line.find( " " ) + 1 );
		token = line.substr( 0, line.find( " " ) );
		line.erase( 0, line.find( " " ) + 1 );

		for( int i = 0; i < 2; i++ )
		{
			if( token[0] == '/' )
			{
				token.erase( 0, token.find( "/" ) + 1 );
				if( token.find( "/" ) == string::npos ) token.clear();
				else token.erase( 0, token.find( "/" ) + 1 );
			}

			if( token.find( "/" ) != string::npos )
			{
				while( token.find( "/" ) != string::npos )
				{
					temp = token.substr( 0, token.find( "/" ) );
					commands[ commands.size() - 1 ].push_back( temp );
					token.erase( 0, token.find( "/" ) + 1 );
				}			
				commands[ commands.size() - 1 ].push_back( token );
				commands[ commands.size() - 1 ].push_back( "switch" );
			}
		
			else
			{
				if( token.size() != 0 )commands[ commands.size() - 1 ].push_back( token );
				commands[ commands.size() - 1 ].push_back( "switch" );
			}
			token = line;
		}
		commands[ commands.size() -1 ].erase( commands[ commands.size() -1 ].end() );
	}

	else if( token == "copy" )
	{
		commands[ commands.size() -1 ].push_back( token );
		line.erase( 0, line.find( " " ) + 1 );
		token = line.substr( 0, line.find( " " ) );
		line.erase( 0, line.find( " " ) + 1 );

		for( int i = 0; i < 2; i++ )
		{
			if( token[0] == '/' )
			{
				token.erase( 0, token.find( "/" ) + 1 );
				if( token.find( "/" ) == string::npos ) token.clear();
				else token.erase( 0, token.find( "/" ) + 1 );
			}

			if( token.find( "/" ) != string::npos )
			{
				while( token.find( "/" ) != string::npos )
				{
					temp = token.substr( 0, token.find( "/" ) );
					commands[ commands.size() - 1 ].push_back( temp );
					token.erase( 0, token.find( "/" ) + 1 );
				}			
				commands[ commands.size() - 1 ].push_back( token );
				commands[ commands.size() - 1 ].push_back( "switch" );
			}
		
			else
			{
				if( token.size() != 0 )commands[ commands.size() - 1 ].push_back( token );
				commands[ commands.size() - 1 ].push_back( "switch" );
			}
			token = line;
		}
		commands[ commands.size() -1 ].erase( commands[ commands.size() -1 ].end() );
	}
}


void
F_operarions::token_line( string line ) //window names<> vektörünü doldurmak için kullanıldı.
{

	string token;

	if( line.find( "/" ) != string::npos ) //dosyadan alınan tüm satırlarda "/" karakteri olması gerektiği için "/" karakterinin olmadığı satırlar için işlem yapılmaz.
	{
		window_names.push_back( vector< string >() );

		while( line.find( "/" ) != string::npos )
		{
			token = line.substr( 0, line.find( "/" ) );
			window_names[ window_names.size() - 1 ].push_back( token );
			line.erase( 0, line.find( "/" ) + 1 );
		}
		window_names[ window_names.size() - 1 ].push_back( line ); //döngüden çıkıldıktan sonra line stringinde sadece dosya ismi kalmıştır.
	}

}

string
F_operarions::find_root()
{
	int row, i, j, place_of_root;

	for( row = 0; row < window_names.size(); row++ )
	{
		place_of_root = row;
		for( i = 0; i < window_names.size(); i++ )
		{
			for( j = 1; j < window_names[i].size(); j++ )
			{
				if( window_names[row][0] == window_names[i][j] )
				{
					place_of_root = -1;
				}
			}
		}
		if( place_of_root != -1 ) break;
	}

	return window_names[ row ][ 0 ];
}

void
F_operarions::create_list( Window * start )
{
	Dir * new_path;
	Dir* temp;
	if( start == NULL );

	else if( dynamic_cast<Dir *>( start ) != NULL )
	{
		temp = dynamic_cast<Dir *>( start );
		if( is_there( temp -> get_name() ) )
		{
			new_path = ( Dir * )create_path( temp -> get_name() );
			add_path( temp -> get_sub_window() , new_path -> get_sub_window() , temp );

		}
		else
		{
			create_list( temp -> get_sub_window() );
			create_list( temp -> get_next_window() );
		}

	}

	else
	{
		create_list( start -> get_next_window() );
	}
}


Window *
F_operarions::create_path( string dir_name )
{
	string name_of_prew;
	string s;
	Dir * start;
	Dir * iter;
	Dir * temp;
	int row;
	for( row = 0; row < window_names.size(); row++ )
	{
		if( window_names[row][0] == dir_name ) break;
	}

	//cout << "row: " << row << endl;

	start = new Dir( Dir( window_names[row][0] ) ); 
	window_names[row].erase( window_names[row].begin() );
	iter = start;

	while( window_names[row].size() != 1 )
	{
		iter -> set_sub_window( new Dir( Dir(window_names[row][0]) ) ); 

		temp =  (Dir * )( iter -> get_sub_window() );
		temp -> set_prew_dir_adress( iter );

		iter = dynamic_cast<Dir *>( iter -> get_sub_window()  );
		window_names[row].erase( window_names[row].begin() );
	}

	iter -> set_sub_window( new File( File(window_names[row][0]) ) ); 

	window_names.erase( window_names.begin() + row );

	//print_list( start, s ); ////



	return start;
	
	
}


void
F_operarions::print_list( Window * start, string path )
{



	Dir* temp;
	if( start == NULL );

	else if( dynamic_cast<Dir *>( start ) != NULL )
	{
		temp = dynamic_cast<Dir *>( start );
		path += start -> get_name();
		path += "/";

		print_list( temp -> get_sub_window(), path );
		path.erase( path.find( temp -> get_name() ) );
		print_list( temp -> get_next_window(), path );
	}

	else
	{
		cout << path << start -> get_name() << endl;
		print_list( start -> get_next_window(), path );
	}



}

void
F_operarions::add_path( Window * current, Window * new_path, Window * prew )
{
	Dir * t_prew = ( Dir * )prew;
	Dir * t_current = ( Dir * )current;
	Dir * t_new_path = ( Dir * )new_path;
	Window * iter;
	Window * prew_iter;


	if( current == NULL )
	{
		t_prew -> set_sub_window( t_new_path );
	}

	else if( t_current -> get_name() == t_new_path -> get_name() )
	{
		add_path( t_current -> get_sub_window(), t_new_path -> get_sub_window(), t_current );
	}

	else
	{
		iter = current -> get_next_window();
		prew_iter = current;

		while(1)
		{
			if( iter == NULL )
			{
				prew_iter -> set_next_window( new_path );
				break;
			}

			else if( iter -> get_name() == new_path -> get_name() )
			{
				add_path( iter, new_path, prew_iter );
				break;
			}

			else
			{
				prew_iter = iter;
				iter = iter -> get_next_window();
			}
		}
	}
}

