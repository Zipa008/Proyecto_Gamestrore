#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Juego {
private:
    string nombre;
    string categoria;
    int tamano;  // en kilobytes
    double precio;
    int licenciasDisponibles;
    int licenciasVendidas;

public:
    Juego(string nombre, string categoria, int tamano, double precio, int licenciasDisponibles)
        : nombre(nombre), categoria(categoria), tamano(tamano), precio(precio), licenciasDisponibles(licenciasDisponibles), licenciasVendidas(0) {}

    string getNombre() const {
        return nombre;
    }

    string getCategoria() const {
        return categoria;
    }

    int getTamanoKB() const {
        return tamano;
    }

    int getTamanoGB() const {
        return tamano / 1024;  // 1 GB = 1024 KB
    }

    double getPrecioColombiano() const {
        return precio;
    }

    double getPrecioDolar() const {
        // Conversión: 1 dólar = 4100 pesos colombianos
        return precio / 4100.0;
    }

    int getLicenciasDisponibles() const {
        return licenciasDisponibles;
    }

    int getLicenciasVendidas() const {
        return licenciasVendidas;
    }

    void mostrarInformacion() const {
        cout << "Nombre: " << nombre << "\n";
        cout << "Categoría: " << categoria << "\n";
        cout << "Tamaño: " << tamano << " KB (" << getTamanoGB() << " GB)\n";
        cout << "Precio: $" << precio << " (USD: $" << getPrecioDolar() << ")\n";
        cout << "Licencias Disponibles: " << licenciasDisponibles << "\n";
        cout << "Licencias Vendidas: " << licenciasVendidas << "\n";
    }
};

class Carrito {
private:
    vector<pair<Juego, int>> juegosEnCarrito;

public:
    void agregarAlCarrito(const Juego& juego, int cantidad) {
        if (cantidad <= juego.getLicenciasDisponibles()) {
            juegosEnCarrito.push_back(make_pair(juego, cantidad));
            cout << "Se han agregado " << cantidad << " licencias de " << juego.getNombre() << " al carrito.\n";
        } else {
            cout << "No hay suficientes licencias disponibles para agregar al carrito de " << juego.getNombre() << "\n";
        }
    }

    void mostrarCarrito() const {
        cout << "Juegos en el carrito:\n";
        double totalPesos = 0;
        double totalDolares = 0;

        for (const auto& par : juegosEnCarrito) {
            const Juego& juego = par.first;
            int cantidad = par.second;

            cout << "- " << cantidad << " licencias de " << juego.getNombre() << " - Valor: $" << juego.getPrecioColombiano() * cantidad
                      << " (USD: $" << juego.getPrecioDolar() * cantidad << ")\n";

            totalPesos += juego.getPrecioColombiano() * cantidad;
            totalDolares += juego.getPrecioDolar() * cantidad;
        }

        cout << "Total en pesos colombianos: $" << totalPesos << "\n";
        cout << "Total en dólares: $" << totalDolares << "\n";
    }

    bool carritoVacio() const {
        return juegosEnCarrito.empty();
    }

    void vaciarCarrito() {
        juegosEnCarrito.clear();
    }

    const vector<pair<Juego, int>>& getJuegosEnCarrito() const {
        return juegosEnCarrito;
    }

    int getLicenciasPorJuego(const Juego& juego) const {
        int contador = 0;
        for (const auto& par : juegosEnCarrito) {
            const Juego& juegoEnCarrito = par.first;
            if (juegoEnCarrito.getNombre() == juego.getNombre()) {
                contador += par.second;
            }
        }
        return contador;
    }
};

