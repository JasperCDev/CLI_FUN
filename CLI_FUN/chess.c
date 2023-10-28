#include "chess.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
  bool isWhite;
  bool isCastle;
  bool isCastleQueenSide;
  bool isEnPassant;
  bool isUp;
  bool isLeft;
  bool isAttackMove;
  bool isRowMove;
  bool isColMove;
  bool isDiagMove;
} MoveInfo;

char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

void printError(const char *errorMessage)
{
  printf("\033[31mINVALID MOVE: %s\033[0m\n\n", errorMessage);
}

void createChessGame(ChessGame *chessGame)
{
  Tile initialBoard[8][8] = {{{0, 1, 'A', 'R', 'B', 0, 0},
                              {1, 1, 'B', 'N', 'B', 0, 1},
                              {2, 1, 'C', 'B', 'B', 0, 2},
                              {3, 1, 'D', 'Q', 'B', 0, 3},
                              {4, 1, 'E', 'K', 'B', 0, 4},
                              {5, 1, 'F', 'B', 'B', 0, 5},
                              {6, 1, 'G', 'N', 'B', 0, 6},
                              {7, 1, 'H', 'R', 'B', 0, 7}},
                             {{8, 2, 'A', 'P', 'B', 1, 0},
                              {9, 2, 'B', 'P', 'B', 1, 1},
                              {10, 2, 'C', 'P', 'B', 1, 2},
                              {11, 2, 'D', 'P', 'B', 1, 3},
                              {12, 2, 'E', 'P', 'B', 1, 4},
                              {13, 2, 'F', 'P', 'B', 1, 5},
                              {14, 2, 'G', 'P', 'B', 1, 6},
                              {15, 2, 'H', 'P', 'B', 1, 7}},
                             {{16, 3, 'A', '-', '-', 2, 0},
                              {17, 3, 'B', '-', '-', 2, 1},
                              {18, 3, 'C', '-', '-', 2, 2},
                              {19, 3, 'D', '-', '-', 2, 3},
                              {20, 3, 'E', '-', '-', 2, 4},
                              {21, 3, 'F', '-', '-', 2, 5},
                              {22, 3, 'G', '-', '-', 2, 6},
                              {23, 3, 'H', '-', '-', 2, 7}},
                             {{24, 4, 'A', '-', '-', 3, 0},
                              {25, 4, 'B', '-', '-', 3, 1},
                              {26, 4, 'C', '-', '-', 3, 2},
                              {27, 4, 'D', '-', '-', 3, 3},
                              {28, 4, 'E', '-', '-', 3, 4},
                              {29, 4, 'F', '-', '-', 3, 5},
                              {30, 4, 'G', '-', '-', 3, 6},
                              {31, 4, 'H', '-', '-', 3, 7}},
                             {{32, 5, 'A', '-', '-', 4, 0},
                              {33, 5, 'B', '-', '-', 4, 1},
                              {34, 5, 'C', '-', '-', 4, 2},
                              {35, 5, 'D', '-', '-', 4, 3},
                              {36, 5, 'E', '-', '-', 4, 4},
                              {37, 5, 'F', '-', '-', 4, 5},
                              {38, 5, 'G', '-', '-', 4, 6},
                              {39, 5, 'H', '-', '-', 4, 7}},
                             {{40, 6, 'A', '-', '-', 5, 0},
                              {41, 6, 'B', '-', '-', 5, 1},
                              {42, 6, 'C', '-', '-', 5, 2},
                              {43, 6, 'D', '-', '-', 5, 3},
                              {44, 6, 'E', '-', '-', 5, 4},
                              {45, 6, 'F', '-', '-', 5, 5},
                              {46, 6, 'G', '-', '-', 5, 6},
                              {47, 6, 'H', '-', '-', 5, 7}},
                             {{48, 7, 'A', 'P', 'W', 6, 0},
                              {49, 7, 'B', 'P', 'W', 6, 1},
                              {50, 7, 'C', 'P', 'W', 6, 2},
                              {51, 7, 'D', 'P', 'W', 6, 3},
                              {52, 7, 'E', 'P', 'W', 6, 4},
                              {53, 7, 'F', 'P', 'W', 6, 5},
                              {54, 7, 'G', 'P', 'W', 6, 6},
                              {55, 7, 'H', 'P', 'W', 6, 7}},
                             {{56, 8, 'A', 'R', 'W', 7, 0},
                              {57, 8, 'B', 'N', 'W', 7, 1},
                              {58, 8, 'C', 'B', 'W', 7, 2},
                              {59, 8, 'D', 'Q', 'W', 7, 3},
                              {60, 8, 'E', 'K', 'W', 7, 4},
                              {61, 8, 'F', 'B', 'W', 7, 5},
                              {62, 8, 'G', 'N', 'W', 7, 6},
                              {63, 8, 'H', 'R', 'W', 7, 7}}};

  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      chessGame->board[row][col] = initialBoard[row][col];
    }
  }
  chessGame->turn = 'W';
};

