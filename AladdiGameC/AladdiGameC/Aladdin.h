#pragma once
#include "Object.h"
#include "AladdinAnimation.h"
#include "AladinState.h"
#include "Viewport.h"
#include "Brick.h"
#include "pendulum.h"
#include "Arrow.h"
class Aladdin:public Object
{
protected:
	AladdinAnimation *animAla;
	AladinState *stateAla;
	AladinState::State state; 
	int delay;

	bool lock;
public:

	Aladdin();
	Aladdin(Sprite *spAla,SpriteSheet *ifoAla);
	~Aladdin();

	const char* pathPNG;
	AladinState *getState();

	void ChangeAnimation(float dt, Keyboard* key);
	
	void OnCollision(Object *obj, D3DXVECTOR2 distance, D3DXVECTOR2 disAla);
	void Update(float dt, Keyboard* key);
	void Render(Viewport *viewport);
};

