#pragma once
#include "Object.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Keyboard.h"
#include "Viewport.h"
#include "Aladdin.h"
#include "Collision.h"
class Bat:public Object
{
protected:
	Animation *batAnim;
	Aladdin *aladin;
	float timecout=0.0f;
	bool dyed=false;
	bool isFly = false;
	D3DXVECTOR2 startpos;
public:
	enum BatState
	{
		stop,
		fly,
	};
	BatState state;
	void ChangeAnim(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	
	Bat(Sprite *sprite, SpriteSheet *info, D3DXVECTOR2 pos, Aladdin *aladin);
	Bat();
	~Bat();
};