int chessGetColumnIndex(char column)
{
  for (int i = 0; i < 8; i++)
  {
    if (column == letters[i])
    {
      return i;
    }
  }
  return -1;
};

int chessGetRowIndex(int row) { return 8 - row; };

void printChessboard(ChessGame *chessGame)
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      if (col == 0)
      {
        printf(" \033[38;5;243m%d\033[0m ", 9 - (row + 1));
      }
      Tile tile = chessGame->board[row][col];
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
  for (int i = 0; i < 8; i++)
  {
    printf(" \033[38;5;243m%c\033[0m ", letters[i]);
    bool isEndOfRow = i == 7;
    if (isEndOfRow)
    {
      printf("\n");
    }
  }
  printf("\n");
};

void movePiece(ChessGame *chessGame, Tile *startTile, Tile *endTile)
{
  chessGame->board[startTile->rowIndex][startTile->colIndex].piece = '-';
  chessGame->board[startTile->rowIndex][startTile->colIndex].pieceColor = '-';
  chessGame->board[endTile->rowIndex][endTile->colIndex].piece = startTile->piece;
  chessGame->board[endTile->rowIndex][endTile->colIndex].pieceColor = startTile->pieceColor;
}

bool isMoveValidKnight(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  int possibleMoves[8][2] = {{startTile->rowIndex + 2, startTile->colIndex + 1},
                             {startTile->rowIndex + 1, startTile->colIndex + 2},
                             {startTile->rowIndex - 1, startTile->colIndex + 2},
                             {startTile->rowIndex - 2, startTile->colIndex + 1},
                             {startTile->rowIndex - 2, startTile->colIndex - 1},
                             {startTile->rowIndex - 1, startTile->colIndex - 2},
                             {startTile->rowIndex + 1, startTile->colIndex - 2},
                             {startTile->rowIndex + 2, startTile->colIndex - 1}};

  for (int i = 0; i < 8; i++)
  {
    int rowIndex = possibleMoves[i][0];
    int colIndex = possibleMoves[i][1];
    bool isPlayerMove = endTile->rowIndex == rowIndex && endTile->colIndex == colIndex;
    if (isPlayerMove)
    {
      return true;
    }
  }
  printError("Knight cannot access that square.");
  return false;
}

bool isMoveValidPawn(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  bool isWhite = startTile->pieceColor == 'W';
  int possibleWhiteMoves[4][3] = {{'A', startTile->rowIndex - 1, startTile->colIndex},
                                  {'B', startTile->rowIndex - 2, startTile->colIndex},
                                  {'C', startTile->rowIndex - 1, startTile->colIndex - 1},
                                  {'D', startTile->rowIndex - 1, startTile->colIndex + 1}};

  int possibleBlackMoves[4][3] = {{'A', startTile->rowIndex + 1, startTile->colIndex},
                                  {'B', startTile->rowIndex + 2, startTile->colIndex},
                                  {'C', startTile->rowIndex + 1, startTile->colIndex + 1},
                                  {'D', startTile->rowIndex + 1, startTile->colIndex - 1}};

  for (int i = 0; i < 4; i++)
  {
    int moveType = isWhite ? possibleWhiteMoves[i][0] : possibleBlackMoves[i][0];
    int rowIndex = isWhite ? possibleWhiteMoves[i][1] : possibleBlackMoves[i][1];
    int colIndex = isWhite ? possibleWhiteMoves[i][2] : possibleBlackMoves[i][2];
    bool isPlayerMove = endTile->rowIndex == rowIndex && endTile->colIndex == colIndex;
    if (isPlayerMove)
    {
      switch (moveType)
      {
      // move forward once
      case 'A':
      {
        bool isOccupied = endTile->piece != '-';
        if (isOccupied)
        {
          printError("There is a piece in the way.");
          return false;
        }
        return true;
      }
      // move forward twice
      case 'B':
      {
        bool isFirstMove = isWhite ? startTile->rowIndex == 6 : startTile->rowIndex == 1;
        if (!isFirstMove)
        {
          printError("You can only move twice with a pawn "
                     "on it's "
                     "first turn.");
          return false;
        }
        Tile tileAbove = isWhite ? chessGame->board[startTile->rowIndex - 1][startTile->colIndex]
                                 : chessGame->board[startTile->rowIndex + 1][startTile->colIndex];
        Tile tileAboveAbove = isWhite
            ? chessGame->board[startTile->rowIndex - 2][startTile->colIndex]
            : chessGame->board[startTile->rowIndex + 2][startTile->colIndex];
        if (tileAbove.piece != '-' || tileAboveAbove.piece != '-')
        {
          printError("There is another piece in the way.");
          return false;
        }
        return true;
      }
      // attack left or attack right
      case 'C':
      case 'D':
      {
        bool isPieceToAttack = endTile->piece != '-';
        if (!isPieceToAttack)
        {
          printError("There is no piece to attack.");
          return false;
        }
        return true;
      }
      }
    }
  }
  return false;
}

