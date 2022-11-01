package ThirdNumPack;

import javax.swing.*;
import java.io.IOException;

public interface View{
    //void openWindow() throws IOException;
    void drawMenu() throws IOException;
    //void drawInitGameProcess() throws IOException;
    void drawGameScene() throws IOException;

    JFrame getFrame();
    int getHeight();
    int getWidth();
    void checkModel(ModelStarShip S);
    void printDescrition();
}
