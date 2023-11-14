#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

// Definición de la clase Juego que representa un videojuego
class Juego {
private:
    std::string nombre;
    std::string categoria;
    int tamano;  // en kilobytes
    double precio;
    int licenciasDisponibles;
    int licenciasVendidas;

public:
    // Constructor de la clase Juego
    Juego(std::string nombre, std::string categoria, int tamano, double precio, int licenciasDisponibles)
        : nombre(nombre), categoria(categoria), tamano(tamano), precio(precio), licenciasDisponibles(licenciasDisponibles), licenciasVendidas(0) {}

    // Métodos para obtener información sobre el juego
    std::string getNombre() const {
        return nombre;
    }

    std::string getCategoria() const {
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

    // Método para vender licencias del juego
    void venderLicencias(int cantidad) {
        if (cantidad <= licenciasDisponibles) {
            licenciasDisponibles -= cantidad;
            licenciasVendidas += cantidad;
            std::cout << "Se han vendido " << cantidad << " licencias de " << nombre << ". Licencias restantes: " << licenciasDisponibles << "\n";
        } else {
            std::cout << "No hay suficientes licencias disponibles para vender de " << nombre << ". Licencias disponibles: " << licenciasDisponibles << "\n";
        }
    }

    // Método para mostrar información del juego
    void mostrarInformacion() const {
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Categoría: " << categoria << "\n";
        std::cout << "Tamaño: " << tamano << " KB (" << getTamanoGB() << " GB)\n";
        std::cout << "Precio: $" << precio << " (USD: $" << getPrecioDolar() << ")\n";
        std::cout << "Licencias Disponibles: " << licenciasDisponibles << "\n";
        std::cout << "Licencias Vendidas: " << licenciasVendidas << "\n";
    }
};

// Definición de la clase Carrito que representa el carrito de compras
class Carrito {
private:
    std::vector<std::pair<Juego, int>> juegosEnCarrito;

public:
    // Método para agregar licencias de un juego al carrito
    void agregarAlCarrito(const Juego& juego, int cantidad) {
        if (cantidad <= juego.getLicenciasDisponibles()) {
            juegosEnCarrito.push_back(std::make_pair(juego, cantidad));
            std::cout << "Se han agregado " << cantidad << " licencias de " << juego.getNombre() << " al carrito.\n";
        } else {
            std::cout << "No hay suficientes licencias disponibles para agregar al carrito de " << juego.getNombre() << "\n";
        }
    }

