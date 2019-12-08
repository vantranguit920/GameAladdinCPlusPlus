#pragma once
#include "Object.h"
#include "Aladdin.h"
class PointMap:public Object
{
protected:
	Aladdin *aladdin;
public:
	PointMap(Aladdin *ala);
	~PointMap();
	void Update(float dt, Keyboard* key);
	void CheckSide(Keyboard* keyboard);
};

