//Tigran Manukyan
//Lab 06
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 100;

class Widget
{
private:
    int orderNumber, orderQuantity, qtyToBeShipped;
    static int newOrderNumber;
public:
    Widget();
    Widget(int, int);
    void setQtyToBeShipped(int);
    int getOrderNumber() const;
    int getOrderQuantity() const;
    int getToBeShipped() const;
};

class Inventory
{
private:
    int deliveryNumber, deliveryQuantity;
    double price;
    static int newDeliveryNumber;
public:
    Inventory();
    Inventory(int, double);
    void setDeliveryQuantity(int);
    int getDeliveryNumber() const;
    int getDeliveryQuantity() const;
    double getPrice() const;
};

struct NodeOrder
{
    Widget info;
    NodeOrder* next;
};

struct NodeInventroy
{
    Inventory info;
    NodeInventroy* next;
};

class OrdersToBeFilled
{
private:
    NodeOrder* head, *tail;
    int length, nbrOfWidgetsShipped;
public:
    OrdersToBeFilled();
    ~OrdersToBeFilled();
    void makeEmpty();
    bool isEmpty() const;
    bool isFull() const;
    void addToWidgetsShipped(int);
    void printDetails() const;
    int getLength();
    void push(Widget);
    void pop();
    Widget* peek();
};

class WidgetsOnHand
{
private:
    NodeInventroy* head, *tail;
    int length, nbrOfWidgetsInStock;
public:
    WidgetsOnHand();
    ~WidgetsOnHand();
    void makeEmpty();
    bool isEmpty() const;
    bool isFull() const;
    void addToWidgetsInStock(int);
    void printDetails() const;
    void push(Inventory);
    void pop();
    Inventory* peek();
};

class Warehouse
{
private:
    WidgetsOnHand warehouse;
    OrdersToBeFilled orders;
public:
    void newOrder();
    void newDelivery();
    void run();
    void displayOrderStack();
    void displayDeliveryStack();
    void printOrderDetails(int, int[], int[], double[], double[], double[]);
};


int verifyInputInt();
double verifyInputDouble();

int Widget::newOrderNumber = 1;
int Inventory::newDeliveryNumber = 1;


