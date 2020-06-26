#pragma once

#include <d3dx9math.h>

class Enemy
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual int GetEnemyDamage() = 0;
	virtual D3DXVECTOR2 GetPosition() = 0;
	virtual float GetRadius() = 0;
	virtual void Hit(float damage) = 0;
};