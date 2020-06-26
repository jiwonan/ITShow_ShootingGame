#pragma once
class CheatManager
{
public:
	CheatManager();
	void KeyF1();
	void KeyF2();
	void KeyF3();
	void KeyF4();
	void KeyF5();
	void KeyF6();
	void KeyF7();

	void Update();
	void Render();

	bool isPause;
};

