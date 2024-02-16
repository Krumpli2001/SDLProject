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

	double* getSavedScale() { return &savedScale; }
	void setSavedScale(double e) { savedScale = e; }
	int* getSavedVolume() { return &savedVolume; }
	void setSavedVolume(int e) { savedVolume = e; }

	void readSettings(std::string source = "settings.set");
	void saveSettings();
};