int main()
{
    Warehouse theWarehouse;
    char choice = NULL;

    while (choice != 'q')
    {
        cout << "Please enter one of the folowing letters:\n"
            << "\'A\' add delivery\n"
            << "\'B\' add new order\n"
            << "\'C\' display inventory on hand\n"
            << "\'D\' display outsanding orders\n"
            << "\'Q\' to quit\n"
            << "Enter here: ";
        cin >> choice;
        choice = tolower(choice);
        cin.ignore(80, '\n');
        switch (choice)
        {
        case 'a':
            theWarehouse.newDelivery();
            theWarehouse.run();
            break;
        case 'b':
            theWarehouse.newOrder();
            theWarehouse.run();
            break;
        case 'c':
            theWarehouse.displayDeliveryStack();
            break;
        case 'd':
            theWarehouse.displayOrderStack();
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


/*********************************** Widget FUNCTIONS AND CONSTRUCTOR ******************************************/

//OrdersToBeFilled Default Constructor
Widget::Widget()
{
    orderNumber = NULL;
    orderQuantity = NULL;
    qtyToBeShipped = NULL;
}

//OrdersToBeFilled Constructor
Widget::Widget(int orderQuantity, int qtyToBeShipped)
{
    orderNumber = newOrderNumber++;
    this->orderQuantity = orderQuantity;
    this->qtyToBeShipped = qtyToBeShipped;
}

//////////////// Getters and Setters for Widget Class /////////////////
void Widget::setQtyToBeShipped(int qtyToBeShipped)
{
    this->qtyToBeShipped = qtyToBeShipped;
}
int Widget::getOrderNumber() const
{
    return orderNumber;
}
int Widget::getOrderQuantity() const
{
    return orderQuantity;
}
int Widget::getToBeShipped() const
{
    return qtyToBeShipped;
}



/*********************************** Inventory FUNCTIONS AND CONSTRUCTOR ******************************************/

//OrdersToBeFilled Default Constructor
Inventory::Inventory()
{
    deliveryNumber = NULL;
    deliveryQuantity = NULL;
    price = NULL;
}

//OrdersToBeFilled Constructor
Inventory::Inventory(int deliveryQuantity, double price)
{
    deliveryNumber = newDeliveryNumber++;
    this->deliveryQuantity = deliveryQuantity;
    this->price = price;
}

//////////////// Getters and Setters for Inventroy Class /////////////////
void Inventory::setDeliveryQuantity(int deliveryQuantity)
{
    this->deliveryQuantity = deliveryQuantity;
}
int Inventory::getDeliveryNumber() const
{
    return deliveryNumber;
}
int Inventory::getDeliveryQuantity() const
{
    return deliveryQuantity;
}
double Inventory::getPrice() const
{
    return price;
}


/*********************************** OrdersToBeFilled FUNCTIONS AND CONSTRUCTOR ******************************************/

//OrdersToBeFilled Constructor
OrdersToBeFilled::OrdersToBeFilled()
{
    head = nullptr;
    tail = nullptr;
    nbrOfWidgetsShipped = 0;
    length = 0;
}

//OrdersToBeFilled Destructor
OrdersToBeFilled::~OrdersToBeFilled()
{
    makeEmpty();
}

//makes que empty
//Pre condition: there has to be a que
//Post condition: the que is empty
void OrdersToBeFilled::makeEmpty()
{
    NodeOrder* temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        length--;
        delete temp;
    }
    tail = nullptr;
}

//returns true if stack is empty
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is empty
bool OrdersToBeFilled::isEmpty() const
{
    return (length == 0);
}

//returns true if stack is full
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is full
bool OrdersToBeFilled::isFull() const
{
    return (length == MAX_SIZE);
}

//ands temp to nbrOfWidgetsShipped
//Pre condition: nbrOfWidgetsShipped is initialized
//Post condition: returns nbrOfWidgetsShipped
void OrdersToBeFilled::addToWidgetsShipped(int temp)
{
    nbrOfWidgetsShipped += temp;
}

//displays details of outstanding orders
//Pre condition: orders stack is not empty
//Post condition: displays details of outstanding orders
void OrdersToBeFilled::printDetails() const
{
    if (length <= 0)
    {
        cout << "\nThere are no outstanding orders.\nThere were " << nbrOfWidgetsShipped << " widgets already shipped.\n" << endl;
    }
    else
    {
        NodeOrder* tempNode = head;
        cout << "\nThere are " << length << " outstanding orders.\nThere were " << nbrOfWidgetsShipped << " widgets already shipped.\nOutstanding orders:\n"
            << setprecision(2) << fixed << right << setw(7) << "Order #" << setw(14) << "Qty Ordered"
            << setw(21) << "Qty to be Shipped\n";
        while (tempNode!=nullptr)
        {
            cout << right << setw(7) << tempNode->info.getOrderNumber() << setw(14) << tempNode->info.getOrderQuantity()
                << setw(20) << tempNode->info.getToBeShipped() << endl;
            tempNode = tempNode->next;
        }
        cout << endl;
    }
}

//returns length of stack
//Pre condition: stack is initialized
//Post condition: returns length of stack
int OrdersToBeFilled::getLength()
{
    return (length);
}

//Adds top item from stack
//Pre condition: stack is not full
//Post condition: top element is new element
void OrdersToBeFilled::push(Widget widget)
{
    if (isFull())
    {
        throw "FullStack";
    }
    NodeOrder *newNode;
    newNode = new NodeOrder;

    newNode->info = widget;
    newNode->next = nullptr;
    if (isEmpty())
    {
        head = newNode;
    }
    else
    {
        tail->next = newNode;
    }

    tail = newNode;
    length++;
}

//Removes top item from stack
//Pre condition: stack is not empty
//Post condition: top element is removed
void OrdersToBeFilled::pop()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    NodeOrder* temp;
    temp = head;
    head = head->next;
    delete temp;
    length--;
}

//pointer to top of stack is returned
//Pre condition: stack is not empty
//Post condition: pointer to top of stack is returned
Widget* OrdersToBeFilled::peek()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    return &head->info;
}



