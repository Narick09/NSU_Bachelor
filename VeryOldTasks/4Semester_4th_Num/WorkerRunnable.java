package FourthNumPack;

public class WorkerRunnable implements Runnable {
    private ThreadPool pool;

    WorkerRunnable(ThreadPool pool) {
        this.pool = pool;
    }
    @Override
    public void run() {
        while (!Thread.interrupted()) {
            try {
                Request rq = pool.getRequest();
                Accessory a = pool.sA.getFromStock();
                Body b = pool.sB.getFromStock();
                Engine e = pool.sE.getFromStock();
                Car c = new Car(pool.getNewId(), a, b, e);
                pool.sC.addToStock(c);
            } catch (InterruptedException e) {
                break;
            }

        }
    }
}
