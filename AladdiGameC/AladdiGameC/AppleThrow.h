#pragma once
#include "Define.h"
#include "Collision.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
using namespace Define;
class AppleThrow: public Object
{
protected:
	Animation *animAple;
	Sound *sound;	
	GSound *throwapple;
public:
	enum applestate {
		fly,
		Bursting
	};
	applestate stateapple;
	AppleThrow(Sprite* sprite_bullet, SpriteSheet* sprite_sheet);
	~AppleThrow();
	void NewApple(D3DXVECTOR2 position, bool flipflag);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision();
};

