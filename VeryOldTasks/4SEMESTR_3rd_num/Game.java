package ThirdNumPack;

import java.io.IOException;
import java.util.ArrayList;

public class Game {
    public void gaming(){
        try {
            Model Spaceship = new ModelStarShip(0, 0, 50);//initialisation
            Controller Control = new ShipController(Spaceship);//initialisation
            ArrayList<meteor> Meteorits = new ArrayList<>();

            for(int i = 0; i < 15; i++){
                Meteorits.add(new meteor(1,1200));//заменить 1 на рандомный номер - чтобы у каждого метеорита была рандом пикча
                Meteorits.get(i).setHealth(20 + (int) (Math.random() * 20));
                //Meteorits.get(i).set
            }
            MeteorController meteorController = new MeteorController(Meteorits);
            StandartView Interface = new StandartView(Spaceship, meteorController,Control, 1200,800);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}