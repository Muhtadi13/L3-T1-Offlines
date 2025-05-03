package Client;
import Server.Stock;

import Utility.NetworkUtil;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

public class Observer {
    String name;
    boolean isLoggedIn;
    public Observer(String name) throws IOException {
        this.name=name;
        isLoggedIn=false;

    }
    public String getName(){
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void update(ArrayList<Stock> stocks){

        if(stocks==null){
            System.out.println("No New Update Available");
            return;
        }

        System.out.println("New Update Available...");

        for(Stock stk:stocks){
            System.out.println(stk.getName()+" : Count changed "+stk.getCount()+" , Price changed "+stk.getPrice());
        }
    }
    public void view(ArrayList<Stock> stocks){
        if(stocks==null) {
            System.out.println("No Subscribed Stock");
            return;
        }
        System.out.println("List of Subscribed Stocks");
        for(Stock stk:stocks){
            System.out.println("Name : "+stk.getName()+", Count : "+stk.getCount()+", Price : "+stk.getPrice());
        }
    }
}
