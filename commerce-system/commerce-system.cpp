#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

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

class ProductCatalog {

    vector<Product> productList;

public:

    vector<Product> getProducts() const {
        return this->productList;
    }

    void addProduct(const Product& product) {
        productList.push_back(product);
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

            string type = words[0]; // Electronics
            string name = words[1]; // Laptop
            double price = stod(words[2]); // 799.99
            int quantity = stoi(words[3]); // 10
            
            additional.assign(words.begin() + 4, words.end());

            // Print the 'additional' vector
            /*for (const auto& word : additional) {
                cout << word << '\n';
            }*/

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

int main()
{
    ConfigReader reader;
    vector<Product*> products = reader.readConfig();

    cout << "products list created" << endl;

    Product* product = products[0];  // Get the i-th product
    Electronics* electronics = dynamic_cast<Electronics*>(product);
    if (electronics != nullptr) {
        // The product is an Electronics, so you can use Electronics methods on it
        cout << "Brand: " << electronics->getBrand() << endl;
    }
    else {
        // The product is not an Electronics
        cout << "The product is not an Electronics object." << endl;
    }


    return 0;
}
