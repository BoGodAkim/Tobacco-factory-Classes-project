#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <bits/stdc++.h>
using std::map;
using std::string;
using std::vector;

class Product;
class Material;
class Client;
class Supplier;
class TobaccoFactory
{
private:
    string name;                  // Name of the factory
    string address;               // Address of the factory
    string phone;                 // Phone number of the factory
    string email;                 // Email of the factory
    string website;               // Website of the factory
    vector<Product *> products;   // Vector of products
    vector<Client *> clients;     // Vector of clients
    vector<Material *> materials; // Vector of materials
    vector<Supplier *> suppliers; // Vector of suppliers
    void add_product();           // Function to add a product with parameters from the manager
    void add_client();            // Function to add a client with parameters from the manager
    void add_material();          // Function to add a material with parameters from the manager
    void add_supplier();          // Function to add a supplier with parameters from the manager
    void update_product_price();  // Function call Product* chooseProduct() and call Product::updatePrice()
    void update_material_price(); // Function call Material* chooseMaterial() and call Material::updatePrice()
    void make_order();            // Function call Client* chooseClient(), Product* chooseProduct() and ask for the quantity of the product and call Client::addProduct_to_Cart()
    void make_delivery();         // Function call Client* chooseClient() and call Client::deleteCart()
    void print_products();        // Function print all products in the vector
    void print_clients();         // Function print all clients in the vector
    void print_materials();       // Function print all materials in the vector
    void print_suppliers();       // Function print all suppliers in the vector
    void print_factory_info();    // Function print information about the factory
    Product *choose_product();    // Function choose product from the vector using function Product::showProduct() and ask for the number of the product from the manager
    Material *choose_material();  // Function choose material from the vector using function Material::showMaterial() and ask for the number of the material from the manager
    Supplier *choose_supplier();  // Function choose supplier from the vector using function Supplier::showSupplier() and ask for the number of the supplier from the manager
    Client *choose_client();      // Function choose client from the vector using function Client::showClient() and ask for the number of the client from the manager
public:
    TobaccoFactory();  // Constructor
    void enter_menu(); // Function to enter the menu and call the function according to the number
};

class Product
{
private:
    string name;                    // Name of the product
    string description;             // Description of the product
    float price;                    // Price of the product
    float price_materials;          // Price of the materials used in the product
    map<Material *, int> materials; // Map of materials and their quantity which are used to produce the product
    void calculate_price_materials(); // Function to calculate the price of the materials used in the product
public:
    int quantity;                                                        // Quantity of the product
    Product();                                                           // Constructor
    Product(const string name, const string description, const float price, const int quantity); // Constructor with parameters
    void add_material(Material *material, int quantity);                 // Function to add material to the map
    void remove_material(Material *material, int quantity);              // Function to remove material from the map
    void update_price();                                                 // Function to update the price of the product wchich ask for the new price from the manager and this price higher than sum of the materials prices
    void print_product();                                                // Function to print the product
    void print_materials();                                              // Function to print the materials used to produce the product
    string get_name();                                                   // Function to return the name of the product
    float get_price();                                                   // Function to return the price of the product
    float get_price_materials();                                         // Function to return the price of the materials used in the product
};

class Client
{
private:
    string name;              // Name of the client
    string address;           // Address of the client
    string phone;             // Phone number of the client
    string email;             // Email of the client
    map<Product *, int> cart; // Map of products and their quantity which are in the cart

public:
    Client();                                                        // Constructor
    Client(const string name, const string address, const string phone, const string email); // Constructor with parameters
    void add_product_to_cart(Product *product, int quantity);        // Function to add product to the cart
    void remove_product_from_cart(Product *product, int quantity);   // Function to remove product from the cart
    void update_cart();                                              // Function to update the cart
    void delete_cart();                                              // Function to delete the cart
    void print_cart();                                               // Function to print the cart
    void print_client();                                             // Function to print the client
};

class Material
{
private:
    string name;        // Name of the material
    string description; // Description of the material
    float price;        // Price of the material
    int quantity;       // Quantity of the material
    Supplier *supplier; // Supplier of the material
    vector<Product *> products; // Vector of products which are made with the material

public:
    Material();                                                                               // Constructor
    Material(string name, string description, float price, int quantity, Supplier *supplier); // Constructor with parameters
    void update_price();                                                                      // Function to update the price of the material with the new price from the manager
    void update_quantity();                                                                   // Function to update the quantity of the material
    void print_material();                                                                    // Function to print the material
    void order_material(int quantity);                                                        // Function to order the material with the quantity
    float get_price();                                                                        // Function to return the price of the material
    string get_name();                                                                        // Function to return the name of the material
};
class Supplier
{
private:
    string name;                   // Name of the supplier
    string address;                // Address of the supplier
    string phone;                  // Phone number of the supplier
    string email;                  // Email of the supplier
    vector<Material *> order_list; // Vector of materials which are ordered

public:
    Supplier();                                                             // Constructor
    Supplier(string name, string address, string phone, string email);      // Constructor with parameters
    void add_material_to_order_list(Material *material, int quantity);      // Function to add material to the order list
    void remove_material_from_order_list(Material *material, int quantity); // Function to remove material from the order list
    void update_order_list();                                               // Function to update the order list
    void delete_order_list();                                               // Function to delete the order list
    void print_order_list();                                                // Function to print the order list
    void print_supplier();                                                  // Function to print the supplier
};

#endif // CLASSES_HPP