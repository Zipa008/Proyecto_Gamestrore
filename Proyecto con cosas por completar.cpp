#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Juego {
private:
    string nombre;
    double precio;

public:
    Juego(string nombre, double precio) : nombre(nombre), precio(precio) {}

    string getNombre() const {
        return nombre;
    }

    double getPrecio() const {
        return precio;
    }

    void mostrarInformacion() const {
        cout << "Nombre: " << nombre << "\n";
        cout << "Precio: $" << precio << "\n";
    }
};

class Carrito {
private:
    vector<Juego> juegosEnCarrito;

public:
    void agregarAlCarrito(const Juego& juego) {
        juegosEnCarrito.push_back(juego);
        cout << "Se ha agregado " << juego.getNombre() << " al carrito.\n";
    }

    void mostrarCarrito() const {
        cout << "Juegos en el carrito:\n";
        double total = 0;

        for (const auto& juego : juegosEnCarrito) {
            cout << "- " << juego.getNombre() << " - Valor: $" << juego.getPrecio() << "\n";
            total += juego.getPrecio();
        }

        cout << "Total: $" << total << "\n";
    }
};

class AppStore {
private:
    vector<Juego> juegos;
    Carrito carrito;

public:
    AppStore() {
        juegos.push_back(Juego("GTA V", 74'900));
        juegos.push_back(Juego("Minecraft", 49'900));
        // falta poner mas juegos pero ya se ve el juego y el precio

        srand(time(0));
    }

    void mostrarListaDeJuegos() {
        cout << "Lista de juegos disponibles:\n";
        for (size_t i = 0; i < juegos.size(); ++i) {
            cout << i + 1 << ". " << juegos[i].getNombre() << "\n";
        }

        int opcionJuego;
        cout << "Seleccione un juego para más opciones (0 para volver al menú principal): ";
        cin >> opcionJuego;

        if (opcionJuego >= 1 && opcionJuego <= juegos.size()) {
            opcionesJuego(juegos[opcionJuego - 1]);
        } else if (opcionJuego != 0) {
            cout << "Opción no válida. Volviendo al menú principal.\n";
        }
    }

    void opcionesJuego(const Juego& juego) {
        int opcion;

        do {
            cout << "\nOpciones para " << juego.getNombre() << ":\n";
            cout << "1. Mostrar más información\n";
            cout << "2. Añadir al carrito\n";
            cout << "3. Mostrar carrito\n";
            cout << "4. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    juego.mostrarInformacion();
                    break;
                case 2:
                    carrito.agregarAlCarrito(juego);
                    break;
                case 3:
                    carrito.mostrarCarrito();
                    break;
                case 4:
                    cout << "Volviendo al menú principal.\n";
                    break;
                default:
                    cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
            }

        } while (opcion != 4);
    }

    void ejecutar() {
        int opcion;

        do {
            mostrarMenu();
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarListaDeJuegos();
                    break;
                case 2:
                    // zipa falta crear el codigo para poder  vender juegos
                    break;
                case 3:
                    // zipa falta crear el codigo para consultar juegos más vendidos
                    break;
                case 4:
                    cout << "Gracias por usar la AppStore. ¡Hasta luego!\n";
                    break;
                default:
                    cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
            }

        } while (opcion != 4);
    }

    void mostrarMenu() const {
        cout << "\n=== Bienvenido(a) a Rakyrak tu GameStore de confianza ===\n";
        cout << "1. Ver lista de juegos\n";
        cout << "2. Vender juegos\n";
        cout << "3. Consultar juegos más vendidos\n";
        cout << "4. Salir\n";
    }
};

int main() {
    AppStore app;
    app.ejecutar();

    return 0;
}



