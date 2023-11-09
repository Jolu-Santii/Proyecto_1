#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Product { //definimos propiedades de cada producto, los cuales solo poseen: 
    string name; // nombre de producto
    float price; // precio de producto
    int quantity; // cantidad de produto 
};

int Add(vector<Product> &products); // Ingreso de productos para ello se aportan ciertos datos
void Search(const vector<Product> &products); // Búsqueda de producto de acuerdo a su identificador único(nombre)
int Remove(vector<Product> &products); // Eliminación de productos en inventario, se proporciona el identificador único(nombre)
void Order(vector<Product> &products); // Ordenador de productos, nos permite a ejecutar la búsqueda binaria
int BinarySearch(const vector<Product> &products, const string &temp); // Búsqueda binaria, nos permite dar continuidad a busqueda y eliminación de productos.
void Inventory(const vector<Product> &products);  // Inventario, continue el cátalogo de productos

int main() {
    int opt;
    vector<Product> products; // products, es aquel vector que permite el almacenamiento de los n productos.

    do {
        cout << "\n====== Ferreteria Ibáñez ======" << endl;

        cout << "\n=== Menú principal ===" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Buscar producto" << endl;
        cout << "3. Eliminar producto" << endl;
        cout << "4. Mostrar productos" << endl;
        cout << "5. Salir" << endl;

        cout << "Ingrese una de las cuatro opciones: ";
        cin >> opt;

        switch (opt) {  // Recibimos la opción a elegir y de acuerdo a ello, ejecutamos aquella acción. 
            case 1: {
                Add(products);
                Order(products);
                break;
            }
            case 2: {
                Search(products);
                break;
            }
            case 3: {
                Remove(products);
                break;
            }
            case 4: {
                Inventory(products);
                break;
            }
            case 5: { // Salida del programa
                cout << "Saliendo del programa. Hasta luego." << endl;
                break;
            }
            default: { // La opción no esta disponible, retornamos mensaje. 
                cout << "Opción no válida, intente de nuevo" << endl;
                break;
            }
        }
    } while (opt != 5);

    return 0;
}

int Add(vector<Product> &products) { // Ingreso de productos para ello se aportan ciertos datos
    int n; // los cuales son nombre, precio, y cantidad disponible. 

    cout << "\n=== Menú de Agregar Productos ===" << endl;
    cout << "¿Cuántos productos desea agregar?: ";
    cin >> n;
    cin.ignore(); // Cuando se recibe el numero de producto se piderán los datos

    if (n <= 0) {
        cout << "Cantidad inválida. Debes ingresar al menos un producto." << endl;
        return 0;  // Ejecución fallida, retornamos la cantidad de productos ingresados( 0 productos )
        // , por ende no hay actualización del inventario. 
    }

    for (int i = 0; i < n; ++i) { // Estamos pidiendo los datos para el nuevo producto
        Product product;
        cout << "\nProducto " << i + 1 << endl;
        cout << "Ingrese el nombre del producto " << i + 1 << ": ";
        cin >> product.name;

        cout << "Ingrese el precio del producto " << i + 1 << ": ";
        cin >> product.price;

        cout << "Ingresa la cantidad disponible del producto " << i + 1 << ": ";
        cin >> product.quantity;

        products.push_back(product); // Se ha registrado el nuevo producto 
    }

    return n; // Ejecución exitosa, retornamos la cantidad de productos (n productos) para la actualización del inventario(products)
}

void Search(const vector<Product> &products) { // Búsqueda de producto de acuerdo a su identificador único(nombre)
    string temp;

    cout << "\nIngrese el nombre del producto que desea buscar (No se aceptan caracteres especiales): ";
    cin.ignore();
    getline(cin, temp);

    int pos = BinarySearch(products, temp); // se ha recibido el producto, lo buscamos en el inventario aplicando busqueda binaria

    if (pos == -1) { // Producto no encontrado
        cout << "\nNo se encontró el producto, intente de nuevo\n" << endl;
    } else {  // Producto encontrado, mostramos datos
        cout << "\n=== Producto " << products[pos].name << " ===";
        cout << endl << "  Precio: $" << products[pos].price << endl << "  Cantidad: " << products[pos].quantity << endl;
    }
}

int Remove(vector<Product> &products) { // Eliminación de productos en inventario, se proporciona el identificador único(nombre)
    int num;
    string temp;

    cout << "\n¿Cuántos productos desea eliminar?: ";
    cin >> num;
    cin.ignore();

    for (int i = 0; i < num; ++i) {
        cout << "\nIngrese el nombre del producto que desea borrar (No se aceptan caracteres especiales): ";
        getline(cin, temp);

        int pos = BinarySearch(products, temp); // hemos recibido el producto, antes de eliminarlo, lo buscamos el producto en inventario

        if (pos == -1) { // No se encontró el producto, no se elimina ningún producto
            cout << "\nNo se encontró el producto, intente de nuevo" << endl;
        } else { // Se encontró el producto, eliminamos producto y actualizamos el inventario.
            products.erase(products.begin() + pos);
            cout << "\nProducto eliminado con éxito" << endl;
        }
    }

    return products.size(); // retornamos el tamaño de products para que el invetario sea nuevamente actualizado
    // cuando este mencionado sea utilizada en las funciones del programa.
}

void Order(vector<Product> &products) { // Ordenador de productos, nos permite a ejecutar la búsqueda binaria
    for (int i = 1; i < products.size(); ++i) {  // Productos sean ordenados por nombre, forma alfábetica
        Product key = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].name > key.name) {
            products[j + 1] = products[j];
            j--;
        }

        products[j + 1] = key;
    }
}

int BinarySearch(const vector<Product> &products, const string &temp) { // Búsqueda binaria
    int left = 0, right = products.size() - 1; // nos permite dar continuidad a busqueda y eliminación de productos.
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (products[mid].name == temp) {
            return mid; // Se contro el producto, se retorna su posición
        } else if (products[mid].name < temp) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // No se encontro producto.
}

void Inventory(const vector<Product> &products) { // Inventario, continie el cátalogo de productos
    cout << "\n===== Inventario de productos =====" << endl; // Mostramos el inventario 
    cout << "Productos registrados: " << products.size() << endl;

    cout << "\n  Nombre" << "\t\t| Precio" << "\t| Cantidad" << endl;
    for (int i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name << "\t\t|$" << products[i].price << "\t\t| " << products[i].quantity << endl;
    }
}
