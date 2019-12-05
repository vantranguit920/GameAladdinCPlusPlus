#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  Shop :public Object
{
protected:
	Animation* ShopAnim;
	Aladdin* aladdin;
	Viewport* viewport;

	float timeout = 0.0f;
public:
	Shop();
	Shop(Sprite* spShop, SpriteSheet* ifoShop, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Shop();

	enum ShopState {
		Show,
		Hitted,
	};

	ShopState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disShop);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(ShopState state);
	void GetState();
	bool GetAllowDraw();
};

