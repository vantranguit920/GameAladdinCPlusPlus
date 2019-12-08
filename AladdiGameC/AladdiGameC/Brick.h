#pragma once
#include "Object.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
class Brick:public Object
{
protected:
	
	Animation* Brickanim;
	float timecout=0.0f;
public:
	enum BrickState
	{
		oppen,
		close,
	};
	BrickState state;
	void ChangeAnim(Keyboard* key);
	void Update(float dt,Keyboard* key);
	void Render(Viewport* viewport);
	void setallowdraw(bool allow);
	void setstate(BrickState state);
	bool getallowdraw();
	int getIndexAnim();
	Brick();
	Brick(Sprite *sprite,SpriteSheet *info, D3DXVECTOR2 pos);
	~Brick();
};

