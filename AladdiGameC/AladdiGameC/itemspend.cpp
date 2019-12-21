#include "itemspend.h"



itemspend::itemspend()
{
}

itemspend::itemspend(Sprite *sprite, SpriteSheet* spriteSheet, Aladdin* aladin) {
	this->sprite = sprite;
	this->ala = aladin;
	this->animaHead = new Animation(spriteSheet);
	this->animaHead->SetFrame(D3DXVECTOR2(380, 470), true, 10, 34, 34, false);
	for (int i = 0; i < 2; i++) {
		this->score[i] = new Score(sprite, spriteSheet, D3DXVECTOR2(point, 470));
		point += 20;
	}


}

void itemspend::render() {
	this->sprite->SetData(animaHead->GetRect(),
		animaHead->GetCenter(),
		animaHead->GetPosition(),
		animaHead->GetScale(),
		animaHead->GetTransform(),
		animaHead->GetAngle());
	this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
	this->sprite->Render();
	for (int i = 0; i < 2; i++) {
		this->score[i]->render();
	}

}
void itemspend::Update(float dt, Keyboard* key) {
	int a, b;
	a = ala->numspend / 10;
	b = ala->numspend % 10;
	animaHead->Update(dt, key);
	this->score[0]->Update(dt, key, a);
	this->score[1]->Update(dt, key, b);

}
itemspend::~itemspend()
{
}
