#include "AladdinAnimation.h"



AladdinAnimation::AladdinAnimation()
{
}
void AladdinAnimation::standAnimation() {
	repeat = true;
	delay = 20;
	start = 0; end = 37;
	//start = 223; end = 227;
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
	delay = 7;
	start = 39; end = 44;
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
	delay = 7;
	start = 112; end = 116;
}
void AladdinAnimation::jumpAttackAnimation() {
	repeat = true;
	delay = 5;
	start = 118; end = 122;
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
void AladdinAnimation::VerticalJumpAnimation()
{
	repeat = true;
	delay = 5;
	start = 82; end = 87;
}
void AladdinAnimation::climbVerticalFallAnimation() {
	repeat = true;
	delay = 20;
	start = 138; end = 141;
}
void AladdinAnimation::damageAnimation() {
	repeat = true;
	delay = 20;
	start = 62; end = 65;
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
void AladdinAnimation::downAnimation()
{
	repeat = false;
	delay = 10;
	start = 66; end = 68;
}
void AladdinAnimation::downThrow()
{
	repeat = true;
	delay = 10;
	start = 69; end = 73;
}
void AladdinAnimation::swingAnim()
{
	repeat = false;
	delay = 10;
	start = 153; end = 153;
}
void AladdinAnimation::swingjump()
{
	repeat = false;
	delay = 10;
	start = 190; end = 198;
}
void AladdinAnimation::swingGoAnim()
{
	repeat = true;
	delay = 10;
	start = 153; end = 162;
}
void AladdinAnimation::swingAttack()
{
	repeat = true;
	delay = 5;
	start = 183; end = 189;
}
void AladdinAnimation::swingThrow()
{
	repeat = true;
	delay = 7;
	start = 176; end = 182;
}
void AladdinAnimation::bleddbyboss()
{
	repeat = true;
	delay = 10;
	start = -1; end = 1;
}
void AladdinAnimation::swingGodown()
{
	repeat = true;
	delay = 10;
	start = 288; end = 296;
}
void AladdinAnimation::dowmAttackAnim()
{
	repeat = true;
	delay = 7;
	start = 74; end = 80;
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
