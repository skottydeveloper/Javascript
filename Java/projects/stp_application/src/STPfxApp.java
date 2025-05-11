import javafx.application.Application;
import javafx.stage.*;
import model.*;
import au.edu.uts.ap.javafx.*;
import javafx.scene.image.*;

public class STPfxApp extends Application {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage stage) throws Exception {
        ViewLoader.showStage(new Session(), "/view/session.fxml", "STPFX - Employer Mode", stage);
        stage.getIcons().add(new Image("view/book.png"));
    }
}