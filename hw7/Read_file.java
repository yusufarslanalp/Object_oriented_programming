import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;


public class Read_file 
{
    //her bina 2 cordinattan oluşan bir Shape'tir. 
    private ArrayList<Shape> buildings;

    Read_file() throws Exception
    {
        buildings = new ArrayList<Shape>();
        read_file();
    }
    
    Shape get( int index )
    {
        return buildings.get(index);
    }
    
    int size()
    { return buildings.size(); }
    
    //data.txt dosyasından okudğu satırların(binaların) harbirini Shape türüne çevirir.
    //shape türüne çevrilmiş binaların herbirini buildings listesine kaydeder.
    void read_file()throws Exception
    {
        int i;
        File file = new File("data.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        String st;
        String[] arr = new String[3];
        int [] int_arr = new int[3];
        while ((st = br.readLine()) != null)
        {
            arr = st.split(" ");

            for( i = 0; i < 3; i++ ) int_arr[i] = Integer.parseInt( arr[i] );
            create_and_add( int_arr );
        }
    }


    void create_and_add( int arr[] ) //üçlük bir int array'i alır ve onu ikilik bir kordinat array'i olarak return eder.
    {
        //buildings.add( Cordinate[] );
        int x0 = arr[2];
        int y0 = arr[1];
        int x1 = arr[2] + arr[0];
        int y1 = 0;

        Cordinate[] temp;  
        temp = new Cordinate[]{ new Cordinate( x0, y0 ), new Cordinate( x1, y1 ) };
        buildings.add( new Shape( temp ) );
    }
}
