package FourthNumPack;

public class AccsSup {
    private Thread th;
    private int cnt_sup = 0;
    private int delay;
    public AccsSup(Stock<Accessory> s, int t, int base_id) {
        delay = t;
        th = new Thread(new Runnable() {
            @Override
            public void run() {
                int cur_id = base_id;

                while (!Thread.interrupted()) {
                    try {
                        Accessory item = new Accessory(cur_id);
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

