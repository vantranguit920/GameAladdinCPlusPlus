#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Collapse.h"
#include "Sound.h"

class Skeleton : public Object
{
protected:
	Collapse* collapse;
	Animation* SkeletonAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	bool dyed = false;
	bool isStand = false;
	float timeout = 0.0f;
	Sound *sound;
	GSound *soundSkeleton;
public:
	Skeleton();
	Skeleton(Sprite* spSkeleton, SpriteSheet* ifoSkeleton, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Skeleton();

	enum SkeletonState {
		Died,
		Sit,
		Stand,
	};

	SkeletonState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);
	void OnCollision();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(SkeletonState state);
	void GetState();
	bool GetAllowDraw();

};