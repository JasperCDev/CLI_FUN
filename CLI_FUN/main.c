#include "chess.h"
#include "hashTable.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
    for (int i = 0; i < (int)strlen(playerMove); i++)
    {
      playerMove[i] = toupper(playerMove[i]);
    }
    if (strlen(playerMove) != 4)
    {
      printf("Move must be 4 characters\n");
      continue;
    }
    chessRegisterMove(&chessGame, playerMove);
  }
  return 0;
}
