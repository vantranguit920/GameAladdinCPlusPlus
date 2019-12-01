#include "AladdinAnimation.h"



AladdinAnimation::AladdinAnimation()
{
}
void AladdinAnimation::standAnimation() {
	repeat = true;
	delay = 20;
	start = 0; end = 37;
}


void AladdinAnimation::jumpAnimation() {
	repeat = false;
	delay = 5;
	start = 91; end = 94;
}
void AladdinAnimation::fallAnimation() {
	repeat = false;
	delay = 10;
	start = 95; end = 99;
}
void AladdinAnimation::runAnimation() {
	repeat = true;
	delay = 5;
	start = 132; end = 143;
}
void AladdinAnimation::stopAnimation() {
	repeat = true;
	delay = 20;
	start = 29; end = 37;
}
void AladdinAnimation::attackAnimation() {
	repeat = true;
	delay = 5;
	start = 44; end = 49;
}
void AladdinAnimation::throwAnimation() {
	repeat = true;
	delay = 20;
	start = 43; end = 48;
}
void AladdinAnimation::crouchIdelAnimation() {
	repeat = true;
	delay = 20;
	start = 49; end = 52;
}
void AladdinAnimation::crouchAttackAnimation() {
	repeat = true;
	delay = 20;
	start = 53; end = 59;
}
void AladdinAnimation::runjumAnimation() {
	repeat = true;
	delay = 20;
	start = 60; end = 64;
}
void AladdinAnimation::runfallAnimation() {
	repeat = true;
	delay = 20;
	start = 65; end = 69;
}
void AladdinAnimation::jumpthrowAnimation() {
	repeat = true;
	delay = 20;
	start = 70; end = 74;
}
void AladdinAnimation::jumpAttackAnimation() {
	repeat = true;
	delay = 20;
	start = 75; end = 80;
}
void AladdinAnimation::springAnimation() {
	repeat = true;
	delay = 20;
	start = 81; end = 100;
}
void AladdinAnimation::climbVerticalAnimation() {
	repeat = true;
	delay = 20;
	start = 101; end = 110;
}
void AladdinAnimation::climbHorizontalMoveAnimation() {
	repeat = true;
	delay = 20;
	start = 111; end = 120;
}
void AladdinAnimation::climbHorizontalIdeAnimation() {
	repeat = true;
	delay = 20;
	start = 121; end = 125;
}
void AladdinAnimation::climAttackAnimation() {
	repeat = true;
	delay = 20;
	start = 126; end = 132;
}
void AladdinAnimation::climbVerticalJumpAnimation() {
	repeat = true;
	delay = 20;
	start = 133; end = 137;
}
void AladdinAnimation::climbVerticalFallAnimation() {
	repeat = true;
	delay = 20;
	start = 138; end = 141;
}
void AladdinAnimation::damageAnimation() {
	repeat = true;
	delay = 20;
	start = 142; end = 147;
}
void AladdinAnimation::deathAnimation() {
	repeat = true;
	delay = 20;
	start = 148; end = 160;
}
void AladdinAnimation::upAnimation() {
	repeat = true;
	delay = 20;
	start = 161; end = 162;
}
void AladdinAnimation::climbthrowAnimation() {
	repeat = true;
	delay = 20;
	start = 163; end = 168;
}
void AladdinAnimation::pushfallAnimation() {
	repeat = true;
	delay = 20;
	start = 169; end = 177;
}
void AladdinAnimation::winAnimation() {
	repeat = true;
	delay = 20;
	start = 178; end = 185;
}
void AladdinAnimation::Update(float dt, Keyboard* key) {
	Animation::Update(dt, key);
}
AladdinAnimation::~AladdinAnimation()
{
}
