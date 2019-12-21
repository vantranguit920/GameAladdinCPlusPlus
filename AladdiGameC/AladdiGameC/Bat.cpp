#include "Bat.h"



void Bat::ChangeAnim(Keyboard * key)
{
	//3-10
	switch (this->state)
	{
	case BatState::stop:
		batAnim->SetFrame(position, flipFlag, 10, 6, 6, false);
		break;
	case BatState::fly:
		batAnim->SetFrame(position, flipFlag, 7, 7, 14, true);
		break;
	case BatState::die:
		batAnim->SetFrame(position, flipFlag, 10, 0, 5, true);
		break;
	case BatState::kick:
		batAnim->SetFrame(position, flipFlag, 7, 7, 14, true);
		break;
	}

}

void Bat::Update(float dt, Keyboard * key)
{
	if (dyed)
		return;
	if (this->state == BatState::die) {
		this->SetVelocity(0, 0);
		if (batAnim->GetIndex() == 5) {
			dyed = true;
			allowDraw = false;
		}
	}else if (this->state!=BatState::kick&&abs(aladin->GetPosition().x - position.x) < 100 && abs(aladin->GetPosition().y - position.y) < 150)
	{
		this->state = BatState::fly;
	}

	if (aladin->GetPosition().x - position.x < 0) {
		this->flipFlag = false;

	}
	else {
		this->flipFlag = true;
	}


	if (this->state == BatState::fly) {
		if (!isFly&&flipFlag) {
			this->SetVelocity(-0.7, -1.0);
			isFly = true;
		}
		else if (!isFly && !flipFlag)
		{
			this->SetVelocity(0.7, -1.0);
			isFly = true;
		}
		if (this->position.x - startpos.x > 80) {
			this->SetVelocityX(-0.7);
		}
		else
			if (this->position.x - startpos.x < -80) {
				this->SetVelocityX(0.7);
			}

		if (this->position.y - startpos.y < -80) {
			this->SetVelocityY(1.0);
		}
		else
			if (this->position.y - startpos.y > 80) {
				this->SetVelocityY(-1.0);
			}


		if (abs(this->position.y - startpos.y) < 5 && abs(this->position.x - startpos.x) < 5 && timecout > 7.0f)
		{
			this->position = startpos;
			this->state = BatState::stop;
			this->SetVelocity(0, 0);
			isFly = false;
			timecout = 0;
			timekick = 0;
		}
		if (timekick >= 3.0f&&abs(aladin->GetPosition().x - position.x) < 150 && abs(aladin->GetPosition().y - position.y) < 150) {
			this->state = BatState::kick;
			timekick = 0;
		}
		timecout += dt;
		timekick += dt;
	}
	else if (this->state == BatState::kick) {
		D3DXVECTOR2 n = D3DXVECTOR2(aladin->GetPosition().x - position.x, aladin->GetPosition().y+30 - position.y);
		this->SetVelocity(n.x / 50, n.y / 50);
		if (Collision::isCollision(this->GetBound2(), aladin->GetBound2())) {
			this->state = BatState::fly;
			aladin->getState()->BleedState((int)(!flipFlag),1);
			D3DXVECTOR2 k = D3DXVECTOR2(startpos.x - position.x, startpos.y - position.y);
			this->SetVelocity(k.x / 60, k.y / 60);
		}
	}
	
	ChangeAnim(key);
	Object::Update(dt, key);
	batAnim->Update(dt, key);
}

void Bat::Render(Viewport * viewport)
{
	/*if (viewport->isContains(this->GetBound())&&!dyed) {
		this->allowDraw = true;*/
	if (this->GetAllowDraw()) {
		this->sprite->SetData(batAnim->GetRect(),
			batAnim->GetCenter(),
			batAnim->GetPosition(),
			batAnim->GetScale(),
			batAnim->GetTransform(),
			batAnim->GetAngle());
		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}
	
	/*}
	else {
		this->allowDraw = false;
		batAnim->SetIndex(0);
	}*/
}

void Bat::OnCollision(Object * obj, D3DXVECTOR2 distance)
{
	if (obj->GetTag() == Object::Tag::Player) {
		Aladdin *ala = (Aladdin*)obj;
		if (ala->getState()->delayComplete) {
			RECT board = this->GetBoard(distance);
			if (Collision::isCollision(board, ala->GetBoundKnif())) {
				if (!Collision::isNested(this->GetBound2(), ala->GetBoundKnif()))
				{
					D3DXVECTOR2 sideCollision;
					float time = Collision::CollisionAABB(this->GetBound2(), ala->GetBoundKnif(), distance, sideCollision);
					if (time < 1.0f)
						ala->getState()->delayComplete = false;
						this->state = BatState::die;
				}
				else {
					ala->getState()->delayComplete = false;
					this->state = BatState::die;
				}
			}
		}
	}
}

void Bat::OnCollision()
{
	this->state = BatState::die;
}



Bat::Bat(Sprite * sprite, SpriteSheet * info, D3DXVECTOR2 pos, Aladdin *aladin)
{
	this->sprite = sprite;
	this->aladin = aladin;
	batAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	this->allowDraw = true;
	this->SetBound(30, 34);
	flipFlag = false;
	this->position = pos;
	this->startpos = pos;
	this->state = BatState::stop;
	dyed = false;
	isFly = false;

}

Bat::Bat()
{
}


Bat::~Bat()
{
}
