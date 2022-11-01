package FourthNumPack;

import java.util.ArrayDeque; //обобщенная двуноправленная очередь (можно добавить элементы и в начало и в конец)
import java.util.Queue; //интерфейс однонаправленной очереди( удаляет первый элемент, который добавили)

public class Stock<T> {
    private Queue<T> q;
    private int q_limit;

    public Stock(int q_limit) {
        q = new ArrayDeque<>();
        this.q_limit = q_limit;
    }

    public synchronized void addToStock(T item) throws InterruptedException {
        while (q.size()>=q_limit) {
            wait();
        }
        q.add(item);
        notifyAll();
    }

    public synchronized T getFromStock() throws InterruptedException {
        while (q.isEmpty()) {
            wait();
        }
        T obj = q.poll();
        notifyAll();
        return obj;
    }

    public int getStockSize() {
        return q.size();
    }
}
