#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Product {

    int productId;
    string name;
    int price;
    int quantityInStock;

public:
    Product(const int id, const string name, const int price, const int quantity)
        : productId(id), name(name), price(price), quantityInStock(quantity){}

    int getId() const {
        return this->productId;
    }

    string getName() const {
        return this->name;
    }

    int getPrice() const {s
        return this->price;
    }

    int getQuantity() const {
        return this->quantityInStock;
    }

    void updateName(const string newName) {
        this->name = newName;
    }

    void updatePrice(const int newPrice) {
        this->price = newPrice;
    }

    void updateQuantity(const string newQuantity) {
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

    Electronics(const int id, const string name, const int price, const int quantity, 
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

    Books(const int id, const string name, const int price, const int quantity,
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

    Clothing(const int id, const string name, const int price, const int quantity,
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

};

int main()
{
    return 0;
}
