#include "ObjectManager.h"
#include "string.h"

ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager()
{

	delete map;
	delete viewport;
	delete soundGame;
	delete sound;
	delete map2;
	delete map3;



}
Aladdin* ObjectManager::getAladdin() {
	return aladin;
}
//Load Game
void ObjectManager::Init(Graphic* graphic)
{

	this->sound = new Sound(graphic->GetHwnd());
	this->sound->Init_DirectSound();
	soundGame = this->sound->LoadSound("./Sound/PrinceAli.wav");
	//
	spriteAladdin = new Sprite(graphic, "AladinAnimXml.png", D3DCOLOR_XRGB(255, 0, 255));
	infoAlddin = new SpriteSheet("AladinAnimXml.xml");
	spriteBrick = new Sprite(graphic, "./Resource Files/Brick.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBrick = new SpriteSheet("./Resource Files/Brickxml.xml");
	//
	spritePendu = new Sprite(graphic, "./Resource Files/pendulum.png", D3DCOLOR_XRGB(163, 73, 164));
	infoPendu = new SpriteSheet("./Resource Files/conlacxml.xml");
	//
	spriteArrow = new Sprite(graphic, "./Resource Files/arrow.png", D3DCOLOR_XRGB(163, 73, 164));
	infoArrow = new SpriteSheet("./Resource Files/arrow.xml");
	spriteGuard = new Sprite(graphic,"./Resource Files/GuardIII.png", D3DCOLOR_XRGB(163, 73, 164));
	infoGuard = new SpriteSheet("./Resource Files/GuardIII.xml");
	//
	spriteBat = new Sprite(graphic, "./Resource Files/BatupdateII.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBat = new SpriteSheet("./Resource Files/BatupdateII.xml");

	//
	spriteSkeleton = new Sprite(graphic, "./Resource Files/skeletonII.png", D3DCOLOR_XRGB(163, 73, 164));
	infoSkeleton = new SpriteSheet("./Resource Files/skeletonII.xml");
	//
	spriteLamp = new Sprite(graphic, "./Resource Files/itemGame.png", D3DCOLOR_XRGB(163, 73, 164));
	infoLamp = new SpriteSheet("./Resource Files/itemGame.xml");
	
	head = new HeadAla(spriteLamp, infoLamp);
	
	
	//
	spriteRodGuard = new Sprite(graphic, "./Resource Files/GoguardII.png", D3DCOLOR_XRGB(163, 73, 164));
	infoRodGuard = new SpriteSheet("./Resource Files/GoguardII.xml");
	//
	spriteShop = new Sprite(graphic, "./Resource Files/Shop.png", D3DCOLOR_XRGB(163, 73, 164));
	infoShop = new SpriteSheet("./Resource Files/Shop.xml");
	//
	spriteSpendThese = new Sprite(graphic, "./Resource Files/SpendThese.png", D3DCOLOR_XRGB(163, 73, 164));
	infoSpendThese = new SpriteSheet("./Resource Files/SpendThese.xml");
	//
	spriteSavePosition = new Sprite(graphic, "./Resource Files/SavePosition.png", D3DCOLOR_XRGB(163, 73, 164));
	infoSavePosition = new SpriteSheet("./Resource Files/SavePosition.xml");
	//
	spriteBonusLevel = new Sprite(graphic, "./Resource Files/BonusLevel2.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBonusLevel = new SpriteSheet("./Resource Files/BonusLevel2.xml");
	//
	spriteApple = new Sprite(graphic, "./Resource Files/appleitem.png", D3DCOLOR_XRGB(163, 73, 164));
	infoApple = new SpriteSheet("./Resource Files/apple.xml");

	//
	aladin = new Aladdin(spriteAladdin, infoAlddin, spriteApple, infoApple);
	point = new PointMap(aladin,2180);
	itemapple = new itemApple(spriteLamp, infoLamp, aladin);
	itemspends = new itemspend(spriteLamp, infoLamp, aladin);
	lamp = new Lamp(spriteLamp, infoLamp, aladin);
	viewport = new Viewport(0, 1152);
	map = new Map(graphic, MapXML, TileSetPNG, D3DCOLOR_XRGB(163, 73, 164));

	map->InitGrid();
	map->WriteGrid(map->grid);

	map2 = new Map(graphic, MapXML2, TileSetPNG, D3DCOLOR_XRGB(163, 73, 164));
	map3 = new Map3D(graphic, MapXML3, TileSetPNG3, D3DCOLOR_XRGB(163, 73, 164));
	grid = new Grid();
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
	grid->getObjectCollision(listObjectCollison, listWall2,listGround, viewport->GetPosition());
}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	aladin->ChangeAnimation(dt, keyboard);
	//aladin->SetVelocityY(-1);
	//Kiểm tra dịch chuyển
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();
		listWall2.clear();
		listGround.clear();
		listObjectCollison.clear();

		grid->getObjectCollision(listObjectCollison, listWall2, listGround, viewport->GetPosition());
		//listObjectCollison.swap(listObject);
	}
	for (size_t i = 0; i < listObjectCollison.size(); i++) {
		if (listObjectCollison.at(i)->GetAllowDraw()) {
			D3DXVECTOR2 disMan = aladin->Distance(dt);
			D3DXVECTOR2 distance = disMan - listObjectCollison.at(i)->Distance(dt);
			aladin->OnCollision(listObjectCollison.at(i), distance, disMan);
			listObjectCollison.at(i)->OnCollision(aladin, distance);
			for (int j = 0; j < 3; j++) {
				if (aladin->applethrow[j]->GetAllowDraw() && aladin->applethrow[j]->stateapple == AppleThrow::fly) {
					if (Collision::isCollision(aladin->applethrow[j]->GetBound(), listObjectCollison.at(i)->GetBound2())) {
						if (listObjectCollison.at(i)->GetName() != "Arow"&&listObjectCollison.at(i)->GetName() != "Pendu"&&listObjectCollison.at(i)->GetTag(listObjectCollison.at(i)->GetName()) == Object::Enemys)
							aladin->applethrow[j]->OnCollision();
						listObjectCollison.at(i)->OnCollision();
					}

				}
			}
		}
		
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
		listWall2.at(i)->Update(dt, keyboard);
	}
	for (size_t i = 0; i < listGround.size(); i++)
	{
		D3DXVECTOR2 disMan = aladin->Distance(dt);
		aladin->OnCollision(listGround.at(i), disMan, disMan);		
		for (int k = 0; k < 3; k++) {
			if (aladin->applethrow[k]->GetAllowDraw()) {
				D3DXVECTOR2 disapple = aladin->applethrow[k]->Distance(dt);
				aladin->applethrow[k]->OnCollision(listGround.at(i), disapple);
			}
			
		}
		listGround.at(i)->Update(dt, keyboard);
	}
	
	aladin->Update(dt, keyboard);
	/*printf("%d\n", (int)listObjectCollison.size());
	printf("%f\n", viewport->GetPosition().x);
	printf("%f\n", viewport->GetPosition().y);*/
	point->Update(dt, keyboard);
	
	

	for (auto o : listObjectCollison) {
		
		o->Update(dt, keyboard);
	}
	viewport->Update(dt, keyboard, aladin->GetPosition(), aladin->GetVelocity(), map->listStage);
	
	sound->LoopSound(soundGame);
	lamp->Update(dt,keyboard);
	head->Update(dt, keyboard);
	itemapple->Update(dt, keyboard);
	itemspends->Update(dt, keyboard);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	
	


	for (auto o : listObjectCollison) {
		o->Render(viewport);
	}

	

	//skeleton->Render(viewport); 
	aladin->Render(viewport);
	map2->Render(viewport);
	map3->Render(viewport, D3DXVECTOR2(10, 70),point->GetPosition());
	lamp->render();
	head->render();
	itemapple->render();
	itemspends->render();
}

void ObjectManager::ReadGrid(TiXmlElement * root, Grid * grid)
{
	if (!root)
		return;
	TiXmlElement *cell = root->FirstChildElement();

	while (cell != NULL)
	{
		float x, y, numobject,w,h;
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
				if (name == "Brick") {
					Brick* brick = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(posX, posY));
					brick->SetName(name);
					brick->id = id;
					if (id%2==0) {
						brick->setstate(Brick::oppen);
					}
					else {
						brick->setstate(Brick::close);
					}
					grid->GetCell(x, y)->Add(brick);
				}
				else if (name == "Pendu")
				{
					pendulum* Pendu = new pendulum(spritePendu,infoPendu, D3DXVECTOR2(posX, posY));
					Pendu->SetName(name);										
					Pendu->id = id;

					grid->GetCell(x, y)->Add(Pendu);


				}
				else if (name == "Bat")
				{
					Bat* bat = new Bat(spriteBat, infoBat, D3DXVECTOR2(posX, posY),aladin);
					bat->SetName(name);
					bat->id = id;
					grid->GetCell(x, y)->Add(bat);


				}
				else if (name == "Arow")
				{
					Arrow* arrow = new Arrow(spriteArrow, infoArrow, D3DXVECTOR2(posX, posY));
					arrow->SetName(name);
					arrow->id = id;
					grid->GetCell(x, y)->Add(arrow);


				}
				else if (name == "Guard")
				{
					Guard* guard = new Guard(spriteGuard, infoGuard, D3DXVECTOR2(posX, posY),aladin);
					guard->SetName(name);
					guard->id = id;
					grid->GetCell(x, y)->Add(guard);


				}
				else if (name == "Skeleton")
				{
					Skeleton* skeleton = new Skeleton(spriteSkeleton, infoSkeleton, D3DXVECTOR2(posX, posY), aladin);
					skeleton->SetName(name);
					skeleton->id = id;
					grid->GetCell(x, y)->Add(skeleton);


				}
				else if (name == "RodGuard")
				{
					RodGuard* rodGuard = new RodGuard(spriteRodGuard, infoRodGuard, D3DXVECTOR2(posX, posY), aladin);
					rodGuard->SetName(name);
					rodGuard->id = id;
					grid->GetCell(x, y)->Add(rodGuard);


				}
				else if (name == "Shop")
				{
					Shop* shop = new Shop(spriteShop, infoShop, D3DXVECTOR2(posX, posY), aladin);
					shop->SetName(name);
					shop->id = id;
					grid->GetCell(x, y)->Add(shop);


				}
				else if (name == "Apple")
				{
					Apple* aplee = new Apple(spriteApple, infoApple, D3DXVECTOR2(posX, posY), aladin);
					aplee->SetName(name);
					aplee->id = id;
					grid->GetCell(x, y)->Add(aplee);


				}
				else if (name == "Spend")
				{
					SpendThese* spends = new SpendThese(spriteSpendThese, infoSpendThese, D3DXVECTOR2(posX, posY), aladin);
					spends->SetName(name);
					spends->id = id;
					grid->GetCell(x, y)->Add(spends);


				}
				else if (name == "Savepoint")
				{
					SavePosition* save = new SavePosition(spriteSavePosition, infoSavePosition, D3DXVECTOR2(posX, posY), aladin);
					save->SetName(name);
					save->id = id;
					grid->GetCell(x, y)->Add(save);


				}
				else if (name == "Bonus")
				{
				BonusLevel* bonus = new BonusLevel(spriteBonusLevel, infoBonusLevel, D3DXVECTOR2(posX, posY), aladin);
				bonus->SetName(name);
				bonus->id = id;
				grid->GetCell(x, y)->Add(bonus);


				}
				else if (name == "Rope")
				{
				Object* rope = new Object();
				rope->SetName(name);
				rope->SetAllowDraw(true);
				rope->SetTag(name);
				rope->SetPosition(D3DXVECTOR2(posX, posY));
				rope->SetPositionStart(D3DXVECTOR2(posX, posY));
				rope->SetBound(w, h);
				rope->id = id;
				grid->GetCell(x, y)->Add(rope);


				}
				else if(name == "Wall")
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



