#pragma once

class Options {
private:
	Options() {}

	double savedScale = -1;
	int savedVolume = -1;
public:
	Options(const Options&) = delete;

	inline static Options* GetInstance(bool del = false)
	{
		static Options* Options_Instance;
		if (del) {
			if (Options_Instance) {
				delete Options_Instance;
			}
			Options_Instance = nullptr;
			return nullptr;
		}
		if (Options_Instance == nullptr)
		{
			Options_Instance = new Options();
		}
		return Options_Instance;
	}

	//elmentett zoom skal�r visszaad�sa
	double* getSavedScale() { return &savedScale; }

	//be�ll�tja, hogy mi legyen az elmentett �rt�k
	void setSavedScale(double e) { savedScale = e; }

	//visszaadja az elmentett hanger�t
	int* getSavedVolume() { return &savedVolume; }

	//be�ll�tja a menteni k�v�nt hanger�t
	void setSavedVolume(int e) { savedVolume = e; }

	//elmentett be�ll�t�sok beolvas�sa
	void readSettings(std::string source = "saves/settings.set");

	//be�ll�t�sok ment�se
	void saveSettings();
};