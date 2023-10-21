//Tigran Manukyan
//Lab 08
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 100;
const double PRICE_PER_WIDGET = 2.22;

class Widget
{
private:
    int orderNumber, orderQuantity, qtyToBeShipped, priorityNumber;
    static int newOrderNumber;
public:
    Widget();
    Widget(int, int, int);
    void operator = (const Widget&);
    bool operator < (const Widget&);
    void setQtyToBeShipped(int);
    int getOrderNumber() const;
    int getOrderQuantity() const;
    int getToBeShipped() const;
    int getPriorityNumber() const;
    string getPriorityString() const;
};

class OrdersToBeFilled
{
private:
    Widget widgets[MAX_SIZE];
    int length, nbrOfWidgetsShipped;
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
    void reheapDown(int);
    void makeItAHeap();
};

class Warehouse
{
private:
    OrdersToBeFilled orders;
    int widgetsInStock = 0;
public:
    void newOrder();
    void newDelivery();
    void closeForTheDay();
    void displayOrderStack();
    void displayDeliveryStack();
};

int verifyInputInt();
int verifyInputOrderType();

int Widget::newOrderNumber = 1;

int main()
{
    Warehouse theWarehouse;
    char choice;

    do
    {
        cout << "Please enter one of the folowing letters:\n"
            << "\'A\' add new order\n"
            << "\'B\' display inventory on hand\n"
            << "\'C\' display outsanding orders\n"
            << "\'D\' close for the day and deliver orders\n"
            << "\'Q\' to quit\n"
            << "Enter here: ";
        cin >> choice;
        choice = tolower(choice);
        cin.ignore(80, '\n');
        switch (choice)
        {
        case 'a':
            theWarehouse.newOrder();
            break;
        case 'b':
            theWarehouse.displayDeliveryStack();
            break;
        case 'c':
            theWarehouse.displayOrderStack();
            break;
        case 'd':
            theWarehouse.closeForTheDay();
            break;
        case 'q':
            cout << "Quiting.\n" << endl;
            break;
        default:
            cout << "\nNot a valid choice please try again.\n" << endl;
        }
    } while (choice != 'q');

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
Widget::Widget(int orderQuantity, int qtyToBeShipped, int priorityNumber)
{
    orderNumber = newOrderNumber++;
    this->orderQuantity = orderQuantity;
    this->qtyToBeShipped = qtyToBeShipped;
    this->priorityNumber = priorityNumber;
}

// = operatior overload
//Pre condition: both Widgets are instantiated
//Post condition: sets orderNumber, orderQuantity, qtyToBeShipped, priorityNumber equal the second Widget+
void Widget::operator = (const Widget& temp)
{
    this->orderNumber = temp.getOrderNumber();
    this->orderQuantity = temp.getOrderQuantity();
    this->qtyToBeShipped = temp.getToBeShipped();
    this->priorityNumber = temp.getPriorityNumber();
}

// < operatior overload
//Pre condition: both Widgets are instantiated
//Post condition: returns true if current widget has higher priority or they have the same priority but this order came first.
bool Widget::operator < (const Widget& temp)
{
    return (this->priorityNumber < temp.getPriorityNumber() || (this->priorityNumber == temp.getPriorityNumber() && this->orderNumber < temp.getOrderNumber()));
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
int Widget::getPriorityNumber() const
{
    return priorityNumber;
}
string Widget::getPriorityString() const
{
    if (priorityNumber == 0)
        return "Extreme Rush Order";
    if (priorityNumber == 1)
        return "Expedite Rush Order";
    return "Standard Order";
}

/*********************************** OrdersToBeFilled FUNCTIONS AND CONSTRUCTOR ******************************************/

//OrdersToBeFilled Constructor
OrdersToBeFilled::OrdersToBeFilled()
{
    nbrOfWidgetsShipped = 0;
    length = 0;
}

//returns true if heap is empty
//Pre condition: heap is initialized
//Post condition: true is reaturned if heap is empty
bool OrdersToBeFilled::isEmpty() const
{
    return (length == 0);
}

//returns true if heap is full
//Pre condition: heap is initialized
//Post condition: true is reaturned if heap is full
bool OrdersToBeFilled::isFull() const
{
    return (length == MAX_SIZE);
}

//returns nbrOfWidgetsShipped
//Pre condition: heap is initialized
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

//returns length of heap
//Pre condition: stack is initialized
//Post condition: returns length of heap
int OrdersToBeFilled::getLength()
{
    return (length);
}

//Adds new item to the bottom of the array(not heap, needs to be turned into heap)
//Pre condition: array is not full
//Post condition: bottom element is new element
void OrdersToBeFilled::push(Widget widget)
{
    if (isFull())
    {
        throw "FullStack";
    }
    widgets[length] = widget;
    length++;
}

//Removes top item from heap and reheapDown is called
//Pre condition: heap is not empty
//Post condition: top element is removed
void OrdersToBeFilled::pop()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    length--;
    swap(widgets[0], widgets[length]);
    reheapDown(0);
}

//pointer to top of heap is returned
//Pre condition: heap is not empty
//Post condition: pointer to top of heap is returned
Widget* OrdersToBeFilled::peek()
{
    if (isEmpty())
    {
        throw "EmptyStack";
    }
    return &widgets[0];
}

//reheaps the top element to it's right place, and next order to be compleated at top
//Pre condition: heap is not empty
//Post condition: heap is now reheaped and next order to be compleated at top
void OrdersToBeFilled::reheapDown(int top)
{
    int childLeft = top * 2 + 1, childRight = top * 2 + 1;
    if (childRight < length)
    {
        if (widgets[childLeft] < widgets[childRight] && widgets[childLeft] < widgets[top])
        {
            swap(widgets[childLeft], widgets[top]);
            reheapDown(childLeft);
        }
        else if (widgets[childRight] < widgets[top])
        {
            swap(widgets[childRight], widgets[top]);
            reheapDown(childRight);
        }
    }
    else if (childLeft < length && widgets[childLeft] < widgets[top])
    {
        swap(widgets[childRight], widgets[top]);
    }
}

//sorts the array to make it a heap with next order to be compleated at top
//Pre condition: heap is not empty
//Post condition: the array is now a heap
void OrdersToBeFilled::makeItAHeap()
{
    int smallest;
    for (int toBeSwithced = 0; toBeSwithced < length - 1; toBeSwithced++)
    {
        smallest = toBeSwithced;
        for (int current = toBeSwithced + 1; current < length; current++)
        {
            if (widgets[current] < widgets[smallest])
                smallest = current;
        }
        if (toBeSwithced != smallest)
            swap(widgets[toBeSwithced], widgets[smallest]);
    }
}



/*********************************** Warehouse FUNCTIONS  ******************************************/

//adds new order to order array
//Pre condition: array is not full
//Post condition: new order added to order array
void Warehouse::newOrder()
{
    if (orders.isFull())
    {
        cout << "\nOrder list is full!\n" << endl;
    }
    else
    {
        int numberOfDeliveryWidgets, rushStatic;
        cout << "Please enter number of Widgets ordered: ";
        numberOfDeliveryWidgets = verifyInputInt();
        cout << "Please enter rush status\n(0 = extreme rush)(1 = expedite rush)(2 = standard): ";
        rushStatic = verifyInputOrderType();

        Widget temp(numberOfDeliveryWidgets, numberOfDeliveryWidgets, rushStatic);
        orders.push(temp);
        cout << endl;
    }
}

//adds 100 widgets to widgetsInStock with each worth the price of PRICE_PER_WIDGET
//Pre condition: widgetsInStock is instantiated
//Post condition: 100 widgets is added to widgetsInStock
void Warehouse::newDelivery()
{
    cout << "\nGetting a delivery of 100 widgets. Each worth " << PRICE_PER_WIDGET << ".\n" << endl;
    widgetsInStock += 100;
}

//ships out orders if orders is not empty, and gets delivery if widgetsInStock is empty
//Pre condition: orders is not empty
//Post condition: all orders are complete
void Warehouse::closeForTheDay()
{
    if (orders.isEmpty())
        cout << "\nThere are no orders.\n" << endl;
    else
    {
        Widget* tempOrder;
        int tempDeliveryNumber, tempQtySippedNum;
        double tempProfit = 0.00, tempSpent, percentMarkup;
        while (!orders.isEmpty())
        {
            orders.makeItAHeap();
            if (widgetsInStock < 1)
                newDelivery();
            else
            {
                tempOrder = orders.peek();

                if (tempOrder->getToBeShipped() > widgetsInStock)
                    tempQtySippedNum = widgetsInStock;
                else
                    tempQtySippedNum = tempOrder->getToBeShipped();

                tempOrder->setQtyToBeShipped(tempOrder->getToBeShipped() - tempQtySippedNum);
                widgetsInStock -= tempQtySippedNum;

                tempDeliveryNumber = widgetsInStock;
                tempSpent = (double)PRICE_PER_WIDGET * (double)tempQtySippedNum;

                if (tempOrder->getPriorityNumber() == 0)
                    percentMarkup = 0.50;
                else if (tempOrder->getPriorityNumber() == 1)
                    percentMarkup = 0.20;
                else if (tempOrder->getPriorityNumber() == 2)
                    percentMarkup = 0.10;

                tempProfit = percentMarkup * tempSpent;

                orders.addToWidgetsShipped(tempQtySippedNum);

                cout << fixed << setprecision(2)
                    << left << setw(28) << "Order Number" << right << setw(25) << tempOrder->getOrderNumber() << '\n'
                    << left << setw(28) << "Qty Ordered" << right << setw(25) << tempOrder->getOrderQuantity() << '\n'
                    << left << setw(28) << "Qty Shipped" << right << setw(25) << tempQtySippedNum << '\n'
                    << left << setw(28) << "Rush Status" << right << setw(25) << tempOrder->getPriorityString() << '\n'
                    << left << setw(28) << "% of markup" << right << setw(25) << percentMarkup * 100 << '\n'
                    << left << setw(28) << "Total Cost to the Warehouse" << right << setw(25) << tempSpent << '\n'
                    << left << setw(28) << "Total Cost to the Customer" << right << setw(25) << tempSpent + tempProfit << '\n'
                    << left << setw(28) << "Profit this Shipment" << right << setw(25) << tempProfit << '\n' << endl;

                cout << "Shipment details:\n" << setprecision(2) << fixed << right << setw(11) << "Qty Shipped"
                    << setw(15) << "Unit Price" << setw(27) << "Cost to the Warehouse" << setw(27) << "Cost to the Customer\n"
                    << setw(11) << tempQtySippedNum << setw(15) << PRICE_PER_WIDGET
                    << setw(27) << tempSpent << setw(26) << tempSpent + tempProfit << endl;

                if (orders.peek()->getToBeShipped() <= 0)
                    orders.pop();
                cout << endl;
            }
        }
    }

}

//displays details of outstanding orders
//Pre condition: orders stack is not empty
//Post condition: displays details of outstanding orders
void Warehouse::displayOrderStack()
{
    orders.makeItAHeap();
    int length = orders.getLength(), widgetsShipped = orders.getWidgetsShipped();
    if (length <= 0)
    {
        cout << "\nThere are no outstanding orders.\nThere were " << widgetsShipped << " widgets already shipped.\n" << endl;
    }
    else
    {
        Widget* tempWidget = orders.peek();
        cout << "\nThere are " << length << " outstanding orders.\nThere were " << widgetsShipped << " widgets already shipped.\nOutstanding orders:\n"
            << setprecision(2) << fixed << right << setw(7) << "Order #" << setw(25) << "Order Type" << setw(15) << "Qty Ordered\n";

        for (int i = 0; i < length; i++)
        {
            cout << right << setw(7) << tempWidget->getOrderNumber() << setw(25) << tempWidget->getPriorityString() << setw(14) << tempWidget->getOrderQuantity() << endl;
            tempWidget++;
        }
        cout << endl;
    }
}

//displays details of inventory on hand
//Pre condition: widgetsInStock is not empty
//Post condition: displays details of inventory on hand
void Warehouse::displayDeliveryStack()
{
    if (widgetsInStock <= 0)
    {
        cout << "\nThere are no widgets in stock.\n" << endl;
    }
    else
    {
        cout << "\nThere are " << widgetsInStock << " widgets in stock.\n"
            << setprecision(2) << fixed << "Price: " << PRICE_PER_WIDGET << '\n' << endl;
    }
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

//makes shure the input is ether a 0=extreme order  1=expedite rush  2=standard rush
int verifyInputOrderType()
{
    int input = -1;

    while (input < 0 || input > 2)
    {
        while (!(cin >> input))
        {
            cout << "Error Not a valid choice. Please enter a valid choice: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (input < 0 || input > 2)
            cout << "Error Not a valid choice. Please enter a valid choice: ";
    }
    return input;
}

//Output
/*
//////////////////////////////////// MAX_SIZE was set to 10 for testing ////////////////////////////////////
Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: b

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: c

There are no outstanding orders.
There were 0 widgets already shipped.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: d

There are no orders.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 6
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 0

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 3
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 2

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 0
Error: Not a positive number. Please enter a positive integer: a
Error: Not a number. Please enter a positive integer: 5
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 1

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 6
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 0

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 9
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 2

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 8
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 0

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 8
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 2

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 7
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 1

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 5
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 1

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 6
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 0

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a

Order list is full!

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: b

There are no widgets in stock.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: c

There are 10 outstanding orders.
There were 0 widgets already shipped.
Outstanding orders:
Order #               Order Type   Qty Ordered
      1       Extreme Rush Order             6
      4       Extreme Rush Order             6
      6       Extreme Rush Order             8
     10       Extreme Rush Order             6
      3      Expedite Rush Order             5
      8      Expedite Rush Order             7
      9      Expedite Rush Order             5
      2           Standard Order             3
      5           Standard Order             9
      7           Standard Order             8

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: d

Getting a delivery of 100 widgets. Each worth 2.22.

Order Number                                        1
Qty Ordered                                         6
Qty Shipped                                         6
Rush Status                        Extreme Rush Order
% of markup                                     50.00
Total Cost to the Warehouse                     13.32
Total Cost to the Customer                      19.98
Profit this Shipment                             6.66

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          6           2.22                      13.32                     19.98

Order Number                                        4
Qty Ordered                                         6
Qty Shipped                                         6
Rush Status                        Extreme Rush Order
% of markup                                     50.00
Total Cost to the Warehouse                     13.32
Total Cost to the Customer                      19.98
Profit this Shipment                             6.66

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          6           2.22                      13.32                     19.98

Order Number                                        6
Qty Ordered                                         8
Qty Shipped                                         8
Rush Status                        Extreme Rush Order
% of markup                                     50.00
Total Cost to the Warehouse                     17.76
Total Cost to the Customer                      26.64
Profit this Shipment                             8.88

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          8           2.22                      17.76                     26.64

Order Number                                       10
Qty Ordered                                         6
Qty Shipped                                         6
Rush Status                        Extreme Rush Order
% of markup                                     50.00
Total Cost to the Warehouse                     13.32
Total Cost to the Customer                      19.98
Profit this Shipment                             6.66

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          6           2.22                      13.32                     19.98

Order Number                                        3
Qty Ordered                                         5
Qty Shipped                                         5
Rush Status                       Expedite Rush Order
% of markup                                     20.00
Total Cost to the Warehouse                     11.10
Total Cost to the Customer                      13.32
Profit this Shipment                             2.22

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          5           2.22                      11.10                     13.32

Order Number                                        8
Qty Ordered                                         7
Qty Shipped                                         7
Rush Status                       Expedite Rush Order
% of markup                                     20.00
Total Cost to the Warehouse                     15.54
Total Cost to the Customer                      18.65
Profit this Shipment                             3.11

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          7           2.22                      15.54                     18.65

Order Number                                        9
Qty Ordered                                         5
Qty Shipped                                         5
Rush Status                       Expedite Rush Order
% of markup                                     20.00
Total Cost to the Warehouse                     11.10
Total Cost to the Customer                      13.32
Profit this Shipment                             2.22

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          5           2.22                      11.10                     13.32

Order Number                                        2
Qty Ordered                                         3
Qty Shipped                                         3
Rush Status                            Standard Order
% of markup                                     10.00
Total Cost to the Warehouse                      6.66
Total Cost to the Customer                       7.33
Profit this Shipment                             0.67

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          3           2.22                       6.66                      7.33

Order Number                                        5
Qty Ordered                                         9
Qty Shipped                                         9
Rush Status                            Standard Order
% of markup                                     10.00
Total Cost to the Warehouse                     19.98
Total Cost to the Customer                      21.98
Profit this Shipment                             2.00

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          9           2.22                      19.98                     21.98

Order Number                                        7
Qty Ordered                                         8
Qty Shipped                                         8
Rush Status                            Standard Order
% of markup                                     10.00
Total Cost to the Warehouse                     17.76
Total Cost to the Customer                      19.54
Profit this Shipment                             1.78

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          8           2.22                      17.76                     19.54

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: b

There are 37 widgets in stock.
Price: 2.22

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: c

There are no outstanding orders.
There were 63 widgets already shipped.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: d

There are no orders.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 40
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 7
Error Not a valid choice. Please enter a valid choice: 2

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 9
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 0

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: a
Please enter number of Widgets ordered: 8
Please enter rush status
(0 = extreme rush)(1 = expedite rush)(2 = standard): 1

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: b

There are 37 widgets in stock.
Price: 2.22

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: c

There are 3 outstanding orders.
There were 63 widgets already shipped.
Outstanding orders:
Order #               Order Type   Qty Ordered
     12       Extreme Rush Order             9
     13      Expedite Rush Order             8
     11           Standard Order            40

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: d
Order Number                                       12
Qty Ordered                                         9
Qty Shipped                                         9
Rush Status                        Extreme Rush Order
% of markup                                     50.00
Total Cost to the Warehouse                     19.98
Total Cost to the Customer                      29.97
Profit this Shipment                             9.99

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          9           2.22                      19.98                     29.97

Order Number                                       13
Qty Ordered                                         8
Qty Shipped                                         8
Rush Status                       Expedite Rush Order
% of markup                                     20.00
Total Cost to the Warehouse                     17.76
Total Cost to the Customer                      21.31
Profit this Shipment                             3.55

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
          8           2.22                      17.76                     21.31

Order Number                                       11
Qty Ordered                                        40
Qty Shipped                                        20
Rush Status                            Standard Order
% of markup                                     10.00
Total Cost to the Warehouse                     44.40
Total Cost to the Customer                      48.84
Profit this Shipment                             4.44

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
         20           2.22                      44.40                     48.84


Getting a delivery of 100 widgets. Each worth 2.22.

Order Number                                       11
Qty Ordered                                        40
Qty Shipped                                        20
Rush Status                            Standard Order
% of markup                                     10.00
Total Cost to the Warehouse                     44.40
Total Cost to the Customer                      48.84
Profit this Shipment                             4.44

Shipment details:
Qty Shipped     Unit Price      Cost to the Warehouse      Cost to the Customer
         20           2.22                      44.40                     48.84

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: b

There are 80 widgets in stock.
Price: 2.22

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: c

There are no outstanding orders.
There were 120 widgets already shipped.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: d

There are no orders.

Please enter one of the folowing letters:
'A' add new order
'B' display inventory on hand
'C' display outsanding orders
'D' close for the day and deliver orders
'Q' to quit
Enter here: q
Quiting.


C:\Users\18182\source\repos\test\Debug\test.exe (process 936) exited with code 0.
Press any key to close this window . . .

*/