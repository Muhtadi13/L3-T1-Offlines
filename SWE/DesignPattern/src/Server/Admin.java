package Server;

import Client.Observer;
import Utility.CommandUtil;
import Utility.LoginUtil;
import Utility.NetworkUtil;
import Utility.UpdateUtil;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Admin implements Runnable{
    private final Thread thread;
    private StockTrader stockTrader;

    private HashMap<String, NetworkUtil> aliveSocket;
    private HashMap<String,ArrayList<Stock>> pendingUpdate;

    public Admin(StockTrader stockTrader,HashMap<String,NetworkUtil> aliveSocket,HashMap<String,ArrayList<Stock>> pendingUpdate){
        this.stockTrader = stockTrader;
        this.aliveSocket=aliveSocket;
        this.pendingUpdate=pendingUpdate;

        this.thread=new Thread(this);
        thread.start();
    }

    @Override
    public void run() {
        try {
            Scanner scanner=new Scanner(System.in);
            while (true) {
                String[] command=scanner.nextLine().split(" ");
                if(command.length!=3){
                    System.out.println("Invalid number of command");
                    continue;
                }
                if(stockTrader.getStockList().get(command[1])==null){
                    System.out.println("Stock Doesn't Exist");
                    continue;
                }
                try {
                    if (command[0].equalsIgnoreCase("I")) {
                        Integer count = stockTrader.getStockList().get(command[1]).getCount();
                        Double price = stockTrader.getStockList().get(command[1]).getPrice() + Double.parseDouble(command[2]);
                        if(price<0.0){
                            System.out.println("Price must be Positive");
                            continue;
                        }
                        stockTrader.updateStock(command[1], count, price);

                        ArrayList<Observer> subscribers = stockTrader.getSubscribers().get(command[1]);
                        if (subscribers != null) {
                            for (Observer observer : subscribers) {
                                if (aliveSocket.get(observer.getName()) != null) {
                                    NetworkUtil networkUtil = aliveSocket.get(observer.getName());
                                    UpdateUtil updateUtil = new UpdateUtil(command[1], 0, Double.parseDouble(command[2]));
                                    networkUtil.write(updateUtil);
                                }else{
                                    Stock stk=new Stock(command[1],0,Double.parseDouble(command[2]));
                                    if(pendingUpdate.get(observer.getName())==null){
                                        pendingUpdate.put(observer.getName(),new ArrayList<>());
                                    }
                                    pendingUpdate.get(observer.getName()).add(stk);

                                }
                            }
                        }

                    }else if (command[0].equalsIgnoreCase("D")) {
                        Integer count = stockTrader.getStockList().get(command[1]).getCount();
                        Double price = stockTrader.getStockList().get(command[1]).getPrice() - Double.parseDouble(command[2]);
                        if(price<0.0){
                            System.out.println("Price must be Positive");
                            continue;
                        }
                        stockTrader.updateStock(command[1], count, price);

                        ArrayList<Observer> subscribers = stockTrader.getSubscribers().get(command[1]);
                        if (subscribers != null) {
                            for (Observer observer : subscribers) {
                                if (aliveSocket.get(observer.getName()) != null) {
                                    NetworkUtil networkUtil = aliveSocket.get(observer.getName());
                                    UpdateUtil updateUtil = new UpdateUtil(command[1], 0, -Double.parseDouble(command[2]));
                                    networkUtil.write(updateUtil);
                                }else{
                                    Stock stk=new Stock(command[1],0,Double.parseDouble(command[2]));
                                    if(pendingUpdate.get(observer.getName())==null){
                                        pendingUpdate.put(observer.getName(),new ArrayList<>());
                                    }
                                    pendingUpdate.get(observer.getName()).add(stk);

                                }
                            }

                        }

                    }else if (command[0].equalsIgnoreCase("C")) {
                        if(Integer.parseInt(command[2])<0){
                            System.out.println("Count must be Positive");
                            continue;
                        }
                        Integer count = stockTrader.getStockList().get(command[1]).getCount()+Integer.parseInt(command[2]);
                        Double price = stockTrader.getStockList().get(command[1]).getPrice();
                        stockTrader.updateStock(command[1], count, price);

                        ArrayList<Observer> subscribers = stockTrader.getSubscribers().get(command[1]);
                        if (subscribers != null) {
                            for (Observer observer : subscribers) {
                                if (aliveSocket.get(observer.getName()) != null) {
                                    NetworkUtil networkUtil = aliveSocket.get(observer.getName());
                                    UpdateUtil updateUtil = new UpdateUtil(command[1], Integer.parseInt(command[2]), 0.0);
                                    networkUtil.write(updateUtil);
                                }else{
                                    Stock stk=new Stock(command[1],Integer.parseInt(command[2]),0.0);
                                    if(pendingUpdate.get(observer.getName())==null){
                                        pendingUpdate.put(observer.getName(),new ArrayList<>());
                                    }
                                    pendingUpdate.get(observer.getName()).add(stk);

                                }
                            }
                        }
                    }
                }catch (Exception e) {
                    System.out.println("Invalid Input "+e);
                }
            }
        }catch (Exception e) {
            throw new RuntimeException(e);
        }

    }
}
