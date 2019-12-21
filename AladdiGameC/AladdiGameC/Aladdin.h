#pragma once
#include "Object.h"
#include "AladdinAnimation.h"
#include "AladinState.h"
#include "Viewport.h"
#include "Brick.h"
#include "pendulum.h"
#include "Arrow.h"
#include "AppleThrow.h"
class Aladdin:public Object
{
protected:
	AladdinAnimation *animAla;
	AladinState *stateAla;
	AladinState::State state; 
	Object* rope;
	int delay;
	int numapple;
	bool lock;
public:

	Aladdin();
	Aladdin(Sprite *spAla,SpriteSheet *ifoAla, Sprite *spApple, SpriteSheet *ifoaple);
	~Aladdin();
	bool isswing = false;
	const char* pathPNG;
	AladinState *getState();
	AppleThrow *applethrow[3];
	int numapples ;
	int numspend;
	void newala();
	void ChangeAnimation(float dt, Keyboard* key);
	RECT GetBoundKnif();
	Animation * getAnimAladdin();
	void OnCollision(Object *obj, D3DXVECTOR2 distance, D3DXVECTOR2 disAla);
	void Update(float dt, Keyboard* key);
	void Render(Viewport *viewport);
};

