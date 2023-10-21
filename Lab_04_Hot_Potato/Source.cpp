//Tigran Manukyan
//Lab 04
#include <iostream>
using namespace std;

struct Node
{
public:
	int number;
	Node* next;
};

class PotatoGame
{
private:
	Node* head;
	int length;
public:
	PotatoGame();
	~PotatoGame();
	void makeEmpty();
	void addNode(int);
	void deleteNode(int);
	void addPeople(int);
	void play();
	int getWinner(int);
	void makeCircular();
};


int verifyInput();

int main()
{
	PotatoGame theGame;
	char choice = NULL;

	while (choice != 'q')
	{
		cout << "Please enter one of the folowing letters:\n"
			<< "\'A\' to play the game.\n"
			<< "Or enter \'Q\' to quit.\n"
			<< "Enter here: ";
		cin >> choice;
		choice = tolower(choice);
		cin.ignore(80, '\n');

		switch (choice)
		{
		case 'a':
			theGame.play();
			break;
		case 'q':
			cout << "Quiting.\n" << endl;
			break;
		default:
			cout << "\nNot a valid choice please try again.\n" << endl;
		}

	}

	return 0;
}


/*********************************** POTATOGAME FUNCTIONS AND CONSTRUCTOR ******************************************/

//AddressBook Constructor
PotatoGame::PotatoGame()
{
	head = nullptr;
	length = 0;
}

//AddressBook Destructor 
PotatoGame::~PotatoGame()
{
	makeEmpty();
}

//makes list empty
//Pre condition: there has to be a list
//Post condition: the list is empty
void PotatoGame::makeEmpty()
{
	Node* temp;
	while (length != 0)
	{
		temp = head;
		head = head->next;
		length--;
		delete temp;
	}
	head = nullptr;
}


//adds a Node to the list
//Pre condition: list is instantiated
//Post condition: the Node is added to the list
void PotatoGame::addNode(int number)
{
	Node* newNode;
	newNode = new Node;

	newNode->number = number;
	newNode->next = head;

	head = newNode;
	length++;
}

//deletes a node from list
//Pre condition: node has to be in the list
//Post condition: node is deleted
void PotatoGame::deleteNode(int number)
{
	Node* prevNode = head, * location = head->next;
	while (location->number != number)
	{
		prevNode = prevNode->next;
		location = location->next;
	}
	if (head->number == location->number)
	{
		head = location->next;
		prevNode->next = head;
	}
	else
	{
		prevNode->next = location->next;
	}
	delete location;
	length--;
}

//adds a certain number  of people to list 
//Pre condition: number has to be greater than one
//Post condition: list is not empty
void PotatoGame::addPeople(int nbrOfPlayers)
{
	while (nbrOfPlayers > 0)
	{
		addNode(nbrOfPlayers);
		nbrOfPlayers--;
	}
	makeCircular();
}

//asks user for number of variables and passes then runs the game
//Pre condition: numbers have to be positive integer
//Post condition: prints the winner
void PotatoGame::play()
{
	int nbrOfPlayers, nbrOfPasses, winner;
	makeEmpty();

	cout << "Enter number of players: ";
	nbrOfPlayers = verifyInput();
	if (nbrOfPlayers == 0)
	{
		cout << "There are no players. No one wins.\n" << endl;
	}
	else
	{
		addPeople(nbrOfPlayers);
		cout << "Enter number of Passes: ";
		nbrOfPasses = verifyInput();
		winner = getWinner(nbrOfPasses);
		cout << "\nThe winner is " << winner << '\n' << endl;
	}
}

//deletes all players except one (the winner)
//Pre condition: list can't be empty
//Post condition: returns the last player
int PotatoGame::getWinner(int nbrOfPasses)
{
	Node* temp = head;
	int i, toBeDeleted;
	while (length > 1)
	{
		for (i = 0; i < nbrOfPasses; i++)
			temp = temp->next;
		toBeDeleted = temp->number;
		temp = temp->next;
		cout << "\nEliminating person " << toBeDeleted;
		deleteNode(toBeDeleted);
	}
	return head->number;
}

//makes list circular
//Pre condition: there is an end to the list
//Post condition: list is circular
void PotatoGame::makeCircular()
{
	Node* ptemp = head;
	while (ptemp->next != nullptr)
		ptemp = ptemp->next;
	ptemp->next = head;
}

/*********************************** FUNCTIONS ******************************************/

//makes shure the input is an integer and positive
int verifyInput()
{
	int input = -1;

	while (input < 0)
	{
		while (!(cin >> input))
		{
			cout << "Error: Not a number. Please enter a positive number: ";
			cin.clear();
			cin.ignore(123, '\n');
		}
		if (input < 0)
			cout << "Error: Not a positive number. Please enter a positive number: ";
	}
	return input;
}


//Output
/*
Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: ase
Error: Not a number. Please enter a positive number: qwe
Error: Not a number. Please enter a positive number: -15
Error: Not a positive number. Please enter a positive number: 11
Enter number of Passes: ds
Error: Not a number. Please enter a positive number: -12
Error: Not a positive number. Please enter a positive number: 1

Eliminating person 2
Eliminating person 4
Eliminating person 6
Eliminating person 8
Eliminating person 10
Eliminating person 1
Eliminating person 5
Eliminating person 9
Eliminating person 3
Eliminating person 11
The winner is 7

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 5
Enter number of Passes: 3

Eliminating person 4
Eliminating person 3
Eliminating person 5
Eliminating person 2
The winner is 1

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 1
Enter number of Passes: 2

The winner is 1

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 6
Enter number of Passes: 0

Eliminating person 1
Eliminating person 2
Eliminating person 3
Eliminating person 4
Eliminating person 5
The winner is 6

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 5
Enter number of Passes: 3

Eliminating person 4
Eliminating person 3
Eliminating person 5
Eliminating person 2
The winner is 1

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 6
Enter number of Passes: 2

Eliminating person 3
Eliminating person 6
Eliminating person 4
Eliminating person 2
Eliminating person 5
The winner is 1

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 5
Enter number of Passes: 4

Eliminating person 5
Eliminating person 1
Eliminating person 3
Eliminating person 4
The winner is 2

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: a
Enter number of players: 5
Enter number of Passes: 1

Eliminating person 2
Eliminating person 4
Eliminating person 1
Eliminating person 5
The winner is 3

Please enter one of the folowing letters:
'A' to play the game.
Or enter 'Q' to quit.
Enter here: q
Quiting.


C:\Users\18182\source\repos\Lab_04_Manukyan_Tigran\x64\Debug\Lab_04_Manukyan_Tigran.exe (process 16172) exited with code 0.
Press any key to close this window . . .

*/