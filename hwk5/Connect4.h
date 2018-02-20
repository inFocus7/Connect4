#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Players.h"
using namespace std;
/* Set some variables as global, since I had problems with them not updating when out of scope, I believe. */
int movesMade = 0, rowAmt, columnAmt, aiMovesMade = 0;
bool GAMEOVER = false;
char latestPiece;

class connect4 {
private:
	int numPlayers, minRequiredToWin;
	char * row, *column, ** board;
public:
	connect4() {
		rowAmt = 6;
		columnAmt = 7;
		// Dynamic 2D Board Creation.
		board = new char*[rowAmt];
		for (int i = 0; i < rowAmt; i++)
			board[i] = new char[columnAmt];
		// Fill Up w/ 0's in the meantime
		for (int i = 0; i < rowAmt; i++)
			for (int j = 0; j < columnAmt; j++)
				board[i][j] = NULL;
	}
	connect4(int NumRows, int NumColumns) {
		rowAmt = NumRows;
		columnAmt = NumColumns;
		// Dynamic 2D Board Creation.
		board = new char*[rowAmt];
		for (int i = 0; i < rowAmt; i++)
			board[i] = new char[columnAmt];
		// Fill Up w/ 0's in the meantime
		for (int i = 0; i < rowAmt; i++)
			for (int j = 0; j < columnAmt; j++)
				board[i][j] = NULL;
	}
	void setNumberOfPlayers(int numberOfPlayers) {
		numPlayers = numberOfPlayers;
		minRequiredToWin = numPlayers * 3 + 1;
	}
	void DrawBoard() {
		cout << "   ";
		for (int i = 0; i < rowAmt; i++)
			cout << i << " ";
		cout << endl;
		for (int i = 0; i < rowAmt; i++) {
			for (int j = 0; j < columnAmt; j++)
			{
				if (j == 0)
				{
					cout << i << " " << "|";
				}
				cout << board[i][j] << " ";
			}
			cout << "|";
			cout << endl;
		}
		cout << "   ";
		for (int i = 0; i <= rowAmt; i++)
			cout << "_ ";
		cout << endl;
	}
	bool GameOver() {
		bool val = GAMEOVER;
		if (val == true) {
			if (movesMade == rowAmt * columnAmt)
				cout << "It's a tie..." << endl;
			else
				cout << "The Winner is: " << Winner() << endl;
			return true;
		}
		else
			return false;
	}
	char Winner()
	{
		return latestPiece;
	}
	bool MakeMove(char piece, int column) {
		bool moveWasMade = false;
		int latestRowIndex;
		//Make Placement. (if possible)
			//Out of bounds checker.
		if (column < 0 || column >= columnAmt) {
			cout << "You seemed to have dropped your piece to the " << (column < 0 ? "left " : "right ") << "of the board..." << endl;
			cout << "Press any key to continue...";
			cin.get();
			cin.ignore();
			return false;
		}
		//Placer.
		for (int i = (rowAmt - 1); i >= 0; i--) { //Descending since the placement has to be put at lowest possible one.
			if (board[i][column] == NULL) { // If the row is initialized to 0/empty, place there
				board[i][column] = piece;
				moveWasMade = true;
				latestRowIndex = i;
				break; //Break once a move is made.
			}
		}
		//Out of bounds checker #2. (column filled)
		if (moveWasMade == false) {
			cout << "Not sure why you decided put your piece in a full row, but okay." << endl;
			cout << "Press any key to continue...";

			cin.get();
			cin.ignore();
			return false;
		}
		DrawBoard();
		//Check If Won. (if move was made and if there *COULD* be a winner)
		if (moveWasMade == true) {
			movesMade++;
		}
		if (movesMade == columnAmt * rowAmt) {
			GAMEOVER = true;
		}
		if (moveWasMade == true && movesMade >= minRequiredToWin) {
			if (checkWin(column, latestRowIndex, piece)) { //If someone got four in a row
				GAMEOVER = true;
			}
		}
		
		latestPiece = piece;
		return moveWasMade;
	}
	bool checkWin(int column, int row, char piece) {
		int connection = 1; // A counter to see how many connected.Initially 1, since this statement only occcurs if one was placed.
		//Check Right & Left
		for (int i = column + 1; i < columnAmt; i++)//Check Right
		{
			if (board[row][i] == piece)
				connection++;
			else
				break;
		}
		for (int i = column - 1; 0 <= i; i--)//Check Left
		{
			if (board[row][i] == piece)
				connection++;
			else
				break;
		}
		if (connection == 4)
			return true;
		else
			connection = 1;
		//Check Up & Down
		for (int i = row - 1; 0 <= i; i--) { //Check Up
			if(board[i][column] == piece)
				connection++;
			else break;
		}
		for (int i = row + 1; i < rowAmt; i++) { //Check Down
			if (board[i][column] == piece)
				connection++;
			else
				break;
		}
		if (connection == 4)
			return true;
		else
			connection = 1;
		//Check Diagonally Up-Right & Down-Left
		for (int i = row - 1, j = column + 1; (j < columnAmt && i >= 0); i--, j++)//Check Up-Right
		{
			if(board[i][j] == piece)
				connection++;
			else 
				break;
		}
		for (int i = row + 1, j = column - 1; (j >= 0 && i < rowAmt); i++, j--)//Check Down-Left
		{
			if (board[i][j] == piece)
				connection++;
			else
				break;
		}
		if (connection == 4)
			return true;
		else
			connection = 1;
		//Check Diagonally Up-Left & Down-Right
		for (int i = row - 1, j = column - 1; (j >= 0 && i >= 0); i--, j--)//Check Up-Left
		{
			if (board[i][j] == piece)
				connection++;
			else
				break;
		}
		for (int i = row + 1, j = column + 1; (j < columnAmt && i < rowAmt); i++, j++)//Check Down-Right
		{
			if (board[i][j] == piece)
				connection++;
			else
				break;
		}
		if (connection == 4)
			return true;
		else
			connection = 1;

		return false;
	}
	int GetAIMove()
	{
		int columnPlacement;
		//Randomize between 0-rowAmt (not including rowAmt due to index)
		columnPlacement = rand() % (rowAmt + 1);
		//Else, "think" strategically (didn't implement due to watching a mit courseware video on minmax+ab algorithm and not finishing it.)
		aiMovesMade++;
		return columnPlacement;
	}
};