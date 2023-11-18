#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Product {

    int productId;
    string name;
    double price;
    int quantityInStock;

public:
    Product(const int id, const string name, const double price, const int quantity)
        : productId(id), name(name), price(price), quantityInStock(quantity){}

    virtual ~Product() {}

    virtual void displayDetails() const {
        cout << "ID: " << this->productId << endl;
        cout << "Name: " << this->name << endl;
        cout << "Price: " << this->price << endl;
        cout << "In stock: " << this->quantityInStock << endl;
        cout << "Additional attributes:" << endl;
    }

    int getId() const {
        return this->productId;
    }

    string getName() const {
        return this->name;
    }

    double getPrice() const {
        return this->price;
    }

    int getQuantity() const {
        return this->quantityInStock;
    }

    void updateName(const string newName) {
        this->name = newName;
    }

    void updatePrice(const double newPrice) {
        this->price = newPrice;
    }

    void updateQuantity(const int newQuantity) {
        this->quantityInStock = newQuantity;
    }

    // Copy constructor
    Product(const Product& other)
        : productId(other.productId), name(other.name), 
        price(other.price), quantityInStock(other.quantityInStock) {}

    // Move constructor
    Product(Product&& other) noexcept
        : productId(move(other.productId)), name(move(other.name)),
        price(move(other.price)), quantityInStock(move(other.quantityInStock)) {

        other.productId = 0;
        other.name = "";
        other.price = 0;
        other.quantityInStock = 0;
    }
};

class Electronics : public Product {
    string brand;
    string model;
    string powerConsumption;

public:

    Electronics(const int id, const string name, const double price, const int quantity,
        const string brand, const string model, const string powerConsumption)
        : Product(id, name, price, quantity), brand(brand), model(model), 
        powerConsumption(powerConsumption) {}

    void displayDetails() const override {
        Product::displayDetails(); // call base class's function
        cout << "Brand: " << this->brand << endl;
        cout << "Model: " << this->model << endl;
        cout << "Power Consumption: " << this->powerConsumption << endl;
    }

    string getBrand() const {
        return this->brand;
    }

    string getModel() const {
        return this->model;
    }

    string getConsumption() const {
        return this->powerConsumption;
    }

    void updateBrand(const string newBrand) {
        this->brand = newBrand;
    }

    void updateModel(const string newModel) {
        this->model = newModel;
    }

    void updateConsumption(const string newConsumption) {
        this->powerConsumption = newConsumption;
    }

    // Copy constructor
    Electronics(const Electronics& other)
        : Product(other), brand(other.brand), model(other.model), 
        powerConsumption(other.powerConsumption) {}

    // Move constructor
    Electronics(Electronics&& other) noexcept
        : Product(move(other)), brand(move(other.brand)), 
        model(move(other.model)), powerConsumption(move(other.powerConsumption)) {
        other.brand = "";
        other.model = "";
        other.powerConsumption = "";
    }
};

class Books : public Product {
    string author;
    string genre;
    string isbn;

public:

    Books(const int id, const string name, const double price, const int quantity,
        const string author, const string genre, const string isbn)
        : Product(id, name, price, quantity), author(author), genre(genre),
        isbn(isbn) {}

    void displayDetails() const override {
        Product::displayDetails(); // call base class's function
        cout << "Author: " << this->author << endl;
        cout << "Genre: " << this->genre << endl;
        cout << "ISBN: " << this->isbn << endl;
    }

    string getAuthor() const {
        return this->author;
    }

    string getGenre() const {
        return this->genre;
    }

    string getISBN() const {
        return this->isbn;
    }

    void updateAuthor(const string newAuthor) {
        this->author = newAuthor;
    }

    void updateGenre(const string newGenre) {
        this->genre = newGenre;
    }

    void updateISBN(const string newISBN) {
        this->isbn = newISBN;
    }

    // Copy constructor
    Books(const Books& other)
        : Product(other), author(other.author), genre(other.genre),
        isbn(other.isbn) {}

    // Move constructor
    Books(Books&& other) noexcept
        : Product(move(other)), author(move(other.author)),
        genre(move(other.genre)), isbn(move(other.isbn)) {
        other.author = "";
        other.genre = "";
        other.isbn = "";
    }
};

class Clothing : public Product {
    string size;
    string color;
    string material;

public:

    Clothing(const int id, const string name, const double price, const int quantity,
        const string size, const string color, const string material)
        : Product(id, name, price, quantity), size(size), color(color),
        material(material) {}

