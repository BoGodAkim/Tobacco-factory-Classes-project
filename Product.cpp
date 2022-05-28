#include "classes.hpp"

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
    material->add_product(this);
    this->calculate_price_materials();
}

void Product::remove_material()
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
    auto it = this->materials.begin();
    for (int i = 0; i < index - 1; i++)
    {
        it++;
    }
    int quantity = -1;
    while (quantity < 0 || quantity > (*it).second)
    {
        cout << "Enter the quantity of the material: ";
        getline(cin, value);
        quantity = stoi(value);
        if (quantity < 0 || quantity > (*it).second)
        {
            cout << "Invalid quantity!" << endl;
        }
    }
    (*it).second -= quantity;
    if ((*it).second == 0)
    {
        (*it).first->delete_product(this);
        this->materials.erase(it);
    }
}

void Product::update_price()
{
    this->calculate_price_materials();
    float new_price = -1;
    string value;
    while (new_price < price_materials)
    {
        cout << "Enter the new price (price of materials " << price_materials << "): ";
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
    float temp_price_materials = 0;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        temp_price_materials += it->first->get_price() * it->second;
    }
    if (this->price_materials != 0) //TODO: rewrite
    {
        this->price = temp_price_materials * (this->price / this->price_materials);
    }
    this->price_materials = temp_price_materials;
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

void Product::make(int quantity)
{
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        int temp_quantity = it->second * quantity - it->first->quantity;
        if (temp_quantity > 0)
        {
            it->first->quantity += temp_quantity;
        }
        it->first->quantity -= it->second * quantity;
    }
    this->quantity += quantity;
}

string Product::get_name()
{
    return this->name;
}

float Product::get_price()
{
    return this->price;
}

float Product::get_price_materials()
{
    return this->price_materials;
}

void Product::save_to_file(ofstream &file, int productID, map<Material *, int> *materialID, ofstream &file_product_material)
{
    file << productID << "," << this->name << "," << this->description << "," << this->price << "," << this->price_materials << "," << this->quantity << endl;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        file_product_material << productID << "," << (*materialID)[it->first] << "," << it->second << endl;
    }
}

void Product::load_from_file(istringstream &iss, map<int, Product *> *productID)
{
    string value;
    getline(iss, value, ',');
    (*productID)[stoi(value)] = this;
    getline(iss, this->name, ',');
    getline(iss, this->description, ',');
    getline(iss, value, ',');
    this->price = stof(value);
    getline(iss, value, ',');
    this->price_materials = stof(value);
    getline(iss, value, ',');
    this->quantity = stoi(value);
}
