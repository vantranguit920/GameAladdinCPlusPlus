#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Score.h"
#include "Aladdin.h"
class itemApple
{
protected:
	Sprite* sprite;
	Score* score[2];
	Animation *animaHead;
	Aladdin* ala;
	int point = 460;
public:
	itemApple(Sprite *sprite, SpriteSheet* spriteSheet,Aladdin* aladin);
	itemApple();
	void render();
	void Update(float dt, Keyboard* key);
	~itemApple();

};

