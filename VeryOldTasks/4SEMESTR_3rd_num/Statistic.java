package ThirdNumPack;

import java.io.FileOutputStream;
import java.util.Scanner;

public class Statistic {
    //записывает в файл текущую статистику(счет) и считывает из файла предыдущие
    private int score = 0;
    private Scanner previousScore;
    private FileOutputStream presentScore;
}
