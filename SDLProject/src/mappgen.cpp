#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#define WIDTH 60
#define HEIGHT 20

enum foreground {
	semmi = 0,
	fu = 8,
	fold = 10,
	viz = 12
};

enum background {
	ko = 5,
	felho = 6
};

int genint(int range) {
	return rand() % range;
}

void genmap(std::ofstream& file, int** f) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == HEIGHT - 1 && j == WIDTH - 1) { file << f[i][j]; break; }
			file << f[i][j] << ",";
		}
		file << "\n";
	}
}

void genForeground(int** foreground) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < WIDTH; j++) {
			foreground[i][j] = semmi;
		}
	}
	for (int i = 5; i < 17; i++) {
		//if (i == 15) { std::cout << "stop\n"; }
		for (int j = 0; j < WIDTH; j++) {
			switch (i)
			{
			case 5:
				if (genint(100) < 2) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				if (genint(100) < 5) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) { foreground[i][j] = fold; }
				break;
			case 11:
			case 12:
				if (genint(100) < 20) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) { foreground[i][j] = fold; }
				break;

			case 13:
			case 14:
			case 15:
			case 16:
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) {
					foreground[i][j] = fold;
				}
				else {
					if (genint(100) < 5) {
						foreground[i][j] = viz;
					}
					else {
						if (genint(100) > 50) {
							foreground[i][j] = fu;
						}
					}
					if (i > 0 and i < HEIGHT and j>0 and j < WIDTH) {
						if (foreground[i - 1][j] == viz || foreground[i + 1][j] == viz || foreground[i][j - 1] == viz || foreground[i][j + 1] == viz) {
							if (foreground[i - 1][j] == viz) {
								if (genint(100) > 10) { foreground[i][j] = viz; }
								else { foreground[i][j] = fold; }
							}
							if (genint(100) < 10) {
								foreground[i][j] = viz;
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
	for (int i = 17; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			foreground[i][j] = fold;
		}
	}
}

void genBackground(int** background, int** foreground) {
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < WIDTH; j++) {
			if (genint(100) < 6) {
				background[i][j] = felho;
			}
			if (j > 0 and j < WIDTH) {
				if (genint(100) < 3) { background[i][j] = felho; }
			}
			if (genint(100) < 3) {
				background[i][j] = ko;
			}
			if (background[i - 1][j] == ko) { background[i][j] = ko; }
			else {
				background[i][j] = semmi;
			}
		}
	}
	for (int i = 7; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (genint(100) < 3) {
				background[i][j] = ko;
			}
			if (background[i - 1][j] == ko) { background[i][j] = ko; }
			else {
				background[i][j] = semmi;
			}
		}
	}
}

void genFlora(int** flora, int** foreground) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (foreground[i][j] == fu) {
				if (genint(10) < 8) {
					flora[i - 1][j] = genint(3) + 1;
				}
				else { flora[i - 1][j] = semmi; }
			}
		}
	}
}

int** matrixLetrehoz() {
	int** y = new int* [HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		y[i] = new int[WIDTH];
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			y[i][j] = 0;
		}
	}
	return y;
}

void delMatrix(int** y) {
	for (int i = 0; i < HEIGHT; i++) {
		delete[] y[i];
	}
	delete[] y;
}

void printMatrix(int** y) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout << y[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void gen(std::string fajlnev) {

	int** flora = matrixLetrehoz();
	//printMatrix(flora);
	int** background = matrixLetrehoz();
	//printMatrix(background);
	int** foreground = matrixLetrehoz();
	//printMatrix(foreground);
	genForeground(foreground);
	//printMatrix(foreground);
	genBackground(background, foreground);
	//printMatrix(background);
	genFlora(flora, foreground);
	//printMatrix(flora);

	std::ofstream f(fajlnev);
	if (f.is_open()) {//ahol nagyreszt szamok vannak ott lehet oket kicserelni valtozokra
		f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			<< "<map version=\"1.10\" tiledversion=\"1.10.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" << WIDTH << "\" height=\"" << HEIGHT << "\" tilewidth=\"120\" tileheight=\"120\" infinite=\"0\" nextlayerid=\"4\" nextobjectid=\"1\">\n"
			<< " <tileset firstgid=\"1\" name=\"flora\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"3\" columns=\"3\">\n"
			<< "  <image source=\"flora.png\" width=\"360\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <tileset firstgid=\"4\" name=\"background\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"3\" columns=\"3\">\n"
			<< "  <image source=\"background.png\" width=\"360\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <tileset firstgid=\"7\" name=\"foreground\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"6\" columns=\"6\">\n"
			<< "  <image source=\"maptextures.png\" width=\"720\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <layer id=\"3\" name=\"flora\" width=\"60\" height=\"20\" visible=\"0\">\n"
			<< "  <data encoding=\"csv\">\n";
		genmap(f, flora);
		f << "</data>\n"
			<< " </layer>\n"


			<< " <layer id=\"2\" name=\"background\" width=\"60\" height=\"20\">\n"
			<< "  <data encoding=\"csv\">\n";
		genmap(f, background);
		f << "</data>\n"
			<< " </layer>\n"





			<< " <layer id=\"1\" name=\"foreground\" width=\"60\" height=\"20\" visible=\"0\">\n"
			<< "  <data encoding=\"csv\">\n";
		genmap(f, foreground);
		f << "</data>\n"
			<< " </layer>\n"


			<< "</map>\n";

		f.close();
	}

	delMatrix(flora);
	delMatrix(background);
	delMatrix(foreground);
}

//int main() {
//	srand(time(0));
//	gen("sajt.tmx");
//	//std::cin.get();
//}