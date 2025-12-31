public abstract class Account {
    private Double balance ;
     private String name ;
     private Double loanStatus;
    private int age;

    public void setAge(int age) {
        this.age = age;
    }
    public Account(String name,Double initialDeposit){
        this.name=name;
        this.balance=initialDeposit;
        this.loanStatus=0.0;
        this.age=0;


    }
    public abstract boolean deposit(Double amount, Bank bank);
    public abstract boolean withdraw(Double amount, Bank bank);
    public abstract boolean requestLoan(Double amount, Bank bank);
    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setLoanStatus(Double loanStatus) {
        this.loanStatus = loanStatus;
    }

    public int getAge() {
        return age;
    }

    public Double getBalance() {
        return balance;
    }

    public String getName() {
        return name;
    }

    public Double getLoanStatus() {
        return loanStatus;
    }

}

class StudentAccount extends Account{

    private static Double loanlimit;
    private static Double withdrawlimit;
    public StudentAccount(String name, Double initialDeposit) {
        super(name, initialDeposit);
        loanlimit=1000D;
        withdrawlimit=10000D;
        System.out.println("Student Account Created for "+name+" initial balance "+initialDeposit);

    }

    @Override
    public boolean deposit(Double amount, Bank bank) {
        bank.setTotalFund(bank.getTotalFund()+amount);
        this.setBalance(this.getBalance()+amount);
        return true;
    }

    @Override
    public boolean withdraw(Double amount, Bank bank) {
        if(amount<=withdrawlimit && amount<=this.getBalance()){
            bank.setTotalFund(bank.getTotalFund()-amount);
            this.setBalance(this.getBalance()-amount);
            return true;
        }
        return false;
    }
    @Override
    public boolean requestLoan(Double amount, Bank bank) {

        if(amount<=loanlimit){
            //this.setLoanStatus(amount);
            bank.addLoanRequests(this.getName(),amount);
            //System.out.println("Can give loan");
            return true;
        }
        return false;

    }

    public static Double getLoanlimit() {
        return loanlimit;
    }

    public static void setLoanlimit(Double loanlimit) {
        StudentAccount.loanlimit = loanlimit;
    }

    public static Double getWithdrawlimit() {
        return withdrawlimit;
    }

    public static void setWithdrawlimit(Double withdrawlimit) {
        StudentAccount.withdrawlimit = withdrawlimit;
    }
}


class SavingsAccount extends Account{
    private static Double loanlimit;
    private static Double withdrawlimit;

    public SavingsAccount(String name, Double initialDeposit) {
        super(name, initialDeposit);
        loanlimit=10000D;
        withdrawlimit=1000D;
        System.out.println("Savings Account Created for "+name+" initial balance "+initialDeposit);
    }

    @Override
    public boolean deposit(Double amount, Bank bank) {
        bank.setTotalFund(bank.getTotalFund()+amount);
        this.setBalance(this.getBalance()+amount);
        return true;
    }

    @Override
    public boolean withdraw(Double amount, Bank bank) {
        if(amount+withdrawlimit<=this.getBalance()){
            bank.setTotalFund(bank.getTotalFund()-amount);
            this.setBalance(this.getBalance()-amount);
            return true;
        }
        return false;

    }

    @Override
    public boolean requestLoan(Double amount, Bank bank) {

        if(amount<=loanlimit){
            bank.addLoanRequests(this.getName(),amount);
           return true;
        }
        return false;
    }

    public static Double getLoanlimit() {
        return loanlimit;
    }

    public static void setLoanlimit(Double loanlimit) {
        SavingsAccount.loanlimit = loanlimit;
    }

    public static Double getWithdrawlimit() {
        return withdrawlimit;
    }

    public static void setWithdrawlimit(Double withdrawlimit) {
        SavingsAccount.withdrawlimit = withdrawlimit;
    }
}


class FixedDepositAccount extends Account{
    private static Double loanlimit;
    private static Double depositlimit;
    private static Integer agelimit;
    private static Integer initDepositLimit= 100000;


    public FixedDepositAccount(String name, Double initialDeposit) {
        super(name, initialDeposit);
        loanlimit=100000D;
        depositlimit=50000D;
        agelimit=0;
        System.out.println("Fixed Deposit Account Created for "+name+" initial balance "+initialDeposit);
    }

    @Override
    public boolean deposit(Double amount, Bank bank) {
        if(amount>=depositlimit) {
            bank.setTotalFund(bank.getTotalFund()+amount);
            this.setBalance(this.getBalance()+amount);
            return true;
        }
        return false;
    }

    @Override
    public boolean withdraw(Double amount, Bank bank) {
        if(this.getAge()>=agelimit){
            bank.setTotalFund(bank.getTotalFund()-amount);
            this.setBalance(this.getBalance()-amount);
            return true;
        }
        return false;

    }
    @Override
    public boolean requestLoan(Double amount, Bank bank) {

        if(amount<=loanlimit){
            bank.addLoanRequests(this.getName(),amount);
            //this.setLoanStatus(amount);
           return true;
        }
       return false;
    }

    public static Double getLoanlimit() {
        return loanlimit;
    }

    public static void setLoanlimit(Double loanlimit) {
        FixedDepositAccount.loanlimit = loanlimit;
    }

    public static Double getDepositlimit() {
        return depositlimit;
    }

    public static void setDepositlimit(Double depositlimit) {
        FixedDepositAccount.depositlimit = depositlimit;
    }

    public static Integer getAgelimit() {
        return agelimit;
    }

    public static void setAgelimit(Integer agelimit) {
        FixedDepositAccount.agelimit = agelimit;
    }

    public static Integer getInitDepositLimit() {
        return initDepositLimit;
    }

    public static void setInitDepositLimit(Integer initDepositLimit) {
        FixedDepositAccount.initDepositLimit = initDepositLimit;
    }
}
