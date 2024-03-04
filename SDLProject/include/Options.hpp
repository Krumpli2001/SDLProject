#pragma once

class Options {
private:
	Options() {}

	double savedScale = -1;
	int savedVolume = -1;
public:
	Options(const Options&) = delete;

	inline static Options* GetInstance()
	{
		static Options* Options_Instance;
		if (Options_Instance == nullptr)
		{
			Options_Instance = new Options();
		}
		return Options_Instance;
	}

	//elmentett zoom skalár visszaadása
	double* getSavedScale() { return &savedScale; }

	//beállítja, hogy mi legyen az elmentett érték
	void setSavedScale(double e) { savedScale = e; }

	//visszaadja az elmentett hangerõt
	int* getSavedVolume() { return &savedVolume; }

	//beállítja a menteni kívánt hangerõt
	void setSavedVolume(int e) { savedVolume = e; }

	//elmentett beállítások beolvasása
	void readSettings(std::string source = "saves/settings.set");

	//beállítások mentése
	void saveSettings();
};