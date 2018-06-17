
#include"gasolinn.h"

#include<unordered_map>
#include<vector>
#include<string>
#include<iostream>
#include<thread>

USING_GASOLINN;
USING_GASOLINN_UI;

//Collider 구현
//ResourceManager 구현


class Ob : public Object
{
public:		
	Texture *texture;
	Texture *texture2;
	Texture *texture3;

	Collider *col1;
	Collider *col2;

	KeyEvent *ke;

	Panel *panel;

	Label *label2;
	Label *label3;

	Slider *slider;

	void Initialize() {
		texture = ResourceManager::GetTexture("a");
		texture2 = ResourceManager::GetTexture("b");
		texture3 = ResourceManager::GetTexture("b");

		col1 = Collider::CreateABRect(this,pos,texture2->size);
		col2 = Collider::CreateOBRect(this, pos + Vec2(35,-35), texture3->size,Vec2(0,0));

		Camera::zoom = 1;
		texture3->angle = 30;

		ke = KeyEvent::Create(GI_KEYCODE_0,GI_KEYCODE_1,NULL);

		Texture *blue = RM::GetTexture("b");
		blue->r = blue->g = 0;
		Texture *oooh = RM::GetTexture("b");
		oooh->r = 128;
		oooh->g = 128;
		panel = Panel::Create(this, Ver2(320, 240), Size(320, 240), true, true, RM::GetTexture("scrollbar"), RM::GetTexture("scrollhead"));
		label2 = Label::Create(this, RM::GetFont("nanum", 50), Ver2(100, 100));
		label3 = Label::Create(this, RM::GetFont("nanum", 50), Ver2(700, 480));
		panel->Add(label2);
		panel->Add(label3);

		slider = Slider::Create(this, Ver2(100, 100), RM::GetTexture("rect"), RM::GetTexture("line"), RM::GetTexture("lineRed"));
	}
	void Step() {
		slider->Update();
		panel->Update();
		if (parent->tag == "Test") {
			//SceneManager::ReplaceScene("Test2")->x = 640;
		}
		if (ke->GetKeyPressed(GI_KEYCODE_0))
			printf("a");
	}
	void Draw() {
		DrawTexture(texture,parent->sceneWidth/2,parent->sceneHeight/2);
		DrawTexture(texture2, pos);
		DrawTexture(texture3, pos + Vec2(35,-35));
		panel->Draw();
		slider->Draw();
	}
	void Release() {
		texture->Release();
		texture2->Release();
		panel->Release();
		slider->Release();
	}
};


class Test : public Scene
{
public:
	void Initialize()
	{
		AddObject(new Ob,320,480-30);
	}
	void Release()
	{

	}
};

class Test2 : public Scene
{
public:
	bool loaded = false;
	void Preloading()
	{
		AddObject(new Ob, 240, 480 - 30);
	}
	bool Loading(Scene *prev)
	{
		prev->x--;
		x--;
		if (x < 0) return false;
		return true;
	}
	void Initialize()
	{
		
	}
	void Release()
	{
		
	}
};

void main()
{
	Engine::On("title", Size(640, 480));
	
	ResourceManager::LoadTextures();
	ResourceManager::LoadFonts();
	SceneManager::AddScene(new Test,new Test2,NULL);

	Engine::Run();
}