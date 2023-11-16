#include <iostream>
using namespace std;
#include<string>

string codigodeljuego;

int main ()
{
  string Juego_matriz[4][7];
  // cargue de juegos
  Juego_matriz[0][0] = "FIFA";
  Juego_matriz[0][1] = "SPORTS";
  Juego_matriz[0][2] = "500 Kb";
  Juego_matriz[0][3] = "$100.000 COP";
  Juego_matriz[0][4] = "10";
  Juego_matriz[0][5] = "5";
  Juego_matriz[0][6] = "1";

  Juego_matriz[1][0] = "Call Of Duty";
  Juego_matriz[1][1] = "Shooter en primera persona";
  Juego_matriz[1][2] = "400000 Kb";
  Juego_matriz[1][3] = "$180.000 COP";
  Juego_matriz[1][4] = "100";
  Juego_matriz[1][5] = "30";
  Juego_matriz[1][6] = "2";

  Juego_matriz[2][0] = "GTAV";
  Juego_matriz[2][1] = "Aventura";
  Juego_matriz[2][2] = "500000 Kb";
  Juego_matriz[2][3] = "$250.000 COP";
  Juego_matriz[2][4] = "150";
  Juego_matriz[2][5] = "20";
  Juego_matriz[2][6] = "3";

  Juego_matriz[3][0] = "Forza Horizon 5";
  Juego_matriz[3][1] = "Carreras";
  Juego_matriz[3][2] = "600000 Kb";
  Juego_matriz[3][3] = "$150.000 COP";
  Juego_matriz[3][4] = "80";
  Juego_matriz[3][5] = "10";
  Juego_matriz[3][6] = "4";

  //Bienvenida//
  cout << "                                                 Bienvenido(a) a Rakyrak tu GameStore de confianza " "\n";
  cout << "Estos son los juegos Disponibles" "\n";


  //Presentacion Juegos
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 1; j++)
	{
	  cout << "Nombre: " << Juego_matriz[i][0] << "\n";
	  cout << "Codigo Juego: " << Juego_matriz[i][6] << "\n";
	  //cout<< "Imagen: "<< matriz [i][j].imagen <<"\n\n";
	}
    }

  //seleccion juego
  cout << "Digite el codigo del juego" "\n";
  cin >> codigodeljuego;
  system("clear");

  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 7; j++)
	    {
        	  if (Juego_matriz[i][j] == codigodeljuego)
        	        {
        	      cout << "Nombre: " << Juego_matriz[i][0] << "\n";
        	      cout << "Categoria: " << Juego_matriz[i][1] << "\n";
        	      cout << "Peso Kb: " << Juego_matriz[i][2] << "\n";
        	      cout << "Precio: " << Juego_matriz[i][3] << "\n";
        	      cout << "Licencias disponibles: " << Juego_matriz[i][4] << "\n";
        	      cout << "Licencias vendidas: " << Juego_matriz[i][5] << "\n";

                  // Opción de compra
                  string opcion_compra;
                  cout << "¿Desea comprar este juego? (Si/No)" "\n";
                  cin >> opcion_compra;
                  if (opcion_compra == "Si" || opcion_compra == "si") {
                      int licencias_disponibles = stoi(Juego_matriz[i][4]);
                      if (licencias_disponibles > 0) {
                          licencias_disponibles--;
                          Juego_matriz[i][4] = to_string(licencias_disponibles);
                          cout << "¡Compra exitosa! Licencias disponibles ahora: " << Juego_matriz[i][4] << "\n";
                      } else {
                          cout << "Lo siento, no hay licencias disponibles para este juego." "\n";
                      }
                  } else if (opcion_compra == "No" || opcion_compra == "n") {
                      cout << "Ok, no se realizó ninguna compra." "\n";
                  } else {
                      cout << "Opción no válida. Por favor, ingrese Si para comprar o No para no comprar." "\n";
                  }
        	        }
	    }
    }

}



