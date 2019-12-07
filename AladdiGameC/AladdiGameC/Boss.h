#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  Boss :public Object
{
protected:
	Animation* BossAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;
public:
	Boss();
	Boss(Sprite* spBoss, SpriteSheet* ifoBoss, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Boss();

	enum BossState {
		AttackPush,
		AttackFire,
		SnakeDisappear,
		SnakeAttack,
	};

	BossState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disBoss);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(BossState state);
	void GetState();
	bool GetAllowDraw();
};

