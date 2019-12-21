#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Fire.h"
#include "Star.h"

class  Boss :public Object
{
protected:
	Animation* BossAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	float timePushFire = 0.0f;
	float timePushStar = 0.0f;
	float delayFire = 0.0f;
	float delayStar = 0.0f;
	bool isJra;
	int hp = 20;
	float timejra = 0.0f;
public:
	Boss();
	Boss(Sprite* spBoss, SpriteSheet* ifoBoss, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Boss();

	enum BossState {
		jra,
		pushStar,
		Snake,
		SnakeFire,
		snakeAppear
	};
	Fire* fire[4];
	Star* star[20];
	int numFire = 0;
	int numStar = 0;
	BossState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);
	void OnCollision();

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(BossState state);
	void GetState();
	bool GetAllowDraw();
};


