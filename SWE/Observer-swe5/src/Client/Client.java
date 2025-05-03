package Client;

import Utility.CommandUtil;
import Utility.NetworkUtil;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    private Observer observer;
    private NetworkUtil networkUtil;
    public Client(String name) throws IOException {

        String serverAddress = "127.0.0.1";
        int serverPort = 12345;
        networkUtil = new NetworkUtil(new Socket(serverAddress,serverPort));
        //System.out.println("New Client Created");
        observer=new Observer(name);

        new ClientReadThread(networkUtil,observer);
        new ClientWriteThread(networkUtil,observer);
    }
    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        System.out.println("Enter Name of Client");
        String name=scanner.nextLine();
        //System.out.println(name);
        try{
            new Client(name);

        }catch(Exception e){
            System.out.println("Can't Connect to Server");
        }
    }
}