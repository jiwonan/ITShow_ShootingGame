#pragma once

enum State
{
	kFirst,
	kMidBoss,
	kSecond,
	kLastBoss,
	kEnd
};

class PlayerInfo
{
public:
	char playerName[128];
	int playerScore;
};

class GameStat
{
public:
	int score;
	int playerState;

	// needs
	int fullHP;
	int hp;
	float speed;

	int playerLevelUp;
	int level;
	float exp;

	int generalDamage;
	int spreadDamage;

	float shootDelay;

	float playerDamage;
	float expGage;

	bool cheatInvincible;

	PlayerInfo ranking[6];

	GameStat();
	void Load();
	void Save();
	void SaveNewRecord(const char* playerName);

	void PlayerLevelUp();
};