/*********************************** WidgetsOnHand FUNCTIONS AND CONSTRUCTOR ******************************************/

//WidgetsOnHand Constructor
WidgetsOnHand::WidgetsOnHand()
{
    head = nullptr;
    tail = nullptr;
    nbrOfWidgetsInStock = 0;
    length = 0;
}

//WidgetsOnHand Destructor
WidgetsOnHand::~WidgetsOnHand()
{
    makeEmpty();
}

//makes que empty
//Pre condition: there has to be a que
//Post condition: the que is empty
void WidgetsOnHand::makeEmpty()
{
    NodeInventroy* temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        length--;
        delete temp;
    }
    tail = nullptr;
}

//returns true if stack is empty
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is empty
bool WidgetsOnHand::isEmpty() const
{
    return (length == 0);
}

//returns true if stack is full
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is full
bool WidgetsOnHand::isFull() const
{
    return (length == MAX_SIZE);
}

//ands temp to nbrOfWidgetsInStock
//Pre condition: nbrOfWidgetsInStock is initialized
//Post condition: returns nbrOfWidgetsInStock
void WidgetsOnHand::addToWidgetsInStock(int temp)
{
    nbrOfWidgetsInStock += temp;
}

//displays details of inventory on hand
//Pre condition: warehouse stack is not empty
//Post condition: displays details of inventory on hand
void WidgetsOnHand::printDetails() const
{
    if (length <= 0)
    {
        cout << "\nThere are no widgets in stock.\n" << endl;
    }
    else
    {
        NodeInventroy* tempNode = head;
        cout << "\nThere are " << nbrOfWidgetsInStock << " widgets in stock.\nInventory:\n"
            << setprecision(2) << fixed << right << setw(10) << "Delivery #" << setw(15) << "Widgets Left"
            << setw(20) << "Price Per Widget\n";
        while (tempNode != nullptr)
        {
            cout << right << setw(10) << tempNode->info.getDeliveryNumber() << setw(15) << tempNode->info.getDeliveryQuantity()
                << setw(19) << tempNode->info.getPrice() << endl;
            tempNode = tempNode->next;
        }
        cout << endl;
    }
}

//Adds top item from stack
//Pre condition: stack is not full
//Post condition: top element is new element
void WidgetsOnHand::push(Inventory widget)
{
    if (isFull())
    {
        throw "FullStack";
    }
    NodeInventroy* newNode;
    newNode = new NodeInventroy;

    newNode->info = widget;
    newNode->next = nullptr;
    if (isEmpty())
    {
        head = newNode;
    }
    else
    {
        tail->next = newNode;
    }

    tail = newNode;
    length++;
}

//Removes top item from stack
//Pre condition: stack is not empty
//Post condition: top element is removed
void WidgetsOnHand::pop()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    NodeInventroy* temp;
    temp = head;
    head = head->next;
    delete temp;
    length--;
}

//pointer to top of stack is returned
//Pre condition: stack is not empty
//Post condition: pointer to top of stack is returned
Inventory* WidgetsOnHand::peek()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    return &head->info;
}



/*********************************** Warehouse FUNCTIONS  ******************************************/

//adds new order to order stack
//Pre condition: stack is not full
//Post condition: new order added to order stack
void Warehouse::newOrder()
{
    if (orders.isFull())
    {
        cout << "\nOrder list is full!\n" << endl;
    }
    else
    {
        int numberOfWidgets;
        cout << "Please enter number of Widgets orderd: ";
        numberOfWidgets = verifyInputInt();

        Widget temp(numberOfWidgets, numberOfWidgets);
        orders.push(temp);

        if (warehouse.isEmpty())
            cout << "Order back-ordered." << endl;
        cout << endl;
    }
}

