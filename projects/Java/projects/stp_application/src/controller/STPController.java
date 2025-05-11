package controller;

import javafx.event.*;
import javafx.fxml.*;
import model.*;
import au.edu.uts.ap.javafx.*;

public class STPController extends Controller<STP> {
    @FXML private void closeSTP(ActionEvent event) {
        stage.close();
    }
}