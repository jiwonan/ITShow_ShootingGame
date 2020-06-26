#pragma once
class SpriteEffect
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
};
