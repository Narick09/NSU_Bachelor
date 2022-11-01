package FourthNumPack;

public class EngSup {
    private Thread th;
    private int cnt_sup = 0;
    private int delay;
    public EngSup(Stock<Engine> s, int t) {
        delay = t;
        th = new Thread(new Runnable() {
            @Override
            public void run() {
                int cur_id = 1;
                while (!Thread.interrupted()) {
                    try {
                        Engine item = new Engine(cur_id);
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

