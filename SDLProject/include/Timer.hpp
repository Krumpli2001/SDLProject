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
	/// a program indítása után eltelt ms
	/// </summary>
	void getTick();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>a kettõ egymást követõ frame közötti eltelt idõ ms-ben</returns>
	inline Uint64 getTimer_DeltaTime() { return Timer_DeltaTime; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>az egy másodperc alatti frissülések/arjzolások száma</returns>
	inline int getFPS() { return fps; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>fps korlátozás aktivitás</returns>
	inline bool getFPSLock() { return fpslock; }

	/// <summary>
	/// fps lock beállítása
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setFPSLock(bool e) { fpslock = e; }

	/// <summary>
	/// menü aktivitása
	/// </summary>
	/// <param name="e">true/false</param>
	inline void setmenu(bool e) { menu = e; }

	/// <summary>
	/// megmondja, hogy mikor dolgozhatõ fel a bejövõ mnk event
	/// </summary>
	/// <param name="time">idõ a gomb nyomás után</param>
	/// <returns>lenyomható e a gomb</returns>
	bool pressable(Uint64 time);
};