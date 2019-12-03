#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  Bonus :public Object
{
protected:
	Animation* BonusAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;
public:
	Bonus();
	Bonus(Sprite* spBonus, SpriteSheet* ifoBonus, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Bonus();

	enum BonusState {
		Show,
		Hitted,
		Destroy
	};

	BonusState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disBonus);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(BonusState state);
	void GetState();
	bool GetAllowDraw();
};

