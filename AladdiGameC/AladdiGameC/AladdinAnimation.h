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
	void VerticalJumpAnimation();
	void climbVerticalFallAnimation();
	void damageAnimation();
	void deathAnimation();
	void upAnimation();
	void downAnimation();
	void downThrow();
	void swingAnim();
	void swingjump();
	void swingGoAnim();
	void swingAttack();
	void swingThrow();
	void bleddbyboss();
	void swingGodown();
	void dowmAttackAnim();
	void climbthrowAnimation();
	void pushfallAnimation();
	void winAnimation();
	void Update(float dt, Keyboard* key);
};


