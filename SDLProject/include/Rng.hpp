#include <iostream>
#include <random>

//cherno videoja alapjan letrehozando singleton -- nem kell "globalisan letrehozni kulon a pointert"

class RNG
{
private:
	RNG() {};
	//static RNG* RNG_Instance;
	int randomInt{};

	std::random_device rd;
public:

	RNG(const RNG&) = delete;

	inline static RNG* GetInstance()
	{
		static RNG* RNG_Instance;
		if (RNG_Instance == nullptr)
		{
			RNG_Instance = new RNG();
			//srand(time(nullptr));
		}
		return RNG_Instance;
	}

	inline int genRandomInt(int range = INT_MAX) {
		std::uniform_int_distribution<int> dist(0, range-1);
		return dist(rd);
	}
};