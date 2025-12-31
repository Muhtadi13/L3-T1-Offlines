import java.util.ArrayList;
import java.util.HashMap;

abstract class Employee {
    private String name;
    public Employee(String name) {
        this.name=name;
        System.out.println(name+" Created");
    }

    public Account lookup(Bank bank, String name){
        ArrayList<Account> accounts=bank.getAllAccounts();
        for (Account account : accounts) {
            if (name.equalsIgnoreCase(account.getName())) {
                //System.out.println(name+" "+account.getBalance());
                return account;
            }
        }
        return null;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
class Manager extends Employee {

    public Manager(String name) {
        super(name);

    }
    public ArrayList<String> approveLoan(Bank bank){
        HashMap<String,Double> loans=bank.getLoanRequests();
        ArrayList<String> names=new ArrayList<>();

        for(Account account:bank.getAllAccounts()){
            if(loans.containsKey(account.getName())){
                account.setBalance(account.getBalance()+loans.get(account.getName()));
                account.setLoanStatus(account.getLoanStatus()+loans.get(account.getName()));
                names.add(account.getName());
            }
        }

        bank.setLoanRequests(new HashMap<>());

        return names;
    }
    public void changeRate(Bank bank, String type, Double rate){
        bank.setInterestRate(type.toUpperCase(),rate);
    }
    public Double internalFund(Bank bank){
        return bank.getTotalFund();
    }
}

class Cashier extends Employee {
        public Cashier(String name) {
        super(name);
    }
    }

class Officer extends Employee {
    public Officer(String name) {
        super(name);
    }
    public ArrayList<String> approveLoan(Bank bank){
        HashMap<String,Double> loans=bank.getLoanRequests();
        ArrayList<String> names=new ArrayList<>();

        for(Account account:bank.getAllAccounts()){
            if(loans.containsKey(account.getName())){
                account.setBalance(account.getBalance()+loans.get(account.getName()));
                account.setLoanStatus(account.getLoanStatus()+loans.get(account.getName()));
                names.add(account.getName());
            }
        }

        bank.setLoanRequests(new HashMap<>());

        return names;
    }

}
