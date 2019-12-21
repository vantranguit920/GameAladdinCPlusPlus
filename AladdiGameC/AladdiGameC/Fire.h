#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  Fire :public Object
{
protected:
	Animation* FireAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;
public:
	Fire();
	Fire(Sprite* spFire, SpriteSheet* ifoFire, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Fire();

	enum FireState {
		Push,
	};

	FireState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);
	Animation *getAnim();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void NewFire(D3DXVECTOR2 position, bool flipflag);
	void SetAllowDraw(bool allow);
	void SetState(FireState state);
	void GetState();
	bool GetAllowDraw();
};


