public class Cordinate
{
    Cordinate( int new_x, int new_y )
    {
        x = new_x;
        y = new_y;
    }
    Cordinate(){}
    int x;
    int y;

    void print()
    {
        System.out.print( "(" + x + "," + y + ")" );
    }
}
