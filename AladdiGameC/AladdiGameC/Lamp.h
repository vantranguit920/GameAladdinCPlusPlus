#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
class Lamp
{
protected:
	Sprite* sprite;
	Animation *animalamp;
	Aladdin * aladin;
public:
	Lamp(Sprite *sprite, SpriteSheet* spriteSheet, Aladdin * aladin);
	Lamp();
	void render();
	void Update(float dt, Keyboard* key);
	~Lamp();
};

