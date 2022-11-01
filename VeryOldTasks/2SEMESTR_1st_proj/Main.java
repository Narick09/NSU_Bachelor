package TmpPack;

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Coder coder = null;
        File Source = null;
        File Out = null;
        Scanner person = new Scanner(System.in);

        if(person.nextInt() == 1){
            coder = new En2Morse();
            Source = new File("C:\\Users\\Даниил\\Desktop\\Текстовухи\\EnglishInput.txt");
            Out = new File("C:\\Users\\Даниил\\Desktop\\Текстовухи\\MorzeOutput.txt");
        } else {
            coder = new Morse2En();
            Source = new File("C:\\Users\\Даниил\\Desktop\\Текстовухи\\MorzeInput.txt");
            Out = new File("C:\\Users\\Даниил\\Desktop\\Текстовухи\\EnglishOutput.txt");
        }
        StringBuilder CodedString = coder.handle(Source);
        FileOutputStream WriteToFile = new FileOutputStream(Out);
        WriteToFile.write(CodedString.toString().getBytes());
    }
}


//разбить по файлам, сделать интерфейс

//ClassLoader
//super()
//this()
//ArrayList
//package as access modifier

//2я часть задачи - статистика использования букавак
//use HashSet  - набор неповторяющихся элементов
//class SecondPart{
//    HashSet<Integer> hs = new HashSet();
//    hs.add(new Statistics('a'));
//    hs.add(new Statistics('a'));
    //map.put(e, null_elem);
    //hash(e);
    //e.equals(key);
    //HashSet - обертка вокруг map
//}

//class Statistics{
//    int counter = 0;
//    char ch;
//    Statistics (char ch){this.ch = ch;}
//    public int hashCode(){
//        return ch;
//    }
//    public boolean equals(Object o){
//       counter++;
//        return true;
//    }
//}