    void displayDetails() const override {
        Product::displayDetails(); // call base class's function
        cout << "Size: " << this->size << endl;
        cout << "Color: " << this->color << endl;
        cout << "Material: " << this->material << endl;
    }

    string getSize() const {
        return this->size;
    }

    string getColor() const {
        return this->color;
    }

    string getMaterial() const {
        return this->material;
    }

    void updateSize(const string newSize) {
        this->size = newSize;
    }

    void updateColor(const string newColor) {
        this->color = newColor;
    }

    void updateMaterial(const string newMaterial) {
        this->material = newMaterial;
    }

    // Copy constructor
    Clothing(const Clothing& other)
        : Product(other), size(other.size), color(other.color),
        material(other.material) {}

    // Move constructor
    Clothing(Clothing&& other) noexcept
        : Product(move(other)), size(move(other.size)),
        color(move(other.color)), material(move(other.material)) {
        other.size = "";
        other.color = "";
        other.material = "";
    }
};

class ConfigReader {

    string filename = "config-input.txt";

public:

    vector<Product*> readConfig() {

        vector<Product*> products;
        ifstream file(filename);
        string line;
        int id = 1;

        if (!file.is_open()) {
            cout << "Unable to open file" << '\n';
            return products;
        }

        while (getline(file, line)) {

            istringstream iss(line);
            vector<string> words;
            string word;
            vector<string> additional;

            while (getline(iss, word, ',')) {

                word.erase(0, word.find_first_not_of(' '));
                words.push_back(word);
            }

            string type = words[0];
            string name = words[1];
            double price = stod(words[2]);
            int quantity = stoi(words[3]);

            additional.assign(words.begin() + 4, words.end());

            if (type == "Electronics") {
                string brand = additional[0];
                string model = additional[1];
                string consumption = additional[2];

                Electronics* electronic = new Electronics(id, name,
                    price, quantity, brand, model, consumption);
                products.push_back(electronic);
                id++;
            }

            else if (type == "Books") {
                string author = additional[0];
                string genre = additional[1];
                string isbn = additional[2];

                Books* book = new Books(id, name, price, quantity, author, genre, isbn);
                products.push_back(book);
                id++;
            }

            else if (type == "Clothing") {
                string size = additional[0];
                string color = additional[1];
                string material = additional[2];

                Clothing* cloth = new Clothing(id, name,
                    price, quantity, size, color, material);
                products.push_back(cloth);
                id++;
            }

            else {
                cout << "Invalid product type";
            }

        }
        file.close();
        return products;
    }
};

class ProductCatalog {

    vector<Product*> productList;

public:

    ProductCatalog(vector<Product*>& products) : productList(products) {}

    vector<Product*> getProducts() const {
        return this->productList;
    }

    void addProduct(Product* product) {
        productList.push_back(product);
    }

    void updateProduct(int id, string attribute, string newValue) {
        for (auto& product : productList) {
            if (product->getId() == id) {
                if (attribute == "name") {
                    product->updateName(newValue);
                }
                else if (attribute == "price") {
                    double newPrice = stod(newValue);
                    product->updatePrice(newPrice);
                }
                else if (attribute == "quantity") {
                    int newQuantity = stoi(newValue);
                    product->updateQuantity(newQuantity);
                }
                else {
                    // Handle attributes specific to Electronics
                    Electronics* electronics = dynamic_cast<Electronics*>(product);
                    if (electronics != nullptr) {
                        if (attribute == "brand") {
                            electronics->updateBrand(newValue);
                        }
                        else if (attribute == "model") {
                            electronics->updateModel(newValue);
                        }
                        else if (attribute == "consumption") {
                            electronics->updateConsumption(newValue);
                        }
                        else {
                            cout << "Invalid attribute for Electronics" << endl;
                        }
                    }

                    // Handle attributes specific to Books
                    Books* book = dynamic_cast<Books*>(product);
                    if (book != nullptr) {
                        if (attribute == "author") {
                            book->updateAuthor(newValue);
                        }
                        else if (attribute == "genre") {
                            book->updateGenre(newValue);
                        }
                        else if (attribute == "ISBN") {
                            book->updateISBN(newValue);
                        }
                        else {
                            cout << "Invalid attribute for Books" << endl;
                        }
                    }

                    // Handle attributes specific to Clothing
                    Clothing* clothing = dynamic_cast<Clothing*>(product);
                    if (clothing != nullptr) {
                        if (attribute == "size") {
                            clothing->updateSize(newValue);
                        }
                        else if (attribute == "color") {
                            clothing->updateColor(newValue);
                        }
                        else if (attribute == "material") {
                            clothing->updateMaterial(newValue);
                        }
                        else {
                            cout << "Invalid attribute for Clothing" << endl;
                        }
                    }
                }
                return;
            }
        }
        cout << "Product not found." << '\n';
    }

