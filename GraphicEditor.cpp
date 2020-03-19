#include <iostream>
#define M_max 250
#define N_max 250
using namespace std;
struct pixel {
	int X;
	int Y;
	char C;
};
struct steck {
	pixel pixelsToColor[M_max * N_max];
	int i = -1;
};
char pixels[M_max][N_max];
int M, N;
///////////////////////////////////////////////////////////
void PushPixel(steck&, pixel);
pixel PopPixel(steck&);
void I_CleanScr(char* pixA, int M, int N);
void S_Save(char* pixA, int M, int N);
void L_SetOixel(char* pixA, int M, int N);
void H_HorizontalLine(char* pixA, int M, int N);
void V_VerticalLine(char* pixA, int M, int N);
void K_FillRectangle(char* pixA, int M, int N);
void F_FillArea(char* pixA, int M, int N);
int main()
{
	char cCurrentKey;
	enum Session {
		OFF,
		RUN
	};
	Session currentSession = RUN;
	while (currentSession == RUN) {
		cin >> cCurrentKey;
		switch (cCurrentKey) {
		case 'I':
			cin >> M >> N;
			I_CleanScr(*pixels, M, N);
			break;
		case 'C':
			I_CleanScr(*pixels, M, N);
			break;
		case 'L':
			L_SetOixel(*pixels, M, N);
			break;
		case 'V':
			V_VerticalLine(*pixels, M, N);
			break;
		case 'H':
			H_HorizontalLine(*pixels, M, N);
			break;
		case 'K':
			K_FillRectangle(*pixels, M, N);
			break;
		case 'F':
			F_FillArea(*pixels, M, N);
			break;
		case 'S':
			S_Save(*pixels, M, N);
			break;
		case 'X':
			currentSession = OFF;
			break;
		}
	}
}
void I_CleanScr(char* pixA, int M, int N) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			*(pixA + i * M + j) = 'O';
		}
	}
}
void S_Save(char* pixels,int M,int N) {
	char letter = ' ';
	char name[12] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
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
		if(name[i] != ' ') cout << name[i];
		i++;
	} while (i < 12);
	cout << "\n";
	for (int j = 0; j < N; j++) {
		for (i = 0; i < M; i++) {
			cout << *(pixels + i*M + j);
		}
		cout << "\n";
	}
	cin >> skipws;
}
void L_SetOixel(char* pixA, int M, int N) {
	char C;
	int X, Y;
	cin >> X >> Y >> C;
	*(pixA + (X - 1) * M + (Y - 1)) = C;
}
void H_HorizontalLine(char* pixA, int M, int N) {
	int X1, X2, Y;
	char C;
	cin >> X1 >> X2 >> Y >> C;
	for (int i = X1 - 1; i < X2; i++) {
		*(pixA + i * M + Y - 1) = C;
	}
}
void V_VerticalLine(char* pixA, int M, int N) {
	int X, Y1, Y2;
	char C;
	cin >> X >> Y1 >> Y2 >> C;
	for (int i = Y1 - 1; i < Y2; i++) {
		*(pixA + (X - 1) * M + i) = C;
	}
}
void K_FillRectangle(char* pixA, int M, int N) {
	int X1, X2, Y1, Y2;
	char C;
	cin >> X1 >> X2 >> Y1 >> Y2 >> C;
	for (int i = X1 - 1; i < X2; i++) {
		for (int j = Y1 - 1; j < Y2; j++) {
			*(pixA + i * M + j) = C;
		}
	}
}
void PushPixel(steck& Steck, pixel InPixel) {
	Steck.i++;
	Steck.pixelsToColor[Steck.i] = InPixel;
}
pixel PopPixel(steck& Steck) {
	if (Steck.i > -1) {
		Steck.i--;
		return Steck.pixelsToColor[Steck.i + 1];
	}
}
void F_FillArea(char* pixA, int M, int N) {
	int X, Y;
	char C, preColor;
	steck Steck;
	pixel currentPixel;
	int condition;
	cin >> X >> Y >> C;
	preColor = *(pixA + (X - 1) * M + (Y - 1));
	PushPixel(Steck, { X - 1, Y - 1, preColor});
	*(pixA + (X - 1) * M + (Y - 1)) = C;
	do {
		currentPixel = PopPixel(Steck);
		for (int i = -1; i < 2; i += 2) {
			X = currentPixel.X + i; Y = currentPixel.Y;
			condition = (X >= 0 && X < M_max && Y >= 0 && Y < N_max && *(pixA + X * M + Y) == preColor);
			if (condition) {
				PushPixel(Steck, { X, Y, preColor });
				*(pixA + X * M + Y) = C;
			}
			X = currentPixel.X; Y = currentPixel.Y + i;
			condition = (X >= 0 && X < M_max && Y >= 0 && Y < N_max && *(pixA + X * M + Y) == preColor);
			if (condition) {
				PushPixel(Steck, { X, Y, preColor });
				*(pixA + X * M + Y) = C;
			}
		}
	} while (Steck.i != -1);
}