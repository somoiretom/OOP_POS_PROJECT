#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <utility> // Include this for std::make_pair

using namespace std;

// Basic product structure
struct Product {
    string name;
    string category; // New member variable for category
    double price;
};

class POS {
private:
    vector<Product> products;
    vector<pair<size_t, int> > cart; // Corrected space between angle brackets

public:
    // Add a product to the product database
    void addProductToDatabase(const string& name, const string& category, double price) {
        products.push_back({ name, category, price });
    }

    // Get the list of products
    const vector<Product>& getProducts() const {
        return products;
    }

    // Display the list of products
    void displayProducts() {
        cout << "Product List:" << endl;
        string currentCategory;
        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].category != currentCategory) {
                currentCategory = products[i].category;
                cout << "----- " << currentCategory << " -----" << endl;
            }
            cout << i + 1 << ". " << products[i].name << " - Ksh." << fixed << setprecision(2) << products[i].price << endl;
        }
    }

    // Add a product to the cart using the product index and quantity
    void addToCart(size_t productIndex, int quantity) {
        if (productIndex > 0 && productIndex <= products.size()) {
            bool productExists = false;
            for (vector<pair<size_t, int> >::iterator it = cart.begin(); it != cart.end(); ++it) {
                if (it->first == productIndex - 1) {
                    it->second += quantity;
                    productExists = true;
                    break;
                }
            }

            if (!productExists) {
                cart.push_back(make_pair(productIndex - 1, quantity));
            }

            cout << quantity << " " << products[productIndex - 1].name << "(s) added to cart." << endl;
        }
        else {
            cout << "Invalid product index." << endl;
        }
    }

    // Calculate the total amount in the cart
    double calculateTotal() {
        double total = 0.0;
        for (size_t i = 0; i < cart.size(); ++i) {
            total += products[cart[i].first].price * cart[i].second; // Multiply by quantity
        }
        return total;
    }

    // Generate and print the receipt
    void generateReceipt() {
        cout << "\nReceipt:" << endl;
        cout << "---------------------------------" << endl;
        for (size_t i = 0; i < cart.size(); ++i) {
            cout << products[cart[i].first].name << " - Quantity: " << cart[i].second << " - Ksh." << fixed << setprecision(2) << products[cart[i].first].price * cart[i].second << endl;
        }
        cout << "---------------------------------" << endl;
        cout << "Total: Ksh." << fixed << setprecision(2) << calculateTotal() << endl;
        cout << "Thank you for shopping with Somoire Shop!" << endl;
    }
};

int main() {
    POS posTerminal;

    // Adding products to the database using the member function
    posTerminal.addProductToDatabase("White Tea", "BreakFast", 100.00);
    posTerminal.addProductToDatabase("Black Cofee", "BreakFast", 50.00);
    posTerminal.addProductToDatabase("Chai Andazi", "BreakFast", 60.00);
    posTerminal.addProductToDatabase("Muthokoi", "Lunch", 150.00);
    posTerminal.addProductToDatabase("Ugali Matumbo", "Lunch", 150.00);
    posTerminal.addProductToDatabase("Githeri", "Lunch", 100.00);
    posTerminal.addProductToDatabase("Chapati Beef", "Dinner", 150.00);
    posTerminal.addProductToDatabase("Mchele Beef", "Dinner", 150.00);
    posTerminal.addProductToDatabase("Ugali Beef", "Dinner", 150.00);
    posTerminal.addProductToDatabase("Fanta", "Drinks", 50.00);
     posTerminal.addProductToDatabase("Coca Cola", "Drinks", 50.00);
      posTerminal.addProductToDatabase("Krest", "Drinks", 50.00);
       posTerminal.addProductToDatabase("Sprite", "Drinks", 50.00);
    // Add more products with different categories...

    cout << "Welcome to Somoire Solutions Group Mall!" << endl;
    posTerminal.displayProducts();

    // User interaction loop
    while (true) {
        cout << "\nEnter the product index (or 0 to generate receipt, -1 to quit): ";
        int inputIndex;
        cin >> inputIndex;

        if (inputIndex == 0) {
            posTerminal.generateReceipt();
            break;
        }
        else if (inputIndex == -1) {
            cout << "Exiting the POS terminal." << endl;
            break;
        }
        else if (inputIndex > 0 && inputIndex <= posTerminal.getProducts().size()) {
            cout << "Enter the quantity: ";
            int inputQuantity;
            cin >> inputQuantity;
            posTerminal.addToCart(static_cast<size_t>(inputIndex), inputQuantity);
        }
        else {
            cout << "Invalid product index." << endl;
        }
    }

    return 0;
}