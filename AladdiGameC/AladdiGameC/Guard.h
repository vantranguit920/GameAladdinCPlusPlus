#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Collision.h"

class Guard :public Object
{
protected:
	Animation* GuardAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	bool isDie = false;
	bool isbleed = false;
	int angry;
	float timeout = 0.0f;
	int hpGuard;
	Sound *sound;
	GSound *soundComon;
	GSound *soundDie;
public:
	Guard();
	Guard(Sprite* spGuard, SpriteSheet* ifoGuard, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Guard();

	enum GuardState {
		Died,
		Common,
		HitByBullets,
		GuillotineKnife,
		stand,
	};

	GuardState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);
	void OnCollision();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void bleed(int dame);
	void SetAllowDraw(bool allow);
	void SetState(GuardState state);
	void GetState();
	bool GetAllowDraw();
};

