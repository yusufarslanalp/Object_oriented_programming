import java.util.ArrayList;

public class Shape
{
    //Shape Class'ı kordinatlardan oluşan bir listedir.
    private  ArrayList<Cordinate> skyline;

    Shape()
    {
        skyline = new ArrayList<Cordinate>();
    }
    
    Shape( Cordinate[] cord )
    {
        skyline = new ArrayList<Cordinate>();
        for( int i = 0; i < cord.length; i++ ) skyline.add( cord[i] ) ;
    }

    Shape( Shape new_shape ) //copy contuructor
    {
        int i;

        for( i = 0; i < new_shape.skyline.size() ; i++ )
        {
            skyline.add( new_shape.skyline.get(i) );
        }
    }

    //skayline şekli ilk oluşturulduğunda sadece soldaki köşelerin köşenin kordinatı
    //skyline ArrayList'inde bulunmaktadır.
    //Bu fonksiyon sağdaki köşeleride oluştutup skyline'a doldurarak skyline listesini
    //İSTENİLEN output formatına dönüştürmüş olur.
    void convert_skyline() 
    {
        int i;
        ArrayList<Cordinate> new_skyline;
        new_skyline = new ArrayList<Cordinate>();   
        
        new_skyline.add(new Cordinate( skyline.get(0).x , 0 ));
        for( i = 0; i <= skyline.size()-2; i++ )
        {
            new_skyline.add( skyline.get(i) );
            new_skyline.add( create_cordinate( i ) );
        }
        new_skyline.add( skyline.get(i) );
        skyline = new_skyline; /////////////////
    }


    // create_cordinate(int) fonksiyonu convert_skayline() fonksiyonunda kullanılmak için yazılmıştır.
    Cordinate create_cordinate( int index )
    {
        Cordinate new_cordinate;
        int new_x, new_y;
            
        new_x = skyline.get( index +1 ).x;   
        new_y = skyline.get( index ).y;
        new_cordinate = new Cordinate( new_x, new_y );
        return new_cordinate;                
    }

    //verilen iki yükseklik değerinden büyük olanın değerini return eder.
    int max_ht( int height_1, int height_2 )
    {
        if( height_1 > height_2 ) return height_1;
        else return height_2;
    }
    
    //Bu fonksiyon merge sort'ta olduğu gibi "divede and concuer" yöntemi ile
    //recursive olarak önce Buildings listesini parçalar.Daha sonra parçaladığı 
    //şekilleri sıralayarak birleştirme işlemine tabi tutar. 
    Shape divide( int left, int right, Read_file Buildings )
    {
        Shape result =null;
        if( right == left )//recursive fonksiyonun durdurucu koşulu.
        {
            result = Buildings.get(left);
            return result;
        }

        else
        {
            Shape shape_right;
            Shape shape_left;
            
            int middle = (right + left)/2;
            shape_left = divide( left, middle, Buildings );
            shape_right = divide( middle+1, right, Buildings );
            result = merge( shape_left, shape_right );//şekillerin birleştirme aşaması.
            return result;
        }
    }
 
    void add_cordinate( int x, int height , Shape result )
    {
        if( result.skyline.size() == 0 )
        {
            result.skyline.add( new Cordinate(x, height) );
        }
    
        else
        {
            //eğer result skyline'ındaki son kordinatın yüksekliği eklenecek kordinatın
            //yüksekliğinden büyükse ekleme işlemini yapma.
            if( height != result.skyline.get( result.skyline.size() -1 ).y )
            {
                result.skyline.add( new Cordinate(x, height) );
            }
        }
    }
    
    //mege(Shape, Shape) fonksiyonu iki skyline'ın birleştirilme işlemini gerçekleştirir.
    //merge sort algoritmasındaki megre fonksiyonuna benzer şekilde çalışır.
    Shape merge( Shape left, Shape right )
    {
        Shape result = new Shape();////////
        
        int size_left = left.skyline.size();
        int size_right = right.skyline.size();
        int l_current = 0;
        int r_current = 0;
        int left_ht = 0;
        int right_ht = 0;
        int left_x;
        int right_x;

        //iki skyline'dan herhangi birinin size'ına ulaşılıncaya kadar döngüden çıkılmaz.
        while( l_current < size_left && r_current < size_right )
        {
            left_x = left.skyline.get( l_current ).x;
            right_x = right.skyline.get( r_current ).x;

            if( left_x < right_x )
            {
                left_ht = left.skyline.get( l_current ).y;
                add_cordinate( left_x, max_ht(left_ht, right_ht), result );
                l_current++;
            }
            
            else if( right_x < left_x )
            {
                right_ht = right.skyline.get( r_current ).y;
                add_cordinate( right_x, max_ht(left_ht, right_ht), result );
                r_current++;
            }
        
            else
            {
                left_ht = left.skyline.get( l_current ).y;
                right_ht = right.skyline.get( r_current ).y;
                add_cordinate( left_x, max_ht(left_ht, right_ht), result );
                l_current++;
                r_current++;
            }
        }
   
        //eğer birleştirilmek istenen skyline'lardan herhangi birinin size'ına ulaşıldıysa
        //size'ına ulaşılmayan skyline'ın arta kalan kordinatları herhangi bir if() koşulu
        //olmadan result skyline'ına doldurulur. Böylelikle kod verimliliği merge sort algoritmasındakine
        //benzer şekilde arttırılmış olur.
        while( l_current < size_left )
        {
            left_ht = left.skyline.get( l_current ).y;
            left_x = left.skyline.get( l_current ).x;
            result.skyline.add( new Cordinate(left_x, left_ht ));
            l_current++;
        }
        
        //üstteki while() döngüsüyle aynı yoruma sahiptir.
        while( r_current < size_right )
        {
            right_ht = right.skyline.get( r_current ).y;
            right_x = right.skyline.get( r_current ).x;
            result.skyline.add( new Cordinate(right_x, right_ht ));
            r_current++;
        }
        
        return result;
    }

    Cordinate get_cord( int index )//accesor fonksiyon.
    {
        return skyline.get(index);
    }
    
    int get_size(){ return skyline.size(); }//accessor fonksiyon.
    
    public static void main(String[] args) throws Exception
    {
        //data.txt dosyası okunarak binalar Shape class'ına çevrilmiştir.
        //blocs objesinde, bir ArrayList<> te data.txt dosyasında yer alan binalar 
        //tutulmaktadır. blocs'daki arraylist Shape türündedir. 
        Read_file blocs = new Read_file();

        Shape shp1 = new Shape();

        Shape result;

        //divide fonksiyonu blocs objesini alır. blocs objesinde binaların bulunduğu bir
        //arraylist<> vardır. bu arraylist'i recursive olarak parçalar. parçalama işleminden sonra
        //gene divide fonksiyonunun içerisinde merge() fonksiyonuyla birleştirir.
        //Ve sonucu return eder.
        result = shp1.divide( 0, blocs.size()-1 , blocs );
        result.convert_skyline();//sonucun istenilen output formatına dönüştürüldüğü kısım.
        
        for( int i = 0; i < result.skyline.size()-1; i++ )//sonuç ekrana bastırılr.
        {
            result.skyline.get(i).print();
            System.out.print(", ");
            
        } 
        result.skyline.get(result.skyline.size()-1).print();
        System.out.println("");
        
        GUI g1 = new GUI( result );//grafik oluşturulur.
    }
}


