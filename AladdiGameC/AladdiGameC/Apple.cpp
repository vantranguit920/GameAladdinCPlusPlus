#include "Apple.h"

Apple::Apple() {}
Apple::~Apple() {

}
Apple::Apple(Sprite* spApple, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spApple;
	this->aladdin = aladdin;
	this->AppleAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = AppleState::Show;

}


void Apple::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case AppleState::Hitted:
		//AppleAnim->SetFrame(position, flipFlag, 20, 4, 17, false);
		break;
	case AppleState::Show:
		AppleAnim->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;

	}
}

void Apple::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	if (abs(aladdin->GetPosition().x - position.x) < 40) {
		this->state = AppleState::Hitted;
	}

	if (timeout >= 0.2f) {

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	AppleAnim->Update(dt, key);
}
void Apple::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disApple) {
}
void Apple::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			AppleAnim->GetRect(),
			AppleAnim->GetCenter(),
			AppleAnim->GetPosition(),
			AppleAnim->GetScale(),
			AppleAnim->GetTransform(),
			AppleAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		AppleAnim->SetIndex(0);
	}
}
void Apple::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	AppleAnim->SetIndex(0);
}

bool Apple::GetAllowDraw() {
	return this->allowDraw;
}
void Apple::SetState(AppleState gState) {
	this->state = gState;
}
void Apple::GetState() {

}