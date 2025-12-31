import java.util.ArrayList;
import java.util.HashMap;

public class Bank{
    private Double totalFund;
    private ArrayList<Account> allAccounts;
    
    private HashMap<String,Double> loanRequests;
    private ArrayList<Manager> managers;
    private ArrayList<Officer> officers;
    private ArrayList<Cashier> cashiers;

    private HashMap<String,Double> interestRate;
//    private HashMap<String,Double> loanLimit;
//    private HashMap<String,Double> withdrawLimit;
//    private HashMap<String,Double> depositLimit;


    public Bank(){

        allAccounts=new ArrayList<>();
        totalFund=0.0;
        loanRequests= new HashMap<>();
        managers= new ArrayList<>();
        officers= new ArrayList<>();
        cashiers= new ArrayList<>();
        interestRate=new HashMap<>();


        interestRate.put("Student".toUpperCase(),5.0);
        interestRate.put("Savings".toUpperCase(),10.0);
        interestRate.put("Fixed".toUpperCase(),15.0);

        System.out.println("Bank Created");

        managers.add(new Manager("MD"));
        for(int i=0;i<2;i++){
            officers.add(new Officer("S"+(i+1)));
        }
        for(int i=0;i<5;i++){
            cashiers.add(new Cashier("C"+(i+1)));
        }
    }

    public ArrayList<Account> getAllAccounts() {
        return allAccounts;
    }

    public Account findAccount(String name){

        for (Account account : allAccounts) {
            if (name.equalsIgnoreCase(account.getName())) {
                return account;
            }
        }
        return null;
    }
    public Employee findEmployee(String name){
        for (Manager manager:managers) {
            if (name.equalsIgnoreCase(manager.getName())) {
            return manager;
            }
        }
        for(Officer officer:officers){
            if(name.equalsIgnoreCase(officer.getName())){
                return officer;
            }
        }

        for(Cashier cashier:cashiers){
            if(name.equalsIgnoreCase(cashier.getName())){
                return cashier;
            }
        }
        return null;
    }


    public void setAllAccounts(ArrayList<Account> allAccounts) {
        this.allAccounts = allAccounts;
    }

    public void addAccount(Account account){
        this.allAccounts.add(account);
        this.setTotalFund(this.getTotalFund()+account.getBalance());
    }

    public void addLoanRequests(String name,Double amount){
        this.loanRequests.put(name,amount);
    }

    public Double getTotalFund() {
        return totalFund;
    }

    public void setTotalFund(Double totalFund) {
        this.totalFund = totalFund;
    }

    public HashMap<String, Double> getLoanRequests() {
        return loanRequests;
    }

    public void setLoanRequests(HashMap<String,Double> loanReq) {
        this.loanRequests = loanReq;
    }

    public ArrayList<Manager> getManagers() {
        return managers;
    }

    public void setManagers(ArrayList<Manager> managers) {
        this.managers = managers;
    }

    public ArrayList<Officer> getOfficers() {
        return officers;
    }

    public void setOfficers(ArrayList<Officer> officers) {
        this.officers = officers;
    }

    public ArrayList<Cashier> getCashiers() {
        return cashiers;
    }

    public void setCashiers(ArrayList<Cashier> cashiers) {
        this.cashiers = cashiers;
    }

    public Double getInterestRate(String type) {
        return interestRate.get(type.toUpperCase());
    }

    public void setInterestRate(String type,Double rate) {
        this.interestRate.put(type,rate);
    }
}