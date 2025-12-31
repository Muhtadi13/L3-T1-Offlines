package Server;

import Client.Observer;
import Utility.CommandUtil;
import Utility.LoginUtil;
import Utility.LogoutUtil;
import Utility.NetworkUtil;
import java.util.ArrayList;
import java.util.HashMap;

public class StockServerThread implements Runnable{
    private final NetworkUtil networkUtil;
    private final Thread thread;
    private StockTrader stockTrader;
    private HashMap<String,ArrayList<Stock>> pendingUpdate;
    private HashMap<String, NetworkUtil> aliveSocket;
    private String observerName;
    HashMap<String,String> password;

    public StockServerThread(NetworkUtil networkUtil,StockTrader stockTrader,HashMap<String,ArrayList<Stock>> pendingUpdate,HashMap<String,NetworkUtil> aliveSocket,HashMap<String,String> password){
        this.networkUtil = networkUtil;
        this.stockTrader = stockTrader;
        this.pendingUpdate = pendingUpdate;
        this.aliveSocket=aliveSocket;
        this.password=password;
        this.thread=new Thread(this);
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
                        Observer observer=new Observer(loginUtil.getUserName());
                        //String pass=loginUtil.getPassword();
                        ArrayList<Stock> allStocks=new ArrayList<>();
                        stockTrader.getStockList().forEach((k, v) ->
                                {
                                    allStocks.add(v);
                                }
                        );

                        if(password.get(loginUtil.getUserName())==null){
                            password.put(loginUtil.getUserName(),loginUtil.getPassword());
                            aliveSocket.put(loginUtil.getUserName(),networkUtil);
                            observerName=loginUtil.getUserName();
                            loginUtil.setStatus(null);
                            loginUtil.setAllStocks(allStocks);

                        } else {
                            if (aliveSocket.get(loginUtil.getUserName()) == null) {
                                if(password.get(loginUtil.getUserName()).equals(loginUtil.getPassword())) {
                                    observerName = loginUtil.getUserName();
                                    aliveSocket.put(loginUtil.getUserName(), networkUtil);
                                    loginUtil.setStatus(pendingUpdate.get(observer.getName()));
                                    loginUtil.setAllStocks(allStocks);
                                    pendingUpdate.remove(observer.getName());
                                }else{
                                    Boolean stat=true;
                                    loginUtil.setStatus(stat);
                                }

                            } else {
                                Boolean stat=false;
                                loginUtil.setStatus(stat);
                            }
                        }
                        networkUtil.write(loginUtil);

                    } else if (obj instanceof CommandUtil) {
                        CommandUtil commandUtil=(CommandUtil) obj;
                        if(aliveSocket.get(commandUtil.getName())!=null) {
                            String stkname = (String) commandUtil.getInfo();
                            if (commandUtil.getInstruction().equalsIgnoreCase("S")) {
                                commandUtil.setInfo(stockTrader.subscribe(new Observer(commandUtil.getName()), stkname));
                                networkUtil.write(commandUtil);

                            } else if (commandUtil.getInstruction().equalsIgnoreCase("U")) {
                                commandUtil.setInfo(stockTrader.unsubscribe(new Observer(commandUtil.getName()), stkname));
                                networkUtil.write(commandUtil);

                            } else if (commandUtil.getInstruction().equalsIgnoreCase("V")) {
                                ArrayList<Stock> stocks = new ArrayList<>();
                                stockTrader.getSubscribers().forEach((k, v) ->
                                        {
                                            for (Observer obs : v) {
                                                if (obs.getName().equalsIgnoreCase(commandUtil.getName())) {
                                                    stocks.add(stockTrader.getStockList().get(k));
                                                    break;
                                                }
                                            }
                                        }
                                );
                                commandUtil.setInfo(stocks);
                                networkUtil.write(commandUtil);
                            } else{
                                commandUtil.setInfo(null);
                                networkUtil.write(commandUtil);
                            }
                        }

                    }else if(obj instanceof LogoutUtil){
                        LogoutUtil logoutUtil=(LogoutUtil) obj;
                        if(observerName==null){
                            logoutUtil.setUserName("false");
                        }else {
                            aliveSocket.remove(observerName);
                            logoutUtil.setUserName("true");
                            networkUtil.write(logoutUtil);
                        }

                    }
                }
            }
        } catch (Exception e) {
            aliveSocket.remove(observerName);
            System.out.println("Client Left System");
        }finally {
            try {
                networkUtil.close();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }

    }
}
