package ThirdNumPack;

import java.util.ArrayList;

public class MeteorController implements Controller{
    private ArrayList<meteor> Meteors = null;
    public MeteorController(ArrayList<meteor> meteors){
        this.Meteors = meteors;
    }
    @Override
    public void moving(boolean Right, boolean Left, boolean Up, boolean Down) {
        for(meteor M: Meteors){
//            if(!M.isDestroyed()){
                if(M.getY() + M.getObjectHeight() + 10 < 1200){
                    M.moveDown();
                    //System.out.println("meteorControl: move");
                }
                else{
                    M.review();
                    //System.out.println("meteorControl: review");
                }
  //          }
        }
    }
    public ArrayList<meteor> getMeteors(){
        return this.Meteors;
    }
}
