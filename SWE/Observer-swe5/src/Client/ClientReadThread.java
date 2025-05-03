package Client;

import Server.Stock;
import Server.StockTrader;
import Utility.*;

import java.util.ArrayList;
import java.util.Scanner;

public class ClientReadThread implements Runnable{

    private NetworkUtil networkUtil;
    private Observer observer;
    private Thread thread;
    public ClientReadThread(NetworkUtil networkUtil, Observer observer) {
        this.networkUtil=networkUtil;
        this.observer=observer;
        this.thread=new Thread(this);
        System.out.println("Waiting for Response from Server...");
        thread.start();
    }
    @Override
    public void run() {
        try {
            while (true) {
                Object obj = networkUtil.read();
                if(obj !=null){
                    if(obj instanceof LoginUtil){
                        LoginUtil loginUtil=(LoginUtil) obj;
                        if(loginUtil.getStatus() instanceof Boolean){
                            Boolean stat=(Boolean) loginUtil.getStatus();
                            if(stat) {
                                System.out.println("Password doesn't match");
                            }else{
                                System.out.println("User already logged in");
                            }
                        }else{
                            System.out.println("Welcome "+loginUtil.getUserName());
                            ArrayList<Stock> allstocks=loginUtil.getAllStocks();
                            for (Stock stock: allstocks) {
                                System.out.println("Stock : "+stock.getName()+", Count : "+stock.getCount()+", Price : "+stock.getPrice());
                            }

                            ArrayList<Stock> stocks = (ArrayList<Stock>) loginUtil.getStatus();
                            observer.update(stocks);
                        }


                    } else if (obj instanceof CommandUtil) {
                        CommandUtil commandUtil=(CommandUtil) obj;
                        if(commandUtil.getInstruction()!=null) {

                            if (commandUtil.getInfo() instanceof Boolean) {
                                Boolean boo=(Boolean) commandUtil.getInfo();
                                if(boo){
                                    System.out.println("Successful Action");
                                }else{
                                    System.out.println("unsuccessful Action");
                                }

                            } else if (commandUtil.getInfo() instanceof ArrayList<?>) {
                                ArrayList<Stock> stocks = (ArrayList<Stock>) commandUtil.getInfo();
                                observer.view(stocks);
                            } else{
                                System.out.println("Invalid Object");
                            }
                        }

                    }else if(obj instanceof UpdateUtil){
                        UpdateUtil updateUtil=(UpdateUtil) obj;
                        Stock stk=new Stock(updateUtil.getName(),updateUtil.getCount(),updateUtil.getPrice());
                        ArrayList<Stock> stocks=new ArrayList<>();
                        stocks.add(stk);
                        observer.update(stocks);

                    }else if(obj instanceof LogoutUtil){

                    }else{
                        System.out.println("Invalid Message from Server");
                    }
                }
            }
        } catch (Exception e) {
            System.out.println("Got Exception in Thread  " + e);
        }finally {
//            try {
//                networkUtil.close();
//            } catch (Exception e) {
//                System.out.println("Exception Closing Connection "+e);
//            }
        }

    }
}
