 #ifndef CLASSES_HPP
 #define CLASSES_HPP

#include <bits/stdc++.h>
using std::string;
using std::vector;
using std::map;

class Product;
class Material;
class Client;
class Supplier;
class Tobacco_Factory
{
private:
    string name;
    string address;
    string phone;
    string email;
    string website;
    vector<Product> products;
    vector<Client> clients;
    vector<Material> materials;
    vector<Supplier> suppliers;
    void add_product();
    void add_client();
    void add_material();
    void add_supplier();
    void update_product_price();
    void update_material_price();
    void make_order();
    void make_delivery();
    void print_products();
    void print_clients();
    void print_materials();
    void print_suppliers();
    void print_factory_info();
public:
    Tobacco_Factory();
    void enter_menu();
};

class Product
{
private:
    string name;
    string description;
    float price;
    int quantity;
    map<Material *, int> materials;
public:
    Product();
    Product(string name, string description, float price, int quantity);
    void add_material(Material *material, int quantity);
    void remove_material(Material *material, int quantity);
    void update_price();
    void update_quantity();
    void print_product();
};

class Client
{
private:
    string name;
    string address;
    string phone;
    string email;
    map<Product *, int> cart;
public:
    Client();
    Client(string name, string address, string phone, string email);
    void add_product_to_cart(Product *product, int quantity);
    void remove_product_from_cart(Product *product, int quantity);
    void update_cart();
    void print_cart();
    void print_client();
};

class Material
{
private:
    string name;
    string description;
    float price;
    int quantity;
    Supplier *supplier;
public:
    Material();
    Material(string name, string description, float price, int quantity, Supplier *supplier);
    void update_price();
    void update_quantity();
    void print_material();
    void order_material(int quantity);
};

class Supplier
{
private:
    string name;
    string address;
    string phone;
    string email;
    vector<Material*> order_list;
public:
    Supplier();
    Supplier(string name, string address, string phone, string email);
    void add_material_to_order_list(Material *material, int quantity);
    void remove_material_from_order_list(Material *material, int quantity);
    void update_order_list();
    void print_order_list();
    void print_supplier();
};

 #endif // CLASSES_HPP