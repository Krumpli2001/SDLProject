#pragma once

#include <SDL.h>

class Timer
{
private:
	Timer() {};
	static Timer* Timer_Instance;
	Uint64 Timer_DeltaTime{}; //millisecbe van, 1 sec = 1000 ms
	Uint64 Timer_LastTime{};

	const double TARGET_FPS = 60;
	const double TARGET_DELTATIME = 1000 / TARGET_FPS;

	bool pressed = false;
	int pressedtimer = 0;

	Uint64 countedframes=0;
	Uint64 sec = 0;
	int fps = 0;
	bool fpslock = false;

	bool menu = false;
public:
	static inline Timer* GetInstance()
	{
		if (Timer_Instance == nullptr)
		{
			Timer_Instance = new Timer();
		}
		return Timer_Instance;
	}

	/// <summary>
	/// a program ind�t�sa ut�n eltelt ms
	/// </summary>
	void getTick();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a kett� egym�st k�vet� frame k�z�tti eltelt id� ms-ben</returns>
	inline Uint64 getTimer_DeltaTime() { return Timer_DeltaTime; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az egy m�sodperc alatti friss�l�sek/arjzol�sok sz�ma</returns>
	inline int getFPS() { return fps; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>fps korl�toz�s aktivit�s</returns>
	inline bool getFPSLock() { return fpslock; }

	/// <summary>
	/// fps lock be�ll�t�sa
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setFPSLock(bool e) { fpslock = e; }

	/// <summary>
	/// men� aktivit�sa
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setmenu(bool e) { menu = e; }

	/// <summary>
	/// megmondja, hogy mikor dolgozhat� fel a bej�v� mnk event
	/// </summary>
	/// <param name="time">id� a gomb nyom�s ut�n</param>
	/// <returns>lenyomhat� e a gomb</returns>
	bool pressable(Uint64 time);
};