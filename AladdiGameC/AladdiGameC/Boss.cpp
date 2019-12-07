#include "Boss.h"

Boss::Boss() {}
Boss::~Boss() {

}
Boss::Boss(Sprite* spBoss, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spBoss;
	this->aladdin = aladdin;
	this->BossAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;

	SetBound(10, 10);
	allowDraw = true;
	flipFlag = false;
	this->state = BossState::AttackPush;
}


void Boss::ChangeAnimation(Keyboard* key) {
	D3DXVECTOR2 posSnake;
	posSnake.x = 20;
	posSnake.y = 67;
	switch (this->state) {
	case BossState::AttackPush:
		BossAnim->SetFrame(position, flipFlag, 20, 0, 7, false);
		break;
	case BossState::AttackFire:
		BossAnim->SetFrame(position, flipFlag, 20, 8, 14, false);
		break;
	case BossState::SnakeDisappear:
		
		BossAnim->SetFrame(position + posSnake, flipFlag, 20, 34, 43, false);
		
		break;
	case BossState::SnakeAttack:
		BossAnim->SetFrame(position + posSnake, flipFlag, 20, 44, 54, false);
		break;

	}
}

void Boss::Update(float dt, Keyboard* key) {

	D3DXVECTOR2 posAla = aladdin->GetPosition();
	/*if (abs(aladdin->GetPosition().x - position.x) < 40) {
		this->state = BossState::AttackFire;
	}*/

	if (timeout >= 3.0f) {
		if (this->state == BossState::AttackFire) {
			this->state = BossState::AttackPush;
		}
		else if (this->state == BossState::AttackPush) {
			this->state = BossState::SnakeAttack;
		}
		else if (this->state == BossState::SnakeAttack) {
			this->state = BossState::SnakeDisappear;
		}
		else if (this->state == BossState::SnakeDisappear) {
			this->state = BossState::AttackFire;
		}

		timeout = 0.0;
	}

	timeout += dt;
	ChangeAnimation(key);
	Object::Update(dt, key);
	BossAnim->Update(dt, key);
}
void Boss::OnCollision(Object* obj, D3DXVECTOR2 distance, D3DXVECTOR2 disBoss) {
}
void Boss::Render(Viewport* viewport) {
	if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;

		this->sprite->SetData(
			BossAnim->GetRect(),
			BossAnim->GetCenter(),
			BossAnim->GetPosition(),
			BossAnim->GetScale(),
			BossAnim->GetTransform(),
			BossAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.5, 1.5));
		this->sprite->Render(viewport);
	}
	else {
		this->allowDraw = false;
		BossAnim->SetIndex(0);
	}
}
void Boss::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	BossAnim->SetIndex(0);
}

bool Boss::GetAllowDraw() {
	return this->allowDraw;
}
void Boss::SetState(BossState gState) {
	this->state = gState;
}
void Boss::GetState() {

}