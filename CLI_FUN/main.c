#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "hashTable.h"
#include "chess.h"

int main(void)
{
    ChessGame chessGame;
    createChessGame(&chessGame);
    while (true)
    {
        printChessboard(&chessGame);
        char playerMove[8];
        printf("\nYour move: ");
        scanf("%s", playerMove);
        printf("\n");
        if (strlen(playerMove) != 4)
        {
            printf("move must be 4 characters\n");
            continue;
        }

        char startMoveColumn = playerMove[0];
        int startMoveRow = playerMove[1] - '0';
        int startRowIndex = chessGetRowIndex(startMoveRow);
        int startColumnIndex = chessGetColumnIndex(startMoveColumn);

        char endMoveColumn = playerMove[2];
        int endMoveRow = playerMove[3] - '0';
        int endRowIndex = chessGetRowIndex(endMoveRow);
        int endColumnIndex = chessGetColumnIndex(endMoveColumn);
        if (
            startRowIndex == -1 || startColumnIndex == -1 || endRowIndex == -1 || endColumnIndex == -1)
        {
            printf("INVALID MOVE: coordinate out of range");
            continue;
        }

        Tile startTile = chessGame.board[startRowIndex][startColumnIndex];
        if (startTile.piece == '-')
        {
            printf(
                "INVALID MOVE: there is no piece on %c%d.\n",
                startMoveColumn,
                startMoveRow);
            continue;
        }
        if (startTile.pieceColor != chessGame.turn)
        {
            const char *color = chessGame.turn == 'W' ? "white's" : "black's";
            printf("INVALID MOVE: It's %s turn\n", color);
            continue;
        }

        Tile endTile = chessGame.board[endRowIndex][endColumnIndex];
        bool isMoveValid = chessIsMoveValid(&chessGame, &startTile, &endTile);
        if (isMoveValid)
        {
            chessMakeMove(&chessGame, &startTile, &endTile);
        }
    }
    printChessboard(&chessGame);
    return 0;
}
