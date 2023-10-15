#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "hashTable.h"

char letters []= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

typedef struct Tile
{
    int id;
    int row;
    char column;
    char piece;
    char pieceColor;
    int rowIndex;
    int colIndex;
} Tile;

char turn = 'W';

Tile chessboard[8][8] = {
    {{0, 1, 'A', 'R', 'B', 0, 0}, {1, 1, 'B', 'N', 'B', 0, 1}, {2, 1, 'C', 'B', 'B', 0, 2}, {3, 1, 'D', 'Q', 'B', 0, 3}, {4, 1, 'E', 'K', 'B', 0, 4}, {5, 1, 'F', 'B', 'B', 0, 5}, {6, 1, 'G', 'N', 'B', 0, 6}, {7, 1, 'H', 'R', 'B', 0, 7}},
    {{8, 2, 'A', 'P', 'B', 1, 0}, {9, 2, 'B', 'P', 'B', 1, 1}, {10, 2, 'C', 'P', 'B', 1, 2}, {11, 2, 'D', 'P', 'B', 1, 3}, {12, 2, 'E', 'P', 'B', 1, 4}, {13, 2, 'F', 'P', 'B', 1, 5}, {14, 2, 'G', 'P', 'B', 1, 6}, {15, 2, 'H', 'P', 'B', 1, 7}},
    {{16, 3, 'A', '-', '-', 2, 0}, {17, 3, 'B', '-', '-', 2, 1}, {18, 3, 'C', '-', '-', 2, 2}, {19, 3, 'D', '-', '-', 2, 3}, {20, 3, 'E', '-', '-', 2, 4}, {21, 3, 'F', '-', '-', 2, 5}, {22, 3, 'G', '-', '-', 2, 6}, {23, 3, 'H', '-', '-', 2, 7}},
    {{24, 4, 'A', '-', '-', 3, 0}, {25, 4, 'B', '-', '-', 3, 1}, {26, 4, 'C', '-', '-', 3, 2}, {27, 4, 'D', '-', '-', 3, 3}, {28, 4, 'E', '-', '-', 3, 4}, {29, 4, 'F', '-', '-', 3, 5}, {30, 4, 'G', '-', '-', 3, 6}, {31, 4, 'H', '-', '-', 3, 7}},
    {{32, 5, 'A', '-', '-', 4, 0}, {33, 5, 'B', '-', '-', 4, 1}, {34, 5, 'C', '-', '-', 4, 2}, {35, 5, 'D', '-', '-', 4, 3}, {36, 5, 'E', '-', '-', 4, 4}, {37, 5, 'F', '-', '-', 4, 5}, {38, 5, 'G', '-', '-', 4, 6}, {39, 5, 'H', '-', '-', 4, 7}},
    {{40, 6, 'A', '-', '-', 5, 0}, {41, 6, 'B', '-', '-', 5, 1}, {42, 6, 'C', '-', '-', 5, 2}, {43, 6, 'D', '-', '-', 5, 3}, {44, 6, 'E', '-', '-', 5, 4}, {45, 6, 'F', '-', '-', 5, 5}, {46, 6, 'G', '-', '-', 5, 6}, {47, 6, 'H', '-', '-', 5, 7}},
    {{48, 7, 'A', 'P', 'W', 6, 0}, {49, 7, 'B', 'P', 'W', 6, 1}, {50, 7, 'C', 'P', 'W', 6, 2}, {51, 7, 'D', 'P', 'W', 6, 3}, {52, 7, 'E', 'P', 'W', 6, 4}, {53, 7, 'F', 'P', 'W', 6, 5}, {54, 7, 'G', 'P', 'W', 6, 6}, {55, 7, 'H', 'P', 'W', 6, 7}},
    {{56, 8, 'A', 'R', 'W', 7, 0}, {57, 8, 'B', 'N', 'W', 7, 1}, {58, 8, 'C', 'B', 'W', 7, 2}, {59, 8, 'D', 'Q', 'W', 7, 3}, {60, 8, 'E', 'K', 'W', 7, 4}, {61, 8, 'F', 'B', 'W', 7, 5}, {62, 8, 'G', 'N', 'W', 7, 6}, {63, 8, 'H', 'R', 'W', 7, 7}}
};

