#include "classes.hpp"

Material::Material()
{
    this->price = 0;
    this->quantity = 0;
}

Material::Material(const string name, const string description, const float price, const int quantity, Supplier *supplier)
{
    this->name = name;
    this->description = description;
    this->price = price;
    this->quantity = quantity;
    this->supplier = supplier;
}

void Material::add_product(Product *product)
{
    this->products.push_back(product);
}

void Material::delete_product(Product *product)
{
    this->products.erase(remove(this->products.begin(), this->products.end(), product), this->products.end());
}

void Material::update_price()
{
    string value;
    float new_price = -1;
    while (new_price < 0)
    {
        cout << "Enter the new price: ";
        getline(cin, value);
        new_price = stof(value);
        if (new_price < 0)
        {
            cout << "Invalid price!" << endl;
        }
    }
    this->price = new_price;
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        (*it)->calculate_price_materials();
    }
}

void Material::print_material()
{
    cout << "Name: " << this->name << endl
         << "Description: " << this->description << endl
         << "Price: " << this->price << endl
         << "Quantity: " << this->quantity << endl
         << "Supplier: " << this->supplier->get_name() << endl
         << "Products: " << this->products.size() << endl;
    this->print_products();
    cout << endl;
}

void Material::print_products()
{
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        cout << (*it)->get_name() << endl;
    }
}

float Material::get_price()
{
    return this->price;
}

string Material::get_name()
{
    return this->name;
}

void Material::save_to_file(ofstream &file, int materialID, map<Supplier *, int> *supplierID)
{
    file << materialID << "," << (*supplierID)[this->supplier] << "," << this->name << "," << this->description << "," << this->price << "," << this->quantity << endl;
}

void Material::load_from_file(istringstream &iss, map<int, Material *> *materialID, map<int, Supplier *> *supplierID)
{
    string value;
    getline(iss, value, ',');
    (*materialID)[stoi(value)] = this;
    getline(iss, value, ',');
    this->supplier = (*supplierID)[stoi(value)];
    this->supplier->add_material(this);
    getline(iss, this->name, ',');
    getline(iss, this->description, ',');
    getline(iss, value, ',');
    this->price = stof(value);
    getline(iss, value, ',');
    this->quantity = stoi(value);
}
