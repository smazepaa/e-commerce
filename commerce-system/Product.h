#pragma once

#include <string>
#include <iostream>

using namespace std;

class Product {
    int productId;
    string name;
    double price;
    int quantityInStock;

public:
    Product(const int& id, const string& name, const double& price, const int& quantity);
    virtual ~Product();
    virtual void displayDetails() const;
    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
    void updateName(const string& newName);
    void updatePrice(const double newPrice);
    void updateQuantity(const int newQuantity);
    Product(const Product& other);
    Product(Product&& other) noexcept;
};

