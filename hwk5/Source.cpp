#include <iostream>
#include <iomanip>
#include <string>
#include "Connect4.h"
#include "Players.h"
using namespace std;

void currentPlayerMove(int playerTurn, char piece, int columnPlacement, connect4 game, bool AI, bool TWO_AI, bool& moveMade)
{
	cout << "It is " << piece << "'s turn: " << endl;
	if (AI == true && playerTurn == 2) { //AI (Player v. AI)
		cout << "Column: ";
		moveMade = game.MakeMove(piece, game.GetAIMove());
	}
	else if (TWO_AI == true) { //AI (AI v. AI)
		cout << "Column: ";
		moveMade = game.MakeMove(piece, game.GetAIMove());
	}
	else { //Player (Player v. X)
		cout << "Column: ";
		cin >> columnPlacement;
		moveMade = game.MakeMove(piece, columnPlacement);
	}
}

int main()
{
	srand(time(NULL));
	//Variables
	connect4 game;
	int numPlayers, boardType, boardColumns, boardRows, columnPlacement = 0;
	char quitGame, piece;
	bool AI, TWO_AI;
	//The Game
	system("cls"); //Initial clear screen in case player resets game (doesn't quit)
	cout << "Welcome To: CONNECT 4." << endl;
	//Board Type
	cout << "Normal Board? or Custom Board?" << endl;
	cout << "1) Normal Board" << endl;
	cout << "2) Custom Board" << endl;
	cin >> boardType;
	if(boardType == 2) {
		cout << "Columns: "; 
		cin >> boardColumns;
		cout << "Rows: ";
		cin >> boardRows;
		game = connect4(boardRows, boardColumns);
	}
	//Player Amount
	cout << "How many human players will be playing? ";
	cin >> numPlayers;
	if (numPlayers < 0) {
		do {
			cout << "Please enter a valid amount of players..." << endl;
			cout << "How many human players will be playing? ";
			cin >> numPlayers;
		} while (numPlayers < 0);
	}
	else if (numPlayers == 0) {
		AI = true; TWO_AI = true;
		numPlayers = 2; //AI vs AI
	}
	else if (numPlayers == 1) {
		AI = true; TWO_AI = false;
		numPlayers = 2;
	}
	else {
		AI = false; TWO_AI = false;
	}
	game.setNumberOfPlayers(numPlayers); //sends number of players to board for me to do some maths.
	linkedList PLAYER;
	for (int i = 1; i <= numPlayers; i++)
	{
		cout << "Insert your char..." << endl;
		cout << i << ": ";
		cin >> piece;
		PLAYER.ADDNODE(piece);
	}
	for (int i = 0; !game.GameOver(); i++) { //do while there is no winner (game isn't over) 
		int playerTurn = (i % numPlayers) + 1;
		bool moveMade;
		piece = PLAYER.PIECE(playerTurn);
		do {
			//Draw the board
			game.DrawBoard();
			//Make a move
			currentPlayerMove(playerTurn, piece, columnPlacement, game, AI, TWO_AI, moveMade);
			system("cls");
		} while (moveMade == false);

	}

	game.DrawBoard();
	//Ending
	cout << "Thanks for playing!" << endl;
	return 0;
}