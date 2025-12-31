package Server;

import Client.Observer;
import Utility.NetworkUtil;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;

public class StockServer {
    private ServerSocket serverSocket;
    private StockTrader stockTrader;
    private HashMap<String,ArrayList<Stock>> pendingUpdate;
    private ArrayList<Observer> loggedIn;
    HashMap<String,NetworkUtil> aliveSocket;
    HashMap<String,String> password;

    public StockServer(){
        //read here

        stockTrader=new StockTrader();
        pendingUpdate = new HashMap<>();
        loggedIn = new ArrayList<>();
        aliveSocket=new HashMap<>();
        password=new HashMap<>();

        try {
            serverSocket=new ServerSocket(12345);
            System.out.println("Server Started");
            new Admin(stockTrader,aliveSocket,pendingUpdate);
            while (true){
                Socket clientSocket=serverSocket.accept();
                System.out.println("New Client Received");

                NetworkUtil networkUtil=new NetworkUtil(clientSocket);
                new StockServerThread(networkUtil,stockTrader,pendingUpdate,aliveSocket,password);

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
            //System.out.println("Client Left System");
        }

    }

    public static void main(String[] args) {
        new StockServer();
    }
}
