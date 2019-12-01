#include "AladinState.h"



AladinState::AladinState()
{
}
AladinState::AladinState(Object *Aladdin)
{
	this->Aladdin = Aladdin;
	this->state = State::Standing;

	this->sound = new Sound(Graphic::getInstance()->GetHwnd());
	this->sound->Init_DirectSound();

	this->attacksound = this->sound->LoadSound("./Sound/Low_Sword.wav");

}
AladinState::State AladinState::GetState() {
	return state;

}
void AladinState::CheckSide(Keyboard* keyboard) {
	if (keyboard->IsKeyDown(DIK_RIGHT))
	{
		Aladdin->SetVelocityX(2.0f);
		Aladdin->SetFlipFlag(false);
	}
	else if (keyboard->IsKeyDown(DIK_LEFT))
	{
		Aladdin->SetVelocityX(-2.0f);;
		Aladdin->SetFlipFlag(true);
	}
	else Aladdin->SetVelocityX(0);
}
void AladinState::SetState(AladinState::State state) {
	this->state = state;
}
void AladinState::StandState(Keyboard *key) {

	if (key->IsKeyDown(DIK_RIGHT) || key->IsKeyDown(DIK_LEFT))
	{
		this->state = AladinState::State::run;
		if (key->IsKeyDown(DIK_C)) {
			this->state = State::jum;
		}

	}
	else
	{
		if (key->IsKeyDown(DIK_X)) {

			this->state = AladinState::State::Attack;
			this->attack = true;
			this->delayattack = true;
		}
		else
		{


			if (key->IsKeyDown(DIK_C)) {
				this->state = State::jum;
			}
			else
			{


				if (attack)
				{
					this->state = AladinState::State::Attack;
				}
				else
				{
					this->state = State::Standing;
				}


			}
		}
	}



}
void AladinState::jumState(Keyboard* key) {
	if (!isjum) {
		startJum = Aladdin->GetPosition().y;
		Aladdin->SetVelocityY(JumpSpeed);
		isjum = true;
	}

	if (isjum) {
		if (Aladdin->GetPosition().y-startJum  > JumpMax) {
			Aladdin->SetVelocityY(-JumpSpeed);
			this->state = State::fall;
			isjum = false;
		}
	}
	
}
void AladinState::fallState(Keyboard* key) {

	/*if (Aladdin->GetVelocity().y == 0) {
		this->state = State::Standing;
	}
	else {
		Aladdin->SetVelocityY(Aladdin->GetVelocity().y - FallAcceleration);
		this->state = State::fall;
	}*/

	if (Aladdin->GetPosition().y <= startJum) {
		Aladdin->SetVelocityY(0);
		this->state = State::Standing;
	}
	
}



void AladinState::AttackState(Keyboard *key) {


	if (!this->attack) {
		switch (this->state)
		{
		case State::Attack:
			StandState(key);
			break;
		}

	}

	if (key->GIsKeyDown(DIK_X)) {

		this->sound->PlaySoundA(attacksound);
	}

}

void AladinState::RunState(Keyboard *key) {
	if (key->IsKeyDown(DIK_RIGHT) || key->IsKeyDown(DIK_LEFT))
	{
		this->state = State::run;

	}
	else
	{
		this->state = State::Standing;
	}
}

bool AladinState::getAttack() {
	return attack;
}
void AladinState::Update(float dt, Keyboard* keyboard) {


	if (delayattack)
	{

		delayattacktime += dt;

		if (delayattacktime > 0.42f)
		{
			printf("%f\n", dt);
			attack = false;
			delayattack = false;
			delayattacktime = 0;

		}
	}
}
AladinState::~AladinState()
{
}
