#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class Skeleton : public Object
{
protected:
	Animation* SkeletonAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;

public:
	Skeleton();
	Skeleton(Sprite* spSkeleton, SpriteSheet* ifoSkeleton, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Skeleton();

	enum SkeletonState {
		Died,
		Attack,
		Stand,
	};

	SkeletonState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disGuard);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(SkeletonState state);
	void GetState();
	bool GetAllowDraw();

};