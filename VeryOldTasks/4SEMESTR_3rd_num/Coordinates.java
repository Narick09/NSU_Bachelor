package ThirdNumPack;

public class Coordinates {
    private int x = 0;
    private int y = 0;
    public int getX(){
        return x;
    }
    public int getY(){
        return y;
    }
    public void setX(int x){
        this.x = x;
    }
    public void setY(int y){
        this.y = y;
    }
    public void setCoordinates(int x, int y){
        this.x = x;
        this.y = y;
    }
    public void changeX(int shiftX){
        this.x += shiftX;
    }
    public void changeY(int shiftY){
        this.y += shiftY;
    }
    public void changeCoordinates(int x, int y){
        this.x = x;
        this.y = y;
    }
}
