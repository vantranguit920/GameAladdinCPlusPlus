#include "Fire.h"

Fire::Fire() {}
Fire::~Fire() {

}
Fire::Fire(Sprite* spFire, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spFire;
	this->aladdin = aladdin;
	this->FireAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = FireState::Push;
}


void Fire::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case FireState::Push:
		FireAnim->SetFrame(position, flipFlag, 20, 20, 25, false);
		break;
	case FireState::Burn:
		FireAnim->SetFrame(position, flipFlag, 20, 15, 19, false);
		break;
	case FireState::FireAttack:

		FireAnim->SetFrame(position, flipFlag, 20, 26, 33, false);

		break;
	
	}
}

void Fire::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	/*if (abs(aladdin->GetPosition().x - position.x) < 40) {
		this->state = FireState::AttackFire;
	}*/

	if (timeout >= 3.0f) {
		if (this->state == FireState::Push) {
			this->state = FireState::Burn;
		}
		else if (this->state == FireState::Burn) {
			this->state = FireState::FireAttack;
		}
		else if (this->state == FireState::FireAttack) {
			this->state = FireState::Push;
		}
		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	FireAnim->Update(dt, key);
}
void Fire::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disFire) {
}
void Fire::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			FireAnim->GetRect(),
			FireAnim->GetCenter(),
			FireAnim->GetPosition(),
			FireAnim->GetScale(),
			FireAnim->GetTransform(),
			FireAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		FireAnim->SetIndex(0);
	}
}
void Fire::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	FireAnim->SetIndex(0);
}

bool Fire::GetAllowDraw() {
	return this->allowDraw;
}
void Fire::SetState(FireState gState) {
	this->state = gState;
}
void Fire::GetState() {

}