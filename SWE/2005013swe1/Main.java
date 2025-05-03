import java.util.ArrayList;
import java.util.Scanner;

public class Main {


    public static void main(String[] args) {
        Bank bank=new Bank();
        Scanner sc1=new Scanner(System.in);
        String[] command = sc1.nextLine().split(" ");

        while(!command[0].equalsIgnoreCase("End")) {
            try{

                if(command[0].equalsIgnoreCase("Create")){
                    String name = command[1];
                    String type = command[2];
                    Double initDeposit = Double.parseDouble(command[3]);
                    Account acc=ClientEnd.create(name,type,initDeposit,bank);
                    if(acc!=null) {
                        ClientEnd.openForClient(acc, bank);
                    }
                }else if (command[0].equalsIgnoreCase("Open")) {
                    String name = command[1];
                    Account acc = bank.findAccount(name);
                    if(acc==null){
                       Employee emp=bank.findEmployee(name);
                        if(emp!=null)
                        {
                            System.out.println(emp.getName()+" Active");
                            if(bank.getLoanRequests().size()>0){
                                System.out.println("there are loan approvals pending");
                            }
                            ClientEnd.openForEmployee(emp,bank);
                        }
                        else{
                            System.out.println("Account not found");
                        }
                    } else{
                        System.out.println("Welcome back , "+acc.getName());
                        ClientEnd.openForClient(acc,bank);
                    }
                }else if(command[0].equalsIgnoreCase("INC")) {
                    ClientEnd.increaseYear(bank);
                }else{
                    System.out.println("Invalid command");
                }
            }catch (Exception e){
                System.out.println("Exception Occurred "+e);
            }
            command = sc1.nextLine().split(" ");
        }
    }
}