package ThirdNumPack;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        Game game = new Game();
        game.gaming();
//перенести все, что ниже во View
//        GamePannel fr = null;
//        try {
//            fr = new GamePannel();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
        //fr.setSize(1200, 900);
        //fr.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//        Picture pic = null;
//        Picture picShip = null;
//        try {
//            pic = new Picture("out/production/3rdNum/ThirdNumPack/Pictures/Background.jpg", 5, 5);
//            //fr.setVisible(true);
//            picShip = new Picture("out/production/3rdNum/ThirdNumPack/Pictures/BattleShip.png", 400, 400);
//            //fr.setVisible(true);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
        //fr.setVisible(true);
//        fr.add(pic);
//       fr.add(picShip);

//        if (fr != null) {
//            fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//            fr.setVisible(true);
//        }
        //что-нибудь супер простое
        //н-р игра с летающим кораблем.
        //ты летишь, а на тебя летят разного рода метеориты, из которых можно добывать ресурс - просто очки,
        //к-рых нужно набрать как можно больше
        //ну и, мб, пара врагов, из которых выпадает опыт для прокачки корабля. или лучше снаряды.
    }
}
