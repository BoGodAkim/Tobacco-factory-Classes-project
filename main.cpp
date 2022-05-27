#include <bits/stdc++.h>

using namespace std;

#include "classes.hpp"

TobaccoFactory::TobaccoFactory()
{
    cout << "Enter the name of the factory: ";
    getline(cin, name);
    cout << "Enter the address of the factory: ";
    getline(cin, address);
    cout << "Enter the phone number of the factory: ";
    getline(cin, phone);
    cout << "Enter the email of the factory: ";
    getline(cin, email);
    cout << "Enter the website of the factory: ";
    getline(cin, website);
    cout << endl;
}

void TobaccoFactory::enter_menu()
{
    int choice;
    string value;
    while (true)
    {
        cout << "1. Add a product" << endl;
        cout << "2. Add a client" << endl;
        cout << "3. Add a material" << endl;
        cout << "4. Add a supplier" << endl;
        cout << "5. Update product price" << endl;
        cout << "6. Update material price" << endl;
        cout << "7. Make an order" << endl;
        cout << "8. Make a delivery" << endl;
        cout << "9. Print products" << endl;
        cout << "10. Print clients" << endl;
        cout << "11. Print materials" << endl;
        cout << "12. Print suppliers" << endl;
        cout << "13. Print factory info" << endl;
        cout << "14. Exit" << endl;
        cout << "Enter your choice: ";
        getline(cin, value);
        choice = stoi(value);
        cout << endl;
        switch (choice)
        {
        case 1:
            add_product();
            break;
        case 2:
            add_client();
            break;
        case 3:
            add_material();
            break;
        case 4:
            add_supplier();
            break;
        case 5:
            update_product_price();
            break;
        case 6:
            update_material_price();
            break;
        case 7:
            make_order();
            break;
        case 8:
            make_delivery();
            break;
        case 9:
            print_products();
            break;
        case 10:
            print_clients();
            break;
        case 11:
            print_materials();
            break;
        case 12:
            print_suppliers();
            break;
        case 13:
            print_factory_info();
            break;
        case 14:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
        cout << endl
             << endl;
    }
}

void TobaccoFactory::add_product()
{
    string value;
    string name;
    string description;
    int price;
    cout << "Enter the name of the product: ";
    getline(cin, name);
    cout << "Enter description of the product: ";
    getline(cin, description);
    cout << "Enter the price of the product: ";
    getline(cin, value);
    price = stof(value);
    products.push_back(new Product(name, description, price, 0));
    this->print_materials();
    int choice = -1;
    while (choice != 0)
    {
        Material *material = NULL;
        cout << "1. Choose Material" << endl
             << "2. Add Material" << endl;
        cout << "Enter your choice: ";
        getline(cin, value);
        choice = stoi(value);
        if (choice == 1)
        {
            material = this->choose_material();
            cout << "Enter the quantity of the material: ";
            getline(cin, value);
            int quantity = stoi(value);
            this->products.back()->add_material(material, quantity);
            cout << endl;
        }
        else if (choice == 2)
        {
            this->add_material();
            material = this->materials.back();
            cout << "Enter the quantity of the material: ";
            getline(cin, value);
            int quantity = stoi(value);
            this->products.back()->add_material(material, quantity);
            cout << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    cout << "Product added!" << endl
         << endl;
}

void TobaccoFactory::add_client()
{
    string name;
    string address;
    string phone;
    string email;
    cout << "Enter the name of the client: ";
    getline(cin, name);
    cout << "Enter the address of the client: ";
    getline(cin, address);
    cout << "Enter the phone number of the client: ";
    getline(cin, phone);
    cout << "Enter the email of the client: ";
    getline(cin, email);
    this->clients.push_back(new Client(name, address, phone, email));
    cout << "Client added!" << endl
         << endl;
}

void TobaccoFactory::add_material()
{
    string value;
    string name;
    string description;
    int price;
    cout << "Enter the name of the material: ";
    getline(cin, name);
    cout << "Enter description of the material: ";
    getline(cin, description);
    cout << "Enter the price of the material: ";
    getline(cin, value);
    price = stof(value);
    int choice = 0;
    Supplier *supplier = NULL;
    while (choice != 1 && choice != 2)
    {
        cout << "1. Choose Supplier" << endl
             << "2. Add Supplier" << endl;
        cout << "Enter your choice: ";
        getline(cin, value);
        choice = stoi(value);
        if (choice == 1)
        {
            supplier = this->choose_supplier();
        }
        else if (choice == 2)
        {
            this->add_supplier();
            supplier = this->suppliers.back();
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    this->materials.push_back(new Material(name, description, price, 0, supplier));
    cout << "Material added!" << endl
         << endl;
}

void TobaccoFactory::add_supplier()
{
    string name;
    string address;
    string phone;
    string email;
    cout << "Enter the name of the supplier: ";
    getline(cin, name);
    cout << "Enter the address of the supplier: ";
    getline(cin, address);
    cout << "Enter the phone number of the supplier: ";
    getline(cin, phone);
    cout << "Enter the email of the supplier: ";
    getline(cin, email);
    this->suppliers.push_back(new Supplier(name, address, phone, email));
    cout << "Supplier added!" << endl
         << endl;
}

void TobaccoFactory::update_product_price()
{
    Product *product = this->choose_product();
    product->update_price();
}

void TobaccoFactory::update_material_price()
{
    Material *material = this->choose_material();
    material->update_price();
}

void TobaccoFactory::make_order()
{
    Client *client = this->choose_client();
    client->update_cart();
}

void TobaccoFactory::make_delivery()
{
    Client *client = this->choose_client();
    client->delete_cart();
}

void TobaccoFactory::print_products()
{
    cout << "Products:" << endl;
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        (*it)->print_product();
    }
}

void TobaccoFactory::print_clients()
{
    cout << "Clients:" << endl;
    for (auto it = this->clients.begin(); it != this->clients.end(); it++)
    {
        (*it)->print_client();
    }
}

void TobaccoFactory::print_materials()
{
    cout << "Materials:" << endl;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        (*it)->print_material();
    }
}

void TobaccoFactory::print_suppliers()
{
    cout << "Suppliers:" << endl;
    for (auto it = this->suppliers.begin(); it != this->suppliers.end(); it++)
    {
        (*it)->print_supplier();
    }
}

Product *TobaccoFactory::choose_product()
{
    cout << "Choose the product: " << endl;
    this->print_products();
    string value;
    int index = -1;
    while (index < 1 || index > this->products.size())
    {
        cout << "Enter the index of the product: ";
        getline(cin, value);
        index = stoi(value);
        if (index < 0 || index >= this->products.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    return this->products[index - 1];
}

Material *TobaccoFactory::choose_material()
{
    cout << "Choose the material: " << endl;
    this->print_materials();
    string value;
    int index = -1;
    while (index < 1 || index > this->materials.size())
    {
        cout << "Enter the index of the material: ";
        getline(cin, value);
        index = stoi(value);
        if (index < 0 || index >= this->materials.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    return this->materials[index - 1];
}

Supplier *TobaccoFactory::choose_supplier()
{
    cout << "Choose the supplier: " << endl;
    this->print_suppliers();
    string value;
    int index = -1;
    while (index < 1 || index > this->suppliers.size())
    {
        cout << "Enter the index of the supplier: ";
        getline(cin, value);
        index = stoi(value);
        if (index < 0 || index >= this->suppliers.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    return this->suppliers[index - 1];
}

Client *TobaccoFactory::choose_client()
{
    cout << "Choose the client: " << endl;
    this->print_clients();
    string value;
    int index = -1;
    while (index < 1 || index > this->clients.size())
    {
        cout << "Enter the index of the client: ";
        getline(cin, value);
        index = stoi(value);
        if (index < 0 || index >= this->clients.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    return this->clients[index - 1];
}

Product::Product()
{
    this->quantity = 0;
    this->price = 0;
}

Product::Product(const string name, const string description, const float price, const int quantity)
{
    this->name = name;
    this->description = description;
    this->price = price;
    this->quantity = quantity;
}

void Product::add_material(Material *material, int quantity)
{
    this->materials[material] += quantity;
    this->calculate_price_materials();
}

void Product::remove_material(Material *material, int quantity)
{
    if (this->materials[material] < quantity)
    {
        cout << "Not enough materials!" << endl;
        return;
    }
    this->materials[material] -= quantity;
    this->calculate_price_materials();
}

void Product::update_price()
{
    this->calculate_price_materials();
    float new_price = -1;
    string value;
    while (new_price < price_materials)
    {
        cout << "Enter the new price: ";
        getline(cin, value);
        new_price = stof(value);
        if (new_price < price_materials)
        {
            cout << "Invalid price!" << endl;
        }
    }
}

void Product::calculate_price_materials()
{
    this->price_materials = 0;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        this->price_materials += it->first->get_price() * it->second;
    }
}

void Product::print_product()
{
    cout << "Name: " << this->name << endl
         << "Description: " << this->description << endl
         << "Price: " << this->price << endl
         << "Quantity: " << this->quantity << endl
         << "Materials: " << endl;
    this->print_materials();
    cout << "Price materials: " << this->price_materials << endl
         << endl;
}

void Product::print_materials()
{
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        cout << it->first->get_name() << ": " << it->second << "(" << it->second * it->first->get_price() << "$)" << endl;
    }
}

Client::Client()
{
}

Client::Client(const string name, const string address, const string phone, const string email)
{
    this->name = name;
    this->address = address;
    this->phone = phone;
    this->email = email;
}

void Client::add_product_to_cart(Product *product, int quantity)
{
    this->cart[product] += quantity;
}

void Client::remove_product_from_cart(Product *product, int quantity)
{
    if (this->cart[product] < quantity)
    {
        cout << "Not enough products in the cart!" << endl;
        return;
    }
    this->cart[product] -= quantity;
}

void Client::print_client()
{
    cout << "Name: " << this->name << endl
         << "Address: " << this->address << endl
         << "Phone: " << this->phone << endl
         << "Email: " << this->email << endl
         << "Cart: " << endl;
    this->print_cart();
    cout << endl;
}

void Client::print_cart()
{
    for (auto it = this->cart.begin(); it != this->cart.end(); it++)
    {
        cout << it->first->get_name() << ": " << it->second << endl;
    }
}