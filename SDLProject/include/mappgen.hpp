 #pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ItemData.hpp"
#include "Rng.hpp"

#include "PerlinNoise.hpp"


namespace mappgen {

	//matrixok kiir�sa f�jlba
	inline void fajlba_matrix(std::ofstream& file, std::vector<std::vector<int>> f, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (i == height - 1 && j == width - 1) { file << f[i][j]; break; }
				file << f[i][j] << ",";
			}
			file << "\n";
		}
	}

	//forground gener�l�sa
	inline void genForeground(std::vector<std::vector<int>>* foreground, int width, int height) {
		auto data = ItemData::GetInstance();
		auto rand = RNG::GetInstance();
		int genheight = height - (2*height / 3); // imo igy jobban atlathato lehetne height/3 is...

		std::vector<std::vector<double>> p(height, std::vector<double>(width, 0));

		auto gen_seed = rand->genRandomInt();
		const siv::PerlinNoise perlin{ static_cast<std::uint32_t>(gen_seed) };

		constexpr double frequency = 15; //0,1..64
		constexpr int octaves = 10; //1..16

		const double fx = (frequency / width);
		const double fy = (frequency / height);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				p[j][i] = perlin.octave2D_01((j * fx), (i * fy), octaves);
			}
		}

		//int genheight = height-10;
		for (int i = 0; i < width; i++) {

			constexpr auto increment = 2;

			int minheight = genheight - increment;
			int maxheight = genheight + increment;
			genheight = rand->genRandomInt(maxheight, minheight);

			constexpr auto magassag_limit = 0;
			genheight = genheight < magassag_limit ? magassag_limit : genheight;

			genheight = genheight > height - 1 ? height - 1 : genheight;

			int minko = genheight + 4;
			int maxko = genheight + 7;

			int genko = rand->genRandomInt(maxko, minko);

			constexpr auto perlin_limit = 0.3;
			for (int j = height-1; j > genheight; j--){
				if (p[j][i] > perlin_limit) {
					(*foreground)[j][i] = data->getTileIDFromName("fold");
					if (j > genko) {
						//proba miatt viz
						(*foreground)[j][i] = data->getTileIDFromName("b_ko");
					}
				}
			}
			if (genheight>0 && (*foreground)[genheight + 1][i] == data->getTileIDFromName("fold")) {
				(*foreground)[genheight][i] = data->getTileIDFromName("fuvesfold");
			}

		}
	}

	//background gener�l�sa
	inline void genBackground(std::vector<std::vector<int>>* background, std::vector<std::vector<int>>* foreground, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				(*background)[i][j] = 0;
			}
		}
	}

	//flora layer gener�l�sa
	inline void genFlora(std::vector<std::vector<int>>* flora, std::vector<std::vector<int>>* foreground, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				(*flora)[i][j] = 0;
			}
		}
	}


	//tesztnek, m�trix kiir�sa konzolra
	inline void printMatrix(int** y, int width, int height) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << y[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	//megfelel� form�tum + f�jlba kiir�s
	inline void szoveg(std::string fajlnev, int width, int height, std::vector<std::vector<int>>* flora, std::vector<std::vector<int>>* background, std::vector<std::vector<int>>* foreground) {
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
			fajlba_matrix(f, *flora, width, height);
			f << "</data>\n"
				<< " </layer>\n"


				<< " <layer id=\"2\" name=\"background\" width=\"" << width << "\" height=\"" << height << "\">\n"
				<< "  <data encoding=\"csv\">\n";
			fajlba_matrix(f, *background, width, height);
			f << "</data>\n"
				<< " </layer>\n"


				<< " <layer id=\"1\" name=\"foreground\" width=\"" << width << "\" height=\"" << height << "\">\n"// visible=\"0\">\n"
				<< "  <data encoding=\"csv\">\n";
			fajlba_matrix(f, *foreground, width, height);
			f << "</data>\n"
				<< " </layer>\n"


				<< "</map>\n";

			f.close();
		}
	}

	//gener�l�s
	inline bool gen(std::string fajlnev, int width, int height) {


		std::vector<std::vector<int>> flora(height, std::vector<int>(width));
		//printMatrix(flora);
		std::vector<std::vector<int>> background(height, std::vector<int>(width));
		//printMatrix(background);
		std::vector<std::vector<int>> foreground(height, std::vector<int>(width));
		//printMatrix(foreground);
		genForeground(&foreground, width, height);
		//printMatrix(foreground);
		genBackground(&background, &foreground, width, height);
		//printMatrix(background);
		genFlora(&flora, &foreground, width, height);
		//printMatrix(flora);

		szoveg(fajlnev, width, height, &flora, &background, &foreground);
		return true;
	}

}