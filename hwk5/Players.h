#pragma once
#include <iostream>
using namespace std;
//Could've done a dynamic array, but wanted to practice linked lists in case needed
class node {
public:
	char data;
	node * next;
};

class linkedList {
private:
	node *head, *tail;
	node *currentPlayer = new node;
public:
	linkedList() {
		head = NULL;
		tail = NULL;
	}
	void ADDNODE(char piece) {
		node *temp = new node;
		temp->data = piece;
		temp->next = NULL;
		//If empty list
		if (head == NULL) { //If the list is empty
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	char PIECE(int playerTurn) {
		if (playerTurn == 1)
			currentPlayer = head;
		else
			currentPlayer = currentPlayer->next;
		return currentPlayer->data;
	}
};