import java.util.ArrayList;
import java.util.Scanner;

public class ClientEnd {

    private static Account createAccount(String type,String name,Double initDeposit){

        if(type.equalsIgnoreCase("Student"))
            return new StudentAccount(name, initDeposit);
        else if (type.equalsIgnoreCase("Savings")) {
            return new SavingsAccount(name, initDeposit);
        } else if (type.equalsIgnoreCase("Fixed")) {
            return new FixedDepositAccount(name, initDeposit);
        }
        return null;
    }

    public static void openForClient(Account account,Bank bank){
        Scanner sc2=new Scanner(System.in);
        String[] command = sc2.nextLine().split(" ");
        while (!command[0].equalsIgnoreCase("close")) {


            if (command[0].equalsIgnoreCase("Deposit")) {
                Double amount=Double.parseDouble(command[1]);
                boolean valid=account.deposit(amount,bank);
                if(valid)
                    System.out.println("Current balance "+account.getBalance());
                else {
                    System.out.println("Invalid Transaction. Current balance "+account.getBalance());
                }
            } else if (command[0].equalsIgnoreCase("Withdraw")) {
                Double amount=Double.parseDouble(command[1]);
                boolean valid=account.withdraw(amount,bank);
                if(valid)
                    System.out.println("Current balance "+account.getBalance());
                else {
                    System.out.println("Invalid Transaction .Current balance "+account.getBalance());
                }
            } else if (command[0].equalsIgnoreCase("Query")) {
                System.out.println("Current balance "+account.getBalance()+", loan "+account.getLoanStatus());
            }else if (command[0].equalsIgnoreCase("Request")) {
                Double amount=Double.parseDouble(command[1]);
                boolean valid=account.requestLoan(amount,bank);
                if(valid)
                    System.out.println("Loan request successful, sent for approval");
                else {
                    System.out.println("Can not request loan");
                }
            }else {
                System.out.println("Invalid Command");
            }

            command = sc2.nextLine().split(" ");
            if(command[0].equalsIgnoreCase("close"))
            {
                System.out.println("Transaction closed for "+account.getName());
            }
        }
    }
    public static void openForEmployee(Employee employee, Bank bank){
        Scanner sc2=new Scanner(System.in);
        String[] command = sc2.nextLine().split(" ");
        while (!command[0].equalsIgnoreCase("close")) {


            if (command[0].equalsIgnoreCase("Approve")) {
                if(employee instanceof Manager){
                    Manager manager=(Manager) employee;
                    ArrayList<String > loans=manager.approveLoan(bank);
                    for(String loan:loans)
                        System.out.println("Loan approved for "+loan);
                } else if (employee instanceof Officer) {
                    Officer officer=(Officer) employee;
                    ArrayList<String > loans= officer.approveLoan(bank);
                    for(String loan:loans)
                        System.out.println("Loan approved for "+loan);
                } else {
                    System.out.println("You don't have permission for this operation");
                }

            } else if (command[0].equalsIgnoreCase("lookup")){
                String name = command[1];
                Account acc=employee.lookup(bank,name);
                if(acc!=null){
                    System.out.println(acc.getName()+" "+acc.getBalance()+"$");
                }
                else {
                    System.out.println("Could not find account");
                }
            } else if (command[0].equalsIgnoreCase("Change")){
                String type=command[1];
                Double rate=Double.parseDouble(command[2]);
                if(employee instanceof Manager) {
                    Manager manager = (Manager) employee;
                    manager.changeRate(bank, type, rate);
                    System.out.println("Interest rate changed for "+type+" account");
                }else {
                    System.out.println("You do not have permission for this operation");
                }
            }else if (command[0].equalsIgnoreCase("See")) {

                if(employee instanceof Manager){
                    Manager manager=(Manager) employee;
                    Double fund= manager.internalFund(bank);
                    System.out.println("Total Internal Fund "+fund);
                }else {
                    System.out.println("You do not have permission for this operation");
                }
            }else {
                System.out.println("Invalid Command");
            }
            command = sc2.nextLine().split(" ");
            if(command[0].equalsIgnoreCase("close"))
            {
                System.out.println("Operations closed for "+employee.getName());
            }
        }
    }
    private static Account findAccount(String name,Bank bank){

        ArrayList<Account> accounts = bank.getAllAccounts();
        for (Account account : accounts) {
            if (name.equalsIgnoreCase(account.getName())) {
                return account;

            }
        }
        return null;
    }

    public static void increaseYear(Bank bank){
        System.out.println("1 year passed ");
        ArrayList<Account> accounts=bank.getAllAccounts();
        for (Account account : accounts) {
            //System.out.println(accounts.get(i).getName());
            Double prevBalance = account.getBalance();
            int prevAge = account.getAge();
            account.setAge(prevAge + 1);
            Double rate=0.0;
            if(account instanceof StudentAccount){
                rate=bank.getInterestRate("Student");
            } else if (account instanceof SavingsAccount) {
                rate=bank.getInterestRate("Savings");
            } else {
                rate=bank.getInterestRate("Fixed");
            }
            account.setBalance(prevBalance + prevBalance * rate / 100.0-account.getLoanStatus()*0.1);
            if(!(account instanceof StudentAccount)) {
                account.setBalance(account.getBalance()-500);
            }
        }

    }

    public static Account create(String name,String type,Double initDeposit,Bank bank){

        Account account=findAccount(name,bank);
        if(account!=null){
            System.out.println("account already exists");
            return null;

        }
        if(type.equalsIgnoreCase("fixed") && initDeposit<FixedDepositAccount.getInitDepositLimit()){
            System.out.println("Account cannot be created");
            return null;
        }

        Account acc=createAccount(type, name, initDeposit);
        bank.addAccount(acc);
        return acc;

    }
}
