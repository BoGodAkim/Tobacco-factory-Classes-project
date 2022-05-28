#include "classes.hpp"

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

void Client::remove_product_from_cart()
{
    cout << "Choose the product: " << endl;
    this->print_cart();
    string value;
    int index = -1;
    while (index < 1 || index > this->cart.size())
    {
        cout << "Enter the index of the product: ";
        getline(cin, value);
        index = stoi(value);
        if (index < 0 || index >= this->cart.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    auto it = this->cart.begin();
    for (int i = 0; i < index - 1; i++)
    {
        it++;
    }
    int quantity = -1;
    while (quantity < 1 || quantity > it->second)
    {
        cout << "Enter the quantity: ";
        getline(cin, value);
        quantity = stoi(value);
        if (quantity < 1 || quantity > it->second)
        {
            cout << "Invalid quantity!" << endl;
        }
    }
    it->second -= quantity;
    if (it->second == 0)
    {
        this->cart.erase(it);
    }
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

void Client::delete_cart()
{
    this->cart.clear();
}

void Client::make_products()
{
    for (auto it = this->cart.begin(); it != this->cart.end(); it++)
    {
        int quantity = it->second - it->first->quantity;
        if (quantity > 0)
        {
            it->first->make(quantity);
        }
    }
}

void Client::deliver_order()
{
    for (auto it = this->cart.begin(); it != this->cart.end(); it++)
    {
        it->first->quantity -= it->second;
    }
    this->delete_cart();
}

float Client::calculate_total_price()
{
    float total_price = 0;
    for (auto it = this->cart.begin(); it != this->cart.end(); it++)
    {
        total_price += it->first->get_price() * it->second;
    }
    return total_price;
}

float Client::calculate_total_price_materials()
{
    float total_price_materials = 0;
    for (auto it = this->cart.begin(); it != this->cart.end(); it++)
    {
        total_price_materials += it->first->get_price_materials() * it->second;
    }
    return total_price_materials;
}

void Client::save_to_file(ofstream &file, int clientID)
{
    file << clientID << "," << this->name << "," << this->address << "," << this->phone << "," << this->email << endl;
}

void Client::load_from_file(istringstream &iss, map<int, Client *> *clientID)
{
    string value;
    getline(iss, value, ',');
    (*clientID)[stoi(value)] = this;
    getline(iss, this->name, ',');
    getline(iss, this->address, ',');
    getline(iss, this->phone, ',');
    getline(iss, this->email, ',');
}
