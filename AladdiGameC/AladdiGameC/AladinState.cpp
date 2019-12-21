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
	isDown = false;
	this->attacksound = this->sound->LoadSound("./Sound/Low_Sword.wav");
	this->Bleedsound = this->sound->LoadSound("./Sound/Aladdin_Hurt.wav");


}
void AladinState::BleedState(int sides, int dame)
{
	this->side = sides;
	isbleed = true;
	damaged = dame;
	sound->PlaySoundA(Bleedsound);
}
void AladinState::BleedState(int side)
{
	this->side = side;
	isStarClip = true;
	
}
void AladinState::BleedbyBoss(int damge)
{
	isbleedbyboss = true;
	damaged = damge;
	sound->PlaySoundA(Bleedsound);
}
void AladinState::jumthrowState(Keyboard * key)
{
	if (isjum) {
		if (Aladdin->GetPosition().y - startJum > JumpMax) {
			Aladdin->SetVelocityY(-JumpSpeed);
			fallatackState(key);
			isjum = false;
		}

	}
	if (!delayThrow) {
		switch (state)
		{
		case State::jumpthrow:
			fallthrow(key);
		default:
			break;
		}
	}

}
void AladinState::fallthrow(Keyboard * key)
{
	isfall = true;
	if (Aladdin->GetVelocity().y == 0) {
		this->state = State::Standing;
		isfall = false;
	}
	else {
		Aladdin->SetVelocityY(Aladdin->GetVelocity().y - FallAcceleration);
	}
}
AladinState::State AladinState::GetState() {
	return state;

}
void AladinState::CheckSide(Keyboard* keyboard) {
	if (isbleed)
		return;
	if (!delayThrow && !delayattack) {
		if (keyboard->IsKeyDown(runRight))
		{
			if (!isDown)
				Aladdin->SetVelocityX(2.0f);
			Aladdin->SetFlipFlag(false);
		}
		else if (keyboard->IsKeyDown(runLeft))
		{
			if (!isDown)
				Aladdin->SetVelocityX(-2.0f);;
			Aladdin->SetFlipFlag(true);
		}
		else Aladdin->SetVelocityX(0);
	}

}
void AladinState::SetState(AladinState::State state) {
	this->state = state;
}
void AladinState::StandState(Keyboard *key) {
	isThrow = false;
	isjum = false;
	isDown = false;
	if (isbleed||isbleedbyboss)
		return;
	if (key->IsKeyDown(runRight) || key->IsKeyDown(runLeft))
	{
		this->state = AladinState::State::run;
		if (key->IsKeyDown(jumkey)) {
			this->state = State::jum;
		}

	}
	else
	{
		if (key->IsKeyDown(attackkey)) {
			if (!isbleed) {
				this->state = AladinState::State::Attack;
				this->attack = true;
				this->delayattack = true;
			}
			
		}
		else
		{


			if (key->IsKeyDown(jumkey)) {
				this->state = State::jum;
			}
			else
			{

				if (key->IsKeyDown(throwkey)) {
					isThrow = true;
					this->state = AladinState::State::standthrow;
					this->delayThrow = true;
				}
				else {
					if (key->IsKeyDown(downkey)) {
						this->state = AladinState::State::down;
						isDown = true;
					}
					else {
						if (attack)
						{
							this->state = AladinState::State::Attack;
						}
						else
						{
							if (Aladdin->GetVelocity().y == -2) {
								this->state = State::fall;
							}
							else {
								Aladdin->SetVelocityY(-2);
								this->state = State::Standing;
							}

						}
					}

				}





			}
		}
	}



}
void AladinState::standthrows(Keyboard* key) {
	isjum = false;
	if (!delayThrow) {
		switch (state)
		{
		case State::standthrow:
			this->state = State::Standing;
			break;
		case State::swingThrow:
			this->state = State::swinggo;
			break;
		case State::downthrow:
			this->state = State::down;
			downState(key);
			break;
		default:
			break;
		}
	}
}
void AladinState::jumState(Keyboard* key) {
	
	if (!isjum) {
		startJum = Aladdin->GetPosition().y;
		Aladdin->SetVelocityY(JumpSpeed);
		isjum = true;
	}
	if (key->IsKeyDown(runLeft) || key->IsKeyDown(runRight)) {
		state = State::verticalJump;
	}
	else {
		if (key->IsKeyDown(attackkey)) {
			state = State::jumAttack;
			this->attack = true;
			this->delayattack = true;
		}
		else {
			if (key->IsKeyDown(throwkey)) {
				state = State::jumpthrow;
				this->delayThrow = true;
				isThrow = true;
			}
		}
	}
	if (isjum) {
		if (Aladdin->GetPosition().y - startJum > JumpMax) {
			Aladdin->SetVelocityY(-JumpSpeed);
			this->state = State::fall;
			isjum = false;
		}
	}

}

void AladinState::jumAtackState(Keyboard * key)
{
	injum = true;
	if (isjum) {
		if (Aladdin->GetPosition().y - startJum > JumpMax) {
			Aladdin->SetVelocityY(-JumpSpeed);
			fallatackState(key);
			isjum = false;
		}

	}
	if (!this->attack) {
		delayComplete = true;
		switch (this->state)
		{
		case State::jumAttack:
			fallatackState(key);
			break;
		}

	}

	if (key->GIsKeyDown(attackkey)) {

		this->sound->PlaySoundA(attacksound);
	}
}

