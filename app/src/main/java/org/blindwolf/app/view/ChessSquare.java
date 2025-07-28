package org.blindwolf.app.view;

import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

/**
  *Represents a single, focusable square on the chessboard
  *This component is responsible for its own appearnace and accessibility information
**/

public class ChessSquare extends StackPane {

//Constants 

  private final int row;
  private final int col;
  private final Rectangle background;

//Constructor

  public ChessSquare (boolean isLightSquare, int row, int col) {
    this.row = row;
    this.col = col;

    //The background Rectangle will determine the color of the ChessSquare
    this.background = new Rectangle(ChessboardView.SQUARE_SIZE, ChessboardView.SQUARE_SIZE);
    if (isLightSquare) {
      background.setFill(Color.web("#F0D9B5"));
    } else {
      background.setFill(Color.web("#B58863"));
    }
    getChildren().add(background);

    //Make the square focusable by keyboard
    setFocusTraversable(true);
    //Set the text screenreaders will announce
    setAccessibleText(getAlgebraicNotation());

    //Add a visual indicator for which square has focus
    focusedProperty().addListener((obs, oldVal, newVal) -> {
      if (newVal) {
        setStyle("-fx-border-color: #f3ca20; -fx-border-width: 4;");
      } else {
        // Remove the border when focus is lost.
        setStyle("");
      }
    });
  }
//Helper Methods

/**
  *Converts the squares row/column index to algebraic notation
  *Example: (0,0) -> "A8, (7, 7) -> "H1"
  *@return the algebraic notation as a string
**/
    private String getAlgebraicNotation() {
      char file = (char) ('a' + this.col);
      char rank = (char) ('8' - this.row);       
    return "" + file + rank; 
    }
}
