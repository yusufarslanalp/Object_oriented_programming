import java.awt.event.KeyEvent;
import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;

public class GUI extends JFrame
{
    private Shape sh;
    
    GUI( Shape s ) //shape class'ının oluşturduğu kordinatları alabilmek için shape class'ını parametre olarak alır.
    {
        sh = s;

        setTitle( "Skyline GUI" );
        setSize(800,800);
        setVisible( true );
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    public void paint( Graphics g )
    {
        int i;
        g.setColor(Color.BLACK);
        for(i = 0; i < sh.get_size()-1; i++)
        {
            g.drawLine( 20*sh.get_cord(i).x, 500 -20*sh.get_cord(i).y, 20*sh.get_cord(i+1).x, 500 -20*sh.get_cord(i+1).y );
        }
        g.drawLine(0, 500, 800, 500);
        
    }
}
