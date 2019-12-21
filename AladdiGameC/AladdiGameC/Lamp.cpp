#include "Lamp.h"



Lamp::Lamp()
{
}

Lamp::Lamp(Sprite *sprite, SpriteSheet* spriteSheet, Aladdin * _aladin) {
	this->sprite = sprite;
	this->aladin = _aladin;
	this->animalamp = new Animation(spriteSheet);
	this->animalamp->SetFrame(D3DXVECTOR2(20, 50), true, 20, 31, 32, true);
}
void Lamp::Update(float dt, Keyboard* key) {
	if(aladin->GetHP()>=0)
		this->animalamp->SetFrame(D3DXVECTOR2(20, 50), true, 20, aladin->GetHP()-1, aladin->GetHP(), true);
	animalamp->Update(dt, key);
}
void Lamp::render() {
	this->sprite->SetData(animalamp->GetRect(),
		animalamp->GetCenter(),
		animalamp->GetPosition(),
		animalamp->GetScale(),
		animalamp->GetTransform(),
		animalamp->GetAngle());
	this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->sprite->Render();
}
Lamp::~Lamp()
{
}