void AladinState::fallState(Keyboard* key) {
	injum = false;
	isfall = true;
	if (Aladdin->GetVelocity().y == 0) {
		this->state = State::Standing;
		isfall = false;
	}
	else {
		Aladdin->SetVelocityY(Aladdin->GetVelocity().y - FallAcceleration);
		this->state = State::fall;
	}
}

void AladinState::downState(Keyboard * key)
{
	if (!key->GIsKeyDown(downkey)) {
		this->state = AladinState::State::Standing;
		isDown = false;
	}
	else {
		if (key->IsKeyDown(attackkey)) {
			this->state = State::downattack;
			this->attack = true;
			this->delayattack = true;
		}
		else {
			if (key->IsKeyDown(throwkey)) {
				this->state = State::downthrow;
				this->delayThrow = true;
				isThrow = true;
			}
		}
	}

}

void AladinState::fallatackState(Keyboard * key)
{
	isfall = true;
	if (Aladdin->GetVelocity().y == 0) {
		this->state = State::Standing;
		isfall = false;
	}
	else {
		Aladdin->SetVelocityY(Aladdin->GetVelocity().y - FallAcceleration);
	}
}

bool AladinState::isbleeds()
{
	return isbleed;
}
void AladinState::swinggostate(Keyboard * key, Object* rope)
{
	if (attack||delayThrow)
		return;
	Aladdin->SetVelocity(0, 0);
	if (key->GIsKeyDown(upkey) && (Aladdin->GetBound2().top <= rope->GetBound().top)) {
		Aladdin->SetVelocityY(1.0f);
		state = State::swinggo;
	}
	else {
		if (key->IsKeyDown(jumkey)) {
			this->state = State::swingjump;
			Aladdin->SetVelocityY(JumpSpeed);
			isswing = false;

		}
		else {
			if (key->IsKeyDown(attackkey)) {
				state = State::swingattack;
				this->attack = true;
				this->delayattack = true;
			}
			else {
				if (key->IsKeyDown(throwkey)) {
					state = State::swingThrow;
					this->delayThrow = true;
					isThrow = true;
				}
				else {
					if (Aladdin->GetBound2().top >= rope->GetBound().bottom) {
						if (key->GIsKeyDown(downkey)) {
							Aladdin->SetVelocityY(-1.0f);
							state = State::swingdown;
						}
						else {
							state = State::swing;
						}
					}
					else {
						this->state = State::fall;
						Aladdin->SetVelocityY(-JumpSpeed);
						isswing = false;
					}
				}
				
			}

		}



	}


}

void AladinState::AttackState(Keyboard *key) {
	//isjum = false;
	if (!this->attack) {
		delayComplete = true;
		switch (this->state)
		{
		case State::Attack:
			StandState(key);
			break;
		case State::jumAttack:
			fallState(key);
			break;
		case State::downattack:
			this->state = State::down;
			downState(key);
			break;
		case State::swingattack:
			this->state = State::swinggo;
			downState(key);
			break;
		}

	}

	if (key->GIsKeyDown(attackkey)) {

		this->sound->PlaySoundA(attacksound);
	}

}

void AladinState::RunState(Keyboard *key) {
	delayComplete = false;
	isjum = false;
	if (isbleed)
		return;
	if (key->IsKeyDown(runRight) || key->IsKeyDown(runLeft))
	{
		if (key->IsKeyDown(jumkey)) {
			state = State::verticalJump;
		}
		else {
			this->state = State::run;
			if (Aladdin->GetVelocity().y == -2)
			{
				state = State::fall;
			}
			else
			{

				Aladdin->SetVelocityY(-2);

			}
		}
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
		//delayattacktime > 0.42f
		if (delayattacktime > 0.42f)
		{

			attack = false;
			delayattack = false;
			delayattacktime = 0;

		}
	}
	if (delayComplete) {
		delaycompeteof += dt;
		if (delaycompeteof > 0.2) {
			delayComplete = false;
			delaycompeteof = 0;
		}

	}
	if (delayThrow) {
		timethrow += dt;
		if (timethrow > 0.6f) {

			delayThrow = false;
			timethrow = 0;
		}
	}
	if (isbleed) {
		timebleed += dt;
		if (timebleed > 0.5f) {
			state = State::Standing;
			isbleed = false;
			Aladdin->SetHP(Aladdin->GetHP() - damaged);
			printf("%d\n", Aladdin->GetHP());
			timebleed = 0;
		}
		else
		{
			if (side > 0) {
				Aladdin->SetVelocityX(-0.2);
			}
			else {
				Aladdin->SetVelocityX(0.2);
			}

		}
	}
	if (isbleedbyboss) {
		timebleed += dt;
		if (timebleed > 0.2f) {
			state = State::Standing;
			isbleedbyboss = false;
			Aladdin->SetHP(Aladdin->GetHP() - damaged);
			printf("%d\n", Aladdin->GetHP());
			timebleed = 0;
		}
	}
	if (isStarClip) {
		timeStarClip += dt;
		if (timeStarClip >= 0.5f) {
			if (!isjum && !isfall)
				state = State::Standing;
			isStarClip = false;
			timeStarClip = 0;
		}
		else {
			if (side > 0) {
				Aladdin->SetVelocityX(0.2);
			}
			else {
				Aladdin->SetVelocityX(-0.2);
			}
		}
	}


}
bool AladinState::getThrow() {
	return isThrow;
}
void AladinState::setThrow(bool isthrowap) {
	this->isThrow = isthrowap;
}
AladinState::~AladinState()
{
}
