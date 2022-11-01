package FourthNumPack;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

public class Config {
    private HashMap<String, Integer> params;
    public Config(String fname) {
        params = new HashMap<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(fname))){
            String curLine;
            while ((curLine = reader.readLine()) != null) {
                StringBuilder key = new StringBuilder();
                int pos = 0;
                for (int i=0;i<curLine.length();i++) {
                    if (curLine.charAt(i)=='=') {
                        pos = i;
                        break;
                    } else {
                        key.append(curLine.charAt(i));
                    }
                }
                StringBuilder val = new StringBuilder();
                for (int i=pos+1;i<curLine.length();i++) {
                    val.append(curLine.charAt(i));
                }
                params.put(key.toString(), Integer.valueOf(val.toString()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public int getParam(String param) {
        return params.get(param);
    }
}