    // Método para mostrar el contenido del carrito
    void mostrarCarrito() const {
        std::cout << "Juegos en el carrito:\n";
        double totalPesos = 0;
        double totalDolares = 0;

        for (const auto& par : juegosEnCarrito) {
            const Juego& juego = par.first;
            int cantidad = par.second;

            std::cout << "- " << cantidad << " licencias de " << juego.getNombre() << " - Valor: $" << juego.getPrecioColombiano() * cantidad
                      << " (USD: $" << juego.getPrecioDolar() * cantidad << ")\n";

            totalPesos += juego.getPrecioColombiano() * cantidad;
            totalDolares += juego.getPrecioDolar() * cantidad;
        }

        std::cout << "Total en pesos colombianos: $" << totalPesos << "\n";
        std::cout << "Total en dólares: $" << totalDolares << "\n";
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
    const std::vector<std::pair<Juego, int>>& getJuegosEnCarrito() const {
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
    std::vector<Juego> juegos;            // Lista de juegos disponibles
    std::vector<Juego> juegosMasComprados; // Lista de juegos más comprados (aún no se utiliza)
    Carrito carrito;                       // Carrito de compras del usuario
    double saldoCuenta;                    // Saldo del usuario
    double saldoAcumulado;                 // Saldo acumulado para compras con tarjeta

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
        std::srand(std::time(0));
    }

    // Método para mostrar la lista de juegos disponibles y ofrecer opciones
    void mostrarListaDeJuegos() {
        std::system("clear");  // Limpia la consola (dependiente del sistema operativo)

        // Muestra la lista de juegos disponibles numerados
        std::cout << "Lista de juegos disponibles:\n";
        for (size_t i = 0; i < juegos.size(); ++i) {
            std::cout << i + 1 << ". " << juegos[i].getNombre() << "\n";
        }

        int opcionJuego;
        std::cout << "Seleccione un juego para más opciones (0 para volver al menú principal): ";
        std::cin >> opcionJuego;

        if (opcionJuego >= 1 && opcionJuego <= juegos.size()) {
            opcionesJuego(juegos[opcionJuego - 1]);  // Llama a las opciones para el juego seleccionado
        } else if (opcionJuego != 0) {
            std::cout << "Opción no válida. Volviendo al menú principal.\n";
        }
    }

    // Método que ofrece opciones para un juego específico
    void opcionesJuego(const Juego& juego) {
        int opcion;

        do {
            std::system("clear");
            std::cout << "\nOpciones para " << juego.getNombre() << ":\n";
            std::cout << "1. Mostrar más información\n";
            std::cout << "2. Añadir licencias al carrito\n";
            std::cout << "3. Añadir más juegos al carrito\n";
            std::cout << "4. Comprar carrito\n";
            std::cout << "5. Vender licencias\n";
            std::cout << "6. Ver carrito\n";
            std::cout << "7. Volver al menú principal\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1:
                    std::system("clear");
                    juego.mostrarInformacion();  // Muestra información detallada del juego
                    std::cout << "Presiona enter para continuar...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    std::cin.get(); // Esperar a que el usuario presione enter
                    std::system("clear");
                    break;
                case 2:
                    std::system("clear");
                    añadirLicenciasAlCarrito(juego);  // Permite al usuario agregar licencias al carrito
                    break;
                case 3:
                    std::system("clear");
                    mostrarListaDeJuegos();  // Muestra nuevamente la lista de juegos para agregar más al carrito
                    std::system("clear");
                    break;
                case 4:
                    std::system("clear");
                    comprarCarrito();  // Permite al usuario comprar el contenido del carrito
                    std::cout << "Presiona enter para continuar...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    std::cin.get(); // Esperar a que el usuario presione enter
                    break;
                case 5:
                    std::system("clear");
                    venderLicencias(juego);  // Permite al usuario vender licencias del juego
                    std::cout << "Presiona enter para continuar...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    std::cin.get(); // Esperar a que el usuario presione enter
                    break;
                 case 6:
                    std::system("clear");
                    carrito.mostrarCarrito();  // Llamar al método para mostrar el contenido del carrito
                    std::cout << "Presiona enter para continuar...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                    std::cin.get(); // Esperar a que el usuario presione enter
                    break;
                case 7:
                    std::cout << "Volviendo al menú principal.\n";
                    break;
                default:
                    std::cout << "Opción no válida. Inténtelo de nuevo.\n";
            }
        } while (opcion != 7);
    }


// Método para añadir licencias de un juego al carrito
void añadirLicenciasAlCarrito(const Juego& juego) {
    int cantidad;
    std::cout << "Ingrese la cantidad de licencias que desea añadir al carrito: ";
    std::cin >> cantidad;

    // Verificar la validez de la cantidad ingresada
    if (cantidad > 0 && cantidad <= juego.getLicenciasDisponibles()) {
        carrito.agregarAlCarrito(juego, cantidad);
        std::cout << "Se han agregado " << cantidad << " licencias de " << juego.getNombre() << " al carrito.\n";
    } else {
        std::cout << "Cantidad no válida. Asegúrese de ingresar un número positivo menor o igual a las licencias disponibles.\n";
    }

    std::cout << "Presiona enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    std::cin.get(); // Esperar a que el usuario presione enter
    std::system("clear");
}


// Método para realizar la compra del contenido del carrito
void comprarCarrito() {
    int opcionPago;
    std::system("clear");

    if (!carrito.carritoVacio()) {
        // Mostrar el saldo disponible y acumulado
        std::cout << "Saldo disponible: $" << saldoCuenta << "\n";
        std::cout << "Saldo acumulado: $" << saldoAcumulado << "\n";

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
        std::cout << "Total antes del descuento: $" << total << "\n";

        // Aplicar descuentos según las condiciones
        double descuento = 0.0;
        if (cantidadRompecabezas >= 25) {
            // Descuento del 20% por juegos de rompecabezas
            descuento = total * 0.2;
            total -= descuento;
            std::cout << "Descuento del 20% aplicado por comprar al menos 25 licencias de juegos de rompecabezas: -$" << descuento << "\n";
        } else if (cantidadDeportes >= 20 && cantidadAccion >= 15) {
            // Descuento del 15% por juegos de deportes y acción
            descuento = total * 0.15;
            total -= descuento;
            std::cout << "Descuento del 15% aplicado por comprar al menos 20 licencias de juegos de deportes y 15 de acción: -$" << descuento << "\n";
        }

        // Mostrar el total después del descuento
        std::cout << "Total con descuento: $" << total << "\n";

        // Mostrar las opciones de pago
        std::cout << "Seleccione la forma de pago (1. Saldo disponible, 2. Saldo acumulado, 3. Tarjeta): ";
        std::cin >> opcionPago;

        // Limpiar el búfer de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Comprobar y procesar el pago según la opción elegida
        if (total <= saldoCuenta) {
            // Pagar con saldo disponible
            std::cout << "¡Compra realizada con éxito! Saldo restante: $" << saldoCuenta << "\n";
        } else if (total <= saldoAcumulado) {
            // Pagar con saldo acumulado
            std::cout << "¡Compra realizada con éxito! Saldo acumulado restante: $" << saldoAcumulado << "\n";
        } else if (opcionPago == 3) {
            // Pagar con tarjeta
            procesarPagoConTarjeta(total);
        } else {
            std::cout << "Opción de pago inválida. Vuelva a intentarlo.\n";
        }

        // Vaciar el carrito después de la compra
        carrito.vaciarCarrito();
    } else {
        std::cout << "El carrito esta vacio. Presiona una tecla para volver al menú principal.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpiar el búfer de entrada
        std::cin.get();  // Esperar a que el usuario presione Enter
    }
}

// Método para procesar el pago con tarjeta
void procesarPagoConTarjeta(double total) {
    std::string nombreTitular, numeroTarjeta, fechaVencimiento, codigoSeguridad;

    // Solicitar información de la tarjeta al usuario
    std::cout << "Ingrese el nombre del titular de la tarjeta: ";
    std::getline(std::cin, nombreTitular);

    // Solicitar y validar el formato del número de tarjeta
    bool formatoCorrecto = false;
    do {
        std::cout << "Ingrese el número de la tarjeta (formato XXXX-XXXX-XXXX-XXXX): ";
        std::getline(std::cin, numeroTarjeta);

        if (numeroTarjeta.length() == 19 && numeroTarjeta[4] == '-' && numeroTarjeta[9] == '-' && numeroTarjeta[14] == '-') {
            formatoCorrecto = true;
        } else {
            std::cout << "Formato incorrecto. Vuelva a intentarlo.\n";
        }
    } while (!formatoCorrecto);

    // Solicitar la fecha de vencimiento y el código de seguridad
    std::cout << "Ingrese la fecha de vencimiento (MM/YY): ";
    std::getline(std::cin, fechaVencimiento);
    std::cout << "Ingrese el código de seguridad: ";
    std::getline(std::cin, codigoSeguridad);

    // Simular procesamiento de pago
    std::cout << "Procesando pago...";
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Simular un tiempo de procesamiento

    // Mostrar el resultado del pago
    std::cout << "\nPago exitoso. Gracias por su compra.\n";
    std::cout << "Monto pagado: $" << total << "\n";
}




