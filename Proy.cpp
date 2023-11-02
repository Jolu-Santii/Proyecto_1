#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Product {
    string name;
    float price;
    int quantity;
};

int Agregar(vector<Product> &products);
void buscar(const vector<Product> &products);
int eliminar(vector<Product> &products);
void ordenar(vector<Product> &products);
int BusqBin(const vector<Product> &products, const string &temp);
void catalogo(const vector<Product> &products);

int main() {
    int opt;
    vector<Product> products;

    do {
        cout << "\n====== Ferreteria Estefi ======" << endl;

        cout << "\n=== Menú principal ===" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Buscar producto" << endl;
        cout << "3. Eliminar producto" << endl;
        cout << "4. Mostrar productos" << endl;
        cout << "5. Salir" << endl;

        cout << "Ingrese una de las cuatro opciones: ";
        cin >> opt;

        switch (opt) {
            case 1: {
                Agregar(products);
                ordenar(products);
                break;
            }
            case 2: {
                buscar(products);
                break;
            }
            case 3: {
                eliminar(products);
                break;
            }
            case 4: {
                catalogo(products);
                break;
            }
            case 5: {
                cout << "Saliendo del programa. Hasta luego." << endl;
                break;
            }
            default: {
                cout << "Opción no válida, intente de nuevo" << endl;
                break;
            }
        }
    } while (opt != 5);

    return 0;
}

int Agregar(vector<Product> &products) {
    int n;

    cout << "\n=== Menú de Agregar Productos ===" << endl;
    cout << "¿Cuántos productos desea agregar?: ";
    cin >> n;
    cin.ignore(); 

    if (n <= 0) {
        cout << "Cantidad inválida. Debes ingresar al menos un producto." << endl;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        Product product;
        cout << "\nProducto " << i + 1 << endl;
        cout << "Ingrese el nombre del producto " << i + 1 << ": ";
        cin >> product.name;

        cout << "Ingrese el precio del producto " << i + 1 << ": ";
        cin >> product.price;

        cout << "Ingresa la cantidad disponible del producto " << i + 1 << ": ";
        cin >> product.quantity;

        products.push_back(product);
    }

    return n;
}

void buscar(const vector<Product> &products) {
    string temp;

    cout << "\nIngrese el nombre del producto que desea buscar (No se aceptan caracteres especiales): ";
    cin.ignore();
    getline(cin, temp);

    int pos = BusqBin(products, temp);

    if (pos == -1) {
        cout << "\nNo se encontró el producto, intente de nuevo\n" << endl;
    } else {
        cout << endl << products[pos].name << endl << "Precio: $" << products[pos].price << endl << "Cantidad: " << products[pos].quantity << endl;
    }
}

int eliminar(vector<Product> &products) {
    int num;
    string temp;

    cout << "\n¿Cuántos productos desea eliminar?: ";
    cin >> num;
    cin.ignore();

    for (int i = 0; i < num; ++i) {
        cout << "\nIngrese el nombre del producto que desea borrar (No se aceptan caracteres especiales): ";
        getline(cin, temp);

        int pos = BusqBin(products, temp);

        if (pos == -1) {
            cout << "\nNo se encontró el producto, intente de nuevo" << endl;
        } else {
            products.erase(products.begin() + pos);
            cout << "\nProducto eliminado con éxito" << endl;
        }
    }

    return products.size();
}

void ordenar(vector<Product> &products) {
    for (int i = 1; i < products.size(); ++i) {
        Product key = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].name > key.name) {
            products[j + 1] = products[j];
            j--;
        }

        products[j + 1] = key;
    }
}

int BusqBin(const vector<Product> &products, const string &temp) {
    int left = 0, right = products.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].name == temp) {
            return mid;
        } else if (products[mid].name < temp) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void catalogo(const vector<Product> &products) {
    cout << "\n===== Catálogo de productos =====" << endl;
    cout << "Productos registrados: " << products.size() << endl;

    cout << "\n  Nombre" << "\t\t| Precio" << "\t| Cantidad" << endl;
    for (int i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name << "\t\t|$" << products[i].price << "\t\t| " << products[i].quantity << endl;
    }
}
