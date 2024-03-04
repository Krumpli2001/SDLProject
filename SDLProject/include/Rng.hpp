#pragma once

#include <iostream>
#include <random>

//cherno videoja alapjan letrehozando singleton -- nem kell "globalisan letrehozni kulon a pointert"

class RNG
{
private:
	RNG() {};

	std::random_device rd;
public:

	RNG(const RNG&) = delete;

	inline static RNG* GetInstance()
	{
		static RNG* RNG_Instance;
		if (RNG_Instance == nullptr)
		{
			RNG_Instance = new RNG();
		}
		return RNG_Instance;
	}

	//visszaad egy random integer-t
	//alaphelyzetben 0 �s a 2^31 - 1 k�z�tt egy eg�sz sz�
	//ELS� opcion�lis param�ter a MAXIMUM
	//M�SODIK a MINIMUM
	inline int genRandomInt(int range = INT_MAX, int min = 0) {
		std::uniform_int_distribution<int> dist(min, range);
		return dist(rd);
	}
};