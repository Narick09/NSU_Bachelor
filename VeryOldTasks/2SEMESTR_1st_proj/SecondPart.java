package TmpPack;

import java.util.HashSet;
import java.util.Iterator;

class SecondPart{
    static HashSet<Statistics> hs = new HashSet<Statistics>();
    static void add(char ch){
        Statistics tmp = new Statistics(ch);
        if(!hs.contains(tmp)){
            //System.out.println("-");
            hs.add(tmp);
        }else{
            //System.out.println("+++++++++++++++++++++");
        }
    }
    static HashSet<Statistics> getStatistics(){
        return hs;
    }
    static void printStatistics(){
        //System.out.println(hs);
        Iterator<Statistics> i = hs.iterator();
        //i.next().counter;
        while (i.hasNext()){
            Statistics tmp = i.next();
            //if(hs.contains(tmp))
            System.out.println(tmp.print());
        }
    }
}
