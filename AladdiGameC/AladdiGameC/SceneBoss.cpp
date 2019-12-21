#include "SceneBoss.h"



SceneBoss::SceneBoss()
{
}
void SceneBoss::Init(Graphic* graphic,Aladdin* ala) {
	this->sound = new Sound(graphic->GetHwnd());
	this->sound->Init_DirectSound();
	soundGame = this->sound->LoadSound("./Sound/BossTune.wav");
	aladin = ala;	
	point = new PointMap(aladin,300);
	viewport = new Viewport(0, 640);
	spriteLamp = new Sprite(graphic, "./Resource Files/itemGame.png", D3DCOLOR_XRGB(163, 73, 164));
	infoLamp = new SpriteSheet("./Resource Files/itemGame.xml");
	lamp = new Lamp(spriteLamp, infoLamp,aladin);
	head = new HeadAla(spriteLamp, infoLamp);
	itemapple = new itemApple(spriteLamp, infoLamp, aladin);
	itemspends = new itemspend(spriteLamp, infoLamp, aladin);
	grid = new Grid();
	map = new Map(graphic, MapBoss, TileSetBoss, D3DCOLOR_XRGB(255, 255, 255));
	map3 = new Map3D(graphic, MapBoss2, TileSetBoss, D3DCOLOR_XRGB(255, 255, 255));
	map->InitGrid();
	map->WriteGrid(map->grid);
	spBoss = new Sprite(graphic, "./Resource Files/Bossfinal.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBoss = new SpriteSheet("./Resource Files/Bossfinal.xml");
	boss = new Boss(spBoss,infoBoss, D3DXVECTOR2(995, 160),aladin);
	
	TiXmlDocument doc(GridXML);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load  file", "Error", MB_OK);
		return;
	}	
	TiXmlElement* root = doc.RootElement();
	ReadGrid(root, grid);
	//objects = grid->GetCell(2, 2)->objects;
	prePosView = viewport->GetPosition();
	//prePosAla = point->GetPosition();
	grid->getObjectCollision(listObjectCollison, listWall2, listGround, viewport->GetPosition());
	
}
//Update Game sau khoảng thời gian dt
void SceneBoss::Update(float dt, Keyboard* key) {
	if (!boss->GetAllowDraw())
		gamecomplete = true;
	aladin->ChangeAnimation(dt, key);
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();
		listWall2.clear();
		listGround.clear();
		listObjectCollison.clear();

		grid->getObjectCollision(listObjectCollison, listWall2, listGround, viewport->GetPosition());
		//listObjectCollison.swap(listObject);
	}
	for (size_t i = 0; i < listWall2.size(); i++)
	{
		D3DXVECTOR2 disMan = aladin->Distance(dt);
		aladin->OnCollision(listWall2.at(i), disMan, disMan);
		for (int k = 0; k < 3; k++) {
			if (aladin->applethrow[k]->GetAllowDraw()) {
				D3DXVECTOR2 disapple = aladin->applethrow[k]->Distance(dt);
				aladin->applethrow[k]->OnCollision(listWall2.at(i), disapple);
			}
		}
		

		listWall2.at(i)->Update(dt, key);
	}
	if (Collision::isCollision(aladin->GetBound2(), boss->GetBound2())&&boss->GetAllowDraw()) {
		aladin->getState()->BleedbyBoss(1);
	}
	for (int j = 0; j < 3; j++) {
		if (aladin->applethrow[j]->GetAllowDraw() && aladin->applethrow[j]->stateapple == AppleThrow::fly) {
			if (Collision::isCollision(aladin->applethrow[j]->GetBound(), boss->GetBound2())) {
				aladin->applethrow[j]->OnCollision();
				boss->OnCollision();
			}
			

		}
	}
	aladin->Update(dt, key);
	point->Update(dt, key);
	boss->Update(dt, key);
	
	viewport->Update(dt, key, aladin->GetPosition(), aladin->GetVelocity(), map->listStage);
	lamp->Update(dt, key);
	head->Update(dt, key);
	itemapple->Update(dt, key);
	itemspends->Update(dt, key);
	this->sound->LoopSound(soundGame);
}
void SceneBoss::stopSound()
{
	sound->StopSound(soundGame);
}
//Vẽ Object lên màn hình 
void SceneBoss::Render() {
	map3->Render(viewport, D3DXVECTOR2(0, 70), point->GetPosition());
	map->Render(viewport);


	boss->Render(viewport);
	
	aladin->Render(viewport);
	lamp->render();
	head->render();
	itemapple->render();
	itemspends->render();
}
void SceneBoss::ReadGrid(TiXmlElement * root, Grid * grid)
{
	if (!root)
		return;
	TiXmlElement *cell = root->FirstChildElement();

	while (cell != NULL)
	{
		float x, y, numobject, w, h;
		cell->QueryFloatAttribute("x", &x);
		cell->QueryFloatAttribute("y", &y);

		cell->QueryFloatAttribute("numobject", &numobject);
		if (numobject > 0) {
			TiXmlElement *obj = cell->FirstChildElement();
			for (int i = 0; i < numobject; i++) {
				string name = (char*)obj->Attribute("name");
				float posX, posY;
				int id;
				obj->QueryFloatAttribute("x", &posX);
				obj->QueryFloatAttribute("y", &posY);
				obj->QueryFloatAttribute("w", &w);
				obj->QueryFloatAttribute("h", &h);
				obj->QueryIntAttribute("id", &id);
				if (name == "Wall")
				{
					Object* wall = new Object();
					wall->SetName(name);
					wall->SetTag(name);
					wall->SetPosition(D3DXVECTOR2(posX, posY));
					wall->SetPositionStart(D3DXVECTOR2(posX, posY));
					wall->SetBound(w, h);
					wall->id = id;
					grid->GetCell(x, y)->Add(wall);


				}
				else if (name == "Ground")
				{
					Object* wall = new Object();
					wall->SetName(name);
					wall->SetTag(name);
					wall->SetPosition(D3DXVECTOR2(posX, posY));
					wall->SetPositionStart(D3DXVECTOR2(posX, posY));
					wall->SetBound(w, h);
					wall->id = id;
					grid->GetCell(x, y)->Add(wall);


				}




				obj = obj->NextSiblingElement();
			}
		}

		cell = cell->NextSiblingElement();
	}


}
SceneBoss::~SceneBoss()
{
}
