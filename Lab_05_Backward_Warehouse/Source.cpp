//Tigran Manukyan
//Lab 05
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

class OrdersToBeFilled
{
private:
    Widget widgets[MAX_SIZE];
    int index, nbrOfWidgetsShipped;
public:
    OrdersToBeFilled();
    bool isEmpty() const;
    bool isFull() const;
    int getWidgetsShipped() const;
    void addToWidgetsShipped(int);
    int getLength();
    void push(Widget);
    void pop();
    Widget* peek();
};

class WidgetsOnHand
{
private:
    Inventory widgets[MAX_SIZE];
    int index, nbrOfWidgetsInStock;
public:
    WidgetsOnHand();
    bool isEmpty() const;
    bool isFull() const;
    int getWidgetsInStock() const;
    void addToWidgetsInStock(int);
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
    void printOrderDetails(int, int[], int[], double[], double[] , double[]);
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

//Widget Default Constructor
Widget::Widget()
{
    orderNumber = NULL;
    orderQuantity = NULL;
    qtyToBeShipped = NULL;
}

//Widget Constructor
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

//Inventory Default Constructor
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
    nbrOfWidgetsShipped = 0;
    index = -1;
}

//returns true if stack is empty
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is empty
bool OrdersToBeFilled::isEmpty() const
{
    return (index == -1);
}

//returns true if stack is full
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is full
bool OrdersToBeFilled::isFull() const
{
    return (index == MAX_SIZE - 1);
}

//returns nbrOfWidgetsShipped
//Pre condition: stack is initialized
//Post condition: returns nbrOfWidgetsShipped
int OrdersToBeFilled::getWidgetsShipped() const
{
    return nbrOfWidgetsShipped;
}

//ands temp to nbrOfWidgetsShipped
//Pre condition: nbrOfWidgetsShipped is initialized
//Post condition: returns nbrOfWidgetsShipped
void OrdersToBeFilled::addToWidgetsShipped(int temp)
{
    nbrOfWidgetsShipped += temp;
}

//returns length of stack
//Pre condition: stack is initialized
//Post condition: returns length of stack
int OrdersToBeFilled::getLength()
{
    return (index + 1);
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
    ++index;
    widgets[index] = widget;
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
    index--;
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
    return &widgets[index];
}



/*********************************** WidgetsOnHand FUNCTIONS AND CONSTRUCTOR ******************************************/

//WidgetsOnHand Constructor
WidgetsOnHand::WidgetsOnHand()
{
    nbrOfWidgetsInStock = 0;
    index = -1;
}

//returns true if stack is empty
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is empty
bool WidgetsOnHand::isEmpty() const
{
    return (index == -1);
}

//returns true if stack is full
//Pre condition: stack is initialized
//Post condition: true is reaturned if stack is full
bool WidgetsOnHand::isFull() const
{
    return (index == MAX_SIZE - 1);
}

//returns nbrOfWidgetsInStock
//Pre condition: stack is initialized
//Post condition: returns nbrOfWidgetsInStock
int WidgetsOnHand::getWidgetsInStock() const
{
    return nbrOfWidgetsInStock;
}

