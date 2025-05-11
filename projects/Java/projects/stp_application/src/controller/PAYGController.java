package controller;

import javafx.event.*;
import javafx.fxml.*;
import model.*;
import au.edu.uts.ap.javafx.*;

public class PAYGController extends Controller<Employee>  {
    @FXML private void closePAYG(ActionEvent event) {
        stage.close();
    }
}