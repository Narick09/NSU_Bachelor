package ThirdNumPack;

import javax.swing.*;
import java.io.IOException;
import java.util.ArrayList;

public class GamePannel extends JFrame {
    private Scene presentScene = null;
    public GamePannel() throws IOException {
        //System.out.println("GamePannel constructor");
        setTitle("GAMA Bullet");
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        //this.panel = new JPanel();
        // Добавление компонента к фрейму.
        presentScene  = new Scene();
        this.add(presentScene);
        setVisible(true);
    }
//    public GamePannel(Scene scene) {
//        //System.out.println("GamePannel constructor2");
//        setTitle("GAMA Bullet");
//        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
//        // Добавление компонента к фрейму.
//        presentScene  = scene;
//        this.add(presentScene);
//
//    }
//    public Scene getScene(){
//        return this.presentScene;
//    }
//    public void reDraw(Scene component){
//        if(component != null) {
//            this.remove(this.presentScene);
//            this.presentScene = component;
//            this.add(this.presentScene);
//            this.setVisible(true);
//            repaint();
//            //System.out.println("GamePannel reDraw");
//        }
//    }
//    public void reDraw(ArrayList<Picture> pictures){
//        this.presentScene.setScene(pictures);
//        this.reDraw(presentScene);
//    }
//    public void reDraw(int index, Coordinates coordinates){
//        //System.out.println("GamePannel reDrawIndex");
//        this.presentScene.moveElement(index, coordinates);
//        repaint();
//    }
//    public void reDraw(){
//        repaint();
//    }
    public void setComponent(Picture p){
        presentScene.addToScene(p);
    }
    public static final int DEFAULT_WIDTH = 1200;
    public static final int DEFAULT_HEIGHT = 900;
}