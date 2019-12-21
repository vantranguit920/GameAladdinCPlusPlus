#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "ObjectManager.h"
#include "Aladdin.h"
#include "SceneBoss.h"
#include "MenuGame.h"

class Scene
{
protected:
	ObjectManager* objManager;
	Aladdin* ala;
	SceneBoss* scenebos;
	MenuGame* menugame;
	bool firt;
	bool inboss = false;
public:
	enum stateScene{
		scene1,
		sceneboss,
		menu,
	};
	stateScene state;
	Scene();
	~Scene();
	//Load Data Game 
	void Init(Graphic* graphic);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();
};

