#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/*
Address:  buildingNumber, streetName, city, state, zipCode
Record: firstName, lastName, number, adress (obj of Address class)
Node: info(obj of Rec) ,pointer to next
Address book: pointer to head
*/

class Address
{
private:
	string buildingNumber, streetName, city, state, zipCode;
public:
	string getFullAddress() const;

	void setAddress(string building, string street, string city, string state, string zip);
};

class Record
{
private:
	string firstName, lastName, phoneNumber;
	Address address;
public:
	string getFullRecord() const;
	string getLastName() const;
	string getNumber() const;

	void setRecord(string first, string last, Address add, string num);
};

class Node
{
private:
	Record info;
	Node* next;
public:
	Record getInfo() const;
	Node* getNext() const;
	void setInfo(Record info);
	void setNext(Node* next);
};

class AddressBook
{
private:
	Node* head;
	int length;
public:
	AddressBook();
	~AddressBook();
	void makeEmpty();
	bool printAddressBook();
	void addRecord(Record);
	Record findRecord(string, bool&);
	Node* deleteRecord(string);
	bool getRecords();
	void searchFor();
	void addANewEntry();
	void deleteAnEntry();
};

string upperCase(string);


/*********************************** MAIN ******************************************/
int main()
{
	AddressBook addressBook;
	bool needToEnd = false;
	char choice = NULL;
	Address item;

	needToEnd = addressBook.getRecords();
	if (needToEnd)
		return 1;

	needToEnd = addressBook.printAddressBook();
	if (needToEnd)
		return -1;


	while (choice != 'q')
	{
		cout << "Please enter one of the folowing letters:\n"
			<< "\'A\' to search for a person by last name or phone number.\n"
			<< "\'B\' to add a new entry to the address book.\n"
			<< "\'C\' to delete an entry from the address book based on phone number or last name.\n"
			<< "Or enter \'Q\' to quit.\n"
			<< "Enter here: ";
		cin >> choice;
		choice = tolower(choice);
		cin.ignore(80, '\n');

		switch (choice)
		{
		case 'a':
			addressBook.searchFor();
			break;
		case 'b':
			addressBook.addANewEntry();
			needToEnd = addressBook.printAddressBook();
			if (needToEnd)
				return -1;
			cout << "\nDone\n" << endl;
			break;
		case 'c':
			addressBook.deleteAnEntry();
			needToEnd = addressBook.printAddressBook();
			if (needToEnd)
				return -1;
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


/*********************************** ADDRESS FUNCTIONS ******************************************/

//Retrurns the address in an address format
string Address::getFullAddress() const
{
	return (buildingNumber + ' ' + streetName + ' ' + city + ", " + state + ' '
		+ zipCode);
}

//sets full address 
void Address::setAddress(string building, string street, string city, string state, string zip)
{
	buildingNumber = building;
	streetName = street;
	this->city = city;
	this->state = state;
	zipCode = zip;
}


/*********************************** RECORD FUNCTIONS ******************************************/

//Retrurns the full record in an record format
string Record::getFullRecord() const
{
	return (firstName + ' ' + lastName + "     " + address.getFullAddress() 
		+ "     (" + phoneNumber.substr(0, 3) + ')' + phoneNumber.substr(3, 3) + '-' + phoneNumber.substr(6));
}

//////////////// Getters and Setter for Record Class /////////////////
string Record::getLastName() const
{
	return lastName;
}
string Record::getNumber() const
{
	return phoneNumber;
}

void Record::setRecord(string first, string last, Address add, string num)
{
	firstName = first;
	lastName = last;
	address = add;
	phoneNumber = num;
}


/*********************************** Node FUNCTIONS ******************************************/

//////////////// Getters and Setters for Address Class /////////////////
Record Node::getInfo() const
{
	return info;
}
Node* Node::getNext() const
{
	return next;
}
void Node::setInfo(Record info)
{
	this->info = info;
}
void Node::setNext(Node* next)
{
	this->next = next;
}


/*********************************** ADDRESSBOOK FUNCTIONS AND CONSTRUCTOR ******************************************/

//AddressBook Constructor
AddressBook::AddressBook()
{
	head = nullptr;
	length = 0;
}

//AddressBook Destructor 
AddressBook::~AddressBook()
{
	makeEmpty();
}

//makes list empty
//Pre condition: there has to be a list
//Post condition: the list is empty
void AddressBook::makeEmpty()
{
	Node* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->getNext();
		length--;
		delete temp;
	}
}

//prints list to a file
//Pre condition: there has to be something in the list 
//Post condition: returns false if output file could not open 
bool AddressBook::printAddressBook()
{
	ofstream out;
	Node* temp = head;

	out.open("printFile.txt");
	if (!out.is_open())
	{
		cout << "Error! Output file could not open. Ending." << endl;
		return true;
	}

	while (temp != nullptr)
	{
		out << temp->getInfo().getFullRecord()  << endl;
		temp = temp->getNext();
	}

	out.close();
	return false;
}

//adds an record to the list
//Pre condition: list can't be full
//Post condition: the record is added to the list
void AddressBook::addRecord(Record item)
{
	Node* pTemp;

	pTemp = new Node;

	pTemp->setInfo(item);
	pTemp->setNext(head);
	head = pTemp;
	length++;
}

//deletes and reterns a record from list
//Pre condition: record has to be in the list
//Post condition: record isn't in the list nullptr is retured
Node* AddressBook::deleteRecord(string item)
{
	Node* location = head;
	Node* tempLocation = head;
	bool found = false;

	if ((head->getInfo().getLastName() == item) || (head->getInfo().getNumber() == item))
	{
		tempLocation = location;
		head = head->getNext();
		found = true;
	}
	else
	{
		while ((location->getNext() != nullptr) && (location->getNext()->getInfo().getLastName() != item) && (location->getNext()->getInfo().getNumber() != item))
		{
			location = location->getNext();
		}

		if ((location->getNext() != nullptr) && ((location->getNext()->getInfo().getLastName() == item) || (location->getNext()->getInfo().getNumber() == item)))
		{
			tempLocation = location->getNext();
			location->setNext(location->getNext()->getNext());
			found = true;
		}
		else
		{
			found = false;
		}
	}

	if (found)
	{
		length--;
		return tempLocation;
	}
	return nullptr;
}

//serches for an record in list
//Pre condition: record has to be in the list
//Post condition: returs record if found and found is set to true
Record AddressBook::findRecord(string searchBy, bool& found)
{
	Node* location;
	Record theAddress;
	location = head;
	found = false;
	while (location != nullptr && !found)
	{
		if ((searchBy == location->getInfo().getLastName()) || (searchBy == location->getInfo().getNumber()))
		{
			found = true;
			theAddress = location->getInfo();
		}
		else
			location = location->getNext();
	}
	return theAddress;
}

//gets all records from input file
//Pre condition: there has to be an input file
//Post condition: returns false if there is no input file
bool AddressBook::getRecords()
{
	ifstream fileIn;
	Record temp;
	Address lAddress;
	string fName, lName, bNumber, sName, lCity, lState, zCode, pNumber;

	fileIn.open("input.txt");

	if (!fileIn.is_open())
	{
		cout << "File did not open. Quiting!" << endl;
		return false;
	}

	makeEmpty();
	
	while (fileIn >> fName)
	{
		fileIn >> lName >> bNumber >> sName >> lCity >> lState >> zCode >> pNumber;

		fName = upperCase(fName);
		lName = upperCase(lName);
		bNumber = upperCase(bNumber);
		sName = upperCase(sName);
		lCity = upperCase(lCity);
		lState = upperCase(lState);
		zCode = upperCase(zCode);
		pNumber = upperCase(pNumber);

		lAddress.setAddress(bNumber, sName, lCity, lState, zCode);
		temp.setRecord(fName, lName, lAddress, pNumber);

		addRecord(temp);
	}
	fileIn.close();
	return false;
}

//askes a user and searches for an record in address book list
//Pre condition: list is not empty
//Post condition: prints the record if found
void AddressBook::searchFor()
{
	string searchBy;
	bool found = false;
	Record record;
	cout << "Please enter a last name or a phone number: ";
	cin >> searchBy;

	searchBy = upperCase(searchBy);

	record = findRecord(searchBy, found);
	if (found)
		cout << '\n' << record.getFullRecord() << '\n' << endl;
	else
		cout << "\nNot found.\n" << endl;
}

//askes a user and adds an record to address book list
//Pre condition: list is instantiated
//Post condition: new record is added to address book list
void AddressBook::addANewEntry()
{
	Record temp;
	Address lAddress;
	string fName, lName, bNumber, sName, lCity, lState, zCode, pNumber;
	cout << "\nPlease enter the folowing information (without any formatting characters):\n"
		<< "First Name: ";
	cin >> fName;
	cout << "Last Name: ";
	cin >> lName;
	cout << "Building Number: ";
	cin >> bNumber;
	cout << "Street Name: ";
	cin >> sName;
	cout << "City: ";
	cin >> lCity;
	cout << "State: ";
	cin >> lState;
	cout << "Zip Code: ";
	cin >> zCode;
	cout << "Phone Number: ";
	cin >> pNumber;

	fName = upperCase(fName);
	lName = upperCase(lName);
	bNumber = upperCase(bNumber);
	sName = upperCase(sName);
	lCity = upperCase(lCity);
	lState = upperCase(lState);
	zCode = upperCase(zCode);
	pNumber = upperCase(pNumber);
	
	lAddress.setAddress(bNumber, sName, lCity, lState, zCode);
	temp.setRecord(fName, lName, lAddress, pNumber);

	addRecord(temp);
}

//askes a user for an phone number or last name and deletes an record from address book list
//Pre condition: the record is in list
//Post condition: deletes the record 
void AddressBook::deleteAnEntry()
{
	bool found = false;
	Node* tempNode;
	string searchBy;
	
	cout << "Please enter a last name or phone number: ";
	cin >> searchBy;
	searchBy = upperCase(searchBy);

	tempNode = deleteRecord(searchBy);
	if (tempNode != nullptr)
	{
		cout << "\nDeleting:\n" << tempNode->getInfo().getFullRecord() << "\nDeleted.\n" << endl;
		delete tempNode;
	}
	else
		cout << "\nNot found. Can't be deleted.\n" << endl;
}


//////////////////////////////////// FUNCTIONS /////////////////////////////////////////////////////////////

//returns a string in all upper case
//Pre condition: the string is not empty
//Post condition: same string but all upper case
string upperCase(string word)
{
	for (char& c : word)
		c = toupper(c);
	return word;
}


//Output
/*
////////////////////////////////////////////////// OUTPUT FILE //////////////////////////////////////////////////
DWIGHT SCHRUTE     6 HONESDALE WAYNECOUNTY, PA 18431     (800)984-3672
JAKE FROM     17827 STATE FARM, CA 91344     (800)782-8332
JOHN DOE     6202 WINNETKA CANOGA, CA 91336     (919)345-7896
DAN DAN     9808 WILSHIRE SANTAMONICA, CA 90333     (109)057-236
SANTA CLAUSE     332 TAMPA NORTHRIDGE, CA 12384     (685)930-5001
MAT JACKSON     1234 BALBOA GRANDAHILLS, CA 91782     (924)768-1982
TIM TOM     89334 VANOWEN VANNUYS, CA 81733     (812)156-8498
SAM SMITH     62234 VICTORY BURBANK, CA 93124     (123)456-7890

////////////////////////////////////////////////// OUTPUT //////////////////////////////////////////////////
Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: A
Please enter a last name or a phone number: A

Not found.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: A
Please enter a last name or a phone number: dsdf

Not found.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: a
Please enter a last name or a phone number: 199312e3

Not found.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: a
Please enter a last name or a phone number: ToM

TIM TOM     89334 VANOWEN VANNUYS, CA 81733     (812)156-8498

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: a
Please enter a last name or a phone number: 1234567890

SAM SMITH     62234 VICTORY BURBANK, CA 93124     (123)456-7890

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: b

Please enter the folowing information (without any formatting characters):
First Name: Random
Last Name: Person
Building Number: 9912
Street Name: house
City: NotHere
State: ca
Zip Code: 8123
Phone Number: 9083432189

Done

////////////////////////////////////////////////// OUTPUT FILE //////////////////////////////////////////////////
RANDOM PERSON     9912 HOUSE NOTHERE, CA 8123     (908)343-2189
DWIGHT SCHRUTE     6 HONESDALE WAYNECOUNTY, PA 18431     (800)984-3672
JAKE FROM     17827 STATE FARM, CA 91344     (800)782-8332
JOHN DOE     6202 WINNETKA CANOGA, CA 91336     (919)345-7896
DAN DAN     9808 WILSHIRE SANTAMONICA, CA 90333     (109)057-236
SANTA CLAUSE     332 TAMPA NORTHRIDGE, CA 12384     (685)930-5001
MAT JACKSON     1234 BALBOA GRANDAHILLS, CA 91782     (924)768-1982
TIM TOM     89334 VANOWEN VANNUYS, CA 81733     (812)156-8498
SAM SMITH     62234 VICTORY BURBANK, CA 93124     (123)456-7890

////////////////////////////////////////////////// OUTPUT //////////////////////////////////////////////////
Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: a
Please enter a last name or a phone number: PERSON

RANDOM PERSON     9912 HOUSE NOTHERE, CA 8123     (908)343-2189

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: c
Please enter a last name or phone number: Person

Deleting:
RANDOM PERSON     9912 HOUSE NOTHERE, CA 8123     (908)343-2189
Deleted.

////////////////////////////////////////////////// OUTPUT FILE //////////////////////////////////////////////////
DWIGHT SCHRUTE     6 HONESDALE WAYNECOUNTY, PA 18431     (800)984-3672
JAKE FROM     17827 STATE FARM, CA 91344     (800)782-8332
JOHN DOE     6202 WINNETKA CANOGA, CA 91336     (919)345-7896
DAN DAN     9808 WILSHIRE SANTAMONICA, CA 90333     (109)057-236
SANTA CLAUSE     332 TAMPA NORTHRIDGE, CA 12384     (685)930-5001
MAT JACKSON     1234 BALBOA GRANDAHILLS, CA 91782     (924)768-1982
TIM TOM     89334 VANOWEN VANNUYS, CA 81733     (812)156-8498
SAM SMITH     62234 VICTORY BURBANK, CA 93124     (123)456-7890

////////////////////////////////////////////////// OUTPUT //////////////////////////////////////////////////
Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: a
Please enter a last name or a phone number: person

Not found.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: c
Please enter a last name or phone number: 1234567890

Deleting:
SAM SMITH     62234 VICTORY BURBANK, CA 93124     (123)456-7890
Deleted.

////////////////////////////////////////////////// OUTPUT FILE //////////////////////////////////////////////////
DWIGHT SCHRUTE     6 HONESDALE WAYNECOUNTY, PA 18431     (800)984-3672
JAKE FROM     17827 STATE FARM, CA 91344     (800)782-8332
JOHN DOE     6202 WINNETKA CANOGA, CA 91336     (919)345-7896
DAN DAN     9808 WILSHIRE SANTAMONICA, CA 90333     (109)057-236
SANTA CLAUSE     332 TAMPA NORTHRIDGE, CA 12384     (685)930-5001
MAT JACKSON     1234 BALBOA GRANDAHILLS, CA 91782     (924)768-1982
TIM TOM     89334 VANOWEN VANNUYS, CA 81733     (812)156-8498

////////////////////////////////////////////////// OUTPUT //////////////////////////////////////////////////
Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: A
Please enter a last name or a phone number: 1234567890

Not found.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: c
Please enter a last name or phone number: sdfer

Not found. Can't be deleted.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: sdr

Not a valid choice please try again.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: efr

Not a valid choice please try again.

Please enter one of the folowing letters:
'A' to search for a person by last name or phone number.
'B' to add a new entry to the address book.
'C' to delete an entry from the address book based on phone number or last name.
Or enter 'Q' to quit.
Enter here: q
Quiting.
*/
