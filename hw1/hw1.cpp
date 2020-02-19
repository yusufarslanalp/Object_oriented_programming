#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

double
recursive( string object );

int
find_size_of_ojects( string line ); // öernek olarak line stringi "1*lastik+1*jant" olduğunda lastik ve jant olmak üzere toplamda iki çeşit obje vardır ve 
// find_size_of_ojects() fonksiyonu 2 değerini return eder.

void
remove_space( string& line ); // parametre olarak aldığı line stringinin tüm space karakterlerini line stringinden siler.


// token_line fonksiyonu kullanıcıdan alınan nesneye ait parçaları "coefficient" ve "sub_objects" arraylerine dağıtır.
// öernek olarak kullanıcıya teker nedir diye sorulduğunda kullanıcı "1*lastik+1*jant" olarak cevap veriyorsa "lastik" stringi sub_objects[0] dizisine ve lastiğin kat sayısıolan 
// 1 tamsayısı coefficient[0] dizisine konulur. Aynı şekilde 1 * jant dizisinde "jant" stringi  sub_objects[1] dizisine konulurken jantın katsayyısı olan 1 tamsayısı coefficient[1]
// dizisine konulur.
void
token_line( string line, int coefficient[], string sub_objects[], int size_of_sub_objects  );

int
is_price( string line ); //bu fonksiyon line stringi bir fiyat olduğunda 1 değeri return eder bir string olduğunda 0 return eder.


int
main( void )
{
	
	string object;
	cout << "Define the object: " << endl;
	getline( cin, object );
	cout << fixed << setprecision(1);
	double res = recursive( object );
	cout << "Total cost of " << object << " is " << res << endl;
	return 0;
}


double
recursive( string object )
{
	double result = 0.0;
	string line="";
	int coefficient[25];
	string sub_objects[25];
	int size_of_sub_objects;
	int i;

	cout << "what is " << object << "?:" << endl;
	getline( cin, line );
	remove_space( line );
	
	if( is_price( line ) == 1 )
	{
		return atof( line.c_str() );
	}

	else
	{
		size_of_sub_objects = find_size_of_ojects( line );
		token_line( line, coefficient, sub_objects, size_of_sub_objects  );

		for( i = 0; i < size_of_sub_objects; ++i )
		{
			result += ( coefficient[i] * recursive( sub_objects[i] ) );
		}	

		return result;
	}
}

int
find_size_of_ojects( string line )
{
	int size_of_objects = 1;
	int i;

	for( i = 0; i < line.size(); ++i )
	{
		if( line[i] == '+' ) ++size_of_objects;
	}

	return size_of_objects;
}

void
remove_space( string& line )
{
	int i,j=0;
	string temp;

	for( i = 0; i < line.size(); i++ )
	{
		if( line[i] != ' ' )
		{
			temp += line[i];
			++j;
		}
	}

	line = temp;
}


void
token_line( string line, int coefficient[], string sub_objects[], int size_of_sub_objects  )
{
	string str_for_int;
	int i;
	int j;

	for( i = 0; i < size_of_sub_objects ; ++i  )
	{
		for( j = 0; line[j] != '*'; j++ )
		{
			str_for_int += line[j];
		}

		coefficient[i] = atoi( str_for_int.c_str() );
		str_for_int.clear();
		line.erase( 0, (line.find( "*" ) + 1) );

		if( line.find( "+" ) != string::npos )
		{
			sub_objects[i] = line.substr( 0, line.find( "+" ) );
			line.erase( 0, ( line.find( "+" ) + 1 ) );
		}		

		else sub_objects[i] = line.substr( 0, line.size() );
	}
}

int
is_price( string line ) //bu fonksiyon line stringi bir fiyat olduğunda 1 değeri return eder.
{
	int i;
	for( i = 0; i < line.size(); ++i ) if( line[i] == '*' ) return 0;

	return 1;
}	



