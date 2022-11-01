package FourthNumPack;

public class Car extends Part {
    private Accessory accessory;
    private Body body;
    private Engine engine;

    public Car(int cur_id, Accessory accessory, Body body, Engine engine) {
        super(cur_id);
        this.accessory = accessory;
        this.body = body;
        this.engine = engine;
    }

    public Accessory getAccessory() {
        return accessory;
    }

    public Body getBody() {
        return body;
    }

    public Engine getEngine() {
        return engine;
    }

}