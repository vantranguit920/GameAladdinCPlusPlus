#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Sound.h"

class  Apple :public Object
{
protected:
	Animation* AppleAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	Sound *sound;
	GSound *applesound;
	float timeout = 0.0f;
public:
	Apple();
	Apple(Sprite* spApple, SpriteSheet* ifoApple, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Apple();

	enum AppleState {
		Show,
	};

	AppleState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(AppleState state);
	void GetState();
	bool GetAllowDraw();
};

