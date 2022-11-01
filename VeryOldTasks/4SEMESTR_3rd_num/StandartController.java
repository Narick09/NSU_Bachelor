package ThirdNumPack;

public class StandartController implements Controller {
    private boolean flag_game_started = false;
    private boolean flag_game_pause = false;
    private boolean flag_game_finished = false;
    private boolean flag_exit = false;
    private int leftBorder = 0;
    private int rightBorder = 1200;
    private int downBorder = 800;
    private int upBorder = 0;
    //private View Viewer = null;
    private Model SpaceShip = null;
    //private KeyListener ac = null;
    StandartController(Model Ship){
        //this.Viewer = Interface;
        this.SpaceShip = Ship;
    }

//    public void controlling() throws IOException{
//        int r = 0;
//        while(r < 100){
//            this.SpaceShip.moveRight();
//        }
//        //destroyEnemies();
//    }
    public void moving(boolean Right, boolean Left, boolean Up, boolean Down){
        if(Right)
            if((SpaceShip.getX() + SpaceShip.getShipWidth()) + 10 < rightBorder)
                SpaceShip.moveRight();
        if(Left)
            if(SpaceShip.getX() > leftBorder)
                SpaceShip.moveLeft();
        if(Up)
            if(SpaceShip.getY() > upBorder)
                SpaceShip.moveUp();
        if(Down)
            if(SpaceShip.getY() + SpaceShip.getShipHeight() + 10 < downBorder)
                SpaceShip.moveDown();
    }
}