//ands temp to nbrOfWidgetsInStock
//Pre condition: nbrOfWidgetsInStock is initialized
//Post condition: returns nbrOfWidgetsInStock
void WidgetsOnHand::addToWidgetsInStock(int temp)
{
    nbrOfWidgetsInStock += temp;
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
    ++index;
    widgets[index] = widget;
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
    index--;
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
    return &widgets[index];
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
        cout << "\nWarehouse is full!\n" << endl;
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

//displays details of outstanding orders
//Pre condition: orders stack is not empty
//Post condition: displays details of outstanding orders
void Warehouse::displayOrderStack()
{
    int length = orders.getLength(), widgetsShipped = orders.getWidgetsShipped();
    if (length <= 0)
    {
        cout << "\nThere are no outstanding orders.\nThere were " << widgetsShipped << " widgets already shipped.\n" << endl;
    }
    else
    {
        OrdersToBeFilled tempOrders = orders;
        Widget* tempWidget;
        cout << "\nThere are " << length << " outstanding orders.\nThere were " << widgetsShipped << " widgets already shipped.\nOutstanding orders:\n"
            << setprecision(2) << fixed << right << setw(7) << "Order #" << setw(14) << "Qty Ordered"
            << setw(21) << "Qty to be Shipped\n";
        while (!tempOrders.isEmpty())
        {
            tempWidget = tempOrders.peek();
            cout << right << setw(7) << tempWidget->getOrderNumber() << setw(14) << tempWidget->getOrderQuantity()
                << setw(20) << tempWidget->getToBeShipped() << endl;
            tempOrders.pop();
        }
        cout << endl;
    }
}

//displays details of inventory on hand
//Pre condition: warehouse stack is not empty
//Post condition: displays details of inventory on hand
void Warehouse::displayDeliveryStack()
{
    int widgetsInStock = warehouse.getWidgetsInStock(); 
    if (widgetsInStock <= 0)
    {
        cout << "\nThere are no widgets in stock.\n" << endl;
    }
    else
    {
        WidgetsOnHand tempWarehouse = warehouse;
        Inventory* tempInventory;
        cout << "\nThere are " << widgetsInStock << " widgets in stock.\nInventory:\n"
            << setprecision(2) << fixed << right << setw(10) << "Delivery #" << setw(15) << "Widgets Left"
            << setw(20) << "Price Per Widget\n";
        while (!tempWarehouse.isEmpty())
        {
            tempInventory = tempWarehouse.peek();
            cout << right << setw(10) << tempInventory->getDeliveryNumber() << setw(15) << tempInventory->getDeliveryQuantity()
                << setw(19) << tempInventory->getPrice() << endl;
            tempWarehouse.pop();
        }
        cout << endl;
    }
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

Warehouse is full!

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
         5             10               5.00
         4              2               4.00
         3              2               2.22
         2              5               3.00
         1             12               2.20

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
Total Cost to the Warehouse      50.00
Total Cost to the Customer       75.00
Profit this Shipment             25.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         5             10              5.00                      50.00                     75.00

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
         4              2               4.00
         3              2               2.22
         2              5               3.00
         1             12               2.20

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
Total Cost to the Warehouse      51.64
Total Cost to the Customer       77.46
Profit this Shipment             25.82

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         4              2              4.00                       8.00                     12.00
         3              2              2.22                       4.44                      6.66
         2              5              3.00                      15.00                     22.50
         1             11              2.20                      24.20                     36.30

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
         1              1               2.20

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
Total Cost to the Warehouse       5.20
Total Cost to the Customer        7.80
Profit this Shipment              2.60

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         6              3              1.00                       3.00                      4.50
         1              1              2.20                       2.20                      3.30

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
      7             3                   3
      6             5                   5
      5            12                  12
      4            12                  12
      3            15                  11

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 16
Please enter the price for one Widget: 2.22

Order Number                         7
Qty Ordered                          3
Qty Shipped this Shipment            3
Qty to be Shipped                    0
Total Cost to the Warehouse       6.66
Total Cost to the Customer        9.99
Profit this Shipment              3.33

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         7              3              2.22                       6.66                      9.99

Order Number                         6
Qty Ordered                          5
Qty Shipped this Shipment            5
Qty to be Shipped                    0
Total Cost to the Warehouse      11.10
Total Cost to the Customer       16.65
Profit this Shipment              5.55

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         7              5              2.22                      11.10                     16.65

Order Number                         5
Qty Ordered                         12
Qty Shipped this Shipment            8
Qty to be Shipped                    4
Total Cost to the Warehouse      17.76
Total Cost to the Customer       26.64
Profit this Shipment              8.88

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         7              8              2.22                      17.76                     26.64

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 3 outstanding orders.
There were 50 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      5            12                   4
      4            12                  12
      3            15                  11

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

Order Number                         5
Qty Ordered                         12
Qty Shipped this Shipment            4
Qty to be Shipped                    0
Total Cost to the Warehouse       4.00
Total Cost to the Customer        6.00
Profit this Shipment              2.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8              4              1.00                       4.00                      6.00

Order Number                         4
Qty Ordered                         12
Qty Shipped this Shipment           12
Qty to be Shipped                    0
Total Cost to the Warehouse      12.00
Total Cost to the Customer       18.00
Profit this Shipment              6.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8             12              1.00                      12.00                     18.00

Order Number                         3
Qty Ordered                         15
Qty Shipped this Shipment            4
Qty to be Shipped                    7
Total Cost to the Warehouse       4.00
Total Cost to the Customer        6.00
Profit this Shipment              2.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
         8              4              1.00                       4.00                      6.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: d

There are 1 outstanding orders.
There were 70 widgets already shipped.
Outstanding orders:
Order #   Qty Ordered   Qty to be Shipped
      3            15                   7

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: a
Please enter number of Widgets delivered: 1
Please enter the price for one Widget: 5

Order Number                         3
Qty Ordered                         15
Qty Shipped this Shipment            1
Qty to be Shipped                    6
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

Order Number                         3
Qty Ordered                         15
Qty Shipped this Shipment            6
Qty to be Shipped                    0
Total Cost to the Warehouse      54.00
Total Cost to the Customer       81.00
Profit this Shipment             27.00

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        10              6              9.00                      54.00                     81.00

Please enter one of the folowing letters:
'A' add delivery
'B' add new order
'C' display inventory on hand
'D' display outsanding orders
'Q' to quit
Enter here: c

There are 4 widgets in stock.
Inventory:
Delivery #   Widgets Left   Price Per Widget
        10              4               9.00

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
Total Cost to the Warehouse     101.44
Total Cost to the Customer      152.16
Profit this Shipment             50.72

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        11             16              6.34                     101.44                    152.16

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
        11              2               6.34
        10              4               9.00

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
Total Cost to the Warehouse      48.68
Total Cost to the Customer       73.02
Profit this Shipment             24.34

Shipment details:
Delivery #    Qty Shipped        Unit Price      Cost to the Warehouse      Cost to the Customer
        11              2              6.34                      12.68                     19.02
        10              4              9.00                      36.00                     54.00

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


C:\Users\18182\source\repos\Lab_05_Manukyan_Tigran\Debug\Lab_05_Manukyan_Tigran.exe (process 20172) exited with code 0.
Press any key to close this window . . .

*/