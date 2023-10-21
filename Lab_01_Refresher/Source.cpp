// Lab 1 Manukyan, Tigran T TH
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct itemStruct {
	string itemId;
	string itemName;
	int itemQuantity;
	double itemPrice;
};

void menuOptionSearch(itemStruct[], int);
int getItems(itemStruct[], itemStruct* [], const int);
void printItemsUnsorted(itemStruct[], int);
void bubbleSort(itemStruct* [], int, char);
void printPointerItems(itemStruct* [], int);
string lowerCase(string);
int search(itemStruct[], int);
double findTotalWorth(itemStruct[], int);
int findTotalCount(itemStruct[], int);
void printInfo(itemStruct items[], int size);

int main()
{
	const int MAX_SIZE = 100;
	int size;
	itemStruct items[MAX_SIZE], * itemPointers[MAX_SIZE];
	char choice = 0;

	size = getItems(items, itemPointers, MAX_SIZE);
	if (size == -1)
		return 1;

	while (choice != 'q')
	{
		cout << "Please enter one of the folowing letters:\n"
				"\'A\' to print unsorted items.\n"
			<< "\'B\' to sort by item ID.\n"
			<< "\'C\' to sort by item name.\n"
			<< "\'D\' to sort by quantity on hand.\n"
			<< "\'E\' to sort by price.\n"
			<< "\'F\' to search by item ID or by item name.\n"
			<< "\'G\' to print a report.\n"
			<< "Or enter \'Q\' to quit.\n"
			<< "Enter here: ";
		cin >> choice;
		choice = tolower(choice);
		cin.ignore(80, '\n');
		switch (choice)
		{
			case 'a':printItemsUnsorted(items, size); break;
			case 'b':
			case 'c':
			case 'd':
			case 'e':bubbleSort(itemPointers, size, choice);
				printPointerItems(itemPointers, size);
				cout << '\n' << endl;
				break;
			case 'f':
				menuOptionSearch(items, size);
				break;
			case 'g':
				printInfo(items, size);
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

//Gets all the items from file and returns the size of the arrays
//Pre condition: there is a file named textFile.txt
//Post condition: size of array is returned, itemStruct array is created, and itemStruct pointer array is created
int getItems(itemStruct items[], itemStruct* itemPointers[], const int MAX_SIZE)
{
	ifstream fileIn;
	ofstream fileOut;
	itemStruct temp;
	int size = 0;
	bool corruptItems = false;
	fileIn.open("136-l1_in.txt");
	fileOut.open("errorFile.txt");

	if (!fileIn.is_open())
	{
		cout << "File did not open. Quiting!" << endl;
		return -1;
	}
	if (!fileOut.is_open())
	{
		cout << "Error file did not open. Quiting!" << endl;
		return -1;
	}

	while (fileIn >> temp.itemId&& size < MAX_SIZE)
	{
		fileIn >> temp.itemName;
		fileIn >> temp.itemQuantity;
		fileIn >> temp.itemPrice;
		temp.itemName = lowerCase(temp.itemName);

		if (temp.itemPrice >= 0 && temp.itemQuantity >= 0)
		{
			items[size] = temp;
			itemPointers[size] = &items[size];
			size++;
		}
		else
		{
			corruptItems = true;
			fileOut << temp.itemId << ' ' << temp.itemName << ' ' << temp.itemQuantity << ' ' << temp.itemPrice << endl;
		}
	}

	if (!fileIn.eof() && size == MAX_SIZE)
		cout << "File too big only using first " << MAX_SIZE << " items." << endl;
	if (corruptItems)
		cout << "Some items were corrupt check \"errorFile.txt\" to see what those items are." << endl;

	fileOut.close();
	fileIn.close();
	return size;
}


//Asks user a value to search by and calls a function to search for it
//Pre condition: the input of user is in the array
//Post condition: if the item is found prints the data of the item
void menuOptionSearch(itemStruct items[], int size)
{
	int index;
	index = search(items, size);
	if (index == -1)
		cout << "Not Found\n" << endl;
	else
	{
		cout << fixed << "Item ID" << setw(19) << "Item Name" << setw(20) << "QTY" << setw(20) << "Price\n"
			<< left << setw(17) << items[index].itemId << setw(12) << items[index].itemName << right << setw(17) << items[index].itemQuantity << setprecision(2) << setw(19) << items[index].itemPrice << '\n' << endl;
	}
}

//Prints itemStruct array
//Pre condition: there are items in itemStruct array
//Post condition: itemStruct array is printed
void printItemsUnsorted(itemStruct items[], int size)
{
	cout << fixed << "Item ID" << setw(19) << "Item Name" << setw(20) << "QTY" << setw(20) << "Price" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(17) << items[i].itemId << setw(12) << items[i].itemName << setw(17) << right << items[i].itemQuantity << setw(20) << setprecision(2) << items[i].itemPrice << endl;
	}
}

//Sortes itemStruct pointer array based on choice
//Pre condition: choice is a, b, c or d
//Post condition: itemStruct pointer array is sorted
void bubbleSort(itemStruct* itemPointers[], int size, char choice)
{
	int i, j;
	itemStruct* temp;
	bool toSwap = false;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{

			switch (choice)
			{
			case 'b':
				toSwap = (itemPointers[j]->itemId > itemPointers[j + 1]->itemId);
				break;
			case 'c':
				toSwap = (itemPointers[j]->itemName > itemPointers[j + 1]->itemName);
				break;
			case 'd':
				toSwap = (itemPointers[j]->itemQuantity > itemPointers[j + 1]->itemQuantity);
				break;
			case 'e':
				toSwap = (itemPointers[j]->itemPrice > itemPointers[j + 1]->itemPrice);
				break;
			default:
				break;
			}
			if(toSwap)
			{
				temp = itemPointers[j];
				itemPointers[j] = itemPointers[j + 1];
				itemPointers[j + 1] = temp;
			}
		}
	}
}

//Prints itemStruct pointer array
//Pre condition: there are items in itemStruct pointer array
//Post condition: itemStruct pointer array is printed
void printPointerItems(itemStruct* itemPointers[], int size)
{
	cout << fixed << "Item ID" << setw(19) << "Item Name" << setw(20) << "QTY" << setw(20) << "Price" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << left << setw(17) << itemPointers[i]->itemId << setw(12) << itemPointers[i]->itemName << setw(17) << right << itemPointers[i]->itemQuantity << setw(20) << setprecision(2)  << itemPointers[i]->itemPrice << endl;
	}
}

