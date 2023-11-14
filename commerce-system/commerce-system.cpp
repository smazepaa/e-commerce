#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Product {

    int productId;
    string name;
    double price;
    int quantityInStock;

public:
    Product(const int id, const string name, const double price, const int quantity)
        : productId(id), name(name), price(price), quantityInStock(quantity){}

    virtual ~Product() {}  // Add a virtual destructor

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

    string trim(const string& str)
    {
        size_t first = str.find_first_not_of(' ');
        if (string::npos == first)
        {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

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
                trim(word);
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

    ConfigReader reader;
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
                delete* it;  // Delete the product
                productList.erase(it);  // Remove the pointer from the vector
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void viewProducts() const {
        for (const auto& product : productList) {
            cout << "ID: " << product->getId() << endl;
            cout << "Name: " << product->getName() << endl;
            cout << "Price: " << product->getPrice() << endl;
            cout << "In stock: " << product->getQuantity() << endl;
            cout << "Additional attributes:" << endl;
            
            Electronics* electronics = dynamic_cast<Electronics*>(product);
            if (electronics != nullptr) {
                cout << "Brand: " << electronics->getBrand() << endl;
                cout << "Model: " << electronics->getModel() << endl;
                cout << "Power Consumption: " << electronics->getConsumption() << endl;
            }

            Books* book = dynamic_cast<Books*>(product);
            if (book != nullptr) {
                cout << "Author: " << book->getAuthor() << endl;
                cout << "Genre: " << book->getGenre() << endl;
                cout << "ISBN: " << book->getISBN() << endl;
            }

            // Handle attributes specific to Clothing
            Clothing* clothing = dynamic_cast<Clothing*>(product);
            if (clothing != nullptr) {
                cout << "Size: " << clothing->getSize() << endl;
                cout << "Color: " << clothing->getColor() << endl;
                cout << "Material: " << clothing->getMaterial() << endl;
            }
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
        : orderID(id), customer(customer), totalCost(0.0), orderStatus("Pending") {}

    void addProduct(Product* product, int quantity) {
        bool found = false;
        for (auto& item : products) {
            if (item.first == product) {
                // The product already exists in the map, so increment its quantity
                item.second += quantity;
                found = true;
                break;
            }
        }

        if (!found) {
            // The product does not exist in the map, so add it
            products[product] = quantity;
        }

        // Update the total cost
        totalCost += product->getPrice() * quantity;
    }

    double calculateTotalCost() const {
        return this->totalCost;
    }

    void changeOrderStatus(const string newStatus) {
        this->orderStatus = newStatus;
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
                int currentQuantity = product->getQuantity();
                if (currentQuantity >= quantity) {
                    product->updateQuantity(currentQuantity - quantity);
                    return;
                }
                else {
                    cout << "Not enough stock available." << endl;
                    return;
                }
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


int main()
{
    /*ProductCatalog catalog;

    vector<Product*> prods = catalog.getProducts();

    Order order1(1, "Customer 1");
    order1.addProduct(prods[0], 2);
    order1.addProduct(prods[1], 1);
    order1.addProduct(prods[0], 1);

    cout << "Total cost: " << order1.calculateTotalCost() << endl;*/

    return 0;
}
