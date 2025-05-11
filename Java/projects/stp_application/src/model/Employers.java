package model;

/**
 *
 * @author George
 */

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Employers {
    private final ObservableList<Employer> employers;

    public Employers() {
        employers = FXCollections.observableArrayList(
                new Employer("John Smith", "john.smith@uts.com", "super123"),
                new Employer("Jane Doe", "jane.doe@uts.com", "user222")
        );      
    }
   
    public boolean hasEmployer(String name, String password) {
        return employers.stream().anyMatch(p -> (p.login(name, password)));
    }

    public Employer getEmployer(String name, String password){
        for(Employer e:employers)
            if(e.login(name, password))
                return e;
        return null;
    }   
}

