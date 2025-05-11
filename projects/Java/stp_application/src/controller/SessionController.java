package controller;

import javafx.event.*;
import javafx.fxml.*;
import model.*;
import au.edu.uts.ap.javafx.*;
import javafx.application.Platform;
import javafx.scene.image.*;
import javafx.stage.*;

public class SessionController extends Controller<Session> { 
    private Stage newStage = new Stage(); 
    
    @FXML private void viewLogin(ActionEvent event) throws Exception { 
        newStage.getIcons().add(new Image("view/book.png"));
        ViewLoader.showStage(new Session(), "/view/login.fxml", "Sign In", newStage);
    }
   
    @FXML private void exitProgram(ActionEvent event) {
        Platform.exit();
    }
}