#include <iostream>
#include <string>

using namespace std;

struct Juego {
    string nombre;
    string categoria;
    string peso;
    string precio;
    int licencias_disponibles;
    int licencias_vendidas;
    string codigo;
};

struct Descuento {
    int licencias_sports;
    int licencias_shooter;
    int licencias_aventura;
};

int main() {
    Juego juegos[4] = {
        {"FIFA", "SPORTS", "500 Kb", "$100.000 COP", 100, 5, "1"},
        {"Call Of Duty", "Shooter en primera persona", "400000 Kb", "$180.000 COP", 100, 30, "2"},
        {"GTAV", "Aventura", "500000 Kb", "$250.000 COP", 150, 20, "3"},
        {"Forza Horizon 5", "Carreras", "600000 Kb", "$150.000 COP", 100, 10, "4"}
    };

    Descuento descuento = {0, 0, 0};

    cout << "                                              Bienvenido(a) a Rakyrak tu GameStore de confianza\n";
    
    cout << "\nEstas son las opciones de descuento disponibles:\n";
    cout << "1. Si compras al menos 25 licencias de juegos de SPORTS, obtendrás un descuento del 20% en tu pedido total.\n";
    cout << "2. Si compras al menos 20 licencias de juegos de Shooter en primera persona y 15 licencias de juegos de Aventura, obtendrás un descuento del 15% en tu pedido total.\n";
    
    char opcion_otro_juego = 'S';
    
    while (opcion_otro_juego == 'S' || opcion_otro_juego == 's') {
        cout << "\nEstos son los juegos Disponibles\n";

        for (int i = 0; i < 4; i++) {
            cout << "Nombre: " << juegos[i].nombre << "\n";
            cout << "Codigo Juego: " << juegos[i].codigo << "\n";
        }

        string codigodeljuego;
        cout << "\nDigite el codigo del juego\n";
        cin >> codigodeljuego;

        for (int i = 0; i < 4; i++) {
            if (juegos[i].codigo == codigodeljuego) {
                cout << "\nNombre: " << juegos[i].nombre << "\n";
                cout << "Categoria: " << juegos[i].categoria << "\n";
                cout << "Peso Kb: " << juegos[i].peso << "\n";
                cout << "Precio: " << juegos[i].precio << "\n";
                cout << "Licencias disponibles: " << juegos[i].licencias_disponibles << "\n";
                cout << "Licencias vendidas: " << juegos[i].licencias_vendidas << "\n";

                int cantidad_compra;
                cout << "\n¿Cuántas licencias desea comprar?\n";
                cin >> cantidad_compra;

                if (cantidad_compra <= juegos[i].licencias_disponibles) {
                    juegos[i].licencias_disponibles -= cantidad_compra;
                    cout << "\n¡Compra exitosa! Licencias disponibles ahora: "
                         << juegos[i].licencias_disponibles
                         << "\n";

                    if (juegos[i].categoria == "SPORTS") {
                        descuento.licencias_sports += cantidad_compra;
                    } else if (juegos[i].categoria == "Shooter en primera persona") {
                        descuento.licencias_shooter += cantidad_compra;
                    } else if (juegos[i].categoria == "Aventura") {
                        descuento.licencias_aventura += cantidad_compra;
                    }
                } else {
                    cout << "\nLo siento, no hay suficientes licencias disponibles para este juego.\n";
                }
            }
        }

        cout << "\n¿Desea comprar licencias de otro juego? (S/N)\n";
        cin >> opcion_otro_juego;
    }

    if (descuento.licencias_sports >= 25) {
        cout << "\n¡Felicidades! Has obtenido un descuento del 20% en tu pedido total.\n";
    } else if (descuento.licencias_shooter >= 20 && descuento.licencias_aventura >= 15) {
        cout << "\n¡Felicidades! Has obtenido un descuento del 15% en tu pedido total.\n";
    }

    return 0;
}



