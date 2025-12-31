
package Utility;
import Server.Stock;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;

public class LoginUtil implements Serializable {

    public String getUserName() {
        return userName;
    }


    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Object getStatus() {
        return status;
    }

    public void setStatus(Object status) {
        this.status = status;
    }

    public ArrayList<Stock> getAllStocks() {
        return allStocks;
    }

    public void setAllStocks(ArrayList<Stock> allStocks) {
        this.allStocks = allStocks;
    }

    public LoginUtil(String userName, String password, Object status) {
        this.userName = userName;
        this.password = password;
        this.status = status;
    }

    private String userName;
    private String password;
    private Object status;
    private ArrayList<Stock> allStocks;
}