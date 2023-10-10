#include <iostream>

class RNG
{
private:
	RNG() {};
	static RNG* RNG_Instance;
	int randomInt{};
public:
	inline static RNG* GetInstance()
	{
		if (RNG_Instance == nullptr)
		{
			RNG_Instance = new RNG();
			srand(time(0));
		}
		return RNG_Instance;
	}

	inline int genRandomInt(int range) {
		return (rand() % range) + 1;
	}
};