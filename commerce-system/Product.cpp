#include "Product.h"
#include <string>
#include <iostream>

using namespace std;

Product::Product(const int& id, const string& name, const double& price, const int& quantity)
    : productId(id), name(name), price(price), quantityInStock(quantity) {}

Product::~Product() {}

void Product::displayDetails() const {
    cout << "ID: " << this->productId << endl;
    cout << "Name: " << this->name << endl;
    cout << "Price: " << this->price << endl;
    cout << "In stock: " << this->quantityInStock << endl;
}

int Product::getId() const {
    return this->productId;
}

string Product::getName() const {
    return this->name;
}

double Product::getPrice() const {
    return this->price;
}

int Product::getQuantity() const {
    return this->quantityInStock;
}

void Product::updateName(const string& newName) {
    this->name = newName;
}

void Product::updatePrice(const double newPrice) {
    this->price = newPrice;
}

void Product::updateQuantity(const int newQuantity) {
    this->quantityInStock = newQuantity;
}

// Copy constructor
Product::Product(const Product& other)
    : productId(other.productId), name(other.name),
    price(other.price), quantityInStock(other.quantityInStock) {}

// Move constructor
Product::Product(Product&& other) noexcept
    : productId(other.productId), name(move(other.name)),
    price(move(other.price)), quantityInStock(move(other.quantityInStock)) {

    other.productId = 0;
    other.name = "";
    other.price = 0;
    other.quantityInStock = 0;
}
