package model;

import javafx.beans.property.ReadOnlyStringProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.ObservableList;

/**
 *
 * @author George
 */
public class Employer {

    private StringProperty name;
    private StringProperty email;
    private StringProperty password;
    private Employees employees;
 

    public Employer(String name, String email, String password) {
        this.name = new SimpleStringProperty();
        this.name.set(name);
        this.email = new SimpleStringProperty();
        this.email.set(email);
        this.password = new SimpleStringProperty();
        this.password.set(password);
        employees = new Employees();
    }

    public Employer() {
        this.employees = new Employees();
    }

    public ReadOnlyStringProperty nameProperty() {
        return name;
    }

    public String getName() {
        return name.getValue();
    }

    public void setName(String name) {
        this.name.set(name);
    }

    public ReadOnlyStringProperty emailProperty() {
        return email;
    }

    public String getEmail() {
        return email.getValue();
    }

    public void setEmail(String email) {
        this.email.set(email);
    }

    public ReadOnlyStringProperty passwordProperty() {
        return password;
    }

    public String getPassword() {
        return password.getValue();
    }

    public void setPassword(String password) {
        this.password.set(password);
    }
    
    public boolean login(String email, String password) {
        return this.getEmail().equals(email) && this.getPassword().equals(password);
    }
    
    public ObservableList<Employee> getEmployees(){
        return this.employees.getCurrentList();
    }
    
    public void addEmployee(Employee e){
        this.employees.addEmployee(e);
    }
    
    public boolean checkEmployee(String name){
        return this.employees.hasEmployee(name);
    }
    
    public void removeEmployee(Employee e){
        this.employees.remove(e);
    }
    
    public void filterList(String name, String email) {
        this.employees.filterList(name, email);
    }
}
