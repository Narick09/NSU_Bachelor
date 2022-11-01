package ThirdNumPack;

import javax.swing.*;
import java.awt.*;
import java.io.IOException;
import java.util.ArrayList;

//мб добавить класс, к-ый будет хранить в себе местоположения и начальные координаты картинок
//и добавить в пикчу конструктор, принимающий массив этих классов

public class Scene extends JPanel
{
    private ArrayList<Picture> pictures = new ArrayList<>();
    public Scene() throws IOException {
        //pictures.add(new Picture("C:\\Users\\Даниил\\IdeaProjects\\3rdNum\\out\\production\\3rdNum\\ThirdNumPack\\Pictures\\Background.jpg",0, 0));
    }
//    public Scene(ArrayList<Picture> pictures){
//        this.pictures = pictures;
//    }

//    public void moveElement(int index, Coordinates coordinates){
//        pictures.get(index).setCoordinates(coordinates.getX(), coordinates.getY());
//        //pictures.get(index).setBounds(coordinates.getX(), coordinates.getY(), pictures.get(index).getWidth(), pictures.get(index).getHeight());
//        repaint();
//    }
//    public void addToScene(String PictureFileName, int x, int y) throws IOException {
//        this.pictures.add(new Picture(PictureFileName, x, y));
//    }
    public void addToScene(Picture p){
        this.pictures.add(p);
    }
//    public void setScene(ArrayList<Picture> pictures){
//        if(pictures != null){
//            this.pictures = pictures;
//        }
//    }
    public void paint(Graphics g)
    {
        for (Picture picture : pictures) {
            g.drawImage(picture.getImage(), picture.getX(), picture.getY(), null);
        }
    }
    //private ArrayList<Image> images = new ArrayList<>();
}