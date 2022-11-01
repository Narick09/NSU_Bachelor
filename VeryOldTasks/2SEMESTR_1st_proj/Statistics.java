package TmpPack;

class Statistics{
    int counter;
    char ch;
    Statistics (char ch){
        counter = 1;
        this.ch = ch;
    }
    @Override
    public int hashCode(){
        return ch;
    }
    @Override
    public boolean equals(Object o){//когда он вызывает этот метод?
        Statistics other = (Statistics) o;
        if (this == o){
            other.counter++;
            this.counter = other.counter;
            return true;
        }
        if (o == null)
            return false;
        if (getClass() != o.getClass())
            return false;
        if (this.ch != other.ch)
            return false;
        other.counter++;
        this.counter = other.counter;
        return true;
    }
    public String print(){
        System.out.println(this.ch);
        return "<" + Character.toString(this.ch) + ">: " + this.counter;
    }
}
