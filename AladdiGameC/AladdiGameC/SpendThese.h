#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  SpendThese:public Object
{
protected:
	Animation* spendTheseAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	Sound *sound;
	GSound *spensound;
	float timeout = 0.0f;
public:
	SpendThese();
	SpendThese(Sprite* spSpendThese, SpriteSheet* ifoSpendThese, D3DXVECTOR2 pos, Aladdin* aladdin);
	~SpendThese();

	enum SpendTheseState {
		Show,
		Destroy
	};

	SpendTheseState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(SpendTheseState state);
	void GetState();
	bool GetAllowDraw();
};

