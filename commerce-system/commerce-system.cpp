#include <iostream>

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

    int getPrice() const {
        return this->price;
    }

    int getQuantity() const {
        return this->quantityInStock;
    }

    // Copy constructor
    Product(const Product& other)
        : productId(other.productId), name(other.name), 
        price(other.price), quantityInStock(other.quantityInStock) {}

    // Move constructor
    Product(Product&& other) //noexcept
        : productId(move(other.productId)), name(move(other.name)), 
        price(move(other.price)), quantityInStock(move(other.quantityInStock)) {

        other.productId = 0;
        other.name = "";
        other.price = 0;
        other.quantityInStock = 0;
};


int main()
{
    cout << "Hello World!\n";
}