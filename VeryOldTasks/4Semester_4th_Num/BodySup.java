package FourthNumPack;

public class BodySup {
    private Thread th;
    private int cnt_sup = 0;
    private int delay;
    public BodySup(Stock<Body> s, int t) {
        delay = t;
        th = new Thread(new Runnable() {
            @Override
            public void run() {
                int cur_id = 1;
                while (!Thread.interrupted()) {
                    try {
                        Body item = new Body(cur_id);
                        s.addToStock(item);
                        cur_id++;
                        cnt_sup++;
                        Thread.sleep(delay);
                    } catch (InterruptedException e) {
                        break;
                    }
                }

            }});
        th.start();
    }

    public void terminate() {
        th.interrupt();
    }

    public int getCntSupplied() {
        return cnt_sup;
    }

    public void setDelay(int t) {
        delay = t;
    }

}