bool isMoveValidRook(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  int step = (moveInfo->isUp || moveInfo->isLeft) ? -1 : 1;
  int startIndex = moveInfo->isRowMove ? startTile->colIndex : startTile->rowIndex;
  int endIndex = moveInfo->isRowMove ? endTile->colIndex : endTile->rowIndex;
  int i = startIndex + step;
  while (i != endIndex)
  {
    Tile currTile = moveInfo->isRowMove ? chessGame->board[startTile->rowIndex][i]
                                        : chessGame->board[i][startTile->colIndex];
    bool isOccupied = currTile.piece != '-';
    if (isOccupied)
    {
      printError("There is a piece in the way.");
      return false;
    }
    i += step;
  }
  return true;
}

bool isMoveValidBishop(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  for (int i = 1; i < 16; i++)
  {
    int rowIndex = moveInfo->isUp ? startTile->rowIndex - (1 * i) : startTile->rowIndex + (1 * i);
    int colIndex = moveInfo->isLeft ? startTile->colIndex - 1 * i : startTile->colIndex + (1 * i);
    bool isValidTile = rowIndex >= 0 && rowIndex < 8 && colIndex >= 0 && colIndex < 8;
    bool isPlayerMove = endTile->rowIndex == rowIndex && endTile->colIndex == colIndex;
    if (!isValidTile)
    {
      continue;
    }
    Tile currTile = chessGame->board[rowIndex][colIndex];
    bool isTileOccupied = currTile.piece != '-';
    if (!isPlayerMove && isTileOccupied)
    {
      printf(" ROW: %d, COL: %d \n", currTile.rowIndex, currTile.colIndex);
      printError("There is a piece in the way.");
      return false;
    }
    if (isPlayerMove)
    {
      return true;
    }
  }

  return false;
}

bool isMoveValidQueen(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  return moveInfo->isDiagMove ? isMoveValidBishop(chessGame, startTile, endTile, moveInfo)
                              : isMoveValidRook(chessGame, startTile, endTile, moveInfo);
}

