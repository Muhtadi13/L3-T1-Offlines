package Utility;

import java.io.Serializable;

public class CommandUtil implements Serializable {

    String name;
    String instruction;
    Object info;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getInstruction() {
        return instruction;
    }

    public void setInstruction(String instruction) {
        this.instruction = instruction;
    }

    public Object getInfo() {
        return info;
    }

    public void setInfo(Object  info) {
        this.info = info;
    }

    public CommandUtil(String name,String instruction, Object info) {

        this.name=name;
        this.instruction = instruction;
        this.info = info;

    }

}