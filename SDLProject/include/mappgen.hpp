#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Rng.hpp"
#include "Tiles.hpp"


namespace mappgen {

	//ez jo
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
		
	}

	void genBackground(std::vector<std::vector<int>> background, std::vector<std::vector<int>> foreground, int width, int height) {
		
	}

	void genFlora(std::vector<std::vector<int>> flora, std::vector<std::vector<int>> foreground, int width, int height) {
		
	}


	//tesztnek
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