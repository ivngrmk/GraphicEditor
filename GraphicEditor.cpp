#include <iostream>
#define M_max 250
#define N_max 250
using namespace std;
struct pixel { //Пиксели, импользующиеся по отдельности в стеке
	int X;
	int Y;
	char C;
};
class PixelSteck {
	int i{ -1 };
	pixel array[M_max * N_max];
public:
	PixelSteck() : i(-1)
	{ } 
	void push_back(const pixel& symbol) {
		array[++i] = symbol;
	}
	pixel pop_back() {
		return array[i--];
	}
	bool empty() {
		if (i == -1) {
			return true;
		}
		else return false;
	}
};
class Screen {
private:
	char pixels[M_max][N_max];
	int M;
	int N;
public:
	Screen() : M(M_max), N(N_max) //Конструктор
	{C_CleanScr(M_max, N_max);}
	//--------------------------------------//
	void C_CleanScr(int M, int N) {//Очистка заданной области 
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				*(*pixels + i * M + j) = 'O';
			}
		}
	}
	//--------------------------------------//
	void C_CleanScr() {           //Очистка текущего экрана
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				*(*pixels + i * M + j) = 'O';
			}
		}
	}
	//--------------------------------------//
	void I_CreateScr() { //Создание нового экрана
		cin >> M >> N;
		C_CleanScr();
	}
	//--------------------------------------//
	void S_Save() {
		char letter = ' ';
		char name[12] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };
		int i = 0;
		cin >> noskipws;
		cin >> letter;
		while (letter != '\n') {
			name[i] = letter;
			cin >> letter;
			i++;
		}
		i = 0;
		do {
			if (name[i] != ' ') cout << name[i];
			i++;
		} while (i < 12);
		cout << "\n";
		for (int j = 0; j < N; j++) {
			for (i = 0; i < M; i++) {
				cout << *(*pixels + i * M + j);
			}
			cout << "\n";
		}
		cin >> skipws;
	}
	//--------------------------------------//
	void L_SetOixel() {
		char C;
		int X, Y;
		cin >> X >> Y >> C;
		*(*pixels + (X - 1) * M + (Y - 1)) = C;
	}
	//--------------------------------------//
	void H_HorizontalLine() {
		int X1, X2, Y;
		char C;
		cin >> X1 >> X2 >> Y >> C;
		for (int i = X1 - 1; i < X2; i++) {
			*(*pixels + i * M + Y - 1) = C;
		}
	}
	//--------------------------------------//
	void V_VerticalLine() {
		int X, Y1, Y2;
		char C;
		cin >> X >> Y1 >> Y2 >> C;
		for (int i = Y1 - 1; i < Y2; i++) {
			*(*pixels + (X - 1) * M + i) = C;
		}
	}
	//--------------------------------------//
	void K_FillRectangle() {
		int X1, X2, Y1, Y2;
		char C;
		cin >> X1 >> X2 >> Y1 >> Y2 >> C;
		for (int i = X1 - 1; i < X2; i++) {
			for (int j = Y1 - 1; j < Y2; j++) {
				*(*pixels + i * M + j) = C;
			}
		}
	}
	//--------------------------------------//
	void F_FillArea() {
		int X, Y;
		char C, preColor;
		PixelSteck* steck = new PixelSteck(); //Вспомогательный стек
		pixel currentPixel;
		int condition;
		cin >> X >> Y >> C;
		preColor = *(*pixels + (X - 1) * M + (Y - 1));
		(*steck).push_back({ X - 1, Y - 1, preColor });
		*(*pixels + (X - 1) * M + (Y - 1)) = C;
		do {
			currentPixel = (*steck).pop_back();
			for (int i = -1; i < 2; i += 2) {
				X = currentPixel.X + i; Y = currentPixel.Y;
				condition = (X >= 0 && X < M_max && Y >= 0 && Y < N_max && *(*pixels + X * M + Y) == preColor);
				if (condition) {
					(*steck).push_back({ X, Y, preColor });
					*(*pixels + X * M + Y) = C;
				}
				X = currentPixel.X; Y = currentPixel.Y + i;
				condition = (X >= 0 && X < M_max && Y >= 0 && Y < N_max && *(*pixels + X * M + Y) == preColor);
				if (condition) {
					(*steck).push_back({ X, Y, preColor });
					*(*pixels + X * M + Y) = C;
				}
			}
		} while (!(*steck).empty());
	}
	//--------------------------------------//
	~Screen() { }
};
//***********************************************//
int main()
{
	Screen* MainScreen = new Screen(); // Объект класса Screen - Экран - создаётся в куче,
	char cCurrentKey;                  // т.к. в стеке для этого может не хватить памяти
	enum Session {                     // (выскакиваает предупреждение об этом).
		OFF,
		RUN
	};
	Session currentSession = RUN;
	while (currentSession == RUN) {
		cin >> cCurrentKey;
		switch (cCurrentKey) {
		case 'I':
			(*MainScreen).I_CreateScr();
			break;
		case 'C':
			(*MainScreen).C_CleanScr();
			break;
		case 'L':
			(*MainScreen).L_SetOixel();
			break;
		case 'V':
			(*MainScreen).V_VerticalLine();
			break;
		case 'H':
			(*MainScreen).H_HorizontalLine();
			break;
		case 'K':
			(*MainScreen).K_FillRectangle();
			break;
		case 'F':
			(*MainScreen).F_FillArea();
			break;
		case 'S':
			(*MainScreen).S_Save();
			break;
		case 'X':
			(*MainScreen).~Screen();
			currentSession = OFF;
			break;
		}
	}
}