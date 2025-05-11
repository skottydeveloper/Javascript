package model;

import java.util.List;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.ReadOnlyDoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

/**
 *
 * @author George
 */
public class STP {
    private DoubleProperty totalWages;
    private DoubleProperty totalTax;
    private DoubleProperty totalNet;
    private DoubleProperty totalSuper;
    private DoubleProperty bas;
    private Employees employees;
    private ObservableList<Report> reports;
    
    public STP(){
        this.employees = new Employees();
        this.reports = FXCollections.<Report>observableArrayList();
        createSTP();        
        this.totalWages = new SimpleDoubleProperty();  
        this.totalWages.set(getTotalWages());
        this.totalTax = new SimpleDoubleProperty();  
        this.totalTax.set(getTotalTax());
        this.totalSuper = new SimpleDoubleProperty();
        this.totalSuper.set(getTotalSuper());
        this.totalNet = new SimpleDoubleProperty();  
        this.totalNet.set(getTotalNet());
        this.bas = new SimpleDoubleProperty();
        this.bas.bind(totalSuper.add(totalTax));
    }
    
    private void createSTP(){
        getEmployees().forEach(e -> {
            reports.add(new Report(e));
        });
    }
    
    public ReadOnlyDoubleProperty totalWagesProperty() {
        return totalWages;
    } 
    
    public double getTotalWages(){
        double total = 0;
        return getEmployees().stream().map(e -> e.getIncome()).reduce(total, (accumulator, _item) -> accumulator + _item);
    }
    
    public ReadOnlyDoubleProperty totalTaxProperty() {
        return totalTax;
    } 
    
    public double getTotalTax(){
        double total = 0;
        return getEmployees().stream().map(e -> e.getDeduction()).reduce(total, (accumulator, _item) -> accumulator + _item);
    }
    
    public ReadOnlyDoubleProperty totalNetProperty() {
        return totalNet;
    } 
    
    public double getTotalNet(){
        double total = 0;
        return getEmployees().stream().map(e -> e.getNet()).reduce(total, (accumulator, _item) -> accumulator + _item);
    }
    
    public ReadOnlyDoubleProperty totalSuperProperty() {
        return totalSuper;
    } 
    
    public double getTotalSuper(){
        double total = 0;
        return getEmployees().stream().map(e -> e.getSuper()).reduce(total, (accumulator, _item) -> accumulator + _item);
    }   
    
    public ReadOnlyDoubleProperty basProperty() {
        return bas;
    } 
    
    public double getBas(){
        return bas.get();
    }
    
    public ObservableList<Employee> getEmployees(){
        return this.employees.getCurrentList();
    }
    
    public ObservableList<Report> reports(){
        return this.reports;
    }
}
