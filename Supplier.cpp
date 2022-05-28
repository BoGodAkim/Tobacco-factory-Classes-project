#include "classes.hpp"

Supplier::Supplier()
{
}

Supplier::Supplier(const string name, const string address, const string phone, const string email)
{
    this->name = name;
    this->address = address;
    this->phone = phone;
    this->email = email;
}

void Supplier::add_material(Material *material)
{
    this->materials.push_back(material);
}

void Supplier::delete_material(Material *material)
{
    this->materials.erase(remove(this->materials.begin(), this->materials.end(), material), this->materials.end());
}

void Supplier::print_supplier()
{
    cout << "Name: " << this->name << endl
         << "Address: " << this->address << endl
         << "Phone: " << this->phone << endl
         << "Email: " << this->email << endl
         << "Materials: " << this->materials.size() << endl;
    this->print_materials();
    cout << endl;
}

void Supplier::print_materials()
{
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        cout << (*it)->get_name() << endl;
    }
}

string Supplier::get_name()
{
    return this->name;
}

void Supplier::save_to_file(ofstream &file, int supplierID)
{
    file << supplierID << "," << this->name << "," << this->address << "," << this->phone << "," << this->email << endl;
}

void Supplier::load_from_file(istringstream &iss, map<int, Supplier *> *supplierID)
{
    string value;
    getline(iss, value, ',');
    (*supplierID)[stoi(value)] = this;
    getline(iss, this->name, ',');
    getline(iss, this->address, ',');
    getline(iss, this->phone, ',');
    getline(iss, this->email, ',');
}
