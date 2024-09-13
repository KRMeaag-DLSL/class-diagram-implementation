#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Declaring of constants for arrays and easy editing
const int NUMOFPRODUCTS = 4;
const int MAXORDERS = 50;
const int WIDTH = 15;

// Struct for list of products in shopping carts and order list
struct listProduct {
    string productIDList;
    string productNameList;
    float productPriceList;
    int productIDQuantity;
};

class Product {
    protected:
        string productID[NUMOFPRODUCTS] = {"AAA", "AAB", "AAC", "AAD"};
        string name[NUMOFPRODUCTS] = {"Pen", "Paper", "Pencil", "Eraser"};
        float price[NUMOFPRODUCTS] = {10, 50, 15, 5};

    public: 

        // Displays list of products
        void display() {
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Name"
            << setw(WIDTH) << "Price" << endl;

            for (int i = 0; i < NUMOFPRODUCTS; i++)
            {
                cout << left << setw(WIDTH) << productID[i] << setw(WIDTH) << name[i] 
                << setw(WIDTH) << price[i] << endl;
            }
        }

        // Checks if ID input by user is in the list of products
        int checkList(string inputID) {
            // Find if inputted string is in database

            if (inputID.length() != productID[0].length()) {
                return -1;
            }

            for (int i = 0; i < inputID.size(); i++) {
                inputID[i] = toupper(inputID[i]);
            }

            for (int i = 0; i < NUMOFPRODUCTS; i++) {
                if (inputID == productID[i]) {
                    return i;
                }
            }

            return -1;
        }
};

class ShoppingCart : protected Product{
    private:
        float total;
        vector<listProduct> shoppingList;
        listProduct shopListBuffer;

    public:
        // Adds products to cart
        void addToCart(int index, int quantity) {
            shopListBuffer.productIDList = productID[index];
            shopListBuffer.productIDQuantity = quantity;
            shopListBuffer.productNameList = name[index];
            shopListBuffer.productPriceList = price[index];

            shoppingList.push_back(shopListBuffer);

            cout << "\nItem has been added sucessfully!" << endl;
        }

        vector<listProduct> returnShoppingList () {
            return shoppingList;
        }

        int returnCartSize() {
            return shoppingList.size();
        }

        float computeTotal()
        {
            total = 0;
            for (int i = 0; i < shoppingList.size(); i++)
            {
                total += shoppingList[i].productPriceList * shoppingList[i].productIDQuantity;
            }

            return total;
        }

        // Displays list of products in shopping cart
        void display() {
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Name"
            << setw(WIDTH) << "Price" << setw(WIDTH) << "Quantity" << endl;
            for (int i = 0; i < shoppingList.size(); i++)
            {
                cout << left << setw(WIDTH) << shoppingList[i].productIDList << setw(WIDTH) << shoppingList[i].productNameList
                << setw(WIDTH) << shoppingList[i].productPriceList << setw(WIDTH) << shoppingList[i].productIDQuantity << endl;
            }
        }

        void clearCart() {
            for (int i = 0; i < shoppingList.size(); i++)
            {
                shoppingList.clear();
            }
        }
};

class Order {
    private:
        int orderID;
        float total;
        vector<listProduct> orderList;

    public:
        // Displays list of products for this order
        void displayOrder() {
            cout << "\nOrder ID: " << orderID<< endl;
            cout << "Total Amount: " << total << endl;
            cout << "Order Details: " << endl;
            
            cout << left << setw(WIDTH) << "Product ID" << setw(WIDTH) << "Name"
            << setw(WIDTH) << "Price" << setw(WIDTH) << "Quantity" << endl;
            for (int i = 0; i < orderList.size(); i++)
            {
                cout << left << setw(WIDTH) << orderList[i].productIDList << setw(WIDTH) << orderList[i].productNameList
                << setw(WIDTH) << orderList[i].productPriceList << setw(WIDTH) << orderList[i].productIDQuantity << endl;
            }
        }

        // Allows user to check out and send to list of orders
        void sendOrder(int orderNum, int totalPrice, ShoppingCart *cartContent) {
            orderID = orderNum;
            total = totalPrice;
            orderList = cartContent->returnShoppingList();
        }
};

