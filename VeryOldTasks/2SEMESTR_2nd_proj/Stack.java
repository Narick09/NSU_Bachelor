package SecondNumPack;

import java.util.ArrayList;

public class Stack{
    private ArrayList<Integer> stack = null;//сам стек, с которого будут сниматься числа для операций
    private ArrayList<num> numbers= null;//все числа, определенные DEFINE.
    private ArrayList<String> lineParameter = null;
    {
        stack = new ArrayList<Integer>();
        numbers = new ArrayList<num>();
    }
    public void AddNum(num n) {
        boolean Added = false;
        int ind = 0;
        for (num number : numbers) {
            if (number.equals(n)) {
                Added = true;
                break;
            }
            ind++;
        }
        if(!Added)
            numbers.add(n);
        else
            numbers.get(ind).b = n.b;
    }
    public void AddToStack(int n){
        stack.add(n);
    }
    public void DeleteFromStack(){
        stack.remove(stack.size() - 1);
    }
    public int getLastInStack(){
        return stack.get(stack.size() - 1);
    }
    public int getNumbersSize(){
        return numbers.size();
    }
    public int getStackSize(){
        return stack.size();
    }

    public void setNumStr(ArrayList<String> a){
        lineParameter = a;
    }
    public ArrayList<String> getNumStr() {return lineParameter;}

    public int getInt(num n){
        return numbers.get(numbers.indexOf(n)).b;
    }
    public int getInt(int n){
        return numbers.get(n).b;
    }
    public num getNum(num n){
        return numbers.get(numbers.indexOf(n));
    }
    public void printNums(){
        int c = 0;
        while (c < numbers.size()) {
            System.out.println(numbers.get(c).print());
            c++;
        }
    }
    public void printStack(){
        int c = 0;
        while (c < stack.size()) {
            System.out.println(stack.get(c));
            c++;
        }
    }
}
