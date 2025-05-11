package model;

/**
 *
 * @author George
 */
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.ReadOnlyDoubleProperty;
import javafx.beans.property.ReadOnlyStringProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Employee {
    private StringProperty name;
    private StringProperty email;
    private StringProperty phone;
    private StringProperty address;
    private StringProperty TFN;
    private StringProperty type; 
    private IntegerProperty hours;
    private DoubleProperty payPerHour;
    private DoubleProperty income;
    private DoubleProperty rate;
    private DoubleProperty net;
    private DoubleProperty deduction;
    private DoubleProperty superannuation;
    private DoubleProperty superRate;
    private Employer employer;

    public Employee(String name, String email, String phone, String address, String TFN, String type, int hours, double payPerHour) {
        this.name = new SimpleStringProperty();
        this.name.set(name);
        this.email = new SimpleStringProperty();
        this.email.set(email);
        this.phone = new SimpleStringProperty();
        this.phone.set(phone);
        this.address = new SimpleStringProperty();
        this.address.set(address);
        this.TFN = new SimpleStringProperty();
        this.TFN.set(TFN);
        this.type = new SimpleStringProperty();
        this.type.set(type);
        this.hours = new SimpleIntegerProperty();
        this.hours.set(hours);
        this.payPerHour = new SimpleDoubleProperty();
        this.payPerHour.set(payPerHour);     
        this.income = new SimpleDoubleProperty();
        this.income.bind(this.hours.multiply(this.payPerHour).multiply(52));
        this.rate = new SimpleDoubleProperty();
        this.rate.set(this.getIncome() >= 180000?45.0/100:this.getIncome() >= 120000?37.0/100:this.getIncome() >= 45000?32.0/100:this.getIncome() >= 15000?19.0/100:0);
        this.net = new SimpleDoubleProperty();
        this.net.bind(this.income.subtract(this.income.multiply(rate)));
        this.deduction = new SimpleDoubleProperty();
        this.deduction.bind(income.subtract(net));
        this.superRate = new SimpleDoubleProperty();
        this.superRate.set(0.09);
        this.superannuation = new SimpleDoubleProperty();
        this.superannuation.bind(income.multiply(superRate));
    }

    public void updateDetails(String name, String email, String phone, String address, String TFN, String type, int hours, double payPerHour){       
        this.name.set(name);    
        this.email.set(email);        
        this.phone.set(phone);     
        this.address.set(address);        
        this.TFN.set(TFN);    
        this.type.set(type);
        this.hours.set(hours);        
        this.payPerHour.set(payPerHour);
    }
    
    public void setEmployer(Employer e){
        this.employer = e;
    }
    
    public Employer getEmployer(){
        return this.employer;
    }
    
    public ReadOnlyStringProperty nameProperty() {
        return name;
    }

    public String getName(){
        return name.getValue();
    }
    
    public ReadOnlyStringProperty emailProperty() {
        return email;
    }

    public String getEmail(){
        return email.getValue();
    }
    
    public ReadOnlyStringProperty phoneProperty() {
        return phone;
    }

    public String getPhone(){
        return phone.getValue();
    }
    
    public ReadOnlyStringProperty addressProperty() {
        return address;
    }

    public String getAddress(){
        return address.getValue();
    }
    
    public ReadOnlyStringProperty TFNProperty() {
        return TFN;
    }

    public String getTFN(){
        return TFN.getValue();
    }
    
    public ReadOnlyStringProperty typeProperty() {
        return type;
    }

    public String getType(){
        return type.getValue();
    }
    
    public IntegerProperty hoursProperty() {
        return hours;
    }
    
    public int getHours(){
        return hours.get();
    }

    public ReadOnlyDoubleProperty payPerHourProperty() {
        return payPerHour;
    }    
    
    public double getPayPerHour(){
        return payPerHour.get();
    }
    
    public ReadOnlyDoubleProperty incomeProperty() {
        return income;
    }    
    
    public double getIncome(){
        return income.get();
    }
    
    public ReadOnlyDoubleProperty netProperty() {
        return net;
    }    
    
    public double getNet(){
        return net.get();
    }
    
    public ReadOnlyDoubleProperty rateProperty() {
        return rate;
    }    
    
    public double getRate(){
        return rate.get();
    }
    
    public ReadOnlyDoubleProperty deductionProperty() {
        return deduction;
    }    
    
    public double getDeduction(){
        return deduction.get();
    }
    
    public ReadOnlyDoubleProperty superProperty() {
        return superannuation;
    }    
    
    public double getSuper(){
        return superannuation.get();
    }
    
    public ReadOnlyDoubleProperty superRateProperty() {
        return superRate;
    }    
    
    public double getSuperRate(){
        return superRate.get();
    }
    
    public boolean hasName(String name){
        return getName().toLowerCase().contains(name.toLowerCase().trim());
    } 
    
    public boolean hasEmail(String email){
        return getEmail().toLowerCase().contains(email.toLowerCase().trim());
    }
}
