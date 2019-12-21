#include "Fire.h"

Fire::Fire() {}
Fire::~Fire() {

}
Fire::Fire(Sprite* spFire, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spFire;
	this->aladdin = aladdin;
	this->FireAnim = new Animation(info);
	SetBound(0, 0);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	this->SetVelocity(0,0);
	
	allowDraw = false;
	flipFlag = false;
	this->state = FireState::Push;
}


void Fire::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case FireState::Push:
		FireAnim->SetFrame(position, flipFlag, 10, 30, 37, true);
		break;

	}
}

void Fire::Update(float dt, Keyboard* key) {
	if (!allowDraw)
		return;
	if (this->position.x < 660 || this->position.x>1320) {
		this->allowDraw = false;
		this->SetBound(0, 0);
		position = D3DXVECTOR2(0, 0);
		velocity = D3DXVECTOR2(0, 0);
		transform = D3DXVECTOR2(0, 0);
		this->SetVelocity(0, 0);
	}
	ChangeAnimation(key);
	Object::Update(dt, key);
	FireAnim->Update(dt, key);
}
void Fire::OnCollision(Object* obj, D3DXVECTOR2 distance) {
	RECT board = this->GetBoard(distance);
	if (Collision::isCollision(this->GetBound2(), obj->GetBound())) {
		//if (!Collision::isNested(GetBound2(), obj->GetBound()))
		//{
		//	D3DXVECTOR2 sideCollision;
		//	//Lấy thời gian va chạm
		//	float time = Collision::CollisionAABB(GetBound2(), obj->GetBound(), distance, sideCollision);
		//	if (time < 1.0f)
		//	{
				
		/*	}
		}*/
		

	}
}
Animation * Fire::getAnim()
{
	return this->FireAnim;
}
void Fire::Render(Viewport* viewport) {
	if (this->GetAllowDraw()) {
		this->sprite->SetData(
			FireAnim->GetRect(),
			FireAnim->GetCenter(),
			FireAnim->GetPosition(),
			FireAnim->GetScale(),
			FireAnim->GetTransform(),
			FireAnim->GetAngle());
		if (this->GetFlipFlag()) {
			this->sprite->SetScale(D3DXVECTOR2(-1.0f, 1.0f));
		}
		else {
			this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		}
	
		this->sprite->Render(viewport);
	}
}
void Fire::NewFire(D3DXVECTOR2 position, bool flipflag)
{
	SetBound(30, 30);
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
	if (flipFlag) {
		this->SetVelocity(-0.5f, 0);
	}
	else {
		this->SetVelocity(0.5f, 0);
	}
}
void Fire::SetAllowDraw(bool allow) {
	this->allowDraw = allow;	
}

bool Fire::GetAllowDraw() {
	return this->allowDraw;
}
void Fire::SetState(FireState gState) {
	this->state = gState;
}
void Fire::GetState() {

}
