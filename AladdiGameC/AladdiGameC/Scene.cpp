#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	delete objManager;
}

//Load Data Game
void Scene::Init(Graphic* graphic)
{
	firt = true;
	menugame = new MenuGame();
	menugame->Init(graphic);
	objManager = new ObjectManager();
	objManager->Init(graphic);
	ala = objManager->getAladdin();
	scenebos = new SceneBoss();
	scenebos->Init(graphic, ala);
	state = stateScene::menu;
}

//Update Game sau khoảng thời gian dt
void Scene::Update(float dt, Keyboard* key)
{

	if (state == stateScene::menu) {
		if (menugame->nextscene) {
			state = stateScene::scene1;
			menugame->nextscene = false;
		}

	}
	else if (state == stateScene::scene1) {
		if (ala->GetPosition().x > 2280) {
			this->state = stateScene::sceneboss;
			ala->SetPosition(D3DXVECTOR2(670, 280));
			ala->getState()->SetState(AladinState::Standing);
			objManager->sound->StopSound(objManager->soundGame);
		}
		else if (ala->GetHP() < 0) {
			state = stateScene::menu;
			objManager->sound->StopSound(objManager->soundGame);
			ala->newala();
		}
	}
	else if (state == stateScene::sceneboss) {
		if (ala->GetHP() < 0) {
			state = stateScene::menu;
			scenebos->stopSound();
			ala->newala();
		}
		else if (scenebos->gamecomplete) {
			state = stateScene::menu;
			scenebos->stopSound();
			ala->newala();
			menugame->complete = true;
		}
	}

	switch (state)
	{
	case stateScene::scene1:
		objManager->Update(dt, key);
		break;
	case stateScene::sceneboss:
		scenebos->Update(dt, key);
		break;
	case stateScene::menu:
		menugame->Update(dt, key);
		break;
	default:
		break;
	}
}

//Vẽ Object lên màn hình
void Scene::Render()
{
	switch (state)
	{
	case stateScene::menu:
		menugame->Render();
		break;
	case stateScene::scene1:
		menugame->Render();
		objManager->Render();
		break;
	case stateScene::sceneboss:
		scenebos->Render();
		break;
	default:
		break;
	}
}