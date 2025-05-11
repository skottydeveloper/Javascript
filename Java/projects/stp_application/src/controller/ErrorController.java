package controller;

import javafx.event.*;
import javafx.fxml.*;
import model.*;
import au.edu.uts.ap.javafx.*;

public class ErrorController extends Controller<InputException> {
    public final InputException getException() {
        return model;
    }
    
    @FXML private void handleOK(ActionEvent event) {
        stage.close();
    }
}