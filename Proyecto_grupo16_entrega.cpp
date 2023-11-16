#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

// Definición de la clase Juego que representa un videojuego
class Juego {
private:
    string nombre;
    string categoria;
    int tamano; // en kilobytes
    double precio;
    int licenciasDisponibles;
    int licenciasVendidas;

public:
    // Constructor de la clase Juego
    Juego(string nombre, string categoria, int tamano, double precio, int licenciasDisponibles)
        : nombre(nombre), categoria(categoria), tamano(tamano), precio(precio), licenciasDisponibles(licenciasDisponibles), licenciasVendidas(0) {}

    // Métodos para obtener información sobre el juego
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
        return tamano / 1024; // 1 GB = 1024 KB
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

    // Método para vender licencias del juego
    void venderLicencias(int cantidad) {
        if (cantidad <= licenciasDisponibles) {
            licenciasDisponibles -= cantidad;
            licenciasVendidas += cantidad;
            cout << "Se han vendido " << cantidad << " licencias de " << nombre << ". Licencias restantes: " << licenciasDisponibles << "\n";
        } else {
            cout << "No hay suficientes licencias disponibles para vender de " << nombre << ". Licencias disponibles: " << licenciasDisponibles << "\n";
        }
    }

    // Método para mostrar información del juego
    void mostrarInformacion() const {
        cout << "Nombre: " << nombre << "\n";
        cout << "Categoría: " << categoria << "\n";
        cout << "Tamaño: " << tamano << " KB (" << getTamanoGB() << " GB)\n";
        cout << "Precio: $" << precio << " (USD: $" << getPrecioDolar() << ")\n";
        cout << "Licencias Disponibles: " << licenciasDisponibles << "\n";
        cout << "Licencias Vendidas: " << licenciasVendidas << "\n";
    }
};

// Definición de la clase Carrito que representa el carrito de compras
class Carrito {
private:
    vector<std::pair<Juego, int>> juegosEnCarrito;

public:
    // Método para agregar licencias de un juego al carrito
    void agregarAlCarrito(const Juego& juego, int cantidad) {
        if (cantidad <= juego.getLicenciasDisponibles()) {
            juegosEnCarrito.push_back(std::make_pair(juego, cantidad));
            cout << "Se han agregado " << cantidad << " licencias de " << juego.getNombre() << " al carrito.\n";
        } else {
            cout << "No hay suficientes licencias disponibles para agregar al carrito de " << juego.getNombre() << "\n";
        }
    }

    // Método para mostrar el contenido del carrito
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

    // Método para verificar si el carrito está vacío
    bool carritoVacio() const {
        return juegosEnCarrito.empty();
    }

    // Método para vaciar el carrito
    void vaciarCarrito() {
        juegosEnCarrito.clear();
    }

    // Método para obtener la lista de juegos en el carrito
    const vector<pair<Juego, int>>& getJuegosEnCarrito() const {
        return juegosEnCarrito;
    }