//returns a string in all lower case
//Pre condition: the string is not empty
//Post condition: same string but all lowercase
string lowerCase(string word)
{
	for (char& c : word)
		c = tolower(c);
	return word;
}

//searches for a value (enterd by user) in itemStruct array and returns its location
//Pre condition: the input of user is in the array
//Post condition: if the value is found returns its location
int search(itemStruct items[], int size)
{
	int index = -1;
	string searchBy;

	cout << "Enter the item ID or item name: ";
	cin >> searchBy;
	searchBy = lowerCase(searchBy);
	cout << '\n';

	for (int i = 0; i < size && index == -1; i++)
		index = items[i].itemId == searchBy || items[i].itemName == searchBy ? i : -1;

	return index;
}

//finds total worth of all items in itemStruct
//Pre condition: there are items in itemStruct array
//Post condition: the total worth of all items int itemStruct array
double findTotalWorth(itemStruct items[], int size)
{
	double total = 0.00;
	for (int i = 0; i < size; i++)
		total += items[i].itemQuantity * items[i].itemPrice;
	return total;
}

//finds total count of all items in itemStruct
//Pre condition: there are items in itemStruct array
//Post condition: the total count of all items int itemStruct array
int findTotalCount(itemStruct items[], int size)
{
	int total = 0;
	for (int i = 0; i < size; i++)
		total += items[i].itemQuantity;
	return total;
}

//prints the number of unique items, total worth, and total count, in itemStruct array
//Pre condition: there are items in itemStruct array
//Post condition: prints the number of unique items, total worth, and total count, in itemStruct array
void printInfo(itemStruct items[], int size)
{
	cout << "There are " << size << " unique items.\n" << fixed << setprecision(2)
		<< "The total worth of the iventory is $" << findTotalWorth(items, size)
		<< "\nThe total count of all items is " << findTotalCount(items, size) << ".\n" << endl;
}


