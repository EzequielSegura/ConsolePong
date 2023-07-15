#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;

// Declarar Variables
string matriz[21][71];
int jugadores = 0;

int jugadorY = 9;
int enemigoY = 9;

int pelotaX = 10;
int pelotaY = 35;
int velocidadY = 1;
int velocidadX = 1;

int puntaje1 = 0;
int puntaje2 = 0;

int contadorFrames = 0;

// Declarar Funciones
void Start();
void DibujarEscenario();
void DibujarMenuInicial();
void Update();
void Jugador();
void Enemigo();
void Pelota();
bool ComprobarGanador();

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void OcultarPuntero() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void SetConsoleColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void VerificarValores() {
	gotoxy(72, 1);
	printf("Jugador Y %d", jugadorY);
	gotoxy(72, 2);
	printf("Enemigo Y %d", enemigoY);
	gotoxy(72, 3);
	printf("Pelota X %d", pelotaX);
	gotoxy(72, 4);
	printf("Pelota Y %d", pelotaY);
	gotoxy(72, 5);
	printf("Fames Totales %d", contadorFrames);
}

void Marcador() {
	gotoxy(33, 2);
	printf("%d", puntaje1);
	gotoxy(37, 2);
	printf("%d", puntaje2);
}

int main()
{
	OcultarPuntero();
	Start();
	Update();
}

void Start() 
{
	DibujarMenuInicial();
}

void DibujarMenuInicial() {
	system("cls");
	for (int i = 0; i <= 19; i++)
	{
		for (int j = 1; j <= 69; j++)
		{
			if (i == 0 || j == 1 || i == 19 || j == 69)
			{
				gotoxy(j, i);
				printf(".");
			}
		}
	}

	gotoxy(28, 3);
	printf("PONG IN CONSOLE");

	gotoxy(52, 18);
	printf("Made by Sticman");

	while (!_kbhit()) {
		Sleep(400); 
		gotoxy(29, 10);
		printf("             ");  
		Sleep(400);
		gotoxy(29, 10);
		printf("Press Any Key");
	}
	_getch();

	gotoxy(29, 10);
	printf("             ");
	gotoxy(28, 10);
	printf("1 or 2 Players?");
	jugadores = _getch() - '0';
	while (jugadores != 1 && jugadores != 2) {
		gotoxy(18, 12);
		printf("Invalid input, Please enter 1 or 2");
		jugadores = _getch() - '0';
	}
	system("cls");
}

void DibujarEscenario() {
	for (int i = 0; i <= 19; i++)
	{
		for (int j = 1; j <= 69; j++)
		{
			if (i == 0 || j == 1 || i == 19 || j == 69)
			{
				gotoxy(j, i);
				printf(".");
			}
		}
	}

	for (int i = 1; i < 20; i++)
	{
		gotoxy(35, i);
		printf("|");
	}

	if (jugadores == 1)
	{
		gotoxy(72, 8);
		printf("W to Up");
		gotoxy(72, 10);
		printf("S to Down");

		gotoxy(72, 19);
		printf("R to reset the game");
	}
	else {
		gotoxy(72, 2);
		printf("PLAYER 1");
		gotoxy(72, 4);
		printf("W to Up");
		gotoxy(72, 5);
		printf("S to Down");

		gotoxy(72, 10);
		printf("PLAYER 2");
		gotoxy(72, 12);
		printf("Key Up to Up");
		gotoxy(72, 13);
		printf("Key Down to Down");

		gotoxy(72, 19);
		printf("R to reset the game");
	}
}

void MensajeDeGanador(string jugador) {
	for (int i = 0; i <= 19; i++)
	{
		for (int j = 1; j <= 69; j++)
		{
			if (i == 0 || j == 1 || i == 19 || j == 69)
			{
				gotoxy(j, i);
				printf(".");
			}
		}
	}

	while (!_kbhit()) {
		Sleep(400);
		gotoxy(29, 10);
		printf("             ");
		Sleep(400);
		gotoxy(29, 10);
		std::cout << jugador << " Win";
	}
	_getch();
	system("cls");
}

