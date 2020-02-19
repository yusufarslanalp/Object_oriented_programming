//Yusuf Abdullah ARSLANALP 151044046
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

class Catalog
{
	public:

		//data dosyasının adını parametre olarak alan constructor.
		Catalog( string input_file ); 

		//string olarak aldığı katalog formatını parçalara böler ve private vektör olan "catalog_tags" Vektörüne doldurur.
		void get_format( string catalog_format ); 

		//"catalog_name" private değişkeninin accessor fonksiyonudur.
		string get_name()const{ return catalog_name; } 

		//"catalog_name" private değişkeninin mutator fonksiyonudur.
		void set_name( string new_name ){ catalog_name = new_name; } 
		int check_errors(ifstream* f);

		//data.txt dosyasını satır satır okur. okuduğu her satırı çift tırnak(") işaretine göre parçalayarak lines<> vektörüne doldurur.
		void read_input_file( string file_name ); 

		//read_input_file() fonksiyonunun içerisinde yer alır. read_input_file() fonksiyonun data dosyasından okuduğu satırı parçalar ve lines vektörüne doldurur.
		void token_line( string line );	

		//lines<> vectörünü kullanarak hatalı satırların silinme işlemini gerçekleştirir. Exeption Handling'in kullanıldığı iki fonksiyondan biri bu fonksiyondur.
		//Missing field ve Duplicate entry hatalarının tespit edildiği ve hataların bildirildiği fonksiyon bu fonksiyondur.
		void clear_lines();	

		//command.txt dosyasından komutları okur ve komutları gerçekleştirir.
		void read_command( string file_name ); 

		//Exeption Handling'in kullanıldığı diğer fonksiyon bu fonksiyondur. Bu fonksiyona commands.txt dosyaında bulunan komutlar read_command() fonksiyonu tarafından verilir.
		//bu fonksiyonda satır olarak aldığı komutu gerçekleştirir. Eğer bir hata varsa bunun tespitini yapar.
		void token_command( string command ); 


		////<type> , <year> gibi bir katalog etiketinin adını string olarak alır. aldığı etiket eğer catalog_tags<> vektöründe varsa etiketin catalog_tags vektöründe
		//bulunduğu index'i return eder. aldığı etiket eğer catalog_tags<> vektöründe yoksa -1 return eder.
		int find_place_of_tag( string word ); 

		//word parametresi ile aldığı string'in bulunduğu satırları bulur ve ekrana basar ( veya dosyaya yazar. ).
		void search( int tag_num, string word ); 
		
		// lines<> vektörünün tüm satırlarını ekrana basar.
		void print_lines(); 

		// data.txt dosyasının ilk satırını alır. aldığı satırdaki katalog ismine göre private member'lar olan catalog_name'i ve catalo_tags<> vektörünü doldurur.
		//böylelikle tek bir programla tüm katalog türleri işlenmiş olur( program genelleştirilmiş olur. ).  
		void specify_catalog_type( string file_name );  

		//STL algoritmasında var olan sort() fonksiyonu bu operaröre göre sıralama işlenini gerçekleştirmektedir.
		bool operator () ( vector<string> & v1 , vector<string> & v2) 
		{
			if( v1[ sort_index ].compare( v2[ sort_index ] ) < 0 ) return true;
		}

	private:
		string catalog_name;

		//catalog etiketlerinin tutulduğu vektördür. örnek olarak music kataloğunun etiketleri: <title> <artists> <year> <genre> olduğuna göre
		//catalog_tags[0] ta <title> catalog_tags[3] de <genre> vardır.
		vector<string> catalog_tags; 

		//data.txt dosyasından okunan her satır iki boyutlu bir vektör olan lines vektörüne doldurulur.
		vector< vector<string> > lines; 

		//sort işleminin yapmak için lines<> vektöründe bulunan iki line'ı karşılaştırmak gerekmektedir. satırları karşılaştırırken kullanıcağımız karşılaştırma faktörü
		//program içerisinde değişime uğramaktadır. yani iki saırı bazen <year> etiketine göre karşılaştırırken bazende <genre> etiketine göre karşılaştırmaktayız.
		//int sort_index değişkeni iki satırın hangi etikete göre karşılaştırılacağının bilgisini saklar. Bu değişken parantez operatörü içerisinde kullanılmaktadır.
		int sort_index;	
};


