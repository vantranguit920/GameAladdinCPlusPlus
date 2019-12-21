#include "HeadAla.h"



HeadAla::HeadAla()
{
}

HeadAla::HeadAla(Sprite *sprite, SpriteSheet* spriteSheet) {
	this->sprite = sprite;
	this->animaHead = new Animation(spriteSheet);
	this->animaHead->SetFrame(D3DXVECTOR2(20, 470), true, 10, 33, 33, false);
	this->spritescore = sprite;
	this->animscore = new Animation(spriteSheet);
	this->animscore->SetFrame(D3DXVECTOR2(45, 475), true, 10, 36, 36, false);
}

void HeadAla::render() {
	this->sprite->SetData(animaHead->GetRect(),
		animaHead->GetCenter(),
		animaHead->GetPosition(),
		animaHead->GetScale(),
		animaHead->GetTransform(),
		animaHead->GetAngle());
	this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->sprite->Render();

	this->spritescore->SetData(animscore->GetRect(),
		animscore->GetCenter(),
		animscore->GetPosition(),
		animscore->GetScale(),
		animscore->GetTransform(),
		animscore->GetAngle());
	this->spritescore->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->spritescore->Render();
}
void HeadAla::Update(float dt, Keyboard* key) {
	
	animaHead->Update(dt, key);
	animscore->Update(dt, key);
	
}
HeadAla::~HeadAla()
{
}
