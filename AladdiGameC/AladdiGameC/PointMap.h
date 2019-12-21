#pragma once
#include "Object.h"
#include "Aladdin.h"
class PointMap:public Object
{
protected:
	Aladdin *aladdin;
	int width;
public:
	PointMap(Aladdin *ala, int width);
	~PointMap();
	void Update(float dt, Keyboard* key);
	void CheckSide(Keyboard* keyboard);
};

