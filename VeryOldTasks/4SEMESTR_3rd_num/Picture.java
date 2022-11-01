package ThirdNumPack;

import javax.swing.*;
import java.awt.*;

public class Picture extends JLabel {
    private final Image Im;
    private Coordinates coordinates = new Coordinates();
    public Picture(String FileName, int x, int y){
        Im = new ImageIcon(FileName).getImage();//ImageIO.read(new File(FileName));
        coordinates.setCoordinates(x, y);
        this.setVisible(true);
    }
    public Image getImage() {
        return this.Im;
    }
//    public void setX(int x){
//        this.coordinates.setX(x);
//    }
//    public void setY(int y){
//        this.coordinates.setY(y);
//    }
//    public void setCoordinates(int x, int y){
//        this.coordinates.setCoordinates(x,y);
//    }
    public void setCoordinates(Coordinates coord){
        this.coordinates = coord;
    }
    public int getX(){
        return this.coordinates.getX();
    }
    public int getY(){
        return this.coordinates.getY();
    }
}