class AppStore {
private:
    vector<Juego> juegos;
    Carrito carrito;

public:
    AppStore() {
                                                 //tamaño del juego - precio -licencias disponibles 
        juegos.push_back(Juego("GTA V", "Acción", 110'000 * 1024, 74'900, 50));
        juegos.push_back(Juego("Minecraft", "Aventura", 40'000 * 1024, 49'900, 100));
        juegos.push_back(Juego("Fortnite", "Acción", 80'000 * 1024, 0, 200));
        juegos.push_back(Juego("Among Us", "Rompecabezas", 2'000 * 1024, 9'900, 150));
        juegos.push_back(Juego("FIFA 22", "Deporte", 38'000 * 1024, 99'900, 80));
        juegos.push_back(Juego("The Legend of Zelda: Breath of the Wild", "Aventura", 160'000 * 1024, 129'900, 30));
        juegos.push_back(Juego("Cyberpunk 2077", "Acción", 100'000 * 1024, 79'900, 20));
        juegos.push_back(Juego("Assassin's Creed Valhalla", "Aventura", 70'000 * 1024, 119'900, 40));
        juegos.push_back(Juego("Call of Duty: Warzone", "Acción", 120'000 * 1024, 0, 60));
        juegos.push_back(Juego("Overwatch", "Acción", 42'000 * 1024, 59'900, 90));
        juegos.push_back(Juego("Rocket League", "Deporte", 15'000 * 1024, 49'900, 120));
        juegos.push_back(Juego("Super Mario Odyssey", "Aventura", 60'000 * 1024, 79'900, 35));
        juegos.push_back(Juego("The Forest", "Acción", 30'000 * 1024, 29'900, 80));
        juegos.push_back(Juego("League of Legends", "Acción", 30'000 * 1024, 0, 100));
        juegos.push_back(Juego("Dota 2", "Acción", 40'000 * 1024, 0, 70));
        juegos.push_back(Juego("World of Warcraft", "Aventura", 90'000 * 1024, 44'900, 25));
        juegos.push_back(Juego("Mortal Kombat 11", "Acción", 60'000 * 1024, 69'900, 55));
        juegos.push_back(Juego("FIFA 23", "Deporte", 32'000 * 1024, 5'900, 120));
        juegos.push_back(Juego("Apex Legends", "Acción", 60'000 * 1024, 0, 65));
        juegos.push_back(Juego("Red Dead Redemption 2", "Acción", 110'000 * 1024, 79'900, 40));
        juegos.push_back(Juego("NBA 2K21", "Deporte", 80'000 * 1024, 119'900, 30));
        juegos.push_back(Juego("Sekiro: Shadows Die Twice", "Acción", 50'000 * 1024, 69'900, 25));
        juegos.push_back(Juego("Pokemon Sword and Shield", "Aventura", 160'000 * 1024, 74'900, 50));
        juegos.push_back(Juego("Counter-Strike: Global Offensive", "Acción", 30'000 * 1024, 0, 80));
        juegos.push_back(Juego("The Sims 4", "Simulación", 45'000 * 1024, 69'900, 35));
        juegos.push_back(Juego("Tom Clancy's Rainbow Six Siege", "Acción", 70'000 * 1024, 59'900, 60));
        juegos.push_back(Juego("FIFA 21", "Deporte", 38'000 * 1024, 109'900, 45));
        juegos.push_back(Juego("Valorant", "Acción", 80'000 * 1024, 0, 70));
        juegos.push_back(Juego("Far Cry 6", "Acción", 100'000 * 1024, 79'900, 30));
        juegos.push_back(Juego("Genshin Impact", "Aventura", 60'000 * 1024, 0, 50));
        juegos.push_back(Juego("Resident Evil Village", "Aventura", 85'000 * 1024, 69'900, 40));

       

     
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
            cout << "2. Añadir licencias al carrito\n";
            cout << "3. Añadir más juegos al carrito\n";
            cout << "4. Comprar carrito\n";
            cout << "5. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    juego.mostrarInformacion();
                    break;
                case 2:
                    añadirLicenciasAlCarrito(juego);
                    break;
                case 3:
                    añadirJuegosAlCarrito();
                    break;
                case 4:
                    comprarCarrito();
                    break;
                case 5:
                    cout << "Volviendo al menú principal.\n";
                    break;
                default:
                    cout << "Opción no válida. Por favor, seleccione una opción válida.\n";
            }

        } while (opcion != 5);
    }

    void añadirLicenciasAlCarrito(const Juego& juego) {
        int cantidad;
        cout << "Ingrese la cantidad de licencias que desea añadir al carrito: ";
        cin >> cantidad;

        carrito.agregarAlCarrito(juego, cantidad);
    }

    void añadirJuegosAlCarrito() {
        mostrarListaDeJuegos();
        int opcionJuego;
        cout << "Seleccione un juego para añadir al carrito (0 para volver al menú principal): ";
        cin >> opcionJuego;

        if (opcionJuego >= 1 && opcionJuego <= juegos.size()) {
            añadirLicenciasAlCarrito(juegos[opcionJuego - 1]);
        } else if (opcionJuego != 0) {
            cout << "Opción no válida. Volviendo al menú principal.\n";
        }
    }

    void comprarCarrito() {
        if (carrito.carritoVacio()) {
            cout << "El carrito está vacío. No hay nada que comprar.\n";
            return;
        }

     
        string numeroTarjeta;
        string nombreTitular;
        string codigoSeguridad;
        string fechaCaducidad;

        cout << "\nIngrese los datos de su tarjeta:\n";
        cout << "Número de tarjeta: ";
        cin >> numeroTarjeta;

        cout << "Nombre del titular: ";
        cin >> nombreTitular;

        cout << "Código de seguridad: ";
        cin >> codigoSeguridad;

        cout << "Fecha de caducidad (MM/AA): ";
        cin >> fechaCaducidad;


        cout << "\nProcesando pago...\n";

  
        double totalPesos = 0;
        double totalDolares = 0;

        for (const auto& par : carrito.getJuegosEnCarrito()) {
            const Juego& juego = par.first;
            int cantidad = par.second;

            for (int i = 0; i < cantidad; ++i) {
                string licencia = generarLicenciaAleatoria();
                cout << "Licencia para " << juego.getNombre() << ": " << licencia << "\n";
            }

            totalPesos += juego.getPrecioColombiano() * cantidad;
            totalDolares += juego.getPrecioDolar() * cantidad;
        }

        cout << "Compra realizada con éxito.\n";
        cout << "Has pagado $" << totalPesos << " (USD: $" << totalDolares << "). Gracias por su compra.\n";
        carrito.vaciarCarrito();
    }

    string generarLicenciaAleatoria() const {
        const string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const size_t longitudLicencia = 12;

        string licencia;
        for (size_t i =0; i < longitudLicencia; ++i) {
            licencia += caracteres[rand() % caracteres.size()];
        }

        return licencia;
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
                    //zipa falta crear el codigo para poder  vender juegos
                    break;
                case 3:
                    // zipa falta crear el codigo para poder para consultar juegos más vendidos
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
        cout << "2. Vender licencias de juegos\n";
        cout << "3. Consultar juegos más vendidos\n";
        cout << "4. Salir\n";
    }
};

int main() {
    AppStore app;
    app.ejecutar();

    return 0;
}