    void removeProduct(int id) {
        for (auto it = productList.begin(); it != productList.end(); ++it) {
            if ((*it)->getId() == id) {
                delete* it;
                productList.erase(it);
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void viewProducts() const {
        for (const auto& product : productList) {
            product->displayDetails();
            cout << endl;
        }
    }
};

class Order {
    int orderID;
    string customer;
    map<Product*, int> products;
    double totalCost;
    string orderStatus;

public:
    Order(const int id, const string customer)
        : orderID(id), customer(customer), totalCost(0.0), orderStatus("Created") {}

    void addProduct(Product* product, int quantity) {
        bool found = false;
        for (auto& item : products) {
            if (item.first == product) {
                item.second += quantity;
                found = true;
                break;
            }
        }

        if (!found) {
            products[product] = quantity;
        }
        totalCost += product->getPrice() * quantity;
    }

    double calculateTotalCost() const {
        return this->totalCost;
    }

    void changeOrderStatus(const string newStatus) {
        this->orderStatus = newStatus;
    }

    void viewOrder() const {

        cout << "Order no. " << this->orderID << endl << "Customer: " << this->customer << endl;

        for (auto& item : products) {
            cout << item.first->getId() << " - " << item.first->getName() << endl
                << "qty: " << item.second << " x " << item.first->getPrice() << endl;
        }

        cout << "Total: " << this->totalCost << endl << endl;
    }
};

class Inventory {

    int lowStockThreshold = 5;
    vector<Product*> products;

public:

    Inventory(vector<Product*>& productList): products(productList){}

    void addQuantity(int id, int quantity) {
        for (Product* product : products) {
            if (product->getId() == id) {
                product->updateQuantity(product->getQuantity() + quantity);
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void removeQuantity(int id, int quantity) {
        for (Product* product : products) {
            if (product->getId() == id) {
                product->updateQuantity(product->getQuantity() - quantity);
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void notifyLowStock() const {
        cout << "Products with low stock:" << endl;
        for (const Product* product : products) {
            if (product->getQuantity() < lowStockThreshold) {
                cout << "Product ID: " << product->getId() << ", Name: " << product->getName()
                    << ", Current Stock: " << product->getQuantity() << endl;
            }
        }
    }

    void getProductsToRestock() const {
        cout << "Products that need restock:" << endl;
        for (const Product* product : products) {
            if (product->getQuantity() == 0) {
                cout << "Product ID: " << product->getId() << 
                    ", Name: " << product->getName() << endl;
            }
        }
    }
};

class InputConfig {
    ConfigReader reader;
    vector<Product*> products;
    vector<Order> orders;
    map<Product*, int> cart;
    int orderId = 1234;

    void showCommands() {
        cout << "1. show all" << endl
            << "2. show <filtered> - based on your parameters (eg show Electronics)" << endl
            << "3. add to cart - add product by id" << endl
            << "4. checkout - proceed to creating order" << endl
            << "5. history - shows previous orders" << endl << endl;
    }

    void showFiltered(vector<string>& inputParams) {

        vector<Product*> filtered;
        string type = inputParams[1];
        vector<string> filterParams;
        filterParams.assign(inputParams.begin() + 2, inputParams.end());
        for (const auto& product : products) {
            if (type == "Electronics") {
                Electronics* electronics = dynamic_cast<Electronics*>(product);

                if (electronics != nullptr) {
                    if (filterParams.size() == 0) {
                        filtered.push_back(product);
                    }
                    else {
                        for (const auto& attribute : filterParams) {
                            if (electronics->getName() == attribute ||
                                electronics->getBrand() == attribute ||
                                electronics->getModel() == attribute ||
                                electronics->getConsumption() == attribute) {
                                filtered.push_back(product);
                                break;
                            }
                        }
                    }
                }
            }

            else if (type == "Books") {
                Books* books = dynamic_cast<Books*>(product);

                if (books != nullptr) {
                    if (filterParams.size() == 0) {
                        filtered.push_back(product);
                    }
                    else {
                        for (const auto& attribute : filterParams) {
                            if (books->getName() == attribute ||
                                books->getAuthor() == attribute ||
                                books->getGenre() == attribute ||
                                books->getISBN() == attribute) {
                                filtered.push_back(product);
                                break;
                            }
                        }
                    }
                    
                }
            }
            else if (type == "Clothing") {                
                Clothing* clothing = dynamic_cast<Clothing*>(product);

                if (clothing != nullptr) {
                    if (filterParams.size() == 0) {
                        filtered.push_back(product);
                    }
                    else {
                        for (const auto& attribute : filterParams) {
                            if (clothing->getName() == attribute ||
                                clothing->getMaterial() == attribute ||
                                clothing->getColor() == attribute ||
                                clothing->getSize() == attribute) {
                                filtered.push_back(product);
                                break;
                            }
                        }
                    }
                    
                }
            }
            else {
                cout << "Invalid product type." << endl;
            }
        }

        if (filtered.size() == 0) {
            cout << "There is no product corresponding to your parameters."
                << endl;
            return;
        }
        cout << "The products that meet your parameters:" << endl;
        for (auto& product : filtered) {
            product->displayDetails();
            cout << endl;
        }
    }

    void addToCart() {
        string prod;
        cout << "Enter product ID and quantity: ";
        getline(cin, prod);

        if (prod == "") {
            cout << "Cannot enter empty input" << endl << endl;
            return;
        }

        istringstream iss(prod);
        string prodInfo;
        vector<string> toCart;
        while (iss >> prodInfo) {
            toCart.push_back(prodInfo);
        }
        
        if (toCart.size() != 2) {
            cout << "The command takes 2 parameters" << endl << endl;
            return;
        }

        int id = stoi(toCart[0]);
        int quantity = stoi(toCart[1]);

        bool prodExists = false;
        for (Product* product : products) {
            if (product->getId() == id) {
                if (product->getQuantity() >= quantity) {
                    cart[product] = quantity;
                    prodExists = true;
                    cout << "Product was added to cart" << endl << endl;
                    return;
                }
                else {
                    cout << "Not enough product in stock" << endl << endl;
                    return;
                }

            }
        }

        if (!prodExists) {
            cout << "There is no product with the given ID" << endl;
            return;
        }
    }

    void createOrder(Inventory& inventory) {
        string customer;

        cout << "Enter your name: ";
        getline(cin, customer);
        Order order1(orderId, customer);
        for (const auto& pair : cart) {
            order1.addProduct(pair.first, pair.second);
            inventory.removeQuantity(pair.first->getId(), pair.second);
        }

        cout << "Order created" << endl << "Order No. " << orderId << endl <<
            "Customer: " << customer <<
            endl << "Total: " << order1.calculateTotalCost() << endl << endl;
        orderId++;
        orders.push_back(order1);
        cart.clear();
    }

    void chechout(Inventory& inventory) {
        if (cart.size() == 0) {
            cout << "Your cart is empty" << endl << endl;
            return;
        }

        cout << "Your cart:" << endl;
        for (auto& item : cart) {
            cout << item.first->getName() << " "
                << item.second << " x " << item.first->getPrice() << endl;
        }

        string confirm;
        cout << endl << "Do you want to place an order?[y/n] ";
        getline(cin, confirm);

        if (confirm == "y") {
            createOrder(inventory);
        }
    }

public:
    InputConfig() {}

    void processInput() {

        products = reader.readConfig();
        Inventory inventory(products);
        ProductCatalog catalog(products);

        showCommands();
        while (true) {
            string inputline;
            
            cout << "> ";
            getline(cin, inputline);

            istringstream iss(inputline);
            string word;
            vector<string> inputParams;
            while (iss >> word) {
                inputParams.push_back(word);
            }

            if (inputParams.size() == 0) {
                cout << "Cannot enter empty input" << endl;
                continue;
            }

            string command = inputParams[0];
            vector<string> filters;

            if (command == "show") {

                if (inputParams.size() == 1) {
                    cout << "Cannot proceed with invalid input" << endl;
                    continue;
                }

                else if (inputParams[1] == "all") {
                    catalog.viewProducts();
                }
                else {
                    showFiltered(inputParams);
                }
            }
            else if (inputline == "add to cart") {
                addToCart();
            }
            else if (command == "checkout") {
                chechout(inventory);
            }
            else if (command == "history") {
                for (const Order order : orders) {
                    order.viewOrder();
                }
            }
            else if (command == "exit") {
                return;
            }
            else {
                cout << "Invalid command" << endl << endl;
            }
        }
    }

};


int main()
{
    InputConfig config;
    config.processInput();

    return 0;
}
