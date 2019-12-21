#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"
class Star :public Object
{
protected:
	Animation* StarAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	bool isclip = false;
	float timeClip = 0.0f;
	int id;

public:
	Star();
	Star(Sprite* spStar, SpriteSheet* ifoStar, D3DXVECTOR2 pos, Aladdin* aladdin);
	~Star();

	enum FireState {
		fly,
		clip,
	};

	FireState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);
	void OnCollision();
	Animation *getAnim();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void NewStar(D3DXVECTOR2 position, bool flipflag, int idstar);
	void SetAllowDraw(bool allow);
	void SetState(FireState state);
	void GetState();
	bool GetAllowDraw();
};

