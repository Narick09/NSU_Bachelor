package SecondNumPack;

import java.util.Scanner;

import static java.lang.Math.sqrt;

interface Commands {
    //All commands implements from this interface.
    //static ArrayList<num> stack = new ArrayList<num>();
    void ToDo(Stack s);
}

class DEFINE implements Commands {
    //DEFINE(int a){}
    //DEFINE(){}
    //public void smt(){};
    @Override
    public void ToDo(Stack s) {
        Scanner check = null;
        num toArr = null;
        try {
            check = new Scanner(s.getNumStr().get(2));
            if (check.hasNextInt()) {
                toArr = new num(s.getNumStr().get(1), check.nextInt());
            } else {
                System.out.println("Wrong number of arguments");

            }
        } catch (NullPointerException | IndexOutOfBoundsException e) {
            e.printStackTrace();
        }
//        if (toArr != null) {
//            System.out.println(toArr.a + ": " + toArr.b);
//        }
        s.AddNum(toArr);
    }
}
class PUSH implements Commands {
    @Override
    public void ToDo(Stack s) {
        if(s.getNumStr().size() == 2){
            num n = new num(s.getNumStr().get(1), 0);
            try{
                s.AddToStack(s.getInt(n));
            }
            catch(IndexOutOfBoundsException e){
                System.out.println("This number is not found");
            }
            catch(Exception e){
                System.out.println(e.getLocalizedMessage());
            }
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}

class POP implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() != 0)
            S.DeleteFromStack();
        else
            System.out.println("Stack is empty");
    }
}

class PRINT implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() != 0)
            System.out.println(S.getLastInStack());
        else
            System.out.println("Stack is empty");
    }
}

class SUM implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() > 1){
            int a = S.getLastInStack();
            S.DeleteFromStack();
            int b = a + S.getLastInStack();
            S.DeleteFromStack();
            S.AddToStack(b);
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}

class MULTIPLY implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() > 1){
            int a = S.getLastInStack();
            S.DeleteFromStack();
            int b =a * S.getLastInStack();
            S.DeleteFromStack();
            S.AddToStack(b);
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}

class SUBTRACT implements Commands {//вычитать
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() > 1){
            int a = S.getLastInStack();
            S.DeleteFromStack();
            int b =a - S.getLastInStack();
            S.DeleteFromStack();
            S.AddToStack(b);
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}

class DEVIDE implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() > 1){
            int a = S.getLastInStack();
            S.DeleteFromStack();
            int b = S.getLastInStack();
            S.DeleteFromStack();
            int f = 0;
            if(b != 0){
                f = a / b;
            }else{
                System.out.println("Second argument is null");
            }
            S.AddToStack(f);
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}

class SQRT implements Commands {
    @Override
    public void ToDo(Stack S) {
        if(S.getStackSize() > 0){
            int a = S.getLastInStack();
            S.DeleteFromStack();
            S.AddToStack((int) sqrt(a));
        }
        else{
            System.out.println("Wrong number of arguments");
        }
    }
}