void chessboard_print(Tile chessboard[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (col == 0) {
                printf(" \033[38;5;243m%d\033[0m ", 9 - (row + 1));
            }
            Tile tile = chessboard[row][col];
            if (tile.pieceColor == 'W')
            {
                printf(" \033[38;5;208m%c\033[0m ", tile.piece);
            }
            else if (tile.pieceColor == 'B')
            {
                printf(" \033[38;5;160m%c\033[0m ", tile.piece);
            }
            else
            {
                printf(" %c ", tile.piece);
            }

            bool isEndOfRow = col == 7;
            if (isEndOfRow)
            {
                printf("\n");
            }
        }
    }
    printf("   ");
    for (int i = 0; i < 8; i++) {
        printf(" \033[38;5;243m%c\033[0m ", letters[i]);
            bool isEndOfRow = i == 7;
            if (isEndOfRow)
            {
                printf("\n");
            }
    }
    printf("\n");
}

int getColumnIndex(char column) {
    for (int i = 0; i < 8; i++) {
        if (column == letters[i]) {
            return i;
        }
    }
    return -1;
}

int getRowIndex(int row) {
    return 8 - row;
}

int main(void)
{
    while (true)
    {
        chessboard_print(chessboard);
        char playerMove[8];
        printf("\nYour move: ");
        scanf("%s", playerMove);
        printf("\n");
        if (strlen(playerMove) != 4) {
            printf("move must be 4 characters\n");
            continue;
        }

        char startMoveColumn = playerMove[0];
        int startMoveRow = playerMove[1] - '0';
        int startRowIndex = getRowIndex(startMoveRow);
        int startColumnIndex = getColumnIndex(startMoveColumn);

        char endMoveColumn = playerMove[2];
        int endMoveRow = playerMove[3] - '0';
        int endRowIndex = getRowIndex(endMoveRow);
        int endColumnIndex = getColumnIndex(endMoveColumn);
        if (
            startRowIndex == -1
            || startColumnIndex == -1
            || endRowIndex == -1
            || endColumnIndex == -1
        ) {
            printf("INVALID MOVE: coordinate out of range");
            continue;
        }

        // printf("%d %d %d %d\n", startRowIndex, startColumnIndex, endRowIndex, endColumnIndex);

        Tile startTile = chessboard[startRowIndex][startColumnIndex];
        if (startTile.piece == '-') {
            printf(
                "INVALID MOVE: there is no piece on %c%d.\n",
                startMoveColumn,
                startMoveRow
            );
            continue;
        }
        if (startTile.pieceColor != turn) {
            const char *color = turn == 'W' ? "white's" : "black's";
            printf("INVALID MOVE: It's %s turn\n", color);
            continue;
        }
        turn = turn == 'W' ? 'B' : 'W';
        Tile endTile = chessboard[endRowIndex][endColumnIndex];
        if (startTile.piece == 'N') {
            int possibleMoves[8][2] = {
                {startTile.rowIndex + 2, startTile.colIndex + 1},
                {startTile.rowIndex + 1, startTile.colIndex + 2},
                {startTile.rowIndex - 1, startTile.colIndex + 2},
                {startTile.rowIndex - 2, startTile.colIndex + 1},
                {startTile.rowIndex - 2, startTile.colIndex - 1},
                {startTile.rowIndex - 1, startTile.colIndex - 2},
                {startTile.rowIndex + 1, startTile.colIndex - 2},
                {startTile.rowIndex + 2, startTile.colIndex - 1}
            };
            bool isMoveValid = false;
            for (int i = 0; i < 8; i++) {
                int rowIndex = possibleMoves[i][0];
                int colIndex = possibleMoves[i][1];
                bool isRowInRange = rowIndex > 0 && rowIndex < 7;
                bool isColInRange = colIndex > 0 && colIndex < 7;
                if (!isRowInRange || !isColInRange) {
                    continue;
                }
                bool isMoveInRange = isRowInRange && isColInRange;
                bool isPlayerMove = endTile.rowIndex == rowIndex && endTile.colIndex == colIndex;
                if (isMoveInRange && isPlayerMove) {
                    isMoveValid = true;
                }
            }

            if (!isMoveValid) {
                printf("INVALID MOVE: Knight cannot reach that square\n");
                continue;
            }
        }
        turn = turn == 'W' ? 'B' : 'W';
        chessboard[startRowIndex][startColumnIndex].piece = '-';
        chessboard[startRowIndex][startColumnIndex].pieceColor = '-';
        chessboard[endRowIndex][endColumnIndex].piece = startTile.piece;
        chessboard[endRowIndex][endColumnIndex].pieceColor = startTile.pieceColor;
    }
    chessboard_print(chessboard);
    return 0;
}
