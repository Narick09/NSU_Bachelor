package ThirdNumPack;

public class ShipController implements Controller {
    private boolean flag_game_started = false;
    private boolean flag_game_pause = false;
    private boolean flag_game_finished = false;
    private boolean flag_exit = false;
    private int leftBorder = 0;
    private int rightBorder = 1200;
    private int downBorder = 800;
    private int upBorder = 0;
    private Model SpaceShip = null;
    ShipController(Model Ship){
        //this.Viewer = Interface;
        this.SpaceShip = Ship;
    }
    public void moving(boolean Right, boolean Left, boolean Up, boolean Down){
        if(Right)
            if((SpaceShip.getX() + SpaceShip.getObjectWidth()) + 10 < rightBorder)
                SpaceShip.moveRight();
        if(Left)
            if(SpaceShip.getX() > leftBorder)
                SpaceShip.moveLeft();
        if(Up)
            if(SpaceShip.getY() > upBorder)
                SpaceShip.moveUp();
        if(Down)
            if(SpaceShip.getY() + SpaceShip.getObjectHeight() + 10 < downBorder)
                SpaceShip.moveDown();
    }
}
