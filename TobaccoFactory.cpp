#include "classes.hpp"

TobaccoFactory::TobaccoFactory()
{
    cout << "1. Load from file" << endl;
    cout << "2. Create new" << endl;
    string value;
    int choice = 0;
    while (choice != 1 && choice != 2)
    {
        cout << "Enter your choice: ";
        getline(cin, value);
        choice = stoi(value);
    }
    switch (choice)
    {
    case 1:
        this->load_from_file();
        break;
    case 2:
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
        break;
    }
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
        cout << "8. Print products" << endl;
        cout << "9. Print clients" << endl;
        cout << "10. Print materials" << endl;
        cout << "11. Print suppliers" << endl;
        cout << "12. Print factory info" << endl;
        cout << "13. Save to file" << endl;
        cout << "0. Exit" << endl;
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
            print_products();
            break;
        case 9:
            print_clients();
            break;
        case 10:
            print_materials();
            break;
        case 11:
            print_suppliers();
            break;
        case 12:
            print_factory_info();
            break;
        case 13:
            save_to_file();
            break;
        case 0:
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
    float price;
    cout << "Enter the name of the product: ";
    getline(cin, name);
    cout << "Enter description of the product: ";
    getline(cin, description);
    products.push_back(new Product(name, description, 0, 0));
    this->print_materials();
    int choice = -1;
    while (choice != 0)
    {
        Material *material = NULL;
        cout << "1. Choose Material" << endl
             << "2. Add Material" << endl
             << "0. Exit" << endl;
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
    this->products.back()->print_materials();
    this->products.back()->update_price();
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
    float price;
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
    int choice = -1;
    while (choice != 3)
    {
        cout << "1. Add to cart" << endl
             << "2. Remove from cart" << endl
             << "3. Order" << endl;
        string value;
        cout << "Enter your choice: ";
        getline(cin, value);
        choice = stoi(value);
        switch (choice)
        {
        case 1:
            this->add_to_cart(client);
            break;
        case 2:
            client->remove_product_from_cart();
            break;
        case 3:
        {
            client->print_cart();
            cout << "Total price: " << client->calculate_total_price() << endl
                 << "Prepayment: " << client->calculate_total_price_materials() << endl;
            int choice2 = -1;
            while (choice2 != 0)
            {
                cout << "1. Pay" << endl
                     << "2. Cancel" << endl
                     << "0. Back" << endl;
                cout << "Enter your choice: ";
                getline(cin, value);
                choice2 = stoi(value);
                switch (choice2)
                {
                case 1:
                    this->make_delivery(client);
                    cout << "Order completed!" << endl;
                    choice2 = 0;
                    choice = 3;
                    break;
                case 2:
                    client->delete_cart();
                    cout << "Order deleted!" << endl;
                    choice2 = 0;
                    choice = 3;
                    break;
                case 0:
                    choice2 = 0;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                }
            }
            return;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
}

void TobaccoFactory::add_to_cart(Client *client)
{
    Product *product = this->choose_product();
    int quantity = 0;
    while (quantity <= 0)
    {
        cout << "Enter the quantity of the product: ";
        string value;
        getline(cin, value);
        quantity = stoi(value);
    }
    client->add_product_to_cart(product, quantity);
}

void TobaccoFactory::make_delivery(Client *client)
{
    client->make_products();
    cout << "Order is ready!" << endl;
    cout << "Cost: " << client->calculate_total_price() - client->calculate_total_price_materials() << endl;
    int choice = -1;
    while (choice != 1 && choice != 2)
    {
        cout << "1. Pay" << endl
             << "2. Cancel" << endl;
        cout << "Enter your choice: ";
        string value;
        getline(cin, value);
        choice = stoi(value);
        switch (choice)
        {
        case 1:
            client->deliver_order();
            cout << "Payment completed!" << endl;
            break;
        case 2:
            client->delete_cart();
            cout << "Order canceled!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
}

void TobaccoFactory::print_products()
{
    cout << "Products:" << endl;
    int i = 1;
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        cout << "Index: " << i << endl;
        (*it)->print_product();
        i++;
    }
}

void TobaccoFactory::print_clients()
{
    cout << "Clients:" << endl;
    int i = 1;
    for (auto it = this->clients.begin(); it != this->clients.end(); it++)
    {
        cout << "Index: " << i << endl;
        (*it)->print_client();
        i++;
    }
}

void TobaccoFactory::print_materials()
{
    cout << "Materials:" << endl;
    int i = 1;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        cout << "Index: " << i << endl;
        (*it)->print_material();
        i++;
    }
}

void TobaccoFactory::print_suppliers()
{
    cout << "Suppliers:" << endl;
    int i = 1;
    for (auto it = this->suppliers.begin(); it != this->suppliers.end(); it++)
    {
        cout << "Index: " << i << endl;
        (*it)->print_supplier();
        i++;
    }
}

void TobaccoFactory::print_factory_info()
{
    cout << "Tobacco Factory:" << endl;
    cout << "Name: " << this->name << endl;
    cout << "Address: " << this->address << endl;
    cout << "Phone: " << this->phone << endl;
    cout << "Email: " << this->email << endl;
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
        if (index < 1 || index > this->products.size())
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
        if (index < 1 || index > this->materials.size())
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
        if (index < 1 || index > this->suppliers.size())
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
        if (index < 1 || index > this->clients.size())
        {
            cout << "Invalid index!" << endl;
        }
    }
    return this->clients[index - 1];
}

void TobaccoFactory::save_to_file(const string fold_name /*= "data/"*/)
{
    map<Supplier *, int> supplierID;
    map<Material *, int> materialID;
    map<Product *, int> productID;
    map<Client *, int> clientID;
    int id = 0;
    for (auto it = this->suppliers.begin(); it != this->suppliers.end(); it++)
    {
        supplierID[*it] = id;
        id++;
    }
    id = 0;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        materialID[*it] = id;
        id++;
    }
    id = 0;
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        productID[*it] = id;
        id++;
    }
    id = 0;
    for (auto it = this->clients.begin(); it != this->clients.end(); it++)
    {
        clientID[*it] = id;
        id++;
    }
    ofstream file(fold_name + "tobacco_factory.txt");
    file << this->name << endl
         << this->address << endl
         << this->phone << endl
         << this->email << endl
         << this->website << endl;
    file.close();

    file.open(fold_name + "suppliers.csv");
    file << "SupplierID,Name,Address,Phone,Email" << endl;
    for (auto it = this->suppliers.begin(); it != this->suppliers.end(); it++)
    {
        (*it)->save_to_file(file, supplierID[*it]);
    }
    file.close();

    file.open(fold_name + "client.csv");
    file << "ClientID,Name,Address,Phone,Email" << endl;
    for (auto it = this->clients.begin(); it != this->clients.end(); it++)
    {
        (*it)->save_to_file(file, clientID[*it]);
    }
    file.close();

    file.open(fold_name + "material.csv");
    file << "MaterialID,SupplierID,Name,Description,Price,Quantity" << endl;
    for (auto it = this->materials.begin(); it != this->materials.end(); it++)
    {
        (*it)->save_to_file(file, materialID[*it], &supplierID);
    }
    file.close();

    file.open(fold_name + "product.csv");
    file << "ProductID,Name,Description,Price,Price_of_materials,Quantity" << endl;
    ofstream file_product_material(fold_name + "product_material.csv");
    file_product_material << "ProductID,MaterialID,Quantity" << endl;
    for (auto it = this->products.begin(); it != this->products.end(); it++)
    {
        (*it)->save_to_file(file, productID[*it], &materialID, file_product_material);
    }
}

void TobaccoFactory::load_from_file(const string foldName /*= "data/"*/)
{
    map<int, Supplier *> supplierID;
    map<int, Material *> materialID;
    map<int, Product *> productID;
    map<int, Client *> clientID;

    ifstream file(foldName + "tobacco_factory.txt");
    string line;
    getline(file, line);
    this->name = line;
    getline(file, line);
    this->address = line;
    getline(file, line);
    this->phone = line;
    getline(file, line);
    this->email = line;
    getline(file, line);
    this->website = line;
    file.close();

    file.open(foldName + "suppliers.csv");
    getline(file, line);
    while (getline(file, line))
    {
        Supplier *supplier = new Supplier();
        this->suppliers.push_back(supplier);
        istringstream iss(line);
        this->suppliers.back()->load_from_file(iss, &supplierID);
    }
    file.close();

    file.open(foldName + "client.csv");
    getline(file, line);
    while (getline(file, line))
    {
        Client *client = new Client();
        this->clients.push_back(client);
        istringstream iss(line);
        this->clients.back()->load_from_file(iss, &clientID);
    }
    file.close();

    file.open(foldName + "material.csv");
    getline(file, line);
    while (getline(file, line))
    {
        Material *material = new Material();
        this->materials.push_back(material);
        istringstream iss(line);
        this->materials.back()->load_from_file(iss, &materialID, &supplierID);
    }
    file.close();

    file.open(foldName + "product.csv");
    getline(file, line);
    while (getline(file, line))
    {
        Product *product = new Product();
        this->products.push_back(product);
        istringstream iss(line);
        this->products.back()->load_from_file(iss, &productID);
    }
    file.close();

    file.open(foldName + "product_material.csv");
    getline(file, line);
    while (getline(file, line))
    {
        istringstream iss(line);
        int product_ID, material_ID, quantity;
        string value;
        getline(iss, value, ',');
        product_ID = stoi(value);
        getline(iss, value, ',');
        material_ID = stoi(value);
        getline(iss, value, ',');
        quantity = stoi(value);
        productID[product_ID]->add_material(materialID[material_ID], quantity);
    }
    file.close();
}
