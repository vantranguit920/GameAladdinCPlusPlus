#include "AppleThrow.h"



AppleThrow::AppleThrow(Sprite* sprite_bullet, SpriteSheet* sprite_sheet)
{
	this->sprite = sprite_bullet;
	animAple = new Animation(sprite_sheet);
	tag = Object::Bullets;
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->throwapple = this->sound->LoadSound("./Sound/Apple_Splat.wav");
	stateapple = applestate::fly;
	allowDraw = false;
	
}
void AppleThrow::NewApple(D3DXVECTOR2 position, bool flipflag) {
	SetBound(4, 4);
	this->sound->PlaySoundA(throwapple);
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
}
void AppleThrow::ChangeAnimation() {
	switch (stateapple)
	{
	case applestate::fly:
		animAple->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;
	case applestate::Bursting:
		animAple->SetFrame(position, flipFlag, 10, 1, 5, false);
		break;
	default:
		break;
	}
	
}
void AppleThrow::Update(float dt, Keyboard* key) {
	if (allowDraw)
	{
		ChangeAnimation();
		if (stateapple == applestate::fly) {
			this->SetVelocityY(this->velocity.y - 0.15);
		}
		else {
			if (animAple->GetIndex() == 5) {
				SetBound(0, 0);
				allowDraw = false;
				animAple->SetIndex(0);
				this->SetPosition(D3DXVECTOR2(0,0));
				stateapple = applestate::fly;
			}
		}
		Object::Update(dt, key);
		animAple->Update(dt, key);
		
	}
}
void AppleThrow::Render(Viewport* viewport) {
	if (allowDraw)
	{
		if (viewport->isContains(this->GetBound())) {

			sprite->SetData(
				animAple->GetRect(),
				animAple->GetCenter(),
				animAple->GetPosition(),
				animAple->GetScale(),
				animAple->GetTransform(),
				animAple->GetAngle()
			);
			this->sprite->SetScale(D3DXVECTOR2(0.7f, 0.7f));
			sprite->Render(viewport);
		}
		else {
			allowDraw = false;
			this->SetVelocity(0, 0);
		}
	}
}
void AppleThrow::OnCollision(Object *obj, D3DXVECTOR2 distance) {
	RECT board = this->GetBoard(distance);
	if (Collision::isCollision(board, obj->GetBound())) {
		D3DXVECTOR2 sideCollision;

		//Lấy thời gian va chạm
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);
		if (time < 1.0f)
		{
			position.x += distance.x * time;
			position.y += distance.y * time;
			this->SetVelocity(0, 0);
			stateapple = applestate::Bursting;
		}
		
	}
}
void AppleThrow::OnCollision() {
	this->SetVelocity(0, 0);
	stateapple = applestate::Bursting;
}
AppleThrow::~AppleThrow()
{
	
}
