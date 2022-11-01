package FourthNumPack;

public class StockCar extends Stock<Car>{

    public StockCar(int q_limit) {
        super(q_limit);
    }

    @Override
    public Car getFromStock() throws InterruptedException {
        synchronized(Window.stc) {
            Window.stc.rq_active++;
            Window.stc.notify();
        }
        return super.getFromStock();
    }
}