    // Método para obtener la cantidad de licencias de un juego específico en el carrito
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

// Fin de la declaración de las clases y métodos


// Definición de la clase AppStore que representa una tienda de aplicaciones de juegos
class AppStore {
private:
    vector<Juego> juegos; // Lista de juegos disponibles
    vector<Juego> juegosMasComprados; // Lista de juegos más comprados (aún no se utiliza)
    Carrito carrito; // Carrito de compras del usuario
    double saldoCuenta; // Saldo del usuario
    double saldoAcumulado; // Saldo acumulado para compras con tarjeta

public:
    // Constructor de la clase AppStore
    AppStore() : saldoCuenta(0), saldoAcumulado(0) {
        //tamaño del juego - precio -licencias disponibles 
        juegos.push_back(Juego("GTA V", "Acción", 110'000 * 1024, 74'900, 50));
        juegos.push_back(Juego("Minecraft", "Aventura", 40'000 * 1024, 49'900, 100));
        juegos.push_back(Juego("Fortnite", "Acción", 80'000 * 1024, 0, 200));
        juegos.push_back(Juego("Among Us", "Rompecabezas", 2'000 * 1024, 9'900, 150));
        juegos.push_back(Juego("Euro Truck Simulator 2", "Simulador", 8'000 * 1024, 19'900, 92));
        juegos.push_back(Juego("FIFA 22", "Deporte", 38'000 * 1024, 99'900, 80));
        juegos.push_back(Juego("The Witness", "Rompecabezas", 55'000 * 1024, 49'900, 40));
        juegos.push_back(Juego("The Legend of Zelda: Breath of the Wild", "Aventura", 160'000 * 1024, 129'900, 30));
        juegos.push_back(Juego("Cyberpunk 2077", "Acción", 100'000 * 1024, 79'900, 20));
        juegos.push_back(Juego("Assassin's Creed Valhalla", "Aventura", 70'000 * 1024, 119'900, 40));
        juegos.push_back(Juego("Call of Duty: Warzone", "Acción", 120'000 * 1024, 0, 60));
        juegos.push_back(Juego("Tetris Effect", "Rompecabezas", 30'000 * 1024, 29'900, 75));
        juegos.push_back(Juego("Overwatch", "Acción", 42'000 * 1024, 59'900, 90));
        juegos.push_back(Juego("Farming Simulator 19", "Simulador", 20'000 * 1024, 49'900, 87));
        juegos.push_back(Juego("Rocket League", "Deporte", 15'000 * 1024, 49'900,120));
        juegos.push_back(Juego("Super Mario Odyssey", "Aventura", 60'000 * 1024, 79'900, 35));
        juegos.push_back(Juego("The Sims 4", "Simulador", 25'000 * 1024, 39'900, 95));
        juegos.push_back(Juego("The Forest", "Supervivencia", 30'000 * 1024, 29'900, 80));
        juegos.push_back(Juego("League of Legends", "Acción", 30'000 * 1024, 0, 100));
        juegos.push_back(Juego("Dota 2", "Acción", 40'000 * 1024, 0, 70));
        juegos.push_back(Juego("Cities: Skylines", "Simulador", 30'000 * 1024, 29'900, 88));
        juegos.push_back(Juego("Puzzle Quest: Challenge of the Warlords", "Rompecabezas", 45'000 * 1024, 39'900, 60));
        juegos.push_back(Juego("World of Warcraft", "Aventura", 90'000 * 1024, 44'900, 25));
        juegos.push_back(Juego("Portal 2", "Rompecabezas", 48'000 * 1024, 44'900, 55));
        juegos.push_back(Juego("Mortal Kombat 11", "Acción", 60'000 * 1024, 69'900, 55));
        juegos.push_back(Juego("Microsoft Flight Simulator", "Simulador", 150'000 * 1024, 59'900, 96));
        juegos.push_back(Juego("FIFA 23", "Deporte", 32'000 * 1024, 5'900, 120));
        juegos.push_back(Juego("Apex Legends", "Acción", 60'000 * 1024, 0, 65));
        juegos.push_back(Juego("Red Dead Redemption 2", "Acción", 110'000 * 1024, 79'900, 40));
        juegos.push_back(Juego("Monument Valley", "Rompecabezas", 20'000 * 1024, 19'900, 80));
        juegos.push_back(Juego("NBA 2K21", "Deporte", 80'000 * 1024, 119'900, 30));
        juegos.push_back(Juego("Sekiro: Shadows Die Twice", "Acción", 50'000 * 1024, 69'900, 25));
        juegos.push_back(Juego("Pokemon Sword and Shield", "Aventura", 160'000 * 1024, 74'900, 50));
        juegos.push_back(Juego("Counter-Strike: Global Offensive", "Acción", 30'000 * 1024, 0, 80));
        juegos.push_back(Juego("The Sims 4", "Simulador", 45'000 * 1024, 69'900, 35));
        juegos.push_back(Juego("Tom Clancy's Rainbow Six Siege", "Acción", 70'000 * 1024, 59'900, 60));
        juegos.push_back(Juego("FIFA 21", "Deporte", 38'000 * 1024, 109'900, 45));
        juegos.push_back(Juego("Planet Zoo", "Simulador", 40'000 * 1024, 44'900, 91));
        juegos.push_back(Juego("Valorant", "Acción", 80'000 * 1024, 0, 70));
        juegos.push_back(Juego("Far Cry 6", "Acción", 100'000 * 1024, 79'900, 30));
        juegos.push_back(Juego("Genshin Impact", "Aventura", 60'000 * 1024, 0, 50));
        juegos.push_back(Juego("Resident Evil Village", "Aventura", 85'000 * 1024, 69'900, 40));
        juegos.push_back(Juego("Bratz Flaunt Your Fashion", "Aventura", 70'000 * 1024, 69'900, 90));
        
    // Configurar la semilla para generar números aleatorios únicos (no utilizado en este fragmento)
        srand(time(0));
    }

    // Método para mostrar la lista de juegos disponibles y ofrecer opciones
    void mostrarListaDeJuegos() {
        system("clear"); // Limpia la consola (dependiente del sistema operativo)

        // Muestra la lista de juegos disponibles numerados
        cout << "Lista de juegos disponibles:\n";
        for (size_t i = 0; i < juegos.size(); ++i) {
            cout << i + 1 << ". " << juegos[i].getNombre() << "\n";
        }

        int opcionJuego;
        cout << "Seleccione un juego para más opciones (0 para volver al menú principal): ";
        cin >> opcionJuego;

        if (opcionJuego >= 1 && opcionJuego <= juegos.size()) {
            opcionesJuego(juegos[opcionJuego - 1]); // Llama a las opciones para el juego seleccionado
        } else if (opcionJuego != 0) {
            cout << "Opción no válida. Volviendo al menú principal.\n";
        }
    }

    // Método que ofrece opciones para un juego específico
    void opcionesJuego(const Juego& juego) {
        int opcion;

        do {
            system("clear");
            cout << "\nOpciones para " << juego.getNombre() << ":\n";
            cout << "1. Mostrar más información\n";
            cout << "2. Añadir licencias al carrito\n";
            cout << "3. Añadir más juegos al carrito\n";
            cout << "4. Comprar carrito\n";
            cout << "5. Vender licencias\n";
            cout << "6. Ver carrito\n";
            cout << "7. Volver al menú principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    system("clear");
                    juego.mostrarInformacion(); // Muestra información detallada del juego
                    cout << "Presiona enter para continuar...";
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    cin.get(); // Esperar a que el usuario presione enter
                    system("clear");
                    break;
                case 2:
                    system("clear");
                    añadirLicenciasAlCarrito(juego); // Permite al usuario agregar licencias al carrito
                    break;
                case 3:
                    system("clear");
                    mostrarListaDeJuegos(); // Muestra nuevamente la lista de juegos para agregar más al carrito
                    system("clear");
                    break;
                case 4:
                    system("clear");
                    comprarCarrito(); // Permite al usuario comprar el contenido del carrito
                    cout << "Presiona enter para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    cin.get(); // Esperar a que el usuario presione enter
                    break;
                case 5:
                    system("clear");
                    venderLicencias(juego); // Permite al usuario vender licencias del juego
                    cout << "Presiona enter para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    cin.get(); // Esperar a que el usuario presione enter
                    break;
                 case 6:
                    system("clear");
                    carrito.mostrarCarrito(); // Llamar al método para mostrar el contenido del carrito
                    cout << "Presiona enter para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    cin.get(); // Esperar a que el usuario presione enter
                    break;
                case 7:
                    cout << "Volviendo al menú principal.\n";
                    break;
                default:
                    cout << "Opción no válida. Inténtelo de nuevo.\n";
            }
        } while (opcion != 7);
    }


// Método para añadir licencias de un juego al carrito
void añadirLicenciasAlCarrito(const Juego& juego) {
    int cantidad;
    cout << "Ingrese la cantidad de licencias que desea añadir al carrito: ";
    cin >> cantidad;

    // Verificar la validez de la cantidad ingresada
    if (cantidad > 0 && cantidad <= juego.getLicenciasDisponibles()) {
        carrito.agregarAlCarrito(juego, cantidad);
        cout << "Se han agregado " << cantidad << " licencias de " << juego.getNombre() << " al carrito.\n";
    } else {
        cout << "Cantidad no válida. Asegúrese de ingresar un número positivo menor o igual a las licencias disponibles.\n";
    }

    cout << "Presiona enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    cin.get(); // Esperar a que el usuario presione enter
    system("clear");
}


// Método para realizar la compra del contenido del carrito
void comprarCarrito() {
    int opcionPago;
    system("clear");

    if (!carrito.carritoVacio()) {
        // Mostrar el saldo disponible y acumulado
        cout << "Saldo disponible: $" << saldoCuenta << "\n";
        cout << "Saldo acumulado: $" << saldoAcumulado << "\n";

        // Calcular el total de la compra
        double total = 0;
        int cantidadRompecabezas = 0;
        int cantidadDeportes = 0;
        int cantidadAccion = 0;

        for (const auto& par : carrito.getJuegosEnCarrito()) {
            const Juego& juego = par.first;
            int cantidad = par.second;
            total += juego.getPrecioColombiano() * cantidad;

            // Contar la cantidad de juegos por categoría
            if (juego.getCategoria() == "Rompecabezas") {
                cantidadRompecabezas += cantidad;
            } else if (juego.getCategoria() == "Deporte") {
                cantidadDeportes += cantidad;
            } else if (juego.getCategoria() == "Acción") {
                cantidadAccion += cantidad;
            }
        }

        // Mostrar el total antes del descuento
        cout << "Total antes del descuento: $" << total << "\n";

        // Aplicar descuentos según las condiciones
        double descuento = 0.0;
        if (cantidadRompecabezas >= 25) {
            // Descuento del 20% por juegos de rompecabezas
            descuento = total * 0.2;
            total -= descuento;
            cout << "Descuento del 20% aplicado por comprar al menos 25 licencias de juegos de rompecabezas: -$" << descuento << "\n";
        } else if (cantidadDeportes >= 20 && cantidadAccion >= 15) {
            // Descuento del 15% por juegos de deportes y acción
            descuento = total * 0.15;
            total -= descuento;
            cout << "Descuento del 15% aplicado por comprar al menos 20 licencias de juegos de deportes y 15 de acción: -$" << descuento << "\n";
        }

        // Mostrar el total después del descuento
        cout << "Total con descuento: $" << total << "\n";

        // Mostrar las opciones de pago
        cout << "Seleccione la forma de pago (1. Saldo disponible, 2. Saldo acumulado, 3. Tarjeta): ";
        cin >> opcionPago;

        // Limpiar el búfer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Comprobar y procesar el pago según la opción elegida
        if (total <= saldoCuenta) {
            // Pagar con saldo disponible
            cout << "¡Compra realizada con éxito! Saldo restante: $" << saldoCuenta << "\n";
        } else if (total <= saldoAcumulado) {
            // Pagar con saldo acumulado
            cout << "¡Compra realizada con éxito! Saldo acumulado restante: $" << saldoAcumulado << "\n";
        } else if (opcionPago == 3) {
            // Pagar con tarjeta
            procesarPagoConTarjeta(total);
        } else {
            cout << "Opción de pago inválida. Vuelva a intentarlo.\n";
        }

        // Vaciar el carrito después de la compra
        carrito.vaciarCarrito();
    } else {
        cout << "El carrito esta vacio. Presiona una tecla para volver al menú principal.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el búfer de entrada
        cin.get(); // Esperar a que el usuario presione Enter
    }
}

// Método para procesar el pago con tarjeta
void procesarPagoConTarjeta(double total) {
    string nombreTitular, numeroTarjeta, fechaVencimiento, codigoSeguridad;

    // Solicitar información de la tarjeta al usuario
    cout << "Ingrese el nombre del titular de la tarjeta: ";
    getline(std::cin, nombreTitular);

    // Solicitar y validar el formato del número de tarjeta
    bool formatoCorrecto = false;
    do {
        cout << "Ingrese el número de la tarjeta (formato XXXX-XXXX-XXXX-XXXX): ";
        getline(std::cin, numeroTarjeta);

        if (numeroTarjeta.length() == 19 && numeroTarjeta[4] == '-' && numeroTarjeta[9] == '-' && numeroTarjeta[14] == '-') {
            formatoCorrecto = true;
        } else {
            cout << "Formato incorrecto. Vuelva a intentarlo.\n";
        }
    } while (!formatoCorrecto);

    // Solicitar la fecha de vencimiento y el código de seguridad
    cout << "Ingrese la fecha de vencimiento (MM/YY): ";
    getline(std::cin, fechaVencimiento);
    cout << "Ingrese el código de seguridad: ";
    getline(std::cin, codigoSeguridad);

    // Simular procesamiento de pago
    cout << "Procesando pago...";
    this_thread::sleep_for(chrono::seconds(2)); // Simular un tiempo de procesamiento

    // Mostrar el resultado del pago
    cout << "\nPago exitoso. Gracias por su compra.\n";
    cout << "Monto pagado: $" << total << "\n";
}




    void venderLicencias(const Juego& juego) {
        int cantidad;
        cout << "Ingrese la cantidad de licencias que desea vender a la App Store: ";
        cin >> cantidad;

        if (cantidad > 0) {
            // Incrementar las licencias disponibles en el inventario
           
            // Devolver el saldo correspondiente al usuario
            double ganancias = juego.getPrecioColombiano() * cantidad;
            saldoCuenta += ganancias;

            cout << "¡Venta realizada con éxito! Ganancias obtenidas: $" << ganancias << " Saldo actual: $" << saldoCuenta << "\n";
        } else {
            cout << "Cantidad no válida. Asegúrese de ingresar un número positivo.\n";
        }
    }

    void recargarSaldo() {
    string nombreTitular, numeroTarjeta, fechaVencimiento, codigoSeguridad;
    double monto;

    cout << "Ingrese el nombre del titular de la tarjeta: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    getline(std::cin, nombreTitular);

    // Solicitar y validar el formato de la tarjeta
    bool formatoCorrecto = false;
    do {
        cout << "Ingrese el número de la tarjeta (formato XXXX-XXXX-XXXX-XXXX): ";
        cin >> numeroTarjeta;

        if (numeroTarjeta.length() == 19 && numeroTarjeta[4] == '-' && numeroTarjeta[9] == '-' && numeroTarjeta[14] == '-') {
            formatoCorrecto = true;
        } else {
            cout << "Formato incorrecto. Vuelva a intentarlo.\n";
        }
    } while (!formatoCorrecto);

    cout << "Ingrese la fecha de vencimiento (MM/YY): ";
    cin >> fechaVencimiento;
    cout << "Ingrese el código de seguridad: ";
    cin >> codigoSeguridad;
    cout << "Ingrese el monto que desea recargar (en pesos colombianos): ";
    cin >> monto;

    // Hacer la conversión a dólares
    double montoEnDolares = monto / 4100.0;

         // Realizar la recarga
        saldoAcumulado += montoEnDolares;

        cout << "Recarga realizada con éxito. Nuevo saldo acumulado: $" << saldoAcumulado << "\n";
    }
       
    
     void actualizarJuegosMasComprados() {
        // Copiar todos los juegos
        juegosMasComprados = juegos;

        // Ordenar los juegos por licencias vendidas de mayor a menor
        sort(juegosMasComprados.begin(), juegosMasComprados.end(), [](const Juego& a, const Juego& b) {
            return a.getLicenciasVendidas() > b.getLicenciasVendidas();
        });
    }

   void mostrarJuegosMasComprados() {
    // Actualizar la lista de juegos más comprados antes de mostrarla
    actualizarJuegosMasComprados();

    cout << "Juegos más comprados:\n";

    bool seMostraronJuegos = false;

    for (const auto& juego : juegosMasComprados) {
        if (juego.getLicenciasVendidas() > 0) {
            cout << juego.getNombre() << " - Licencias vendidas: " << juego.getLicenciasVendidas() << "\n";
            seMostraronJuegos = true;
        }
    }

    if (!seMostraronJuegos) {
        cout << "No hay juegos mas comprados aún.\n";
    }
}

// Método para mostrar el menú principal de la aplicación de la tienda
void mostrarMenuPrincipal() {
    system("clear"); // Limpiar la pantalla

    int opcion; // Variable para almacenar la opción seleccionada por el usuario
    string categoriaFiltro; // Variable para almacenar la categoría de filtro en la opción 4

    // Bucle do-while para mantener el menú hasta que el usuario elija salir (opción 10)
    do {
        system("clear");
        // Mostrar el encabezado del menú
        cout << "\n=== Bienvenido(a) a Rakyrak tu GameStore de confianza ===\n";
        cout << "1. Mostrar lista de juegos\n";
        cout << "2. Filtrar juegos (A-Z)\n";
        cout << "3. Filtrar juegos (Z-A)\n";
        cout << "4. Filtrar juegos por categoría\n";
        cout << "5. Mostrar juegos más comprados\n";
        cout << "6. Mostrar carrito\n";
        cout << "7. Comprar carrito\n";
        cout << "8. Recargar saldo\n";
        cout << "9. Información de Descuentos\n";
        cout << "10. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion; // Obtener la opción del usuario

        // Switch para manejar las diferentes opciones del menú
        switch (opcion) {
            case 1:
                mostrarListaDeJuegos(); // Llamar al método para mostrar la lista de juegos
                break;
            case 2:
                // Filtrar juegos A-Z
                sort(juegos.begin(), juegos.end(), [](const Juego& a, const Juego& b) {
                    return a.getNombre() < b.getNombre();
                });
                mostrarListaDeJuegos(); // Llamar al método para mostrar la lista de juegos
                break;
            case 3:
                // Filtrar juegos Z-A
                sort(juegos.begin(), juegos.end(), [](const Juego& a, const Juego& b) {
                    return a.getNombre() > b.getNombre();
                });
                mostrarListaDeJuegos(); // Llamar al método para mostrar la lista de juegos
                break;
            case 4: {
                system("clear"); // Limpiar la pantalla

                // Mostrar lista numerada de categorías
                cout << "Categorías disponibles:\n";
                vector<std::string> categoriasMostradas;

                size_t categoriaIndex = 1; // Indice para numerar las categorías

                // Iterar sobre los juegos para obtener las categorías únicas
                for (const auto& juego : juegos) {
                    const string& categoria = juego.getCategoria();
                    if (find(categoriasMostradas.begin(), categoriasMostradas.end(), categoria) == categoriasMostradas.end()) {
                        categoriasMostradas.push_back(categoria);
                        cout << categoriaIndex << ". " << categoria << "\n";
                        ++categoriaIndex;
                    }
                }

                // Permitir al usuario seleccionar una categoría
                int opcionCategoria;
                cout << "Seleccione el número de la categoría (0 para volver al menú principal): ";
                cin >> opcionCategoria;
                system("clear"); // Limpiar la pantalla

                // Verificar si la opción de categoría es válida
                if (opcionCategoria >= 1 && opcionCategoria <= categoriasMostradas.size()) {
                    // Filtrar juegos por la categoría seleccionada
                    const string& categoriaSeleccionada = categoriasMostradas[opcionCategoria - 1];
                    cout << "Juegos en la categoría '" << categoriaSeleccionada << "':\n";
                
                    size_t juegoIndex = 1; // Indice para numerar los juegos en la categoría seleccionada
                
                    // Iterar sobre los juegos y mostrar aquellos de la categoría seleccionada
                    for (const auto& juego : juegos) {
                        if (juego.getCategoria() == categoriaSeleccionada) {
                            cout << juegoIndex << ". " << juego.getNombre() << "\n";
                            ++juegoIndex;
                        }
                    }

                    // Permitir al usuario seleccionar un juego de la categoría y mostrar opciones
                    int opcionJuego;
                    cout << "Seleccione un juego para más opciones (0 para volver al menú principal): ";
                    cin >> opcionJuego;

                    // Verificar si la opción de juego es válida
                    if (opcionJuego >= 1 && opcionJuego <= juegoIndex - 1) {
                        // Obtener el juego seleccionado
                        const auto& juegoSeleccionado = find_if(juegos.begin(), juegos.end(), [&](const Juego& juego) {
                            return juego.getCategoria() == categoriaSeleccionada;
                        });

                        opcionesJuego(*juegoSeleccionado); // Llamar al método para mostrar opciones de juego
                    } else if (opcionJuego != 0) {
                        cout << "Opción no válida. Volviendo al menú principal.\n";
                    }
                } else if (opcionCategoria != 0) {
                    cout << "Opción no válida. Volviendo al menú principal.\n";
                }
                break;
            }
            case 5:
                system("clear");
                // Mostrar juegos más comprados
                actualizarJuegosMasComprados();
                mostrarJuegosMasComprados(); // Llamar al método para mostrar juegos más comprados
                cout << "Presiona enter para continuar...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                cin.get(); // Esperar a que el usuario presione enter
                system("clear");
                break;
            case 6:
                system("clear");
                carrito.mostrarCarrito(); // Llamar al método para mostrar el contenido del carrito
                cout << "Presiona enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                cin.get(); // Esperar a que el usuario presione enter
                system("clear");
                break;
            case 7:
                comprarCarrito(); // Llamar al método para comprar el carrito
                break;
            case 8:
                system("clear"); // Limpiar la pantalla
                recargarSaldo(); // Llamar al método para recargar el saldo
                cout << "Presiona enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                cin.get(); // Esperar a que el usuario presione enter
                system("clear");
                break;

            case 9:
                system("clear"); // Limpiar la pantalla
                // Nueva opción para mostrar información de descuentos
                mostrarInformacionDescuentos(); // Llamar al método para mostrar información de descuentos
                break;

            case 10:
                system("clear"); // Limpiar la pantalla
                cout << "Gracias por usar la App Store. ¡Hasta luego!\n";
                break;

            default:
                cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    } while (opcion != 10); // Salir del bucle si la opción seleccionada es 10
}

// Nuevo método para mostrar información de descuentos
void mostrarInformacionDescuentos() {
    cout << "=== Información de Descuentos ===\n";
    cout << "En Rakyrak, ofrecemos descuentos especiales para compras en volumen:\n";
    cout << "- Descuento del 20% por la compra de al menos 25 licencias de juegos de rompecabezas.\n";
    cout << "- Descuento del 15% por la compra de al menos 20 licencias de juegos de deportes y 15 de acción.\n";
    cout << "\n¡Aprovecha estas ofertas y disfruta de tus juegos favoritos!\n";

    // Opción para regresar al menú principal
    cout << "\nPresiona '1' para regresar al menú principal: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        // El usuario eligió regresar al menú principal
        return;
    } else {
        cout << "Opción no válida. Volviendo al menú principal.\n";
    }
}

// Método para mostrar la lista de juegos vendidos
void mostrarListaDeJuegosVendidos() {
    cout << "Lista de juegos vendidos:\n";
    for (const auto& juego : juegos) {
        if (juego.getLicenciasVendidas() > 0) {
            cout << juego.getNombre() << " - Licencias vendidas: " << juego.getLicenciasVendidas() << "\n";
        }
    }
}

// Método para ejecutar la aplicación de la tienda
void ejecutar() {
    cout << "Developers\n";
    cout << "=== Jeison Cadena, Santiago Zipa, Santiago Rodriguez, Yoseph Galvis===\n";
    mostrarMenuPrincipal(); // Llamar al método para mostrar el menú principal
}
};


int main() {
    AppStore appStore;
    appStore.ejecutar();

    return 0;
}



