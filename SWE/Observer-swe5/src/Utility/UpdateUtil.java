package Utility;

import java.io.Serializable;

public class UpdateUtil implements Serializable {
    String name;
    Integer count;
    Double price;

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

    public UpdateUtil(String name,Integer count, Double price) {

        this.name=name;
        this.count = count;
        this.price = price;

    }
}