//Output
/*
//When there is no file:
File did not open. Quiting!

C:\Users\18182\source\repos\Lab_01_Manukyan_Tigran\Debug\Lab_01_Manukyan_Tigran.exe (process 18652) exited with code 1.
Press any key to close this window . . .


//When there is more then the max array size:
File too big only using first 10 items.
Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: q
Quiting.


C:\Users\18182\source\repos\Lab_01_Manukyan_Tigran\Debug\Lab_01_Manukyan_Tigran.exe (process 17904) exited with code 0.
Press any key to close this window . . .


//File with corrupt items:
Some items were corrupt check "errorFile.txt" to see what those items are.
Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: q
Quiting.


C:\Users\18182\source\repos\Lab_01_Manukyan_Tigran\Debug\Lab_01_Manukyan_Tigran.exe (process 20408) exited with code 0.
Press any key to close this window . . .


Please enter one of the folowing letters:
'A' to print unsorted items.
'B' to sort by item ID.
'C' to sort by item name.
'D' to sort by quantity on hand.
'E' to sort by price.
'F' to search by item ID or by item name.
'G' to print a report.
Or enter 'Q' to quit.
Enter here: a
Item ID          Item Name                 QTY               Price
912137           canvas                     21               32.75
912132           scissors                   29               10.60
912131           paper                      22                2.62
912135           clothes                    25               13.77
912141           clock                      25               27.56
912133           stuff                      11              132.72
912139           scizors                     1                6.56
912130           wendesdays                 44              234.71
912140           source                      2              334.77
912136           pants                       4                9.89
912138           shirts                      9               11.36
912134           cd                         56               34.78


Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: b
Item ID          Item Name                 QTY               Price
912130           wendesdays                 44              234.71
912131           paper                      22                2.62
912132           scissors                   29               10.60
912133           stuff                      11              132.72
912134           cd                         56               34.78
912135           clothes                    25               13.77
912136           pants                       4                9.89
912137           canvas                     21               32.75
912138           shirts                      9               11.36
912139           scizors                     1                6.56
912140           source                      2              334.77
912141           clock                      25               27.56


Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: c
Item ID          Item Name                 QTY               Price
912137           canvas                     21               32.75
912134           cd                         56               34.78
912141           clock                      25               27.56
912135           clothes                    25               13.77
912136           pants                       4                9.89
912131           paper                      22                2.62
912132           scissors                   29               10.60
912139           scizors                     1                6.56
912138           shirts                      9               11.36
912140           source                      2              334.77
912133           stuff                      11              132.72
912130           wendesdays                 44              234.71


Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: d
Item ID          Item Name                 QTY               Price
912139           scizors                     1                6.56
912140           source                      2              334.77
912136           pants                       4                9.89
912138           shirts                      9               11.36
912133           stuff                      11              132.72
912137           canvas                     21               32.75
912131           paper                      22                2.62
912141           clock                      25               27.56
912135           clothes                    25               13.77
912132           scissors                   29               10.60
912130           wendesdays                 44              234.71
912134           cd                         56               34.78


Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: e
Item ID          Item Name                 QTY               Price
912131           paper                      22                2.62
912139           scizors                     1                6.56
912136           pants                       4                9.89
912132           scissors                   29               10.60
912138           shirts                      9               11.36
912135           clothes                    25               13.77
912141           clock                      25               27.56
912137           canvas                     21               32.75
912134           cd                         56               34.78
912133           stuff                      11              132.72
912130           wendesdays                 44              234.71
912140           source                      2              334.77


Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: f
Enter the item ID or item name: 912231

Not Found

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: f
Enter the item ID or item name: sdfesesf

Not Found

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: f
Enter the item ID or item name: 912140

Item ID          Item Name                 QTY               Price
912140           source                      2              334.77

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: f
Enter the item ID or item name: Paper

Item ID          Item Name                 QTY               Price
912131           paper                      22                2.62

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: g
There are 12 unique items.
The total worth of the iventory is $16638.78
The total count of all items is 249.

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: sds

Not a valid choice please try again.

Please enter one of the folowing letters:
'A' to sort by item ID.
'B' to sort by item name.
'C' to sort by quantity on hand.
'D' to sort by price.
'E' to search by item ID or by item name.
'F' to print a report.
Or enter 'Q' to quit.
Enter here: q
Quiting.


C:\Users\18182\source\repos\test\Debug\test.exe (process 10556) exited with code 0.
Press any key to close this window . . .


*/
