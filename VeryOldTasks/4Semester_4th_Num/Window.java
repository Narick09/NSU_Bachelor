package FourthNumPack;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.WindowEvent;

public class Window {

    private JFrame frame;
    private JLabel lbl;

    private Thread th;

    public static Config conf = new Config("conf.txt");

    public static Stock<Accessory> stockAccessories = new Stock<Accessory>(conf.getParam("StorageAccessorySize"));
    public static Stock<Body> stockBody = new Stock<Body>(conf.getParam("StorageBodySize"));
    public static Stock<Engine> stockEngine = new Stock<Engine>(conf.getParam("StorageMotorSize"));
    public static StockCar stockCar = new StockCar(conf.getParam("StorageAutoSize"));
    public static ThreadPool pool = new ThreadPool(conf.getParam("Workers"));
    public static StockController stc = new StockController();

    public static boolean doLog = (conf.getParam("LogSale")==1);
    private static AccsSup aSup[];
    private static BodySup bSup;
    private static EngSup eSup;
    private static Dealer dealer[];

    public static void main(String[] args) {

        int aSupCnt = conf.getParam("AccessorySuppliers");
        aSup = new AccsSup[aSupCnt];
        for (int i = 0;i < aSupCnt; i++) {
            aSup[i] = new AccsSup(stockAccessories, 2000, i*10000);
        }

        bSup = new BodySup(stockBody, 1000);
        eSup = new EngSup(stockEngine, 500);

        int dealerCnt = conf.getParam("Dealers");
        dealer = new Dealer[dealerCnt];
        for (int i=0;i<dealerCnt;i++) {
            dealer[i] = new Dealer(3000, i, stockCar);
        }

        Window window = new Window();
        window.frame.setVisible(true);
    }

    private void updateInfo() {
        int sum_accessory_produced = 0;
        for (int i=0;i<aSup.length;i++) {
            sum_accessory_produced+=aSup[i].getCntSupplied();
        }
        String msg = String.format("<html>Accessory: Avail: %d, total: %d<br>Body: Avail: %d, total: %d<br>Engine: Avail: %d, total: %d</html>",
                stockAccessories.getStockSize(),sum_accessory_produced,
                stockBody.getStockSize(),bSup.getCntSupplied(),
                stockEngine.getStockSize(),eSup.getCntSupplied());
        lbl.setText(msg);
        lbl.revalidate();
    }

    public Window() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        frame.getContentPane().add(panel, BorderLayout.NORTH);
        panel.setLayout(new GridLayout(0, 1, 0, 0));

        JSlider slider = new JSlider();

        slider.setMinimum(100);
        slider.setMaximum(15000);
        slider.setValue(2000);
        panel.add(slider);
        slider.addChangeListener(new ChangeListener() {

            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                int val = slider.getValue();
                for (int i=0;i<aSup.length;i++) {
                    aSup[i].setDelay(val);
                }
            }});

        JSlider slider_1 = new JSlider();

        slider_1.setMinimum(100);
        slider_1.setMaximum(15000);
        slider_1.setValue(1000);
        panel.add(slider_1);

        slider_1.addChangeListener(new ChangeListener() {

            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                bSup.setDelay(slider_1.getValue());
            }});

        JSlider slider_2 = new JSlider();
        slider_2.setMinimum(100);
        slider_2.setMaximum(15000);
        slider_2.setValue(500);
        panel.add(slider_2);

        slider_2.addChangeListener(new ChangeListener() {

            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                eSup.setDelay(slider_2.getValue());
            }});

        JSlider slider_3 = new JSlider();
        slider_3.setMinimum(100);
        slider_3.setMaximum(15000);
        slider_3.setValue(3000);
        panel.add(slider_3);

        slider_3.addChangeListener(new ChangeListener() {

            @Override
            public void stateChanged(ChangeEvent arg0) {
                // TODO Auto-generated method stub
                int val = slider_3.getValue();
                for (int i=0;i<dealer.length;i++) {
                    dealer[i].setDelay(val);
                }
            }});

        JPanel panel_1 = new JPanel();
        frame.getContentPane().add(panel_1, BorderLayout.CENTER);
        panel_1.setLayout(new GridLayout(0, 1, 0, 0));

        lbl = new JLabel("54321");
        lbl.setFont(new Font(null, Font.PLAIN, 20));
        lbl.setHorizontalAlignment(SwingConstants.CENTER);
        panel_1.add(lbl);

        th = new Thread(new Runnable() {
            @Override
            public void run() {
                while (!Thread.interrupted()) {
                    try {
                        Thread.sleep(500);
                        EventQueue.invokeLater(new Runnable() {

                            @Override
                            public void run() {
                                // TODO Auto-generated method stub
                                Window.this.updateInfo();
                            }});
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            }});
        th.start();

        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(WindowEvent winEvt) {
                th.interrupt();
                pool.terminate();
                stc.terminate();
                for (int i=0;i<aSup.length;i++) {
                    aSup[i].terminate();
                }
                bSup.terminate();
                eSup.terminate();
                for (int i=0;i<dealer.length;i++) {
                    dealer[i].terminate();
                }
                System.exit(0);
            }
        });
    }

}
