using namespace std;

class SparseVector
{
	public:
		SparseVector();
		SparseVector( string file_name );
		void fill_place_and_number( string line );
		double dot( const SparseVector& other_vetor  )const;
		const SparseVector operator -()const;
		friend ostream& operator <<(ostream& output_stream, const SparseVector& take_vector ); 
		const SparseVector operator +( const SparseVector& second_vector )const;
		const SparseVector operator -( const SparseVector& second_vector )const;
		void operator = (const SparseVector& right_value );
	private:
		vector<int> place;	//sparse vektöründeki sıfır haricindeki sayıların indislerini tutan vektördür. 
		vector <double> number;	//sparse vektöründeki sıfır haricindeki sayıların değerini tutan vektördür.
};	

class SparseMatrix
{
	public:
		SparseMatrix();
		SparseMatrix( string file_name );

		friend ostream& operator <<( ostream& output_stream, const  SparseMatrix take_matrix );
		const SparseMatrix operator +( const SparseMatrix& second_matrix )const;
		const SparseMatrix operator -( SparseMatrix second_matrix )const;
		const SparseMatrix operator -()const;
		void operator = (const SparseMatrix& right_value );
		SparseMatrix transpose();

		//aşağıdaki fonksiyonlar yardımcı fonksiyonlardır.
		int check_errors(ifstream* f);
		void create_new_line_num( vector<int>& new_line_num );
		void fill();
		void fill_matrix_line( string line );

	private:
		vector< vector<int> > place; //sparse matrix deki sıfır haricindeki sayıların indislerini tutan vektördür.
		vector< vector<double> > number; //sparse matrix deki sıfır haricindeki sayıların değerini tutan vektördür.
		vector<int> line_num; //sparse matrix deki sıfır haricinde sayı bulundıran satırların indislerini tutan vektördür.
};
