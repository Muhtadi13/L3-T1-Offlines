package Server;

import java.io.Serializable;

public class Stock implements Serializable {
    String name;
    Integer count;
    Double price;
    public Stock(String name,Integer count,Double price){
        this.name=name;
        this.price=price;
        this.count=count;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getCount() {
        return count;
    }

    public void setCount(Integer count) {
        this.count = count;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }
}
