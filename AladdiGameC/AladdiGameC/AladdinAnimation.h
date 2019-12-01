#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Animation.h"
#include "SpriteSheet.h"

class AladdinAnimation:public Animation
{

public:
	AladdinAnimation(SpriteSheet *info) :Animation(info) {}
	AladdinAnimation();
	~AladdinAnimation();
	void standAnimation();

	void jumpAnimation();
	void fallAnimation();
	void runAnimation();
	void stopAnimation();
	void attackAnimation();
	void throwAnimation();
	void crouchIdelAnimation();
	void crouchAttackAnimation();
	void runjumAnimation();
	void runfallAnimation();
	void jumpthrowAnimation();
	void jumpAttackAnimation();
	void springAnimation();
	void climbVerticalAnimation();
	void climbHorizontalMoveAnimation();
	void climbHorizontalIdeAnimation();
	void climAttackAnimation();
	void climbVerticalJumpAnimation();
	void climbVerticalFallAnimation();
	void damageAnimation();
	void deathAnimation();
	void upAnimation();
	void climbthrowAnimation();
	void pushfallAnimation();
	void winAnimation();
	void Update(float dt, Keyboard* key);
};


