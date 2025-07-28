package org.blindwolf.app;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.blindwolf.app.view.ChessboardView;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        ChessboardView board = new ChessboardView();

        Scene scene = new Scene(board, ChessboardView.BOARD_SIZE * ChessboardView.SQUARE_SIZE, ChessboardView.BOARD_SIZE * ChessboardView.SQUARE_SIZE);

        primaryStage.setTitle("Rooks");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
        
        board.requestInitialFocus();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
