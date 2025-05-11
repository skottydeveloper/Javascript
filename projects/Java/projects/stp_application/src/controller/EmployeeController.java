package controller;

import javafx.event.*;
import javafx.fxml.*;
import model.*;
import au.edu.uts.ap.javafx.*;
import javafx.scene.control.*;

public class EmployeeController extends Controller<Employee> {
    @FXML private Button addButton;
    @FXML private Button updateButton;
    @FXML private Button closeButton;
    @FXML private TextField name;
    @FXML private TextField email;
    @FXML private TextField phone;
    @FXML private TextField address;
    @FXML private TextField tfn;
    @FXML private TextField hours;
    @FXML private TextField rate;
    @FXML private TextField type;
    
    @FXML private void initialize() {
        if (name.getText().isEmpty()) {
            addButton.setDisable(false);
            updateButton.setDisable(true);
        } else {
            addButton.setDisable(true);
            updateButton.setDisable(false);
        }
    }
    
    private String getName() {
        return name.getText();
    }
    
    private String getEmail() {
        return email.getText();
    }
    
    private String getPhone() {
        return phone.getText();
    }
    
    private String getAddress() {
        return address.getText();
    }
    
    private String getTFN() {
        return tfn.getText();
    }
    
    private String getType() {
        return type.getText();
    }
    
    private int getHours() {
        return Integer.parseInt(hours.getText());
    }
    
    private Double getRate() {
        return Double.parseDouble(rate.getText());
    }
    
    public final Employee getEmployee() {
        return model;
    }
    
    @FXML private void handleAdd(ActionEvent event) throws InputException {
        //getEmployee().addEmployee(getName(), getEmail(), getPhone(), getAddress(), getTFN(), getType(), getHours(), getRate());
        //model.updateDetails();
        stage.close();
    }
    
    @FXML private void handleUpdate(ActionEvent event) throws Exception { 
        stage.close();
    }
   
    @FXML private void closeEmployee(ActionEvent event) {
        stage.close();
    }
}
