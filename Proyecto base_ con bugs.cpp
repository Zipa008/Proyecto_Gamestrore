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
        // Agregar más juegos aquí...
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
        int opcion = 0;

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
        int opcion = 0;

        do {
            mostrarMenu();
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    mostrarListaDeJuegos();
                    break;
                case 2:
                    // falta crear para vender juegos
                    break;
                case 3:
                    // zipa santiago yoseph falta programar el menu de juego mas vendidos
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


//ATENCION ZIPA Y SANTIAGO, Yoseph y yo encontramos estos bugs hay que revisarlos y hacer que funcione

// Manejo de Carrito:
// Bug 1: se agrega el mismo juego al carrito sin verificar duplicados
// Bug 2: al visualizar el carrito, no se muestra la cantidad total de juegos en el carrito

// Lógica de la Aplicación:
// Bug 3: no esta sirviendo la logica de la semilla 
// Bug 4: se estando mostrando los juegos mal
// Bug 5: al seleccionar un juego, se pasa un índice fuera de rango
// Bug 6: no estan sirviendo los menus de la Aplicación

// Lógica de Juego:
// Bug 7: al seleccionar opciones para un juego, no estan sirviendo los menusbl
// Bug 8: las opciones para un juego muestran opciones incorrectas, lo que puede confundir a las personas.
// Bug 9: al mostrar información o agregar al carrito desde las opciones del juego, no se llama a la función correcta
// Bug 10: No se manejan adecuadamente los casos donde se seleccionan opciones incorrectas

// Lógica de Menú Principal:
// Bug 11: al seleccionar opciones en el menú principal, practicamente no sirve el menu
// Bug 12: si el usuario pone opciones incorrctas no se muestra error o algo asi
// Bug 13: el mensaje de bienvenida se ve feo no se muestra bien.
// Bug 14: No se muestra correctamente la última opción en el menú principal.


