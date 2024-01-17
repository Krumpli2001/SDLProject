#include <iostream>
#include <string>
#include <fstream>
#include "Rng.hpp"
#include "Tiles.hpp"

//using namespace Tiles;

//#define width 60
//#define height 20



enum szintek{
	eg,
	hegyteto,
	hegy,
	hegyalj,
	foldszint,
};

void fajlba_matrix(std::ofstream& file, int** f, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == height - 1 && j == width - 1) { file << f[i][j]; break; }
			file << f[i][j] << ",";
		}
		file << "\n";
	}
}

void genForeground(int** foreground, int width, int height) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < width; j++) {
			foreground[i][j] = semmi;
		}
	}
	for (int i = 0; i < height; i++) {

		int szint{};
		if (i <= 0 and i > 5) { szint = eg; }
		else if (i == 5) { szint = hegyteto; }
		else if (i > 5 and i <= 10) { szint = hegy; }
		else if (i > 10 and i <= 12) { szint = hegyalj; }
		else if (i > 12) { szint = foldszint; }

		for (int j = 0; j < width; j++) {
			
			switch (szint)
			{
			case eg:
				break;

			case hegyteto:
				if (RNG::GetInstance()->genRandomInt(100) < 2) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				break;

			case hegy:
				if (RNG::GetInstance()->genRandomInt(100) < 5) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) { foreground[i][j] = fold; }
				break;

			case hegyalj:
				if (RNG::GetInstance()->genRandomInt(100) < 20) {
					foreground[i][j] = fu;
				}
				else {
					foreground[i][j] = semmi;
				}
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) { foreground[i][j] = fold; }
				break;

			case foldszint:
				if (foreground[i - 1][j] == fu or foreground[i - 1][j] == fold) {
					foreground[i][j] = fold;
				}
				else {
					if (RNG::GetInstance()->genRandomInt(100) < 5) {
						foreground[i][j] = viz;
					}
					else {
						if (RNG::GetInstance()->genRandomInt(100) > 50) {
							foreground[i][j] = fu;
						}
					}
					if (i > 0 and i < height and j>0 and j < width) {
						if (foreground[i - 1][j] == viz || foreground[i + 1][j] == viz || foreground[i][j - 1] == viz || foreground[i][j + 1] == viz) {
							if (foreground[i - 1][j] == viz) {
								if (RNG::GetInstance()->genRandomInt(100) > 10) { foreground[i][j] = viz; }
								else { foreground[i][j] = fold; }
							}
							if (RNG::GetInstance()->genRandomInt(100) < 10) {
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
}

void genBackground(int** background, int** foreground, int width, int height) {
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < width; j++) {
			if (RNG::GetInstance()->genRandomInt(100) < 6) {
				background[i][j] = felho;
			}
			if (j > 0 and j < width) {
				if (RNG::GetInstance()->genRandomInt(100) < 3) { background[i][j] = felho; }
			}
			if (RNG::GetInstance()->genRandomInt(100) < 3) {
				background[i][j] = ko;
			}
			if (background[i - 1][j] == ko) { background[i][j] = ko; }
			else {
				background[i][j] = semmi;
			}
		}
	}
	for (int i = 7; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (RNG::GetInstance()->genRandomInt(100) < 3) {
				background[i][j] = ko;
			}
			if (background[i - 1][j] == ko) { background[i][j] = ko; }
			else {
				background[i][j] = semmi;
			}
		}
	}
}

void genFlora(int** flora, int** foreground, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (foreground[i][j] == fu) {
				if (RNG::GetInstance()->genRandomInt(10) < 8) {
					flora[i - 1][j] = RNG::GetInstance()->genRandomInt(3) + 1;
				}
				else { flora[i - 1][j] = semmi; }
			}
		}
	}
}

int** matrixLetrehoz(int width, int height) {
	int** y = new int* [height];
	for (int i = 0; i < height; i++) {
		y[i] = new int[width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			y[i][j] = 0;
		}
	}
	return y;
}

void delMatrix(int** y, int height) {
	for (int i = 0; i < height; i++) {
		delete[] y[i];
	}
	delete[] y;
}

void printMatrix(int** y, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << y[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void gen(std::string fajlnev, int width, int height) {

	int** flora = matrixLetrehoz(width, height);
	//printMatrix(flora);
	int** background = matrixLetrehoz(width, height);
	//printMatrix(background);
	int** foreground = matrixLetrehoz(width, height);
	//printMatrix(foreground);
	genForeground(foreground, width, height);
	//printMatrix(foreground);
	genBackground(background, foreground, width, height);
	//printMatrix(background);
	genFlora(flora, foreground, width, height);
	//printMatrix(flora);

	std::ofstream f("saves/maps/" + fajlnev + ".tmx");
	if (f.is_open()) {//ahol nagyreszt szamok vannak ott lehet oket kicserelni valtozokra
		f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			<< "<map version=\"1.10\" tiledversion=\"1.10.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"" << width << "\" height=\"" << height << "\" tilewidth=\"120\" tileheight=\"120\" infinite=\"0\" nextlayerid=\"4\" nextobjectid=\"1\">\n"
			<< " <tileset firstgid=\"1\" name=\"flora\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"3\" columns=\"3\">\n"
			<< "  <image source=\"flora.png\" width=\"360\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <tileset firstgid=\"4\" name=\"background\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"3\" columns=\"3\">\n"
			<< "  <image source=\"background.png\" width=\"360\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <tileset firstgid=\"7\" name=\"foreground\" tilewidth=\"120\" tileheight=\"120\" tilecount=\"6\" columns=\"6\">\n"
			<< "  <image source=\"maptextures.png\" width=\"720\" height=\"120\"/>\n"
			<< " </tileset>\n"

			<< " <layer id=\"3\" name=\"flora\" width=\"" << width << "\" height=\"" << height << "\">\n"// visible=\"0\">\n"
			<< "  <data encoding=\"csv\">\n";
		fajlba_matrix(f, flora, width, height);
		f << "</data>\n"
			<< " </layer>\n"


			<< " <layer id=\"2\" name=\"background\" width=\"" << width << "\" height=\"" << height << "\">\n"
			<< "  <data encoding=\"csv\">\n";
		fajlba_matrix(f, background, width, height);
		f << "</data>\n"
			<< " </layer>\n"


			<< " <layer id=\"1\" name=\"foreground\" width=\"" << width << "\" height=\"" << height << "\">\n"// visible=\"0\">\n"
			<< "  <data encoding=\"csv\">\n";
		fajlba_matrix(f, foreground, width, height);
		f << "</data>\n"
			<< " </layer>\n"


			<< "</map>\n";

		f.close();
	}

	delMatrix(flora , height);
	delMatrix(background, height);
	delMatrix(foreground, height);
}
