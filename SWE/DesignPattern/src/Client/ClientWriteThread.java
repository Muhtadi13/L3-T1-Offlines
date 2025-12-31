package Client;

import Utility.CommandUtil;
import Utility.LoginUtil;
import Utility.LogoutUtil;
import Utility.NetworkUtil;

import java.util.Scanner;
import java.util.logging.Logger;

public class ClientWriteThread implements Runnable{

    private NetworkUtil networkUtil;
    private Observer observer;
    private Thread thread;
    public ClientWriteThread(NetworkUtil networkUtil, Observer observer) {
        this.networkUtil=networkUtil;
        this.observer=observer;
        this.thread=new Thread(this);
        System.out.println("In Write Thread of Client...");
        System.out.println("Type \"login\" to continue");
        thread.start();
    }
    @Override
    public void run() {
        try {
            Scanner scanner=new Scanner(System.in);


            while (true) {
                String[] command = scanner.nextLine().split(" ");
                if (command.length > 2 || command.length < 1) {
                    System.out.println("Invalid number of command");
                    continue;
                }
                try {
                    if (command.length == 1 && command[0].equalsIgnoreCase("login")) {
                        System.out.println("Enter Password");
                        String pass=scanner.nextLine();
                        LoginUtil loginUtil=new LoginUtil(observer.getName(),pass,false);
                        networkUtil.write(loginUtil);

                    }else if (command.length == 2 && command[0].equalsIgnoreCase("S")) {
                        CommandUtil commandUtil = new CommandUtil(observer.getName(), command[0], command[1]);
                        networkUtil.write(commandUtil);

                    }else if (command.length == 2 && command[0].equalsIgnoreCase("U")) {
                        CommandUtil commandUtil = new CommandUtil(observer.getName(), command[0], command[1]);
                        networkUtil.write(commandUtil);
                    }else if (command.length == 1 && command[0].equalsIgnoreCase("V")) {
                        CommandUtil commandUtil = new CommandUtil(observer.getName(), command[0], null);
                        networkUtil.write(commandUtil);
                    }else if (command.length == 1 && command[0].equalsIgnoreCase("logout")) {
                        LogoutUtil logoutUtil=new LogoutUtil();
                        networkUtil.write(logoutUtil);
                    }else{
                        System.out.println("Invalid Command");
                    }
                } catch (Exception e) {
                    System.out.println("Invalid Input");
                }
            }
        }catch (Exception e){
            System.out.println("Exception while Writing in Client "+e);
        }finally {
            try {
                networkUtil.close();
            } catch (Exception e) {
                System.out.println("Exception Closing Connection "+e);
            }
        }

    }
}
