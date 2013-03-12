// ChinaChess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessGame.h"
int main(int argc, char* argv[])
{
	CChessGame game;
	game.InitGame();
	game.RunGame();
	game.ReleaseGame();
	printf("Hello World!\n");
	return 0;
}

