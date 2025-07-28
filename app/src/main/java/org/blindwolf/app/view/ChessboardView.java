package org.blindwolf.app.view;

import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

/**
  *Represents the visual component of the chessboard
  *This class extends GridPane and draws an 8x8 grid
  *with its appropriate squares
*/


public class ChessboardView extends GridPane {
    //Set constants for board dimensions
    public static final int BOARD_SIZE = 8;
    public static final int SQUARE_SIZE = 80; //Number of pixels for each square on the board

    //Create constructor method to create an 8x8 grid of alternating colored squares
    public ChessboardView() {
        //Loop through each rank and file to create an 8x8 grid
        for (int file=0; file<BOARD_SIZE; file++){
            for (int rank=0; rank<BOARD_SIZE; rank++) {
                //Create a square for each cell on the grid
                Rectangle square = new Rectangle(SQUARE_SIZE, SQUARE_SIZE);

                //Determine the color of the square based on its position
                if((rank + file) %2 == 0) {
                    square.setFill(Color.web("#F0D9B5")); //Light wood
                } else {
                    square.setFill(Color.web("#B58863")); //Dark wood
                }

                //Add the square to the grid at the specified rank/file coordinate
                this.add(square, file, rank);
            }
        }
    }

}