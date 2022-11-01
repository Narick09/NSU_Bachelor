package ThirdNumPack;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class meteor implements Model{
    private Coordinates coordinates = null;
    private int speed = 2;
    private Picture Meteor = null;
    private int Height;
    private int Width;
    private boolean destroyed = false;
    private boolean AtField = false;
    private int health = 5;
    private int initialHealth = 5;
    private int windowWidth = 1200;

    private Properties meteors = null;
    {
        meteors= new Properties();
        try {
            meteors.load(new FileReader(new File("C:\\Users\\Даниил\\IdeaProjects\\3rdNum\\src\\ThirdNumPack\\meteors.properties")));
            //System.out.println("Meteor Picture is Ready!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public meteor(int numPic, int windowWidth) throws IOException {
        int random_number = ((int) (Math.random() * 500)) - 100;
        this.coordinates = new Coordinates();
        this.coordinates.setY(-1*random_number);

        this.windowWidth = windowWidth;
        random_number = (int) (Math.random() * (windowWidth - 100));
//        System.out.println(random_number);
        this.coordinates.setX(random_number);

        random_number = 10 + (int) (Math.random() * 20);
//        System.out.println(random_number);
        this.speed = random_number;

        this.health = (int) (Math.random() * 7);
        this.initialHealth = this.health;

        String M = meteors.getProperty(String.valueOf(numPic));
//        System.out.println(String.valueOf(numPic));
        //System.out.println(M);
        Meteor = new Picture(M, this.coordinates.getX(), this.coordinates.getY());
        this.Height = Meteor.getHeight();
        this.Width = Meteor.getWidth();
        Meteor.setCoordinates(this.coordinates);
    }

    public void moveLeft(){
        this.coordinates.changeX(-1*speed);
    }
    public void moveRight(){
        this.coordinates.changeX(speed);
    }
    public void moveDown(){
        this.coordinates.changeY(speed);
    }
    public void moveUp(){
        this.coordinates.changeY(-1*speed);
    }

    public void review(){
        this.coordinates.setY(-1*((int) (Math.random() * 500)) - 100);
        this.coordinates.setX((int) (Math.random() * (windowWidth - 100)));
        this.speed = 10 + (int) (Math.random() * 20);
        this.health = this.initialHealth;
    }
//    public boolean isDestroyed(){
//        return this.destroyed;
//    }
    @Override
    public void doACt() {

    }

    public Coordinates getCoordinates(){
        return this.coordinates;
    }
    public int getX(){
        return this.coordinates.getX();
    }
    public int getY(){
        return this.coordinates.getY();
    }
    public int getObjectHeight(){
        return this.Height;
    }

    @Override
    public Picture getPicture() {
        return this.Meteor;
    }

    public int getObjectWidth(){
        return this.Width;
    }

    public void setHealth(int health){
        this.health = health;
    }
}
