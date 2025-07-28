package org.blindwolf.app;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.blindwolf.app.view.ChessboardView; 

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        // 1. Instantiate chessboard view.
        ChessboardView board = new ChessboardView();

        // 2. Create the scene, using the board as its root.
        Scene scene = new Scene(board, ChessboardView.BOARD_SIZE * ChessboardView.SQUARE_SIZE, ChessboardView.BOARD_SIZE * ChessboardView.SQUARE_SIZE);

        // 3. Set up and show the stage.
        primaryStage.setTitle("Rooks");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
