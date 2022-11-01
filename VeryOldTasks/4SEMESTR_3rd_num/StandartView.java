package ThirdNumPack;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;
import java.util.ArrayList;

//создаем окно с менюшкой
//в нем кнопка старт
//тыкаем старт - скрываем кнопку и начинаем игру.
public class StandartView implements View, ActionListener {
    private int width = 0;
    private int height = 0;
    GamePannel frame;//scene here
    private String description;
    private boolean skipDescriptionFlag = false;
    private Model S = null;
    private MeteorController M = null;
    private Controller C = null;

    Timer timer = null;
    //int delete = 0;

    private Statistic statistic;

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        M.moving(false, false, false,true);
        //System.out.println("smtsssssssssssssssssssssssssssssssss");
        frame.repaint();
    }

//    public void scanSpaceObjects(MeteorController M) {
//        this.M = M;
//    }

    private class Menu{
        JButton Start;
        JButton Description;
        JButton Score;
    }

    StandartView(Model s, MeteorController M, Controller c, int width, int height) throws IOException {
        this.S = s;
        this.C = c;
        statistic = new Statistic();
        this.M = M;

        frame = new GamePannel();
        frame.setComponent(this.S.getPicture());
        for(meteor m:M.getMeteors())
            frame.setComponent(m.getPicture());

        description = "smt description";
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.width = width;
        this.height = height;
        this.frame.setSize(width, height);
        //можно ли добавить 2 кейлистенера, чтобы они работали параллельно?
        frame.addKeyListener(new KeyListener() {
            public void keyPressed(KeyEvent e) {
                int key = e.getKeyCode();
                if(key == KeyEvent.VK_W) {
                    C.moving(false,false,true,false);
                    //M.moving(false,true,false,false);
                    //System.out.println("wwwwwwwwwwwwwwwwwww");
                    frame.repaint();
                    //delete++;
                }
                if(key == KeyEvent.VK_S) {
                    C.moving(false,false,false,true);
                    //M.moving(false,true,false,false);
                    //System.out.println("sssssssssssssssssss");
                    frame.repaint();
                    //delete++;
                }
                if(key == KeyEvent.VK_A) {
                    C.moving(false,true,false,false);
                    //M.moving(false,true,false,false);
                    //System.out.println("aaaaaaaaaaaaaaaaaaaa");
                    frame.repaint();
                    //delete++;
                }
                if(key == KeyEvent.VK_D) {
                    C.moving(true,false,false,false);
                    //M.moving(false,true,false,false);
                    //System.out.println("dddddddddddddddddddd");
                    frame.repaint();
                    //delete++;
                }
            }
            public void keyReleased(KeyEvent e) {
                int key = e.getKeyCode();
                if(key == KeyEvent.VK_Q){
                    drawGameScene();
                    //frame.repaint();
                }
                //System.out.println("wwwwwwwwwwwwwwwww");
            }
            public void keyTyped(KeyEvent e) {
                //System.out.println("rrrrrrrrrrrrrrrrrrrrrrrrrrr");
            }
        });
    }

    public int getWidth(){
        return width;
    }
    public int getHeight() {
        return height;
    }

    public void drawMenu() {
    }
    public void checkModel(ModelStarShip S){
//        this.frame.getScene().moveElement(0, this.S.getCoordinates());
    }
    public void drawGameScene(){
//        ArrayList<Picture> pictures = new ArrayList<>();
//        try {
//            pictures.add(new Picture("C:\\Users\\Даниил\\IdeaProjects\\3rdNum\\out\\production\\3rdNum\\ThirdNumPack\\Pictures\\Background.jpg",0, 0));
//            pictures.add(new Picture("C:\\Users\\Даниил\\IdeaProjects\\3rdNum\\out\\production\\3rdNum\\ThirdNumPack\\Pictures\\BattleShip.png",450 + (200*i), 550));
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        //Scene sc = new Scene(pictures);
//        frame.reDraw(pictures);
        timer = new Timer(100, this);//период срабатывания
        timer.start();//поток с акшион листенером
//        Thread run = new Thread(new Runnable() {
//            @Override
//            public void run() {
//                while (true) {
//                    try {
//                        M.moving(false, false, false,false);
//                        frame.reDraw(1,S.getCoordinates());
//                        Thread.sleep(100);
//                    } catch (InterruptedException ex) {
//                        ex.printStackTrace();
//                    }
//                }
//            }
//        });
//        run.start();//поток с раном треда
    }

    @Override
    public JFrame getFrame() {
        return this.frame;
    }

    public void printDescrition() {
        while(!skipDescriptionFlag){
            //doing smt
            //flag = true, if button "Skip" is pressed
        }
    }
}
