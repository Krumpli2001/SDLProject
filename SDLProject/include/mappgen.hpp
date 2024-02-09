#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Rng.hpp"
#include "Tiles.hpp"


namespace mappgen {

	enum szintek {
		eg,
		hegyteto,
		hegy,
		hegyalj,
		foldszint,
	};

	void fajlba_matrix(std::ofstream& file, std::vector<std::vector<int>> f, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (i == height - 1 && j == width - 1) { file << f[i][j]; break; }
				file << f[i][j] << ",";
			}
			file << "\n";
		}
	}

	void genForeground(std::vector<std::vector<int>> foreground, int width, int height) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < width; j++) {
				foreground[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
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
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fu");
					}
					else {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
					}
					break;

				case hegy:
					if (RNG::GetInstance()->genRandomInt(100) < 5) {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fu");
					}
					else {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
					}
					if (foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fu") or foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fold")) { foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fold"); }
					break;

				case hegyalj:
					if (RNG::GetInstance()->genRandomInt(100) < 20) {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fu");
					}
					else {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
					}
					if (foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fu") or foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fold")) { foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fold"); }
					break;

				case foldszint:
					if (foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fu") or foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("fold")) {
						foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fold");
					}
					else {
						if (RNG::GetInstance()->genRandomInt(100) < 5) {
							foreground[i][j] = TileData::GetInstance()->getTileIDFromName("viz");;
						}
						else {
							if (RNG::GetInstance()->genRandomInt(100) > 50) {
								foreground[i][j] = TileData::GetInstance()->getTileIDFromName("viz");
							}
						}
						if (i > 0 and i < height and j>0 and j < width) {
							if (foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("viz") || foreground[i + 1][j] == TileData::GetInstance()->getTileIDFromName("viz") || foreground[i][j - 1] == TileData::GetInstance()->getTileIDFromName("viz") || foreground[i][j + 1] == TileData::GetInstance()->getTileIDFromName("viz")) {
								if (foreground[i - 1][j] == TileData::GetInstance()->getTileIDFromName("viz")) {
									if (RNG::GetInstance()->genRandomInt(100) > 10) { foreground[i][j] = TileData::GetInstance()->getTileIDFromName("viz"); }
									else { foreground[i][j] = TileData::GetInstance()->getTileIDFromName("fold"); }
								}
								if (RNG::GetInstance()->genRandomInt(100) < 10) {
									foreground[i][j] = TileData::GetInstance()->getTileIDFromName("viz");
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

	void genBackground(std::vector<std::vector<int>> background, std::vector<std::vector<int>> foreground, int width, int height) {
		for (int i = 1; i < 7; i++) {
			for (int j = 1; j < width; j++) {
				if (RNG::GetInstance()->genRandomInt(100) < 6) {
					background[i][j] = TileData::GetInstance()->getTileIDFromName("b_felho");
				}
				if (j > 0 and j < width) {
					if (RNG::GetInstance()->genRandomInt(100) < 3) { background[i][j] = TileData::GetInstance()->getTileIDFromName("b_felho"); }
				}
				if (RNG::GetInstance()->genRandomInt(100) < 3) {
					background[i][j] = TileData::GetInstance()->getTileIDFromName("b_ko");
				}
				if (background[i - 1][j] == TileData::GetInstance()->getTileIDFromName("b_ko")) { background[i][j] = TileData::GetInstance()->getTileIDFromName("b_ko"); }
				else {
					background[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
				}
			}
		}
		for (int i = 7; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (RNG::GetInstance()->genRandomInt(100) < 3) {
					background[i][j] = TileData::GetInstance()->getTileIDFromName("b_ko");
				}
				if (background[i - 1][j] == TileData::GetInstance()->getTileIDFromName("b_ko")) { background[i][j] = TileData::GetInstance()->getTileIDFromName("b_ko"); }
				else {
					background[i][j] = TileData::GetInstance()->getTileIDFromName("semmi");
				}
			}
		}
	}

	void genFlora(std::vector<std::vector<int>> flora, std::vector<std::vector<int>> foreground, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (foreground[i][j] == TileData::GetInstance()->getTileIDFromName("fu")) {
					if (RNG::GetInstance()->genRandomInt(10) < 8) {
						flora[i - 1][j] = RNG::GetInstance()->genRandomInt(3) + 1;
					}
					else { flora[i - 1][j] = TileData::GetInstance()->getTileIDFromName("semmi"); }
				}
			}
		}
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


	//ez lesz a mentesre is
	void szoveg(std::string fajlnev, int width, int height, std::vector<std::vector<int>> flora, std::vector<std::vector<int>> background, std::vector<std::vector<int>> foreground) {
		std::ofstream f("saves/" + fajlnev + ".tmx");
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
	}

	void gen(std::string fajlnev, int width, int height) {


		std::vector<std::vector<int>> flora;// = matrixLetrehoz(width, height);
		//printMatrix(flora);
		std::vector<std::vector<int>> background;// = matrixLetrehoz(width, height);
		//printMatrix(background);
		std::vector<std::vector<int>> foreground;// = matrixLetrehoz(width, height);
		//printMatrix(foreground);
		genForeground(foreground, width, height);
		//printMatrix(foreground);
		genBackground(background, foreground, width, height);
		//printMatrix(background);
		genFlora(flora, foreground, width, height);
		//printMatrix(flora);

		szoveg(fajlnev, width, height, flora, background, foreground);
	}

}