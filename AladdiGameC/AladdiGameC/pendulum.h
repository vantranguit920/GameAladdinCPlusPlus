#pragma once
#include "Object.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
class pendulum:public Object
{
protected:
	Animation *penduAnim;
public:
	void ChangeAnim(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	pendulum();
	pendulum(Sprite *sprite, SpriteSheet *info, D3DXVECTOR2 pos);
	~pendulum();
};

