#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include "hw3.h"

int
main()
{
	int i;
	double x;
	ofstream out_file;
	out_file.open( "out.txt" );



	SparseVector v1( "input1.txt" );
	SparseVector v2( "input2.txt" );
	SparseVector v3;
	SparseVector v4;
	SparseVector v5;

	out_file << "v1" << endl << v1 << endl;
	out_file << "v2" << endl << v2 << endl;


	v3 = v1 + v2;
	out_file << "v3 = v1 + v2" << endl << "v3 = " << v3 << endl;
	x = v1.dot( v2 );
	out_file << "x = v1.dot( v2 ) = " << x << endl << endl;
	v4 = -v1;
	out_file << "v4 = -v1" << endl << "v4 = " << v4 << endl;

	v5 = v1 - v2;
	out_file << "v5 = v1 - v2" << endl << "v5 = " << v5 << endl;

	v5 = v4;
	out_file << "v5 = v4" << endl << "v5 = " << v5 << endl;


	SparseMatrix m1( "m1.txt" );
	SparseMatrix m2( "m2.txt" );
	SparseMatrix m4( "m4.txt" );
	SparseMatrix m3;
	SparseMatrix m5;

	out_file << "m1" << endl;
	out_file << m1 << endl;

	out_file << "m2" << endl;
	out_file << m2 << endl;

	m3 = m1 + m2;
	out_file << "m3 = m1 + m2" << endl << "m3 =" << endl << m3 << endl;

	m3 = m1 - m2;
	out_file << "m3 = m1 - m2" << endl << "m3 =" << endl << m3 << endl;

	out_file << "m4" << endl << m4 << endl;
	m5 = m4.transpose();
	out_file << "m5 = m4.transpose()" << endl << "m5 =" << endl << m5 << endl;

	m5 = -m4;
	out_file << "m5 = -m4" << endl << "m5 =" << endl << m5 << endl;
}

SparseMatrix::SparseMatrix()
{	}

SparseMatrix::SparseMatrix( string file_name )
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
			fill_matrix_line( line );
		}
	}
}

SparseMatrix
SparseMatrix::transpose()
{

	int i,place_row, place_col;
	SparseMatrix temp;


	create_new_line_num( temp.line_num );
	temp.place.push_back( vector<int>() );
	temp.number.push_back( vector<double>() );
	
	for( i = 0; i < temp.line_num.size(); i++ )
	{
		for( place_row = 0; place_row < place.size(); place_row++ )
		{
			for( place_col = 0; place_col < place[ place_row ].size(); place_col++ )
			{
				if( temp.line_num[i] == place[place_row][place_col] )
				{
					temp.place[i].push_back( line_num[ place_row ] );
					temp.number[i].push_back( number[place_row][place_col] );
				}
			}
		}
		temp.place.push_back( vector<int>() );
		temp.number.push_back( vector<double>() );
	}
	return temp;
}

void
SparseMatrix::create_new_line_num( vector<int>& new_line_num )
{
	int i,j, temp;
	for( i = 0; i < place.size(); ++i )
	{
		for( j = 0; j < place[i].size(); ++j )
		{
			new_line_num.push_back( place[i][j] );
		}
	}

	for( i = 0; i < new_line_num.size(); ++i )
	{
		for( j = (i+1) ; j < new_line_num.size(); j++  )
		{
			if( new_line_num[i] == new_line_num[j] )
			{
				new_line_num.erase( new_line_num.begin() + j );
				--j;
			}
		}
	}

	for( i = 0; i < new_line_num.size(); ++i )
	{
		for( j = i ; j < new_line_num.size(); j++  )
		{
			if( new_line_num[i] > new_line_num[j] )
			{
				temp = new_line_num[i];
				new_line_num[i] = new_line_num[j];
				new_line_num[j] = temp;
			}
		}
	}
}

const SparseMatrix
SparseMatrix::operator -()const
{
	int i,j;
	SparseMatrix temp;
	temp.line_num = line_num;
	temp.place = place;
	temp.number = number;

	for( i = 0; i < temp.number.size(); i++ )
	{
		for( j = 0; j < temp.number[i].size(); j++ )
		{
			temp.number[i][j] *= -1;
		}
	}
	return temp;
}

const SparseMatrix
SparseMatrix::operator -( SparseMatrix second_matrix )const
{
	SparseMatrix operand_one;
	SparseMatrix operand_two;

	operand_one.place = place;
	operand_one.number = number;
	operand_one.line_num = line_num;

	operand_two = -second_matrix;
	return ( operand_one + operand_two );
}

