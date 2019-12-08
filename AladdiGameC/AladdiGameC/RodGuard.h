#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class RodGuard : public Object
{
protected:
	Animation* RodGuardAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;

public:
	RodGuard();
	RodGuard(Sprite* spRodGuard, SpriteSheet* ifoRodGuard, D3DXVECTOR2 pos, Aladdin* aladdin);
	~RodGuard();

	enum RodGuardState {
		Died,
		Hitted,
		Attack,
		Stand,
	};

	RodGuardState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(RodGuardState state);
	void GetState();
	bool GetAllowDraw();

};