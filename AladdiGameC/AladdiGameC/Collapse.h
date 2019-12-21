#pragma once
#include "Object.h"
#include "Define.h"
#include "Sprite.h"
#include "SpriteSheet.h"

class Collapse : public Object
{
protected:
	
	SpriteSheet* spriteSheetCollapse;
	int start, end;
	int listRECT[4];
	float timecout = 0.0f;
public:
	Object* element[4];
	enum CollapseType
	{
		CollapseSkeleton,
		CollapseGuard		
	};
	CollapseType type;

	Collapse(Sprite *sprite_collapse, SpriteSheet* spriteSheet);
	Collapse();
	~Collapse();

	void NewCollapse(D3DXVECTOR2 pos, int enemyType);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* view);
};