    void venderLicencias(const Juego& juego) {
        int cantidad;
        std::cout << "Ingrese la cantidad de licencias que desea vender a la App Store: ";
        std::cin >> cantidad;

        if (cantidad > 0) {
            // Incrementar las licencias disponibles en el inventario
           
            // Devolver el saldo correspondiente al usuario
            double ganancias = juego.getPrecioColombiano() * cantidad;
            saldoCuenta += ganancias;

            std::cout << "¡Venta realizada con éxito! Ganancias obtenidas: $" << ganancias << " Saldo actual: $" << saldoCuenta << "\n";
        } else {
            std::cout << "Cantidad no válida. Asegúrese de ingresar un número positivo.\n";
        }
    }

    void recargarSaldo() {
    std::string nombreTitular, numeroTarjeta, fechaVencimiento, codigoSeguridad;
    double monto;

    std::cout << "Ingrese el nombre del titular de la tarjeta: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpiar el buffer de entrada
    std::getline(std::cin, nombreTitular);

    // Solicitar y validar el formato de la tarjeta
    bool formatoCorrecto = false;
    do {
        std::cout << "Ingrese el número de la tarjeta (formato XXXX-XXXX-XXXX-XXXX): ";
        std::cin >> numeroTarjeta;

        if (numeroTarjeta.length() == 19 && numeroTarjeta[4] == '-' && numeroTarjeta[9] == '-' && numeroTarjeta[14] == '-') {
            formatoCorrecto = true;
        } else {
            std::cout << "Formato incorrecto. Vuelva a intentarlo.\n";
        }
    } while (!formatoCorrecto);

    std::cout << "Ingrese la fecha de vencimiento (MM/YY): ";
    std::cin >> fechaVencimiento;
    std::cout << "Ingrese el código de seguridad: ";
    std::cin >> codigoSeguridad;
    std::cout << "Ingrese el monto que desea recargar (en pesos colombianos): ";
    std::cin >> monto;

    // Hacer la conversión a dólares
    double montoEnDolares = monto / 4100.0;

         // Realizar la recarga
        saldoAcumulado += montoEnDolares;

        std::cout << "Recarga realizada con éxito. Nuevo saldo acumulado: $" << saldoAcumulado << "\n";
    }
       
    
     void actualizarJuegosMasComprados() {
        // Copiar todos los juegos
        juegosMasComprados = juegos;

        // Ordenar los juegos por licencias vendidas de mayor a menor
        std::sort(juegosMasComprados.begin(), juegosMasComprados.end(), [](const Juego& a, const Juego& b) {
            return a.getLicenciasVendidas() > b.getLicenciasVendidas();
        });
    }

