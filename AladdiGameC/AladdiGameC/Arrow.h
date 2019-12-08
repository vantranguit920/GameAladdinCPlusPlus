#pragma once
#include "Object.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
class Arrow :public Object
{
protected:
	Animation * arrowAnim;
	float timecout=0;
public:
	enum ArrowState
	{
		oppen,
		close,
	};
	ArrowState state;
	void ChangeAnim(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void setstate(ArrowState state);
	int getIndexAnim();
	RECT GetBound();
	Arrow();
	Arrow(Sprite *sprite, SpriteSheet *info, D3DXVECTOR2 pos);
	~Arrow();
};


