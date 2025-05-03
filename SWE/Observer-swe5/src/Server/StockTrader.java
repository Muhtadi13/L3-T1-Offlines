package Server;

import Utility.NetworkUtil;
import Client.Observer;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;

public class StockTrader{
    private static final String INPUT_FILE_NAME = "init_stocks.txt";
    private HashMap<String,ArrayList<Observer>> subscribers;
    private HashMap<String, Stock> stockList;


    public StockTrader(){
        subscribers=new HashMap<>();
        stockList = new HashMap<>();
        read();
    }
    public Boolean subscribe(Observer observer, String stockName){
        if(stockList.get(stockName)==null){
            ;
            return false;
        }
        //System.out.println(stockList.get(stockName).getName());
        if(subscribers.get(stockName)==null){
            subscribers.put(stockName,new ArrayList<>());
        }
        subscribers.get(stockName).add(observer);
        return true;

    }
    public Boolean unsubscribe(Observer observer, String stockName){
        if(stockList.get(stockName)==null || subscribers.get(stockName)==null){
            return false;
        }
        for(Observer observer1:subscribers.get(stockName)){
            if(observer1.getName().equalsIgnoreCase(observer.getName())){
                subscribers.get(stockName).remove(observer1);
                return true;
            }
        }
        return false;
    }
    public void createStock(String name,Integer count,Double price){
        Stock stock=new Stock(name,count,price);
        subscribers.put(name,new ArrayList<>());
        stockList.put(name,stock);

    }
    public void updateStock(String name,Integer count,Double price){
        Stock stk=new Stock(name,count,price);
        stockList.remove(name);
        stockList.put(name,stk);
        //System.out.println("Updated "+stockList.get(name).getCount()+" "+stockList.get(name).getPrice());
    }

    public HashMap<String, ArrayList<Observer>> getSubscribers() {
        return subscribers;
    }

    public HashMap<String, Stock> getStockList() {
        return this.stockList;
    }
    public void read(){
        try {
            BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE_NAME));
            while (true) {
                String line = br.readLine();
                if (line == null) break;
                String[] arrString = line.split(" ");
                Integer count=Integer.parseInt(arrString[1]);
                Double price =Double.parseDouble(arrString[2]);
                Stock stock=new Stock(arrString[0],count,price);
                stockList.put(arrString[0],stock);
            }
            br.close();
        }catch (Exception e){
            System.out.println("FIle exception "+ e);
        }


    }
}
