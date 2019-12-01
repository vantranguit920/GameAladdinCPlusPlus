#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class Guard :public Object
{
protected:
	Animation* GuardAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;
public:
	Guard();
	Guard(Sprite* spGuard, SpriteSheet* ifoGuard, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Guard();

	enum GuardState {
		Died,
		Common,
		HitByBullets,
		GuillotineKnife,
	};

	GuardState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(GuardState state);
	void GetState();
	bool GetAllowDraw();
};