const SparseMatrix
SparseMatrix::operator +( const SparseMatrix& second_matrix )const
{
	SparseMatrix temp;
	int current_line_num_one = 0;
	int current_line_num_two = 0;
	int current_row_num_one = 0;
	int current_row_num_two = 0;

	while( current_line_num_one < line_num.size() || current_line_num_two < second_matrix.line_num.size() )
	{
		if( line_num[ current_line_num_one ] < second_matrix.line_num[ current_line_num_two ] )
		{
			temp.line_num.push_back( line_num[ current_line_num_one ] );
			temp.place.push_back( place[ current_line_num_one ] );
			temp.number.push_back( number[ current_line_num_one ] );
			current_line_num_one++;
		}

		else if( second_matrix.line_num[ current_line_num_two ] < line_num[ current_line_num_one ] )
		{
			temp.line_num.push_back( second_matrix.line_num[ current_line_num_two ] );
			temp.place.push_back( second_matrix.place[ current_line_num_two ] );
			temp.number.push_back( second_matrix.number[ current_line_num_two ] );
			current_line_num_two++;

		}

		else if( line_num[ current_line_num_one ] == second_matrix.line_num[ current_line_num_two ] )
		{
			temp.line_num.push_back( line_num[ current_line_num_one ] );
			temp.place.push_back( vector<int>() );
			temp.number.push_back( vector<double>() );
			current_row_num_one =  0;
			current_row_num_two = 0;
			while( current_row_num_one < place[ current_line_num_one ].size() ||
				   current_row_num_two < second_matrix.place[ current_line_num_two ].size() )
			{
				if( current_row_num_one == place[ current_line_num_one ].size() )
				{
					temp.place[ temp.place.size() -1 ].push_back( second_matrix.place[ current_line_num_two ][ current_row_num_two ] );
					temp.number[ temp.number.size() -1 ].push_back( second_matrix.number[ current_line_num_two ][ current_row_num_two ] );
					++current_row_num_two;
				}

				else if(  current_row_num_two == second_matrix.place[ current_line_num_two ].size() )
				{
					temp.place[ temp.place.size() -1 ].push_back( place[ current_line_num_one ][ current_row_num_one ] );
					temp.number[ temp.number.size() -1 ].push_back( number[ current_line_num_one ][ current_row_num_one ] );
					++current_row_num_one;
				}

				else if( place[ current_line_num_one ][ current_row_num_one ] < second_matrix.place[ current_line_num_two ][ current_row_num_two ] )
				{
					temp.place[ temp.place.size() -1 ].push_back( place[ current_line_num_one ][ current_row_num_one ] );
					temp.number[ temp.number.size() -1 ].push_back( number[ current_line_num_one ][ current_row_num_one ] );
					++current_row_num_one;
				}

				else if( second_matrix.place[ current_line_num_two ][ current_row_num_two ] < place[ current_line_num_one ][ current_row_num_one ] )
				{
					temp.place[ temp.place.size() -1 ].push_back( second_matrix.place[ current_line_num_two ][ current_row_num_two ] );
					temp.number[ temp.number.size() -1 ].push_back( second_matrix.number[ current_line_num_two ][ current_row_num_two ] );
					++current_row_num_two;
				}

				else if( place[ current_line_num_one ][ current_row_num_one ] == second_matrix.place[ current_line_num_two ][ current_row_num_two ] )
				{
					temp.place[ temp.place.size() -1 ].push_back( place[ current_line_num_one ][ current_row_num_one ] );

					temp.number[ temp.number.size() -1 ].push_back( number[ current_line_num_one ][ current_row_num_one ] +
																 	second_matrix.number[ current_line_num_two ][ current_row_num_two ] );
					current_row_num_one++;
					current_row_num_two++;
				}
			}
			current_line_num_one++;
			current_line_num_two++;
		}
	}
	return temp;
}

ostream&
operator <<( ostream& output_stream, const  SparseMatrix take_matrix )
{
	int i,j;
	for( i = 0; i < take_matrix.line_num.size(); ++i )
	{
		output_stream << take_matrix.line_num[i] << " ";
		for( j = 0; j < take_matrix.place[i].size(); ++j )
		{
			output_stream << take_matrix.place[i][j] << ":" << take_matrix.number[i][j] << " ";
		}
		output_stream << endl;
	}
	return output_stream;
}

int
SparseMatrix::check_errors(ifstream* f)
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
SparseMatrix::fill_matrix_line( string line )
{
	string str_for_place;
	string str_for_number;
	string	str_for_line_num;
	place.push_back( vector<int>() );
	number.push_back( vector<double>() );

	if( line.find( " " ) != string::npos )
	{
		str_for_line_num = line.substr( 0, line.find( " " ) );
		line_num.push_back( atoi(str_for_line_num.c_str()) );
		str_for_line_num.clear();
		line.erase( 0, (line.find( " " ) + 1) );
	}

	while( line.size() != 0 )
	{
		if( line.find( ":" ) != string::npos )
		{
			str_for_place = line.substr( 0, line.find( ":" ) );
			place[ place.size() - 1 ].push_back( atoi(str_for_place.c_str()) );
			str_for_place.clear();
			line.erase( 0, (line.find( ":" ) + 1) );
		}

		if( line.find( " " ) != string::npos )
		{
			str_for_number = line.substr( 0, line.find( " " ) );
			if( str_for_number.empty() == 1 ) break;
			number[ number.size() -1 ].push_back( atof(str_for_number.c_str()) );
			line.erase( 0, ( line.find( " " ) + 1 ) );
		}	

		else
		{
			str_for_number = line.substr( 0, line.size() );
			if( str_for_number.empty() == 1 ) break;
			number[ number.size() -1 ].push_back( atof(str_for_number.c_str()) );
			line.clear();
		}
	}
}

