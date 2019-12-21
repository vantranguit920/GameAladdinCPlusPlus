#include "Shop.h"

Shop::Shop() {}
Shop::~Shop() {

}
Shop::Shop(Sprite* spShop, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spShop;
	this->aladdin = aladdin;
	this->ShopAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = ShopState::Show;

}


void Shop::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case ShopState::Hitted:
		//ShopAnim->SetFrame(position, flipFlag, 20, 4, 17, false);
		break;
	case ShopState::Show:
		ShopAnim->SetFrame(position, flipFlag, 20, 0, 29, false);
		break;

	}
}

void Shop::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 40) {
		this->state = ShopState::Hitted;
	}

	if (timeout >= 0.2f) {

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	ShopAnim->Update(dt, key);
}
void Shop::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disShop) {
}
void Shop::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/

		this->sprite->SetData(
			ShopAnim->GetRect(),
			ShopAnim->GetCenter(),
			ShopAnim->GetPosition(),
			ShopAnim->GetScale(),
			ShopAnim->GetTransform(),
			ShopAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	/*}
	else {
		this->allowDraw = false;
		ShopAnim->SetIndex(0);
	}*/
}
void Shop::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	ShopAnim->SetIndex(0);
}

bool Shop::GetAllowDraw() {
	return this->allowDraw;
}
void Shop::SetState(ShopState gState) {
	this->state = gState;
}
void Shop::GetState() {

}