// Prints Menu
int menu()
{
    int choice;

    cout << "Menu" << endl;
    cout << "\n1 — View Products";
    cout << "\n2 - View Shopping Cart";
    cout << "\n3 - View Orders";
    cout << "\n4 - Exit" << endl;
        
    cout << "\nType the number to where you want to go: ";
    cin >> choice;

    system("clear");
    return choice;
}

// Takes user input to put itme to cart
void newCartItem(Product products, ShoppingCart* cart)
{
    char choice;
    bool exitChoice;
    string itemID;
    int productIndex;
    int amount;

    do
    {
        cout << "\nIs there anything you like? [Y/N]: ";
        cin >> choice;
    } while (toupper(choice) != 'Y' && toupper(choice) != 'N');

    if (toupper(choice) == 'N')
    {
        return;
    }

    do {
        cout << "\nType the Product ID of the product you want: ";
        cin >> itemID;

        productIndex = products.checkList(itemID);

        if (productIndex == -1)
        {
            cout << "\nProduct ID not found, Try Again!" << endl;
            return;
        }

        do {
            cout << "\nHow many? ";
            cin >> amount;

            if (amount < 1)
            {
                cout << "\nAmount should be more than 0! Try again." << endl;
            }
        } while (amount < 1);

        cart->addToCart(productIndex, amount);

        do
        {
            cout << "Do you want to add another product? [Y/N]: ";
            cin >> choice;
        } while (toupper(choice) != 'Y' && toupper(choice) != 'N');

        if (toupper(choice) == 'Y')
        {
            exitChoice = true;
        }
        else
        {
            exitChoice = false;
        }
    } while (exitChoice);
}

// Orders the list of products in the shopping cart
void checkout(ShoppingCart* cart, Order* orders, int *orderNum)
{
    char choice;
    float totalPrice;
    do
    {
        cout << "\nDo you want to check out? [Y/N]: ";
        cin >> choice;
    } while (toupper(choice) != 'Y' && toupper(choice) != 'N');

    if (toupper(choice) == 'N')
    {
        return;
    }

    cout << "\nThese are the products that will be checked out, along with the total. Thank you!" << endl;

    cart->display();

    totalPrice = cart->computeTotal();

    cout << "\nTotal: " << totalPrice << endl;

    orders[*orderNum].sendOrder(*orderNum + 1, totalPrice, cart);

    cart->clearCart();

    *orderNum += 1;
}

int main(void)
{
    system("clear");
    Product products;
    ShoppingCart cart;
    Order customerOrders[MAXORDERS];
    int numOfOrders = 0;
    char choice;
    bool continueProg = true;

    while (continueProg)
    {
        cout << endl;
        switch(menu())
        {
            case 1: // View Products
                cout << "\nHere are the products available: " << endl;;
                products.display();

                if (numOfOrders < MAXORDERS) {
                    newCartItem(products, &cart);
                }
                else {
                    cout << "\nYou've reached the maximum amount of orders! Please restart the program." << endl;
                }
                
                cout << "\nType any key and enter to continue: ";
                cin >> choice;
                system("clear");
                break;

            case 2: // View Shopping Cart
                if (cart.returnCartSize() > 0) {
                    cout << "\nHere is your cart: " << endl;
                    cart.display();
                    checkout(&cart, customerOrders, &numOfOrders);
                }
                else {
                    cout << "There are no items in your cart! Add items by checking the list of products." << endl;
                }
                
                cout << "\nType any key and enter to continue: ";
                cin >> choice;
                system("clear");
                break;

            case 3: // View Orders
                if (numOfOrders > 0) {
                    cout << "\nHere is your order history: ";
                    for (int i = 0; i < numOfOrders; i++)
                    {
                        customerOrders[i].displayOrder();
                    }
                }
                else {
                    cout << "You have not ordered anything!" << endl;
                }
                
                cout << "\nType any key and enter to continue: ";
                cin >> choice;
                system("clear");
                break;

            case 4: // Exit
                do {
                cout << "\nAre you sure you want to exit? [Y/N]: ";
                cin >> choice;

                if (toupper(choice) == 'Y'){
                    continueProg = false;
                }
                } while (toupper(choice) != 'Y' && toupper(choice) != 'N');
                system("clear");
                break;
            
            default:
                cout << "\nInvalid Input! Please try again!" << endl;
        }
    }
    
    return 0;
}