/*****************************************************************************************************************/

SparseVector::SparseVector( string file_name )
{
	const char * char_ptr_file_name = file_name.c_str();
	string line;
	ifstream cin_from_file;
	
	cin_from_file.open( char_ptr_file_name );
	getline(cin_from_file, line);

	fill_place_and_number( line );
}

SparseVector::SparseVector()
{	}

void
SparseVector::fill_place_and_number( string line )
{
	string str_for_place;
	string str_for_number;
	int i;
	int j;

	while( line.size() != 0 )
	{
		if( line.find( ":" ) != string::npos )
		{
			str_for_place = line.substr( 0, line.find( ":" ) );
			place.push_back( atoi(str_for_place.c_str()) );
			str_for_place.clear();
			line.erase( 0, (line.find( ":" ) + 1) );
		}

		if( line.find( " " ) != string::npos )
		{
			str_for_number = line.substr( 0, line.find( " " ) );
			if( str_for_number.empty() == 1 ) break;
			number.push_back( atof(str_for_number.c_str()) );
			line.erase( 0, ( line.find( " " ) + 1 ) );
		}	

		else
		{
			str_for_number = line.substr( 0, line.size() );
			if( str_for_number.empty() == 1 ) break;
			number.push_back( atof(str_for_number.c_str()) );
			line.clear();
		}
	}
}

void
SparseMatrix::operator = (const SparseMatrix& right_value )
{
	place = right_value.place;
	number = right_value.number;
	line_num = right_value.line_num;
}


ostream&
operator <<(ostream& output_stream, const SparseVector& take_vector )
{
	int i;
	for( i = 0; i < take_vector.place.size(); ++i )
	{
		output_stream << take_vector.place[i] << ":" << take_vector.number[i] << " ";
	}
	output_stream << endl;
	return output_stream;
}


const SparseVector
SparseVector::operator +( const SparseVector& second_vector )const
{
	SparseVector temp;
	int current_one = 0;
	int current_two = 0;

	while( current_one < place.size() || current_two < second_vector.place.size() )
	{
		if( current_one == place.size() )
		{
			temp.place.push_back( second_vector.place[current_two] );
			temp.number.push_back( second_vector.number[ current_two ] );
			++current_two;
		}

		else if( current_two == second_vector.place.size() )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] );
			++current_one;
		}

		else if( place[current_one] < second_vector.place[current_two] )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] );
			++current_one;
		}

		else if( second_vector.place[current_two] < place[current_one] )
		{
			temp.place.push_back( second_vector.place[current_two] );
			temp.number.push_back( second_vector.number[ current_two ] );
			++current_two;		
		}

		else if( place[current_one] == second_vector.place[current_two] )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] + second_vector.number[ current_two ] );
			++current_one;
			++current_two;
		}
	}
	return temp;
}

const SparseVector
SparseVector::operator -( const SparseVector& second_vector )const
{
	SparseVector temp;
	int current_one = 0;
	int current_two = 0;

	while( current_one < place.size() || current_two < second_vector.place.size() )
	{
		if( current_one == place.size() )
		{
			temp.place.push_back( second_vector.place[current_two] );
			temp.number.push_back( -1 * (second_vector.number[ current_two ]) );
			++current_two;
		}

		else if( current_two == second_vector.place.size() )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] );
			++current_one;
		}

		else if( place[current_one] < second_vector.place[current_two] )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] );
			++current_one;
		}

		else if( second_vector.place[current_two] < place[current_one] )
		{
			temp.place.push_back( second_vector.place[current_two] );
			temp.number.push_back( -1 * (second_vector.number[ current_two ]) );
			++current_two;		
		}

		else if( place[current_one] == second_vector.place[current_two] )
		{
			temp.place.push_back( place[current_one] );
			temp.number.push_back( number[ current_one ] - second_vector.number[ current_two ] );
			++current_one;
			++current_two;
		}
	}
	return temp;
}

void
SparseVector::operator = (const SparseVector& right_value )
{
	place = right_value.place;
	number = right_value.number;
}

double
SparseVector::dot( const SparseVector& other_vetor  )const
{
	double result = 0;
	int current_one = 0;
	int current_two = 0;

	while( current_one != place.size() && current_two != other_vetor.place.size() )
	{
		if( place[current_one] < other_vetor.place[current_two] )
		{
			++current_one;
		}

		else if( other_vetor.place[current_two] < place[current_one] )
		{
			++current_two;		
		}

		else if( place[current_one] == other_vetor.place[current_two] )
		{
			result += number[current_one] * other_vetor.number[current_two];
			++current_one;
			++current_two;
		}
	}
	return result;
}

const SparseVector
SparseVector::operator -()const
{
	int i;
	SparseVector temp;
	temp.place = place;
	temp.number = number;

	for( i = 0; i < temp.number.size(); i++ )
	{
		temp.number[i] *= -1;
	}
	return temp;
}