//adds new delivery to delivery stack
//Pre condition: stack is not full
//Post condition: new delivery added to delivery stack
void Warehouse::newDelivery()
{
    if (warehouse.isFull())
    {
        cout << "\nWarehouse list is full!\n" << endl;
    }
    else
    {
        int numberOfWidgets;
        double price;
        cout << "Please enter number of Widgets delivered: ";
        numberOfWidgets = verifyInputInt();
        cout << "Please enter the price for one Widget: ";
        price = verifyInputDouble();

        Inventory temp(numberOfWidgets, price);
        warehouse.push(temp);

        cout << endl;
        warehouse.addToWidgetsInStock(numberOfWidgets);
    }
}

//ships out orders if orders and warhouse are not empty
//Pre condition: orders and warhouse are not empty
//Post condition: all orders are complete, or at least all those who can be complete
void Warehouse::run()
{
    Widget* tempOrder;
    Inventory* tempStock;
    int totalQtyShipped = 0, tempDeliveryNumbers[MAX_SIZE], tempQtySippedNums[MAX_SIZE], index;
    double totalProfit = 0.0, totalSpent = 0.0, tempProfit, tempSpent[MAX_SIZE], tempPrice[MAX_SIZE], tempTotal[MAX_SIZE];
    string temp;
    while ((!warehouse.isEmpty()) && (!orders.isEmpty()))
    {
        index = -1;
        tempOrder = orders.peek();
        tempStock = warehouse.peek();

        temp = "";

        while (!warehouse.isEmpty() && tempOrder->getToBeShipped() > 0)
        {
            index++;
            tempStock = warehouse.peek();

            if (tempOrder->getToBeShipped() > tempStock->getDeliveryQuantity())
                tempQtySippedNums[index] = tempStock->getDeliveryQuantity();
            else
                tempQtySippedNums[index] = tempOrder->getToBeShipped();

            tempOrder->setQtyToBeShipped(tempOrder->getToBeShipped() - tempQtySippedNums[index]);
            tempStock->setDeliveryQuantity(tempStock->getDeliveryQuantity() - tempQtySippedNums[index]);

            tempDeliveryNumbers[index] = tempStock->getDeliveryNumber();
            tempPrice[index] = tempStock->getPrice();
            tempSpent[index] = (double)tempStock->getPrice() * (double)tempQtySippedNums[index];
            tempProfit = (double)tempSpent[index] * 0.5;
            tempTotal[index] = tempProfit + tempSpent[index];


            totalQtyShipped += tempQtySippedNums[index];
            totalSpent += tempSpent[index];
            totalProfit += tempProfit;

            if (warehouse.peek()->getDeliveryQuantity() == 0)
                warehouse.pop();
        }

        warehouse.addToWidgetsInStock((0 - totalQtyShipped));
        orders.addToWidgetsShipped(totalQtyShipped);

        cout << fixed << setprecision(2)
            << left << setw(28) << "Order Number" << right << setw(10) << tempOrder->getOrderNumber() << '\n'
            << left << setw(28) << "Qty Ordered" << right << setw(10) << tempOrder->getOrderQuantity() << '\n'
            << left << setw(28) << "Qty Shipped this Shipment" << right << setw(10) << totalQtyShipped << '\n'
            << left << setw(28) << "Qty to be Shipped" << right << setw(10) << tempOrder->getToBeShipped() << '\n'
            << left << setw(28) << "Total Cost to the Warehouse" << right << setw(10) << totalSpent << '\n'
            << left << setw(28) << "Total Cost to the Customer" << right << setw(10) << totalSpent + totalProfit << '\n'
            << left << setw(28) << "Profit this Shipment" << right << setw(10) << totalProfit << '\n' << endl;

        printOrderDetails(index, tempDeliveryNumbers, tempQtySippedNums, tempPrice, tempSpent, tempTotal);

        if (orders.peek()->getToBeShipped() <= 0)
            orders.pop();

        totalQtyShipped = 0;
        totalProfit = 0.0;
        totalSpent = 0.0;
    }
}

//calls function to display details of outstanding orders
//Pre condition: orders stack is not empty
//Post condition: calls function to display details of outstanding orders
void Warehouse::displayOrderStack()
{
    orders.printDetails(); 
}

