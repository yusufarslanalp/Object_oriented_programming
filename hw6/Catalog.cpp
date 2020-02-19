//Yusuf Abdullah ARSLANALP 151044046
#include "Catalog.h"

Catalog::Catalog( string input_file )
{
	specify_catalog_type( input_file );
	read_input_file( input_file );

	cout << "Catalog Read: " << catalog_name << endl;
	clear_lines();
	read_command( "commands.txt" );		
}


// data.txt dosyasının ilk satırını alır. aldığı satırdaki katalog ismine göre private member'lar olan catalog_name'i ve catalo_tags<> vektörünü doldurur.
//böylelikle tek bir programla tüm katalog türleri işlenmiş olur( program genelleştirilmiş olur. ). 
void
Catalog::specify_catalog_type( string file_name )
{
	string book_format = "<title> <authors> <year> <tags>";
	string music_format = "<title> <artists> <year> <genre>";
	string movie_format = "<title> <director> <year> <genre> <starring>";	


	const char * char_ptr_file_name = file_name.c_str();
	string line;
	ifstream cin_from_file;
	cin_from_file.open( char_ptr_file_name );
	if (cin_from_file.is_open())
	{
		getline(cin_from_file, line);
	}

	if( line.find( "book" ) != string::npos )
	{
		catalog_name = "book";
		get_format( book_format );
	}

	else if( line.find( "music" ) != string::npos )
	{
		catalog_name = "music";
		get_format( music_format );
	}

	else if( line.find( "movie" ) != string::npos )
	{
		catalog_name = "movie";
		get_format( movie_format );
	}

	else cout << "undefined catalog!" << endl;
}


//Exeption Handling'in kullanıldığı diğer fonksiyon bu fonksiyondur. Bu fonksiyona commands.txt dosyaında bulunan komutlar read_command() fonksiyonu tarafından verilir.
//bu fonksiyonda satır olarak aldığı komutu gerçekleştirir. Eğer bir hata varsa bunun tespitini yapar.
void
Catalog::token_command( string command )
{
	string word;
	string tag;
	string token;
	string back_up = command;

	try
	{
		if( command.find( '"' ) != string::npos )
		{
			
			if( command.find("search") != string::npos )
			{
				command.erase( 0, command.find('"')+1 );
				word = command.substr( 0, command.find('"') );
			
				command.erase( 0, command.find('"')+1 );
				command.erase( 0, command.find('"')+1 );
				tag = command.substr( 0, command.find('"') );

				if( find_place_of_tag(tag) < 0 ) throw 10; //command is wrong.
				else  				
				{
					cout << back_up << endl;
					search( find_place_of_tag(tag), word );			
				}
			}

			else if( command.find("sort") != string::npos )
			{
				command.erase( 0, command.find('"')+1 );
				tag = command.substr( 0, command.find('"') );
				sort_index = find_place_of_tag(tag);
				sort (lines.begin() , lines.end(), *this ); //SORT FONKSİYONUNUN KULLANILDIĞI YER
				cout << back_up << endl;
				print_lines();
			}
			else throw 10; //command is wrong.
		}
	}
	catch(int x){ cout << "Exception: command is wrong" << endl << back_up << endl; }
}


//command.txt dosyasından komutları okur ve komutları gerçekleştirir.
void
Catalog::read_command( string file_name )
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
			token_command( line );
		}
	}	
}


////<type> , <year> gibi bir katalog etiketinin adını string olarak alır. aldığı etiket eğer catalog_tags<> vektöründe varsa etiketin catalog_tags vektöründe
//bulunduğu index'i return eder. aldığı etiket eğer catalog_tags<> vektöründe yoksa -1 return eder.
int
Catalog::find_place_of_tag( string word )
{
	for( int i = 0; i < catalog_tags.size(); i++ )
	{
		if( catalog_tags[i].find(word) != string::npos ) return i;
	}
	return -1;
}


//word parametresi ile aldığı string'in bulunduğu satırları bulur ve ekrana basar ( veya dosyaya yazar. ).
void
Catalog::search( int tag_num, string word )
{
	for( int i = 0; i < lines.size(); i++ )
	{
		if( lines[i][tag_num].find(word) != string::npos )
		{
			for( int j = 0; j < lines[i].size(); j++ ) cout << '"' << lines[i][j] << '"' << " ";
			cout << endl;
		}
	}
}


//lines<> vectörünü kullanarak hatalı satırların silinme işlemini gerçekleştirir. Exeption Handling'in kullanıldığı iki fonksiyondan biri bu fonksiyondur.
//Missing field ve Duplicate entry hatalarının tespit edildiği ve hataların bildirildiği fonksiyon bu fonksiyondur.
void
Catalog::clear_lines()
{
	int i,j;

	for( i = 0; i < lines.size(); i++ )
	{
		try
		{
			if( lines[i].size() != catalog_tags.size() ) throw 1;
			else
			{
				for( j = i-1 ; j >= 0; j-- )
				{
					if( lines[i][0] == lines[j][0] ) throw 2;
				}
			}
		}
		catch( int x )
		{
			if (x == 1) cout << "Exception: missing field" << endl;
			else if( x == 2 ) cout << "Exception: duplicate entry" << endl;
			for( j = 0; j < lines[i].size(); j++ ) cout << '"' << lines[i][j] << '"' << " ";
			cout << endl;
			lines.erase( lines.begin()+i );
			i--;
		}
	}
	cout << lines.size() << " unique entries" << endl;
}


//read_input_file() fonksiyonunun içerisinde yer alır. read_input_file() fonksiyonun data dosyasından okuduğu satırı parçalar ve lines vektörüne doldurur.
void
Catalog::token_line( string line )
{
	string token;
	if( line.find( '"' ) != string::npos )
	{
		lines.push_back( vector<string>() );		

		while( line.find( '"' ) != string::npos )
		{
			line.erase( 0, line.find( '"' ) + 1 );
			token = line.substr( 0, line.find( '"' ) );
			lines[ lines.size() -1 ].push_back( token );
			line.erase( 0, line.find( '"' ) +1 );
		}	
	}
}


//data.txt dosyasını satır satır okur. okuduğu her satırı çift tırnak(") işaretine göre parçalayarak lines<> vektörüne doldurur.
void
Catalog::read_input_file( string file_name )
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


int
Catalog::check_errors(ifstream* f)
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


//string olarak aldığı katalog formatını parçalara böler ve private vektör olan "catalog_tags" Vektörüne doldurur.
void
Catalog::get_format( string catalog_format )
{
	string token;
	catalog_format += " ";

	while( catalog_format.find( "<" ) != string::npos )
	{
		token = catalog_format.substr( 0, catalog_format.find( " " ) );
		catalog_tags.push_back( token );
		catalog_format.erase( 0, catalog_format.find( " " ) + 1 );		
	}
}


// lines<> vektörünün tüm satırlarını ekrana basar.
void
Catalog::print_lines()
{
	for( int i = 0; i < lines.size(); i++ )
	{
		for( int j = 0; j < lines[i].size(); j++ )
		{
			cout << '"' << lines[i][j] << '"' << " ";
		}
		cout << endl; 
	}
}

