// Lab 2 Manukyan, Tigran T TH
#include <iostream>
using namespace std;

void raiseNtoX();
void sumOfSquares();
void addFirstNTerms();
int raiseNtoXRecursion(int, int);
int sumOfSquaresRecursion(int, int);
int addFirstNTermsRecursion(int);
int verifyInput();

int main() {
	char input = 0;

	while (input != 'q')
	{
		cout << "Please enter one of the folowing letters:\n"
			<< "\'A\' to calculate the power of two number.\n"
			<< "\'B\' to calculate the sum of squares of the first n terms.\n"
			<< "\'C\' to calculate the sum of the first n terms.\n"
			<< "Or enter \'Q\' to quit.\n"
			<< "Enter here: ";
		cin >> input;
		cin.ignore(80, '\n');
		input = tolower(input);
		cout << endl;

		switch (input)
		{
		case 'a':
			raiseNtoX();
			break;

		case 'b':
			sumOfSquares();
			break;

		case 'c':
			addFirstNTerms();
			break;

		case 'q':
			cout << "Quiting.\n";
			break;

		default:
			cout << "Not valid. Please try again.\n\n";
			break;
		}
	}
	return 0;
}

//Ask user for two numbers and prints the power of the two
//Pre condition: user must enter two numbers
//Post condition: the power of the two items is outputed
void raiseNtoX()
{
	int n, x;

	cout << "Please enter the base: ";
	n = verifyInput();
	cout << "Please enter the exponent: ";
	x = verifyInput();

	if (x < 0)
	{
		if (n==0)
			cout << n << " raised to the power of " << x << " is undefined.\n" << endl;
		else
			cout << n << " raised to the power of " << x << " is equal to " << 1.0/ raiseNtoXRecursion(n, x * -1) << ".\n" << endl;
	}
	else if (n == 0 && x == 0)
		cout << n << " raised to the power of " << x << " is undefined.\n" << endl;
	else
		cout << n << " raised to the power of " << x << " is equal to " << raiseNtoXRecursion(n, x) << ".\n" << endl;
}

//Ask user for a number and outputs its sum of squares
//Pre condition: user must enter a number
//Post condition: the sum of squares is outputed
void sumOfSquares()
{
	int n, i;

	cout << "Please enter n: ";
	n = verifyInput();

	if (n < 0)
	{
		cout << "n has to be positive, using " << n * -1 << " instead.\n" << endl;
		n *= -1;
	}
	if (n == 0)
		cout << "0 = 0\n" << endl;
	else
	{
		i = sumOfSquaresRecursion(1, n);
		cout << i << '\n' << endl;
	}
}

//Ask user for a number and outputs its addition of first n terms
//Pre condition: user must enter a number
//Post condition: the addition of first n terms is outputed
void addFirstNTerms()
{
	int n, i;

	cout << "Please enter n: ";
	n = verifyInput();

	if (n < 0)
	{
		cout << "n has to be positive, using " << n * -1 << " instead.\n" << endl;
		n *= -1;
	}
	
	i = addFirstNTermsRecursion(n);
	cout << i << '\n' << endl;
}

//calculates power of the secend number to the first
//Pre condition: first and second numbers have to be ints
//Post condition: returns the power of two numbers
int raiseNtoXRecursion(int n, int x)
{
	if (x > 0)
		return n * raiseNtoXRecursion(n, x - 1);
	else
		return 1;
}

//caluculates the sum of squares of a number
//Pre condition: number has to be positive
//post condition: returns the sum of squares of a number
int sumOfSquaresRecursion(int start, int n)
{
	if (start == 1)
	{
		cout << "1 + ";
		return 1 + sumOfSquaresRecursion(start + 1, n);
	}
	else if (n > start)
	{
		cout << "(" << start << " * " << start << ") + ";
		return (start * start) + sumOfSquaresRecursion(start + 1, n);
	}
	else 
	{
		cout << "(" << start << " * " << start << ") = ";
		return start * start;
	}
		
}

//calculates the first n terms of a number
//Pre condition: number has to be positive
//Post condition: returns the addition of the first N terms of a number
int addFirstNTermsRecursion(int n)
{
	if (n > 1)
	{
		cout << "(" << n << " * " << n << ") + ";
		return (n * n) + addFirstNTermsRecursion(n - 1);
	}
	else if (n == 0)
	{
		cout << "0 = ";
		return 0;
	}
	else {
		cout << "1 = ";
		return 1;
	}
}

//makes shure the input is a integer
int verifyInput()
{
	int input;

	while (!(cin >> input))
	{
		cout << "Error: Not a number. Please enter a number: ";
		cin.clear();
		cin.ignore(123, '\n');
	}

	return input;
}

//Output
/*
Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: g

Not valid. Please try again.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: f

Not valid. Please try again.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: 0
Please enter the exponent: -2
0 raised to the power of -2 is undefined.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: 0
Please enter the exponent: 0
0 raised to the power of 0 is undefined.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: A

Please enter the base: 0
Please enter the exponent: 1
0 raised to the power of 1 is equal to 0.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: 5
Please enter the exponent: -3
5 raised to the power of -3 is equal to 0.008.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: -5

Not valid. Please try again.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: -5
Please enter the exponent: 3
-5 raised to the power of 3 is equal to -125.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: 5
Please enter the exponent: -2
5 raised to the power of -2 is equal to 0.04.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: -5
Please enter the exponent: 2
-5 raised to the power of 2 is equal to 25.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: 5

Not valid. Please try again.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: 5
Please enter the exponent: 0
5 raised to the power of 0 is equal to 1.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: 5
1 + (2 * 2) + (3 * 3) + (4 * 4) + (5 * 5) = 55

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: -7
n has to be positive, using 7 instead.

1 + (2 * 2) + (3 * 3) + (4 * 4) + (5 * 5) + (6 * 6) + (7 * 7) = 140

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: 7
1 + (2 * 2) + (3 * 3) + (4 * 4) + (5 * 5) + (6 * 6) + (7 * 7) = 140

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: 0
0 = 0

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: 1
1 = 1

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: 7
(7 * 7) + (6 * 6) + (5 * 5) + (4 * 4) + (3 * 3) + (2 * 2) + 1 = 140

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: -7
n has to be positive, using 7 instead.

(7 * 7) + (6 * 6) + (5 * 5) + (4 * 4) + (3 * 3) + (2 * 2) + 1 = 140

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: 0
0 = 0

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: 1
1 = 1

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: -1
n has to be positive, using 1 instead.

1 = 1

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: 5
(5 * 5) + (4 * 4) + (3 * 3) + (2 * 2) + 1 = 55

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: a

Please enter the base: -2
Please enter the exponent: d
Error: Not a number. Please enter a number: 2
-2 raised to the power of 2 is equal to 4.

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: b

Please enter n: ds
Error: Not a number. Please enter a number: 2
1 + (2 * 2) = 5

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: c

Please enter n: e
Error: Not a number. Please enter a number: 1
1 = 1

Please enter one of the folowing letters:
'A' to calculate the power of two number.
'B' to calculate the sum of squares of the first n terms.
'C' to calculate the sum of the first n terms.
Or enter 'Q' to quit.
Enter here: q

Quiting.

C:\Users\18182\source\repos\Lab_02_Manukyan_Tigran\Debug\Lab_02_Manukyan_Tigran.exe (process 5340) exited with code 0.
Press any key to close this window . . .

*/