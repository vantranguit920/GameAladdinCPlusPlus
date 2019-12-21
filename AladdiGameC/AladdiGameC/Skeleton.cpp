#include "Skeleton.h"

Skeleton::Skeleton() {}
Skeleton::~Skeleton() {}
Skeleton::Skeleton(Sprite* spSkeleton, SpriteSheet* info, D3DXVECTOR2 pos, Aladdin* aladdin) {
	this->sprite = spSkeleton;
	this->aladdin = aladdin;
	this->SkeletonAnim = new Animation(info);
	transform = D3DXVECTOR2(0, 0);
	position = pos;
	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();
	this->soundSkeleton = this->sound->LoadSound("./Sound/Skeleton.wav");
	SetBound(30, 100);
	allowDraw = true;
	flipFlag = false;
	this->state = SkeletonState::Sit;
	collapse = new Collapse(spSkeleton, info);
}


void Skeleton::ChangeAnimation(Keyboard* key) {
	switch (this->state) {
	case SkeletonState::Sit:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 0, 0, false);
		break;
	case SkeletonState::Stand:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 0, 19, false);
		break;
	case SkeletonState::Died:
		SkeletonAnim->SetFrame(position, flipFlag, 20, 20, 25, false);
		break;
	}
}

void Skeleton::Update(float dt, Keyboard* key) {


	if (!dyed) {
		if (abs(aladdin->GetPosition().x - position.x) < 150 && abs(aladdin->GetPosition().y - position.y) < 100) {

			this->state = SkeletonState::Stand;
			isStand = true;
		}
		if (isStand) {
			timeout += dt;
			if (timeout > 6.0f) {
				this->state = SkeletonState::Died;
				collapse->NewCollapse(this->position, Collapse::CollapseType::CollapseSkeleton);
				this->sound->PlaySoundA(soundSkeleton);
				dyed = true;
				isStand = false;
				timeout = 0;
			}
		}
	}
	else {
		for (int i = 0; i <= 3; i++) {
			if (collapse->element[i]->GetAllowDraw()) {
				if (Collision::isCollision(aladdin->GetBound2(), collapse->element[i]->GetBound())) {

					aladdin->getState()->BleedState((int)collapse->element[i]->GetFlipFlag(), 1);
				}
			}
			
		}
		collapse->Update(dt, key);
		if (SkeletonAnim->GetIndex() == 25) {
			this->allowDraw = false;
		}
	}
	
	
	
	ChangeAnimation(key);
	Object::Update(dt, key);
	SkeletonAnim->Update(dt, key);
}
void Skeleton::OnCollision(Object* obj, D3DXVECTOR2 distance) {
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
				}
				else {				
					ala->getState()->delayComplete = false;
					this->state = SkeletonState::Died;
					dyed = true;
					isStand = false;
					timeout = 0;
				}
			}
		}
	}
}
void Skeleton::OnCollision()
{
	this->state = SkeletonState::Died;
	dyed = true;
	isStand = false;
	timeout = 0;
}
void Skeleton::Render(Viewport* viewport) {
	/*if (viewport->isContains(this->GetBound())) {
		this->allowDraw = true;*/
	if (allowDraw) {
		this->sprite->SetData(
			SkeletonAnim->GetRect(),
			SkeletonAnim->GetCenter(),
			SkeletonAnim->GetPosition(),
			SkeletonAnim->GetScale(),
			SkeletonAnim->GetTransform(),
			SkeletonAnim->GetAngle());

		this->sprite->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		this->sprite->Render(viewport);
	}
	
	if (dyed) {
		collapse->Render(viewport);
	}
	/*}
	else {
		this->allowDraw = false;
		SkeletonAnim->SetIndex(0);
	}*/
}
void Skeleton::SetAllowDraw(bool allow) {
	this->allowDraw = allow;
	SkeletonAnim->SetIndex(0);
}

bool Skeleton::GetAllowDraw() {
	return this->allowDraw;
}
void Skeleton::SetState(SkeletonState gState) {
	this->state = gState;
}
void Skeleton::GetState() {

}