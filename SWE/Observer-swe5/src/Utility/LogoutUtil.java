package Utility;

import java.io.Serializable;

public class LogoutUtil implements Serializable {
    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    private String userName;


}