//calls function to display details of inventory on hand
//Pre condition: warehouse stack is not empty
//Post condition: calls function to display details of inventory on hand
void Warehouse::displayDeliveryStack()
{
    warehouse.printDetails();
}

//prints out order details
//Pre condition: all arrays have at leaset one number in them
//Post condition: order details are printed
void Warehouse::printOrderDetails(int index, int tempDeliveryNumbers[], int tempQtySippedNums[], double tempPrice[], double tempSpent[], double tempTotal[])
{
    cout << "Shipment details:\n" << setprecision(2) << fixed << right << setw(10) << "Delivery #" << setw(15) << "Qty Shipped"
        << setw(18) << "Unit Price" << setw(27) << "Cost to the Warehouse" << setw(27) << "Cost to the Customer\n";
    for (int i = 0; i <= index; i++)
    {
        cout << setw(10) << tempDeliveryNumbers[i] << setw(15) << tempQtySippedNums[i] << setw(18)
            << tempPrice[i] << setw(27) << tempSpent[i] << setw(26) << tempTotal[i] << endl;
    }
    cout << endl;
}



/*********************************** FUNCTIONS ******************************************/

//makes shure the input is an integer and positive
int verifyInputInt()
{
    int input = -1;

    while (input <= 0)
    {
        while (!(cin >> input))
        {
            cout << "Error: Not a number. Please enter a positive integer: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (input <= 0)
            cout << "Error: Not a positive number. Please enter a positive integer: ";
    }
    return input;
}

//makes shure the input is a double and positive
double verifyInputDouble()
{
    double input = -1;

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
//////////////////////////////////// MAX_SIZE was set to 5 for testing ////////////////////////////////////
Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are no outstanding orders.
There were 0 widgets already shipped.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 12
Please enter the price for one Widget: 2.2

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 5
Please enter the price for one Widget: 3

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 2
Please enter the price for one Widget: 2.22

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 2
Please enter the price for one Widget: 4

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 10
Please enter the price for one Widget: 5

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a

Warehouse list is full!

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are 31 widgets in stock.
Inventory:
Delivery #   Widgets Left   Price Per Widget
         1             12               2.20
         2              5               3.00
         3              2               2.22
         4              2               4.00
         5             10               5.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are no outstanding orders.
There were 0 widgets already shipped.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 10

Order Number                         1
Qty Ordered                         10
Qty Shipped this Shipment           10
Qty to be Shipped                    0
Total Cost to the Warehouse      22.00
Total Cost to the Customer       33.00
Profit this Shipment             11.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         1             10              2.20                      22.00                     33.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are 21 widgets in stock.
Inventory:
Delivery #   Widgets Left   Price Per Widget
         1              2               2.20
         2              5               3.00
         3              2               2.22
         4              2               4.00
         5             10               5.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 20

Order Number                         2
Qty Ordered                         20
Qty Shipped this Shipment           20
Qty to be Shipped                    0
Total Cost to the Warehouse      76.84
Total Cost to the Customer      115.26
Profit this Shipment             38.42

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         1              2              2.20                       4.40                      6.60
         2              5              3.00                      15.00                     22.50
         3              2              2.22                       4.44                      6.66
         4              2              4.00                       8.00                     12.00
         5              9              5.00                      45.00                     67.50

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are 1 widgets in stock.
Inventory:
Delivery #   Widgets Left   Price Per Widget
         5              1               5.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are no outstanding orders.
There were 30 widgets already shipped.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 3
Please enter the price for one Widget: 1

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 15

Order Number                         3
Qty Ordered                         15
Qty Shipped this Shipment            4
Qty to be Shipped                   11
Total Cost to the Warehouse       8.00
Total Cost to the Customer       12.00
Profit this Shipment              4.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         5              1              5.00                       5.00                      7.50
         6              3              1.00                       3.00                      4.50

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 1 outstanding orders.
There were 34 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      3            15                  11

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 12
Order back-ordered.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 12
Order back-ordered.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 5
Order back-ordered.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 3
Order back-ordered.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b

Order list is full!

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 5 outstanding orders.
There were 34 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      3            15                  11
      4            12                  12
      5            12                  12
      6             5                   5
      7             3                   3

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 16
Please enter the price for one Widget: 2.22

Order Number                         3
Qty Ordered                         15
Qty Shipped this Shipment           11
Qty to be Shipped                    0
Total Cost to the Warehouse      24.42
Total Cost to the Customer       36.63
Profit this Shipment             12.21

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         7             11              2.22                      24.42                     36.63

Order Number                         4
Qty Ordered                         12
Qty Shipped this Shipment            5
Qty to be Shipped                    7
Total Cost to the Warehouse      11.10
Total Cost to the Customer       16.65
Profit this Shipment              5.55

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         7              5              2.22                      11.10                     16.65

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 4 outstanding orders.
There were 50 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      4            12                   7
      5            12                  12
      6             5                   5
      7             3                   3

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 20
Please enter the price for one Widget: 1

Order Number                         4
Qty Ordered                         12
Qty Shipped this Shipment            7
Qty to be Shipped                    0
Total Cost to the Warehouse       7.00
Total Cost to the Customer       10.50
Profit this Shipment              3.50

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8              7              1.00                       7.00                     10.50

Order Number                         5
Qty Ordered                         12
Qty Shipped this Shipment           12
Qty to be Shipped                    0
Total Cost to the Warehouse      12.00
Total Cost to the Customer       18.00
Profit this Shipment              6.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8             12              1.00                      12.00                     18.00

Order Number                         6
Qty Ordered                          5
Qty Shipped this Shipment            1
Qty to be Shipped                    4
Total Cost to the Warehouse       1.00
Total Cost to the Customer        1.50
Profit this Shipment              0.50

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8              1              1.00                       1.00                      1.50

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 2 outstanding orders.
There were 70 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      6             5                   4
      7             3                   3

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 1
Please enter the price for one Widget: 5

Order Number                         6
Qty Ordered                          5
Qty Shipped this Shipment            1
Qty to be Shipped                    3
Total Cost to the Warehouse       5.00
Total Cost to the Customer        7.50
Profit this Shipment              2.50

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         9              1              5.00                       5.00                      7.50

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 10
Please enter the price for one Widget: 9

Order Number                         6
Qty Ordered                          5
Qty Shipped this Shipment            3
Qty to be Shipped                    0
Total Cost to the Warehouse      27.00
Total Cost to the Customer       40.50
Profit this Shipment             13.50

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        10              3              9.00                      27.00                     40.50

Order Number                         7
Qty Ordered                          3
Qty Shipped this Shipment            3
Qty to be Shipped                    0
Total Cost to the Warehouse      27.00
Total Cost to the Customer       40.50
Profit this Shipment             13.50

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        10              3              9.00                      27.00                     40.50

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are no outstanding orders.
There were 77 widgets already shipped.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 18
Please enter the price for one Widget: 6.34

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 16

Order Number                         8
Qty Ordered                         16
Qty Shipped this Shipment           16
Qty to be Shipped                    0
Total Cost to the Warehouse     112.08
Total Cost to the Customer      168.12
Profit this Shipment             56.04

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        10              4              9.00                      36.00                     54.00
        11             12              6.34                      76.08                    114.12

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are 6 widgets in stock.
Inventory:
Delivery #   Widgets Left   Price Per Widget
        11              6               6.34

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: b
Please enter number of Widgets orderd: 6

Order Number                         9
Qty Ordered                          6
Qty Shipped this Shipment            6
Qty to be Shipped                    0
Total Cost to the Warehouse      38.04
Total Cost to the Customer       57.06
Profit this Shipment             19.02

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        11              6              6.34                      38.04                     57.06

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are no outstanding orders.
There were 99 widgets already shipped.

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: q
Quiting.


C:\Users\18182\source\repos\Lab_06_Manukyan_Tigran\Debug\Lab_06_Manukyan_Tigran.exe (process 21732) exited with code 0.
Press any key to close this window . . .

*/