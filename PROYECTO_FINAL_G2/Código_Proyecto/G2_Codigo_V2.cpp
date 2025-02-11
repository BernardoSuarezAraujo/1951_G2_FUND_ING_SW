#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <conio.h> // Para getch() en Windows

using namespace std;

struct Usuario {
    string username;
    string password;
};

struct Producto {
    string nombre;
    vector<string> variedades;
    vector<double> precios;
};

vector<Usuario> admins;
vector<Usuario> clientes;
vector<Producto> catalogo = {
    {"Sofa de cuero", {"Negro", "Marron"}, {500.0, 550.0}},
    {"Mesa de madera", {"Roble", "Nogal"}, {200.0, 250.0}},
    {"Silla ergonomica", {"Roja", "Azul"}, {100.0, 120.0}},
    {"Estante modular", {"Grande", "Pequeno"}, {300.0, 180.0}}
};
vector<string> servicios = {"Limpieza", "Reparacion", "Venta de muebles"};
vector<string> pedidosProductos;
vector<string> pedidosServicios;

// Función para limpiar la entrada en caso de error
template<typename T>
void validarEntrada(T& variable) {
    while (!(cin >> variable)) {
        cout << "Entrada invalida. Por favor ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Guardar usuarios en archivo
template<typename T>
void guardarUsuarios(const string& archivo, const vector<T>& usuarios) {
    ofstream file(archivo);
    if (!file) {
        cerr << "Error al abrir el archivo " << archivo << " para escritura." << endl;
        return;
    }
    for (const auto& user : usuarios) {
        file << user.username << " " << user.password << "\n";
    }
}

// Cargar usuarios desde archivo
template<typename T>
void cargarUsuarios(const string& archivo, vector<T>& usuarios) {
    ifstream file(archivo);
    if (!file) return;
    string username, password;
    while (file >> username >> password) {
        usuarios.push_back({username, password});
    }
}

// Leer contraseña con asteriscos
string leerPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !password.empty()) {
            password.pop_back();
            cout << "\b \b";
        } else if (ch != '\b') {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void registrarUsuario(vector<Usuario>& usuarios, const string& archivo) {
    cout << "Ingrese nombre de usuario: ";
    string username;
    cin >> username;
    cout << "Ingrese contrasena: ";
    string password = leerPassword();

    usuarios.push_back({username, password});
    guardarUsuarios(archivo, usuarios);
    cout << "Usuario registrado exitosamente.\n";
}

void mostrarCatalogoYServicios() {
    cout << "\nCatalogo de Muebles:\n";
    for (size_t i = 0; i < catalogo.size(); i++) {
        cout << i + 1 << ". " << catalogo[i].nombre << "\n";
    }
    cout << "\nServicios Disponibles:\n";
    for (size_t i = 0; i < servicios.size(); i++) {
        cout << i + 1 << ". " << servicios[i] << "\n";
    }
}

void seleccionarProducto() {
    cout << "Seleccione un producto: ";
    int opcion;
    validarEntrada(opcion);
    if (opcion < 1 || opcion > catalogo.size()) {
        cout << "Opcion no valida.\n";
        return;
    }

    Producto& producto = catalogo[opcion - 1];
    cout << "Variedades disponibles:\n";
    for (size_t i = 0; i < producto.variedades.size(); i++) {
        cout << i + 1 << ". " << producto.variedades[i] << " - Precio: " << producto.precios[i] << "\n";
    }

    cout << "Seleccione una variedad: ";
    int variedad;
    validarEntrada(variedad);
    if (variedad < 1 || variedad > producto.variedades.size()) {
        cout << "Opcion no valida.\n";
        return;
    }
    pedidosProductos.push_back(producto.nombre + " - " + producto.variedades[variedad - 1]);
    cout << "Pedido realizado con exito.\n";
}

void seleccionarServicio() {
    cout << "Seleccione un servicio: ";
    int opcion;
    validarEntrada(opcion);
    if (opcion < 1 || opcion > servicios.size()) {
        cout << "Opcion no valida.\n";
        return;
    }
    pedidosServicios.push_back(servicios[opcion - 1]);
    cout << "Pedido de servicio realizado con exito.\n";
}

void iniciarSesion() {
    cout << "Ingrese nombre de usuario: ";
    string username;
    cin >> username;
    cout << "Ingrese contrasena: ";
    string password = leerPassword();

    for (const auto& admin : admins) {
        if (admin.username == username && admin.password == password) {
            cout << "Inicio de sesion exitoso como Administrador.\n";
            mostrarCatalogoYServicios();
            return;
        }
    }
    for (const auto& cliente : clientes) {
        if (cliente.username == username && cliente.password == password) {
            cout << "Inicio de sesion exitoso como Cliente.\n";
            int opcion;
            do {
                mostrarCatalogoYServicios();
                cout << "\nSeleccione una opcion:\n1. Comprar un producto\n2. Solicitar un servicio\n3. Salir\nOpcion: ";
                validarEntrada(opcion);
                if (opcion == 1) seleccionarProducto();
                else if (opcion == 2) seleccionarServicio();
            } while (opcion != 3);
            return;
        }
    }
    cout << "Usuario o contrasena incorrectos.\n";
}

int main() {
    cargarUsuarios("admins.txt", admins);
    cargarUsuarios("clientes.txt", clientes);

    int opcion;
    do {
        cout << "\n=== Menu Principal ===\n1. Iniciar sesion\n2. Registrar cliente\n3. Registrar administrador\n4. Salir\nSeleccione una opcion: ";
        validarEntrada(opcion);
        switch (opcion) {
            case 1: iniciarSesion(); break;
            case 2: registrarUsuario(clientes, "clientes.txt"); break;
            case 3: registrarUsuario(admins, "admins.txt"); break;
            case 4: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
    return 0;
}
