package controller;

import javafx.event.*;
import javafx.fxml.*;
import javafx.stage.*;
import model.*;
import au.edu.uts.ap.javafx.*;
import javafx.scene.control.*;
import javafx.scene.image.*;

public class LoginController extends Controller<Session>  {  
    private Stage newStage = new Stage();
    @FXML private TextField email;
    @FXML private PasswordField password;
    @FXML private Label error_text;
    
    @FXML private void handleLogin(ActionEvent event) throws Exception {
        Employer employer = returnEmployer().getEmployer(getEmail(), getPassword());
        
        if (employer != null) {
            newStage.getIcons().add(new Image("view/employer.png"));
            ViewLoader.showStage(employer, "/view/employer.fxml", "Session Admin: " + employer.getName(), newStage);
            stage.close();
        } else {
            error_text.setText("Incorrect login details");
            email.setText("");
            password.setText("");
        }
    }
    
    public final Session returnEmployer() {
        return model;
    }
    
    public String getEmail() {
        return email.getText();
    }
    
    public String getPassword() {
        return password.getText();
    }
   
    @FXML private void cancelLogin(ActionEvent event) {
        stage.close();
    }
}