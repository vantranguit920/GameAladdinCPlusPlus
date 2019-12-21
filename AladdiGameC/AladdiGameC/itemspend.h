#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Score.h"
class itemspend
{
protected:
	Sprite* sprite;
	Animation *animaHead;
	Score* score[2];
	int point = 400;
	Aladdin* ala;
public:
	itemspend(Sprite *sprite, SpriteSheet* spriteSheet, Aladdin* aladin);
	itemspend();
	void render();
	void Update(float dt, Keyboard* key);
	~itemspend();
};

