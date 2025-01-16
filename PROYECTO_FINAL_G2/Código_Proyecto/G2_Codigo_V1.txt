#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Estructuras para Administrador y Cliente
struct Admin {
    string username;
    string password;
};

struct Cliente {
    string username;
    string password;
};

// Variables globales
vector<Admin> admins;
vector<Cliente> clientes;

// Listas de catalogo y servicios
vector<string> catalogo = {"Sofa de cuero", "Mesa de madera", "Silla ergonomica", "Estante modular"};
vector<string> servicios = {"Limpieza", "Reparacion", "Venta de muebles"};

// Funciones para mostrar el catalogo y servicios
void mostrarCatalogoYServicios() {
    cout << "\n=== Visualizacion de Lista de Catalogo y Servicios ===\n";
    cout << "Catalogo de Muebles:\n";
    for (size_t i = 0; i < catalogo.size(); i++) {
        cout << i + 1 << ". " << catalogo[i] << "\n";
    }

    cout << "\nServicios Disponibles:\n";
    for (size_t i = 0; i < servicios.size(); i++) {
        cout << i + 1 << ". " << servicios[i] << "\n";
    }
    cout << "\n";
}

// Funcion para modificar el catalogo y servicios
void modificarCatalogoYServicios() {
    int opcion;
    do {
        cout << "\n=== Modificar Catalogo y Servicios ===\n";
        cout << "1. Agregar al catalogo\n";
        cout << "2. Eliminar del catalogo\n";
        cout << "3. Agregar a servicios\n";
        cout << "4. Eliminar de servicios\n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        if (opcion == 1) {
            if (catalogo.size() >= 10) {
                cout << "El catalogo esta lleno.\n";
                continue;
            }
            cout << "Ingrese el nombre del nuevo articulo: ";
            string articulo;
            getline(cin, articulo);
            catalogo.push_back(articulo);
            cout << "Articulo agregado exitosamente.\n";
        } else if (opcion == 2) {
            cout << "Ingrese el numero del articulo a eliminar: ";
            int eliminar;
            cin >> eliminar;
            cin.ignore();
            if (eliminar < 1 || eliminar > (int)catalogo.size()) {
                cout << "Opcion no valida.\n";
                continue;
            }
            catalogo.erase(catalogo.begin() + eliminar - 1);
            cout << "Articulo eliminado exitosamente.\n";
        } else if (opcion == 3) {
            if (servicios.size() >= 10) {
                cout << "La lista de servicios esta llena.\n";
                continue;
            }
            cout << "Ingrese el nombre del nuevo servicio: ";
            string servicio;
            getline(cin, servicio);
            servicios.push_back(servicio);
            cout << "Servicio agregado exitosamente.\n";
        } else if (opcion == 4) {
            cout << "Ingrese el numero del servicio a eliminar: ";
            int eliminar;
            cin >> eliminar;
            cin.ignore();
            if (eliminar < 1 || eliminar > (int)servicios.size()) {
                cout << "Opcion no valida.\n";
                continue;
            }
            servicios.erase(servicios.begin() + eliminar - 1);
            cout << "Servicio eliminado exitosamente.\n";
        } else if (opcion != 5) {
            cout << "Opcion no valida. Intente nuevamente.\n";
        }
    } while (opcion != 5);
}

// Funcion para registrar un administrador
void registrarAdministrador() {
    if (admins.size() >= 10) {
        cout << "Se alcanzo el limite de administradores.\n";
        return;
    }
    cout << "=== Registro de Administrador ===\n";
    cout << "Ingrese nombre de usuario: ";
    string username;
    cin >> username;
    cout << "Ingrese contrasena: ";
    string password;
    cin >> password;

    admins.push_back({username, password});
    cout << "Administrador registrado exitosamente.\n";
}

// Funcion para registrar un cliente
void registrarCliente() {
    if (clientes.size() >= 10) {
        cout << "Se alcanzo el limite de clientes.\n";
        return;
    }
    cout << "=== Registro de Cliente ===\n";
    cout << "Ingrese nombre de usuario: ";
    string username;
    cin >> username;
    cout << "Ingrese contrasena: ";
    string password;
    cin >> password;

    clientes.push_back({username, password});
    cout << "Cliente registrado exitosamente.\n";
}

// Funcion para iniciar sesion
void iniciarSesion() {
    cout << "=== Inicio de Sesion ===\n";
    cout << "Ingrese nombre de usuario: ";
    string username;
    cin >> username;
    cout << "Ingrese contrasena: ";
    string password;
    cin >> password;

    // Verificar si es administrador
    for (const auto& admin : admins) {
        if (admin.username == username && admin.password == password) {
            cout << "Inicio de sesion exitoso como Administrador.\n";
            mostrarCatalogoYServicios();
            modificarCatalogoYServicios();
            return;
        }
    }

    // Verificar si es cliente
    for (const auto& cliente : clientes) {
        if (cliente.username == username && cliente.password == password) {
            cout << "Inicio de sesion exitoso como Cliente.\n";
            mostrarCatalogoYServicios();
            return;
        }
    }

    cout << "Nombre de usuario o contrasena incorrectos.\n";
}

// Menu principal
void menu() {
    int opcion;
    do {
        cout << "\n=== Menu Principal ===\n";
        cout << "1. Registrar Administrador\n";
        cout << "2. Registrar Cliente\n";
        cout << "3. Iniciar Sesion\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarAdministrador();
                break;
            case 2:
                registrarCliente();
                break;
            case 3:
                iniciarSesion();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
        }
    } while (opcion != 4);
}

// Funcion principal
int main() {
    menu();
    return 0;
}
