#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
class HeadAla
{
protected:
	Sprite* sprite;
	Animation *animaHead;
	Sprite* spritescore;
	Animation *animscore;
	
public:
	HeadAla(Sprite *sprite, SpriteSheet* spriteSheet);
	HeadAla();
	void render();
	void Update(float dt, Keyboard* key);
	~HeadAla();
};

