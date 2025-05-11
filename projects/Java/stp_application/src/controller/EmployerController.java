package controller;

import javafx.event.*;
import javafx.fxml.*;
import javafx.stage.*;
import model.*;
import au.edu.uts.ap.javafx.*;
import javafx.scene.control.*;
import javafx.scene.image.*;

public class EmployerController extends Controller<Employer> {
    private Stage addRetrieveEmployee = new Stage();
    private Stage viewPAYG = new Stage();
    private Stage viewSTP = new Stage();
  
    @FXML private Button addButton;
    @FXML private Button deleteButton;
    @FXML private Button selectButton; 
    @FXML private Button PAYGButton;
    @FXML private Button STPButton;
    @FXML private Button closeButton; 
    @FXML private TextField name; 
    @FXML private TextField email;
    @FXML private TableView<Employees> employeesTv;
    
    private Employees getEmployee() {
        return employeesTv.getSelectionModel().getSelectedItem();
    }
    
    @FXML private void initialize() {
        name.setPromptText("Filter by name");
        email.setPromptText("Filter by email");
        employeesTv.getSelectionModel().selectedItemProperty().addListener(
            (observable, oldEmployee, newEmployee) -> {
            deleteButton.setDisable(newEmployee == null);
            selectButton.setDisable(newEmployee == null);
            PAYGButton.setDisable(newEmployee == null);
        });
        //Employer employer = getEmployer().filterList(getName(), getEmail());
    }
    
    public final Employer getEmployer() {
        return model;
    }
    
    public String getName() {
        return name.getText();
    }
    
    public String getEmail() {
        return email.getText();
    }
   
    @FXML private void addEmployee(ActionEvent event) throws Exception { 
        addRetrieveEmployee.getIcons().add(new Image("view/edit.png"));
        ViewLoader.showStage(new Employer(), "/view/employee.fxml", "Adding New Employee", addRetrieveEmployee);
    }
    
    @FXML private void deleteEmployee(ActionEvent event) throws Exception { 
        employeesTv.getItems().remove(employeesTv.getSelectionModel().getSelectedItem());
        deleteButton.setDisable(true);
        selectButton.setDisable(true);
        PAYGButton.setDisable(true);
        employeesTv.getSelectionModel().clearSelection();
    }
    
    @FXML private void selectEmployee(ActionEvent event) throws Exception { 
        addRetrieveEmployee.getIcons().add(new Image("view/edit.png"));
        ViewLoader.showStage(new Employer(), "/view/employee.fxml", "Accessing File:", addRetrieveEmployee);
        deleteButton.setDisable(true);
        selectButton.setDisable(true);
        PAYGButton.setDisable(true);
        employeesTv.getSelectionModel().clearSelection();
    }
    
    @FXML private void viewPAYG(ActionEvent event) throws Exception { 
        viewPAYG.getIcons().add(new Image("view/edit.png"));
        ViewLoader.showStage(new Employer(), "/view/payg.fxml", "PAYG Report", viewPAYG);
        deleteButton.setDisable(true);
        selectButton.setDisable(true);
        PAYGButton.setDisable(true);
        employeesTv.getSelectionModel().clearSelection();
    }
    
    @FXML private void viewSTP(ActionEvent event) throws Exception { 
        viewSTP.getIcons().add(new Image("view/stp.png"));
        ViewLoader.showStage(new STP(), "/view/stp.fxml", "STP Report", viewSTP);
    }
   
    @FXML private void exitEmployerMenu(ActionEvent event) {
        stage.close();
    }
}