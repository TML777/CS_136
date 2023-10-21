//Tigran Manukyan
//Lab 07
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct TreeNode
{
	char info;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

class ExpressionTree
{
private:
	TreeNode* root, *lastAdded;
public:
	ExpressionTree();
	~ExpressionTree();
	ExpressionTree(const ExpressionTree&);
	void operator = (const ExpressionTree&);

	void makeEmpty();
	string getPrint(string);
	TreeNode* getRoot() const;
	TreeNode* getLastAdded() const;
	void addToTop(char);
	void addToRightOfRoot(char);
	void addNonSpecial(char);
};

class Expressions
{
private:
	ExpressionTree tree;
	bool empty;
public:
	Expressions();
	bool isEmpty() const;
	void getExpressionsFromFileAndPrint();
	void addToExpressions(string);
	void print();
};

void makeTreeEmpty(TreeNode*);
string printPre(TreeNode*);
string printPost(TreeNode*);
string printIn(TreeNode*);
void copyTree(TreeNode*&, const TreeNode*);


int main()
{
	try
	{
		Expressions theProgram;
		theProgram.getExpressionsFromFileAndPrint();
	}
	catch (const char* c)
	{
		cout << c << endl;
		return 1;
	}
	

	return 0;
}


/*********************************** ExpressionTree FUNCTIONS AND CONSTRUCTOR ******************************************/

//Constructor
ExpressionTree::ExpressionTree()
{
	root = nullptr;
	lastAdded = nullptr;
}

//Destructor
ExpressionTree::~ExpressionTree()
{
	makeEmpty();
}

//Copy Constructor
ExpressionTree::ExpressionTree(const ExpressionTree& tempTree)
{
	copyTree(root, tempTree.getRoot());
	this->lastAdded = tempTree.getLastAdded();
}

//Operator overload
void ExpressionTree::operator = (const ExpressionTree& tempTree)
{
	makeEmpty();
	copyTree(root, tempTree.getRoot());
	this->lastAdded = tempTree.getLastAdded();
}

//////////////// Getters for ExpressionTree Class ////////////////
TreeNode* ExpressionTree::getRoot() const
{
	return root;
}
TreeNode* ExpressionTree::getLastAdded() const
{
	return lastAdded;
}

//Calls recursive funtion to make tree empty
//Pre condition: there has to be something in tree
//Post condition: tree is empty
void ExpressionTree::makeEmpty()
{
	makeTreeEmpty(root);
}

//calls recursive function to tree tree in pre/post/in order
//Pre conditon: type equals "preorder" || "postorder" || "inorder"
//Post condition: tree is returned as a strint in pre/post/in order
string ExpressionTree::getPrint(string type)
{
	if (type == "preorder")
		return printPre(root);
	if (type == "postorder")
		return printPost(root);
	if (type == "inorder")
		return printIn(root);
	return "";
}

//Adds temp to top of tree
//Pre conditon: temp can't be null
//Post condition: temp is added to top of tree
void ExpressionTree::addToTop(char temp)
{
	TreeNode* newRoot;
	newRoot = new TreeNode;
	newRoot->info = temp;
	newRoot->left = root;
	newRoot->right = nullptr;
	root = newRoot;
	lastAdded = root;
}

//Adds temp to right of root
//Pre conditon: tree can't be empty
//Post condition: temp is added to right of root
void ExpressionTree::addToRightOfRoot(char temp)
{
	TreeNode* newRoot;
	newRoot = new TreeNode;
	newRoot->info = temp;
	newRoot->left = root->right;
	newRoot->right = nullptr;
	root->right = newRoot;
	lastAdded = newRoot;
}

//Adds temp right of last added 
//Pre conditon: temp can't be null
//Post condition: temp is added to right of last added 
void ExpressionTree::addNonSpecial(char temp)
{
	TreeNode* newRoot;
	newRoot = new TreeNode;
	newRoot->info = temp;
	newRoot->left = nullptr;
	newRoot->right = nullptr;
	lastAdded->right = newRoot;
	lastAdded = root;
}


/*********************************** Expressions FUNCTIONS AND CONSTRUCTOR ******************************************/

//Constructor
Expressions::Expressions()
{
	empty = true;
}

//returns true if array is empty
//Pre condition: array is initialized
//Post condition: true is reaturned if array is empty
bool Expressions::isEmpty() const
{
	return empty;
}

//gets all expressions from input file and calls function to print them
//Pre condition: there has to be an input file
//Post condition: all expressions have been read and printed
void Expressions::getExpressionsFromFileAndPrint()
{
	ifstream inFile;
	inFile.open("expression.txt");
	if (!inFile.is_open())
		throw "Input File Did Not Open! Ending Program!";

	cout << left << setw(20) << "Expression" << setw(20) << "PreOrder" << setw(20) << "PostOrder" << setw(20) << "InOrder" << endl;

	string fullExpression;
	while (inFile >> fullExpression)
	{
		addToExpressions(fullExpression);
		cout << setw(20)<< fullExpression;
		print();
	}
	inFile.close();
}

//creates expression tree from given expression and adds it to tree
//Pre condition: expression can't be empty
//Post condition: expression added to tree
void Expressions::addToExpressions(string expression)
{
	TreeNode* tempRoot;
	ExpressionTree tempTree;
	bool firstTime = true;
	for (char& temp : expression)
	{
		if (firstTime)
		{
			tempTree.addToTop(temp);
			firstTime = false;
		}
		else
		{
			switch (temp)
			{
			case '+':
			case '-':
				tempTree.addToTop(temp);
				break;
				case '*':
			case '/':
				tempRoot = tempTree.getRoot();
				if (tempRoot->info == '+' || tempRoot->info == '-')
				{
					tempTree.addToRightOfRoot(temp);
				}
				else
				{
					tempTree.addToTop(temp);
				}
				break;
				default:
				tempTree.addNonSpecial(temp);
				break;
			}
		}
	}
	tree = tempTree;
	empty = false;
}

//prints tree in pre/post/in order
//Pre condition: tree can't be empty
//Post condition: tree is printed in pre/post/in order
void Expressions::print()
{
	if(!isEmpty())
		cout << left << setw(20) << tree.getPrint("preorder") << setw(20) << tree.getPrint("postorder") << setw(30) << tree.getPrint("inorder") << endl;
}



/*********************************** Expressions FUNCTIONS AND CONSTRUCTOR ******************************************/

//Recursive function to make any tree empty
//Pre condition: root has to nullptr leafs
//Post condition: tree is empty
void makeTreeEmpty(TreeNode* root)
{
	if (root != nullptr)
	{
		makeTreeEmpty(root->left);
		makeTreeEmpty(root->right);
		delete root;
	}
}

//Recursive function to return tree in preorder
//Pre condition: tree is not empty
//Post condition: tree returned in preorder
string printPre(TreeNode* root)
{
	if (root != nullptr)
	{
		return (root->info + printPre(root->left) + printPre(root->right));
	}
	return "";
}

//Recursive function to return tree in postorder
//Pre condition: tree is not empty
//Post condition: tree returned in postorder
string printPost(TreeNode* root)
{
	if (root != nullptr)
	{
		return (printPost(root->left) + printPost(root->right) + root->info);
	}
	return "";
}

//Recursive function to return tree in inorder
//Pre condition: tree is not empty
//Post condition: tree returned in inorder
string printIn(TreeNode* root)
{
	if (root != nullptr)
	{
		return ('(' + printIn(root->left) + root->info + printIn(root->right) + ')');
	}
	return "";
}

//Recursive function to copy root2 to root1
//Pre condition: root2 is const
//Post condition: root1 equals root2
void copyTree(TreeNode*& root1, const TreeNode* root2)
{
	if (root2 == nullptr)
	{
		root1 = nullptr;
	}
	else
	{
		root1 = new TreeNode;
		root1->info = root2->info;
		copyTree(root1->left, root2->left);
		copyTree(root1->right, root2->right);
	}
}

//Output
/*
//////////////////////////////////// No File ////////////////////////////////////
Input File Did Not Open! Ending Program!

C:\Users\18182\source\repos\Lab_07_Manukyan_Tigran\Debug\Lab_07_Manukyan_Tigran.exe (process 16600) exited with code 1.
Press any key to close this window . . .

//////////////////////////////////// File ////////////////////////////////////
x+y*a/b x/s-y+a-b
y-z*x z*x+g
g*y-r+t
y*x-a/b


/////////// Output ///////////
Expression          PreOrder            PostOrder           InOrder
x+y*a/b             +x/*yab             xya*b/+             ((x)+(((y)*(a))/(b)))
x/s-y+a-b           -+-/xsyab           xs/y-a+b-           (((((x)/(s))-(y))+(a))-(b))
y-z*x               -y*zx               yzx*-               ((y)-((z)*(x)))
z*x+g               +*zxg               zx*g+               (((z)*(x))+(g))
g*y-r+t             +-*gyrt             gy*r-t+             ((((g)*(y))-(r))+(t))
y*x-a/b             -*yx/ab             yx*ab/-             (((y)*(x))-((a)/(b)))

C:\Users\18182\source\repos\Lab_07_Manukyan_Tigran\Debug\Lab_07_Manukyan_Tigran.exe (process 21744) exited with code 0.
Press any key to close this window . . .


*/