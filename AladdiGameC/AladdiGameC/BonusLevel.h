#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
#include "Sound.h"
class  BonusLevel :public Object
{
protected:
	Animation* BonusLevelAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	Sound *sound;
	GSound *bonusSound;
	float timeout = 0.0f;
public:
	BonusLevel();
	BonusLevel(Sprite* spBonusLevel, SpriteSheet* ifoBonusLevel, D3DXVECTOR2 pos, Aladdin* aladdin);
	~BonusLevel();

	enum BonusLevelState {
		Show,
		Hitted,
	};

	BonusLevelState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(BonusLevelState state);
	void GetState();
	bool GetAllowDraw();
};