bool isMoveValidKing(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{
  Tile *row = chessGame->board[startTile->rowIndex];
  if (moveInfo->isCastle)
  {
    if (moveInfo->isWhite && (startTile->colIndex != 4 || startTile->rowIndex != 7))
    {
      printError("Invalid castle attempt: your king is not on it's starting square.");
      return false;
    }
    if (!moveInfo->isWhite && (startTile->colIndex != 4 || startTile->rowIndex != 0))
    {
      printError("Invalid castle attempt: your king is not on it's starting square.");
      return false;
    }
    bool isRookValid = moveInfo->isCastleQueenSide ? row[0].piece == 'R' : row[7].piece == 'R';
    if (!isRookValid)
    {
      printError("Invalid castle attempt: your rook is not on it's starting square.");
      return false;
    }
    if (!moveInfo->isCastleQueenSide &&
        (row[startTile->colIndex + 1].piece != '-' || row[startTile->colIndex + 2].piece != '-'))
    {
      printError("Invalid castle attempt: there is a piece in the way.");
      return false;
    }
    if (moveInfo->isCastleQueenSide &&
        (row[startTile->colIndex - 1].piece != '-' || row[startTile->colIndex - 2].piece != '-' ||
         row[startTile->colIndex - 3].piece != '-'))
    {
      printError("Invalid castle attempt: there is a piece in the way.");
      return false;
    }

    return true;
  }

  int possibleMoves[8][2] = {{startTile->rowIndex - 1, startTile->colIndex},
                             {startTile->rowIndex - 1, startTile->colIndex + 1},
                             {startTile->rowIndex, startTile->colIndex + 1},
                             {startTile->rowIndex + 1, startTile->colIndex + 1},
                             {startTile->rowIndex + 1, startTile->colIndex},
                             {startTile->rowIndex + 1, startTile->colIndex - 1},
                             {startTile->rowIndex, startTile->colIndex - 1},
                             {startTile->rowIndex - 1, startTile->colIndex - 1}};
  for (int i = 0; i < 8; i++)
  {
    int rowIndex = possibleMoves[i][0];
    int colIndex = possibleMoves[i][1];

    if (endTile->rowIndex == rowIndex && endTile->colIndex == colIndex)
    {
      return true;
    }
  }

  printError("The King cannot reach that square.");
  return false;
}

bool chessIsMoveValid(ChessGame *chessGame, Tile *startTile, Tile *endTile, MoveInfo *moveInfo)
{

  if (startTile->piece == '-')
  {
    printError("There is no piece there.");
    return false;
  }
  if (startTile->pieceColor != chessGame->turn)
  {
    printError("Wrong color.");
    return false;
  }

  bool isOppositeColor = startTile->pieceColor != endTile->pieceColor;
  if (!isOppositeColor)
  {
    printError("Cannot capture your own piece.");
    return false;
  }

  switch (startTile->piece)
  {
  case 'N':
    return isMoveValidKnight(chessGame, startTile, endTile, moveInfo);
  case 'P':
    return isMoveValidPawn(chessGame, startTile, endTile, moveInfo);
  case 'Q':
    return isMoveValidQueen(chessGame, startTile, endTile, moveInfo);
  case 'R':
    return isMoveValidRook(chessGame, startTile, endTile, moveInfo);
  case 'B':
    return isMoveValidBishop(chessGame, startTile, endTile, moveInfo);
  case 'K':
    return isMoveValidKing(chessGame, startTile, endTile, moveInfo);
  }
  return true;
};

void chessRegisterMove(ChessGame *chessGame, char *playerMove)
{
  char startMoveCol = playerMove[0];
  int startMoveRow = playerMove[1] - '0';
  int startRowIndex = chessGetRowIndex(startMoveRow);
  int startColumnIndex = chessGetColumnIndex(startMoveCol);
  char endMoveColumn = playerMove[2];
  int endMoveRow = playerMove[3] - '0';
  int endRowIndex = chessGetRowIndex(endMoveRow);
  int endColumnIndex = chessGetColumnIndex(endMoveColumn);

  if (startRowIndex == -1 || startColumnIndex == -1 || endRowIndex == -1 || endColumnIndex == -1)
  {
    printError("Coordinate out of range.");
    return;
  }
  Tile startTile = chessGame->board[startRowIndex][startColumnIndex];
  Tile endTile = chessGame->board[endRowIndex][endColumnIndex];
  Tile *startTileP = &startTile;
  Tile *endTileP = &endTile;

  MoveInfo moveInfo;
  moveInfo.isAttackMove = endTile.piece != '-';
  moveInfo.isCastle = startTile.piece == 'K' && abs(endTile.colIndex - startTile.colIndex) == 2;
  moveInfo.isCastleQueenSide = moveInfo.isCastle && endTile.colIndex < startTile.colIndex;
  moveInfo.isEnPassant = false;   // TODO
  moveInfo.isUp = endTile.rowIndex < startTile.rowIndex;
  moveInfo.isLeft = endTile.colIndex < startTile.colIndex;
  moveInfo.isWhite = chessGame->turn == 'W';
  moveInfo.isRowMove = endTile.rowIndex == startTile.rowIndex;
  moveInfo.isColMove = endTile.colIndex == startTile.colIndex;
  moveInfo.isDiagMove = !moveInfo.isRowMove && !moveInfo.isColMove;

  bool isMoveValid = chessIsMoveValid(chessGame, startTileP, endTileP, &moveInfo);
  if (isMoveValid)
  {
    chessGame->turn = chessGame->turn == 'W' ? 'B' : 'W';
    movePiece(chessGame, startTileP, endTileP);
    if (moveInfo.isCastle)
    {
      Tile *row = chessGame->board[startTile.rowIndex];
      Tile rookTile = row[moveInfo.isCastleQueenSide ? 0 : 7];
      Tile rookDestinationTile =
          row[moveInfo.isCastleQueenSide ? startTile.colIndex - 1 : startTile.colIndex + 1];
      movePiece(chessGame, &rookTile, &rookDestinationTile);
    }
  }
}