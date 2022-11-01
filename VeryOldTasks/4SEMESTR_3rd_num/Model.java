package ThirdNumPack;

public interface Model {
    Coordinates getCoordinates();
    int getX();
    int getY();

    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void doACt();
    int getObjectWidth();
    int getObjectHeight();
    Picture getPicture();
}
