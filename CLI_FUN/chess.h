#ifndef chess_h
#define chess_h

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

typedef struct ChessGame
{
  char turn;
  Tile board[8][8];
} ChessGame;

void createChessGame(ChessGame *chessGame);

void chessMakeMove(ChessGame *chessGame, Tile *startTile, Tile *endTile);

bool chessIsMoveValid(ChessGame *chessGame, Tile *startTile, Tile *endTile);

int chessGetColumnIndex(char column);

int chessGetRowIndex(int row);

void printChessboard(ChessGame *chessGame);

#endif