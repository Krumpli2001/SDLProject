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

	inline static RNG* GetInstance(bool del = false)
	{
		static RNG* RNG_Instance;
		if (del) {
			if (RNG_Instance) {
				delete RNG_Instance;
			}
			RNG_Instance = nullptr;
			return nullptr;
		}
		if (RNG_Instance == nullptr)
		{
			RNG_Instance = new RNG();
		}
		return RNG_Instance;
	}

	//visszaad egy random integer-t
	//alaphelyzetben 0 és a 2^31 - 1 között egy egész szá
	//ELSÕ opcionális paraméter a MAXIMUM
	//MÁSODIK a MINIMUM
	inline int genRandomInt(int range = INT_MAX, int min = 0) {
		std::uniform_int_distribution<int> dist(min, range);
		return dist(rd);
	}
};