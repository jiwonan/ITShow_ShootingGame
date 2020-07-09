#include "stdafx.h"
#include "game_stat.h"
#include <cstring>
#include <iostream>
#include <algorithm>

GameStat::GameStat()
{
	// 임시 랭킹 정보

	for (int i = 0; i < 6; ++i)
	{
		strcpy_s<128>(ranking[i].playerName, "player");
		ranking[i].playerScore = 100 - i * 5;
	}


}

void GameStat::PlayerLevelUp()
{
	playerLevelUp *= 1.5;
	exp = 0;
	level++;
	hp = fullHP;
	playerDamage *= 0.8;
	expGage *= 0.8;
	speed *= 1.2;
	shootDelay /= 1.5;
	generalDamage *= 1.2;
	spreadDamage *= 1.2;
}

void GameStat::Load()
{
	// c style
	FILE* fp = nullptr;

	fopen_s(&fp, "ranking.dat", "rt");

	if (fp != nullptr)
	{
		for (int i = 0; i < 5; ++i)
		{
			char name[128];
			int score;
			fscanf_s(fp, "%s %d", name, 128, &score);
			strcpy_s<128>(ranking[i].playerName, name);
			ranking[i].playerScore = score;
		}

		fclose(fp);
	}
	else
	{
		Save();
	}
}

void GameStat::Save()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "ranking.dat", "wt");

	for (int i = 0; i < 5; ++i)
	{
		fprintf(fp, "%s %d\n", ranking[i].playerName, ranking[i].playerScore);
	}

	fclose(fp);
}

bool compareFunc(const PlayerInfo& a, const PlayerInfo& b)
{
	return a.playerScore > b.playerScore;
}

void GameStat::SaveNewRecord(const char* playerName)
{
	// 내림차순
	strcpy_s(ranking[5].playerName, playerName);
	ranking[5].playerScore = score;

	std::sort(ranking, ranking + 6, compareFunc);

	// bubble sort
	/*for (int i = 0; i < 5; ++i)
	{
		for (int j = i + 1; j < 6; ++j)
		{
			if (ranking[i].playerScore < ranking[j].playerScore)
			{
				// 교체
				char tempPlayerName[128];
				strcpy_s(tempPlayerName, ranking[i].playerName);
				int tempPlayerScore = ranking[i].playerScore;

				strcpy_s(ranking[i].playerName, ranking[j].playerName);
				ranking[i].playerScore = ranking[j].playerScore;

				strcpy_s(ranking[j].playerName, tempPlayerName);
				ranking[j].playerScore = tempPlayerScore;
			}
		}
	}*/

	Save();
}