package SecondNumPack;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;

class num{
    String a;
    int b;
    num(String a, int b){
        this.a = a;
        this.b = b;
    }
    String print(){
        return "<" + a + ">: " + b;
    }
    public boolean equals(Object o){
        num toCheck = (num)o;
        return this.a.equals(toCheck.a);
    }
}

public class Calc{
    //Main functional.
    private Properties commandsNames = null;
    private Scanner scan = null;
    private Stack stack = null;
    private Parser parser = null;
    {
        FileInputStream in_d = null;
        commandsNames = new Properties();
        try {
            in_d = new FileInputStream("C:\\Users\\Даниил\\IdeaProjects\\SecondProj\\src\\SecondNumPack\\LoadClassesNames.properties");
            commandsNames.load(in_d);
        } catch (IOException e) {
            e.printStackTrace();
        }
        stack = new Stack();
        parser = new Parser();
    }
    String getProperty(String s) {
        return commandsNames.getProperty(s);
    }

    Calc() {
        this.scan = new Scanner(System.in);
    }
    Calc(String s) {
        this.scan = new Scanner(s);
    }

    void calculations() {
        while (scan.hasNext()) {
            String s = scan.nextLine();
            if (s.equals("EXIT")) {
//                System.out.println("Numbers:");
//                stack.printNums();
//                System.out.println("Stack:");
//                stack.printStack();
                break;
            }
            //parsing
            Scanner strings = new Scanner(s);
            ArrayList<String> ArrStr = new ArrayList<>();
            while (strings.hasNext()) {
                String tmp = strings.next();
                //if(tmp != null){
                    if(!tmp.contains("#"))
                        ArrStr.add(tmp);
                    else {
                        tmp = (tmp.indexOf('#') == 0) ? "#" : tmp.substring(0, tmp.indexOf('#'));
                        ArrStr.add(tmp);
                        break;
                    }
                //}
            }
            int i = 0;
            String commandName = null;
            while (i < ArrStr.size()) {
                if (this.getProperty(ArrStr.get(i)) != null) {
                    commandName = this.getProperty(ArrStr.get(i));
                    break;
                } else if(ArrStr.get(i).substring(0,1).equals("#")){
                    commandName ="#";
                    break;
                }
                i++;
            }
            ArrStr.remove((String)"#");
            if(commandName == null){
                System.out.println("WrongCommand");
                continue;
            }
            if (commandName.equals("#")) {
                continue;
            }
            stack.setNumStr(ArrStr);
            //call parser
            parser.parsing(stack, commandName);
        }
    }
}
