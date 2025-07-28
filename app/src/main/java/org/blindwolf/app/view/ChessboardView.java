package org.blindwolf.app.view;

import javafx.application.Platform;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;

public class ChessboardView extends GridPane {

    public static final int BOARD_SIZE = 8;
    public static final int SQUARE_SIZE = 80;

    private final ChessSquare[][] squares = new ChessSquare[BOARD_SIZE][BOARD_SIZE];
    private int focusedRow = 0;
    private int focusedCol = 0;

    public ChessboardView() {
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                boolean isLightSquare = (row + col) % 2 == 0;
                ChessSquare square = new ChessSquare(isLightSquare, row, col);
                this.squares[row][col] = square;
                this.add(square, col, row);
            }
        }

        setupKeyHandler();
    }

    private void setupKeyHandler() {
        this.setOnKeyPressed(event -> {
            KeyCode code = event.getCode();
            int newRow = focusedRow;
            int newCol = focusedCol;

            switch (code) {
                case UP:    newRow = Math.max(0, focusedRow - 1); break;
                case DOWN:  newRow = Math.min(BOARD_SIZE - 1, focusedRow + 1); break;
                case LEFT:  newCol = Math.max(0, focusedCol - 1); break;
                case RIGHT: newCol = Math.min(BOARD_SIZE - 1, focusedCol + 1); break;
                default:
                    return; // Do nothing for other keys
            }

            // If the key press resulted in a move, update the focus.
            if (newRow != focusedRow || newCol != focusedCol) {
                updateFocus(newRow, newCol);
            }
            
            event.consume(); 
        });
    }

    /**
     * Moves the application focus to a new square.
     * @param newRow The target row.
     * @param newCol The target column.
     */
    private void updateFocus(int newRow, int newCol) {
        this.focusedRow = newRow;
        this.focusedCol = newCol;
        squares[newRow][newCol].requestFocus();
    }
    
    public void requestInitialFocus() {
        Platform.runLater(() -> squares[0][0].requestFocus());
    }
}