void ReiniciarJuego() {
	if ((GetAsyncKeyState('R') & 0x8000) && jugadorY > 1) {
		jugadores = 0;
		jugadorY = 9;
		enemigoY = 9;
		pelotaX = 10;
		pelotaY = 35;
		velocidadY = 1;
		velocidadX = 1;
		puntaje1 = 0;
		puntaje2 = 0;

		DibujarMenuInicial();
	}
}

void Update() 
{
	while (true) {
		DibujarEscenario();
		Jugador();
		Enemigo();
		Pelota();
		// VerificarValores();
		Marcador();
		contadorFrames++;
		Sleep(60);
		if (ComprobarGanador()) {
			break;
		}
		ReiniciarJuego();
	}

	system("cls");

	if (puntaje1 > puntaje2)
	{
		MensajeDeGanador("Jugador 1");
	}
	else
	{
		MensajeDeGanador("Jugador 2");
	}
}

void Jugador() {
	// Borrar jugador en la posición anterior
	for (int i = jugadorY; i <= jugadorY + 3; i++) {
		gotoxy(5, i);
		printf(" ");
	}

	// Verificar si una tecla está siendo presionada
	if ((GetAsyncKeyState('W') & 0x8000) && jugadorY > 1) {  // Tecla "W"
		jugadorY--;
	}
	else if ((GetAsyncKeyState('S') & 0x8000) && jugadorY < 15) {  // Tecla "S"
		jugadorY++;
	}


	// Dibujar jugador en la nueva posición
	for (int i = jugadorY; i <= jugadorY + 3; i++) {
		gotoxy(5, i);
		printf("|");
	}
}

void Enemigo() {
	// Borrar enemigo en la posición anterior
	for (int i = enemigoY; i <= enemigoY + 3; i++) {
		gotoxy(65, i);
		printf(" ");
	}

	// Juego automatico del enemigo
	if (jugadores == 1) {
		if (velocidadX > 0 && pelotaY > 20) {
			// Seguir Pelota
			if (pelotaX > enemigoY + 3) {
				enemigoY++;
			}
			if (pelotaX < enemigoY) {
				enemigoY--;
			}
		}
	
	}

	// Juego manual del enemigo
	// Verificar si una tecla está siendo presionada
	if (GetAsyncKeyState(VK_UP) & 0x8000 && enemigoY > 1) {  // Flecha hacia arriba
		enemigoY--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && enemigoY < 15) {  // Flecha hacia abajo
		enemigoY++;
	}

	// Dibujar enemigo en la nueva posición
	for (int i = enemigoY; i <= enemigoY + 3; i++) {
		gotoxy(65, i);
		printf("|");
	}
}


void Pelota() {
	// Borrar pelota en la posición anterior
	gotoxy(pelotaY, pelotaX);
	printf(" ");

	// Mover Pelota 
	pelotaX += velocidadY;
	pelotaY += velocidadX;

	// Marcar Puntos
	if (pelotaY <= 2) {
		puntaje2++;
		pelotaX = 10;
		pelotaY = 35;
		Sleep(1000);
		velocidadX *= -1;
	}
	else if (pelotaY >= 68) {
		puntaje1++;
		pelotaX = 10;
		pelotaY = 35;
		Sleep(1000);
		velocidadX *= -1;
	}
	// Rebotar Paredes
	else if (pelotaX <= 1 || pelotaX >= 18) {
		velocidadY *= -1;
	}
	
	// Colisión con Jugador
	if (pelotaY == 6 && (pelotaX >= jugadorY && pelotaX <= jugadorY + 3)) {
		velocidadX *= -1;
	}

	// Colisión con Enemigo
	if (pelotaY == 64 && (pelotaX >= enemigoY && pelotaX <= enemigoY + 3)) {
		velocidadX *= -1;
	}

	// Dibujar pelota en la nueva posición
	gotoxy(pelotaY, pelotaX);
	printf("*");

}

bool ComprobarGanador() {
	if (puntaje1 == 1 || puntaje2 == 1) {
		return true;
	}
	else {
		return false;
	}
}