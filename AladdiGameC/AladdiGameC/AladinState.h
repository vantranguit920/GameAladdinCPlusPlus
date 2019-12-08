#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Object.h"
#include "Sound.h"
class AladinState
{
protected:
	Object *Aladdin;
	bool attack = false,delayattack,isjum=false;
	Sound *sound;
	GSound *attacksound;
	float delayattacktime = 0;
	float timebleed = 0;
	int startJum,side;
	bool isbleed=false;
public:

	enum State
	{
		Standing,		//Đứng
		Attack,
		run,
		runattack,
		jum,
		fall,
		bleed,
	};
	State state;
	AladinState(Object *aladdin);
	AladinState();
	~AladinState();
	bool getAttack();

	void CheckSide(Keyboard* keyboard);
	void StandState(Keyboard* key);
	void AttackState(Keyboard* key);
	void RunState(Keyboard *key);
	void jumState(Keyboard *key);
	void fallState(Keyboard* key);
	bool isbleeds();
	void BleedState(int side);
	State GetState(); 
	void SetState(State State);

	void Update(float dt, Keyboard* keyboard);
};

