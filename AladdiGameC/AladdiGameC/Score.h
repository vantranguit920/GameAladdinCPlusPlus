#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
class Score
{
protected:
	Sprite* sprite;
	Animation *animascore;
	int scores = 0;
public:
	Score(Sprite *sprite, SpriteSheet* spriteSheet,D3DXVECTOR2 pos);
	Score();
	D3DXVECTOR2 postion;
	void render();
	void changeAnim();
	void Update(float dt, Keyboard* key,int scorep);
	~Score();
};

