#pragma once
#include "Object.h"
#include "Viewport.h"
#include "Sprite.h"
#include "Animation.h"
#include "Aladdin.h"
#include "SpriteSheet.h"
#include "Keyboard.h"

class  SavePosition :public Object
{
protected:
	Animation* SavePositionAnim;
	Aladdin* aladdin;
	Viewport* viewport;
	float timeout = 0.0f;
public:
	SavePosition();
	SavePosition(Sprite* spSavePosition, SpriteSheet* ifoSavePosition, D3DXVECTOR2 pos, Aladdin* aladdin);
	~SavePosition();

	enum SavePositionState {
		Show,
		Hitted,
		Destroy
	};

	SavePositionState state;
	void ChangeAnimation(Keyboard* key);

	void OnCollision(Object* obj, D3DXVECTOR2 distance);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);

	void SetAllowDraw(bool allow);
	void SetState(SavePositionState state);
	void GetState();
	bool GetAllowDraw();
};

