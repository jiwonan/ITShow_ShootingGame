#pragma once

enum State
{
	kFirst,
	kMidBoss,
	kSecond,
	kLastBoss,
	kEnd
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
	int exp;

	int generalDamage;
	int spreadDamage;

	float shootDelay;

	bool cheatInvincible;

	void PlayerLevelUp()
	{
		playerLevelUp *= 1.5;
		exp = 0;
		level++;
		fullHP *= 1.2;
		hp = fullHP;
		speed *= 1.2;
		shootDelay /= 2;
		generalDamage *= 1.2;
		spreadDamage *= 1.2;
	}
};