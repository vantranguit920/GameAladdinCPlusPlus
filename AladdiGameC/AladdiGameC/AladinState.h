#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Object.h"
#include "Sound.h"
#define runRight DIK_RIGHT
#define runLeft DIK_LEFT
#define jumkey DIK_C
#define attackkey DIK_X
#define downkey DIK_DOWN
#define upkey DIK_UP
#define throwkey DIK_S
class AladinState
{
protected:
	Object *Aladdin;
	bool attack = false,delayattack,isjum=false;
	Sound *sound;
	GSound *attacksound;
	GSound *Bleedsound;
	float delayattacktime = 0;
	float timebleed = 0;
	float timeStarClip = 0;
	float delaycompeteof = 0;
	int startJum,side;
	bool isbleed=false;
	bool isfall = false;
	bool isThrow = false;
	bool delayThrow = false;
	float timethrow = 0;
	
	bool injum = false;
	int damaged = 0;
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
		standthrow,
		verticalJump,
		jumAttack,
		down,
		up,
		upattack,
		downattack,
		jumpthrow,
		downthrow,
		swing,
		swinggo,
		swingdown,
		swingjump,
		swingattack,
		swingThrow,

	};
	State state;
	AladinState(Object *aladdin);
	AladinState();
	~AladinState();
	bool getAttack();
	bool isbleedbyboss = false;
	bool getThrow();
	bool delayComplete = false;
	bool isStarClip= false;
	bool isDown;
	void CheckSide(Keyboard* keyboard);
	void StandState(Keyboard* key);
	void AttackState(Keyboard* key);
	void RunState(Keyboard *key);
	void jumState(Keyboard *key);
	void jumAtackState(Keyboard *key);
	void fallState(Keyboard* key);
	void downState(Keyboard* key);
	void fallatackState(Keyboard* key);
	void standthrows(Keyboard* key);
	bool isswing = false;
	bool isbleeds();
	void swinggostate(Keyboard *key,Object* rope);
	void BleedState(int side,int dame);
	void BleedState(int side);
	void BleedbyBoss(int damge);
	void jumthrowState(Keyboard* key);
	void fallthrow(Keyboard* key);
	State GetState(); 
	void SetState(State State);
	void setThrow(bool isthrowap);
	void Update(float dt, Keyboard* keyboard);
};

