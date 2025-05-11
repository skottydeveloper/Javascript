package model;

/**
 *
 * @author George
 */
import java.util.ArrayList;
import java.util.List;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;

public class Employees {

    private ObservableList<Employee> employees;
    private ObservableList<Employee> current;

    public Employees() {
        current = FXCollections.<Employee>observableArrayList();
        employees = FXCollections.observableArrayList(
                new Employee("Thomas Muller", "thomas.muller@uts.com", "99991111", "3 Byern St. Sydney 2001", "888-888", "Full-Time", 40, 35),
                new Employee("ALice Stefan", "alice.stefan@uts.com", "88881111", "24 Pitt St. Sydney 2001", "777-123", "Part-Time", 20, 29),
                new Employee("Lucy Lu", "lucy.lu@uts.com", "98981100", "11 Hunter St. Sydney 2100", "111-154", "Casual", 20, 45),
                new Employee("Andreas Brehme", "andreas.b@uts.com", "90001222", "91 Sussex St. Sydney 2100", "172-288", "Full-Time", 40, 33),
                new Employee("Ruddy Voller", "ruddy.v@uts.com", "98980000", "15 Stan St. Sydney 2100", "155-154", "Full-Time", 40, 80),
                new Employee("Monica Shwarz", "monica.s@uts.com", "92241188", "155 Jones St. Sydney 2001", "110-994", "Casual", 8, 20)
        );
        current.addAll(employees);
        employees.addListener(new ListChangeListener<Employee>() {
            @Override
            public void onChanged(javafx.collections.ListChangeListener.Change<? extends Employee> c) {
                current.clear();
                current.addAll(employees);
            }
        });
    }

    public void addEmployee(Employee employee) {
        employees.add(employee);
    }

    public void addEmployee(String name, String email, String phone, String address, String TFN, String type, int hours, double payPerHour) {
        employees.add(new Employee(name,email,phone,address,TFN,type,hours,payPerHour));
    }
    
    public boolean hasEmployee(String name) {
        for(Employee e:employees)
            if(e.hasName(name)&& !name.isEmpty())
                return true;
        return false;
    }
    
    public Employee getEmployee(String name){
        for(Employee p: employees)
            if(p.hasName(name))
                return p;
        return null;                        
    }

    public void remove(Employee p) {
        this.employees.remove(p);
    }

    public void remove(List<Employee> selectedItems) {
        this.employees.removeAll(selectedItems);
    }

    public void addEmployees(List<Employee> selectedItems) {
        this.employees.addAll(selectedItems);
    }

    public ObservableList<Employee> getCurrentList() {
        return this.current;
    }

    public void filterList(String name, String email) {

        List<Employee> temp = new ArrayList<>();

        employees.forEach((Employee p) -> {
            try {
                if ((p.hasName(name)) || (p.hasEmail(email))) {
                    temp.add(p);
                }
            } catch (NumberFormatException e) {
            }
        });

        this.current.clear();
        this.current.addAll(temp);
    }
}