   void mostrarJuegosMasComprados() {
    // Actualizar la lista de juegos más comprados antes de mostrarla
    actualizarJuegosMasComprados();

    std::cout << "Juegos más comprados:\n";

    bool seMostraronJuegos = false;

    for (const auto& juego : juegosMasComprados) {
        if (juego.getLicenciasVendidas() > 0) {
            std::cout << juego.getNombre() << " - Licencias vendidas: " << juego.getLicenciasVendidas() << "\n";
            seMostraronJuegos = true;
        }
    }

    if (!seMostraronJuegos) {
        std::cout << "No hay juegos mas comprados aún.\n";
    }
}

// Método para mostrar el menú principal de la aplicación de la tienda
void mostrarMenuPrincipal() {
    std::system("clear");  // Limpiar la pantalla

    int opcion;  // Variable para almacenar la opción seleccionada por el usuario
    std::string categoriaFiltro;  // Variable para almacenar la categoría de filtro en la opción 4

    // Bucle do-while para mantener el menú hasta que el usuario elija salir (opción 10)
    do {
        std::system("clear");
        // Mostrar el encabezado del menú
        std::cout << "\n=== Bienvenido(a) a Rakyrak tu GameStore de confianza ===\n";
        std::cout << "1. Mostrar lista de juegos\n";
        std::cout << "2. Filtrar juegos (A-Z)\n";
        std::cout << "3. Filtrar juegos (Z-A)\n";
        std::cout << "4. Filtrar juegos por categoría\n";
        std::cout << "5. Mostrar juegos más comprados\n";
        std::cout << "6. Mostrar carrito\n";
        std::cout << "7. Comprar carrito\n";
        std::cout << "8. Recargar saldo\n";
        std::cout << "9. Información de Descuentos\n";
        std::cout << "10. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;  // Obtener la opción del usuario

        // Switch para manejar las diferentes opciones del menú
        switch (opcion) {
            case 1:
                mostrarListaDeJuegos();  // Llamar al método para mostrar la lista de juegos
                break;
            case 2:
                // Filtrar juegos A-Z
                std::sort(juegos.begin(), juegos.end(), [](const Juego& a, const Juego& b) {
                    return a.getNombre() < b.getNombre();
                });
                mostrarListaDeJuegos();  // Llamar al método para mostrar la lista de juegos
                break;
            case 3:
                // Filtrar juegos Z-A
                std::sort(juegos.begin(), juegos.end(), [](const Juego& a, const Juego& b) {
                    return a.getNombre() > b.getNombre();
                });
                mostrarListaDeJuegos();  // Llamar al método para mostrar la lista de juegos
                break;
            case 4: {
                std::system("clear");  // Limpiar la pantalla

                // Mostrar lista numerada de categorías
                std::cout << "Categorías disponibles:\n";
                std::vector<std::string> categoriasMostradas;

                size_t categoriaIndex = 1;  // Indice para numerar las categorías

                // Iterar sobre los juegos para obtener las categorías únicas
                for (const auto& juego : juegos) {
                    const std::string& categoria = juego.getCategoria();
                    if (std::find(categoriasMostradas.begin(), categoriasMostradas.end(), categoria) == categoriasMostradas.end()) {
                        categoriasMostradas.push_back(categoria);
                        std::cout << categoriaIndex << ". " << categoria << "\n";
                        ++categoriaIndex;
                    }
                }

                // Permitir al usuario seleccionar una categoría
                int opcionCategoria;
                std::cout << "Seleccione el número de la categoría (0 para volver al menú principal): ";
                std::cin >> opcionCategoria;
                std::system("clear");  // Limpiar la pantalla

                // Verificar si la opción de categoría es válida
                if (opcionCategoria >= 1 && opcionCategoria <= categoriasMostradas.size()) {
                    // Filtrar juegos por la categoría seleccionada
                    const std::string& categoriaSeleccionada = categoriasMostradas[opcionCategoria - 1];
                    std::cout << "Juegos en la categoría '" << categoriaSeleccionada << "':\n";
                
                    size_t juegoIndex = 1;  // Indice para numerar los juegos en la categoría seleccionada
                
                    // Iterar sobre los juegos y mostrar aquellos de la categoría seleccionada
                    for (const auto& juego : juegos) {
                        if (juego.getCategoria() == categoriaSeleccionada) {
                            std::cout << juegoIndex << ". " << juego.getNombre() << "\n";
                            ++juegoIndex;
                        }
                    }

                    // Permitir al usuario seleccionar un juego de la categoría y mostrar opciones
                    int opcionJuego;
                    std::cout << "Seleccione un juego para más opciones (0 para volver al menú principal): ";
                    std::cin >> opcionJuego;

                    // Verificar si la opción de juego es válida
                    if (opcionJuego >= 1 && opcionJuego <= juegoIndex - 1) {
                        // Obtener el juego seleccionado
                        const auto& juegoSeleccionado = std::find_if(juegos.begin(), juegos.end(), [&](const Juego& juego) {
                            return juego.getCategoria() == categoriaSeleccionada;
                        });

                        opcionesJuego(*juegoSeleccionado);  // Llamar al método para mostrar opciones de juego
                    } else if (opcionJuego != 0) {
                        std::cout << "Opción no válida. Volviendo al menú principal.\n";
                    }
                } else if (opcionCategoria != 0) {
                    std::cout << "Opción no válida. Volviendo al menú principal.\n";
                }
                break;
            }
            case 5:
                std::system("clear");
                // Mostrar juegos más comprados
                actualizarJuegosMasComprados();
                mostrarJuegosMasComprados();  // Llamar al método para mostrar juegos más comprados
                std::cout << "Presiona enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                std::cin.get(); // Esperar a que el usuario presione enter
                std::system("clear");
                break;
            case 6:
                std::system("clear");
                carrito.mostrarCarrito();  // Llamar al método para mostrar el contenido del carrito
                std::cout << "Presiona enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                std::cin.get(); // Esperar a que el usuario presione enter
                std::system("clear");
                break;
            case 7:
                comprarCarrito();  // Llamar al método para comprar el carrito
                break;
            case 8:
                std::system("clear");  // Limpiar la pantalla
                recargarSaldo();  // Llamar al método para recargar el saldo
                std::cout << "Presiona enter para continuar...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
                std::cin.get(); // Esperar a que el usuario presione enter
                std::system("clear");
                break;

            case 9:
                std::system("clear");  // Limpiar la pantalla
                // Nueva opción para mostrar información de descuentos
                mostrarInformacionDescuentos();  // Llamar al método para mostrar información de descuentos
                break;

            case 10:
                std::system("clear");  // Limpiar la pantalla
                std::cout << "Gracias por usar la App Store. ¡Hasta luego!\n";
                break;

            default:
                std::cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    } while (opcion != 10);  // Salir del bucle si la opción seleccionada es 10
}

// Nuevo método para mostrar información de descuentos
void mostrarInformacionDescuentos() {
    std::cout << "=== Información de Descuentos ===\n";
    std::cout << "En Rakyrak, ofrecemos descuentos especiales para compras en volumen:\n";
    std::cout << "- Descuento del 20% por la compra de al menos 25 licencias de juegos de rompecabezas.\n";
    std::cout << "- Descuento del 15% por la compra de al menos 20 licencias de juegos de deportes y 15 de acción.\n";
    std::cout << "\n¡Aprovecha estas ofertas y disfruta de tus juegos favoritos!\n";

    // Opción para regresar al menú principal
    std::cout << "\nPresiona '1' para regresar al menú principal: ";
    int opcion;
    std::cin >> opcion;

    if (opcion == 1) {
        // El usuario eligió regresar al menú principal
        return;
    } else {
        std::cout << "Opción no válida. Volviendo al menú principal.\n";
    }
}

// Método para mostrar la lista de juegos vendidos
void mostrarListaDeJuegosVendidos() {
    std::cout << "Lista de juegos vendidos:\n";
    for (const auto& juego : juegos) {
        if (juego.getLicenciasVendidas() > 0) {
            std::cout << juego.getNombre() << " - Licencias vendidas: " << juego.getLicenciasVendidas() << "\n";
        }
    }
}

// Método para ejecutar la aplicación de la tienda
void ejecutar() {
    std::cout << "Developers\n";
    std::cout << "=== Jeison Cadena, Santiago Zipa, Santiago Rodriguez, Yoseph Galvis===\n";
    mostrarMenuPrincipal();  // Llamar al método para mostrar el menú principal
}
};


int main() {
    AppStore appStore;
    appStore.ejecutar();

    return 0;
}



