#pragma once
#include "Object.h"
class PointMap:public Object
{
protected:

public:
	PointMap();
	~PointMap();
	void Update(float dt, Keyboard* key);
	void CheckSide(Keyboard* keyboard);
};

