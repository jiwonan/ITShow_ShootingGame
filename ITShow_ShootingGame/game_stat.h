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
	float exp;

	int generalDamage;
	int spreadDamage;

	float shootDelay;

	float playerDamage;
	float expGage;

	bool cheatInvincible;

	void PlayerLevelUp()
	{
		playerLevelUp *= 1.5;
		exp = 0;
		level++;
		hp = fullHP;
		playerDamage *= 0.8;
		expGage *= 0.7;
		speed *= 1.2;
		shootDelay /= 1.5;
		generalDamage *= 1.2;
		spreadDamage *= 1.2;
	}
};