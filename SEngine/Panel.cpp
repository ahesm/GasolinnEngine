#include"Panel.h"

#include"System.h"
#include"Mouse.h"
#include"Camera.h"
#include"Scene.h"
#include"UI.h"
#include"Collision.h"
#include"Texture.h"

#define SCR_INTERVAL 12

namespace ui
{
	Panel* Panel::Create(Object *parent, Ver2 pos, Size size)
	{
		Panel* panel = new Panel;
		panel->parent = parent;
		panel->pos = pos;
		panel->size = size;
		panel->rSize = size;
		panel->buffer = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, size.width, size.height);
		SDL_SetTextureBlendMode(panel->buffer, SDL_BLENDMODE_BLEND);
		
		return panel;
	}

	Panel* Panel::Create(Object *parent, Ver2 pos, Size size, bool vScroll, bool hScroll,Texture* scrollbar,Texture* head)
	{
		Panel* panel = new Panel;
		panel->parent = parent;
		panel->pos = pos;
		panel->extendedSize = Size(size.width+head->size.width,size.height+head->size.height);
		panel->size = size;
		panel->rSize = size;
		panel->vScroll = vScroll;
		panel->hScroll = hScroll;
		panel->scrollbar = scrollbar;
		panel->buffer = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, panel->extendedSize.width, panel->extendedSize.height);
		SDL_SetTextureBlendMode(panel->buffer, SDL_BLENDMODE_BLEND);
		panel->scrollPos = Ver2(0, 0);

		if (head == nullptr || scrollbar == nullptr)
		{
			printf("No Texture In Create Panel: %s\t%d\n",parent->parent->tag,parent->id);
		}

		Texture **headbody = Texture::SplitTextureWithHeight(head, head->size.height - 1);
		panel->head = headbody[0];
		panel->vBody = Texture::ResizeTexture(headbody[1], Size(head->size.width, size.height));
		panel->hBody = Texture::ResizeTexture(headbody[1], Size(head->size.width, size.width));
		
		head->Release();
		//head = nullptr;
		headbody[1]->Release();
		delete[] headbody;

		SDL_Texture *headBuffer = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, size.width, size.height);
		SDL_SetTextureBlendMode(panel->buffer, SDL_BLENDMODE_BLEND);


		return panel;
	}

	void Panel::Add(UI * ui)
	{
		if (rSize.height < ui->pos.y + ui->size.height / 2)
			rSize.height = ui->pos.y + ui->size.height / 2;
		if (rSize.width < ui->pos.x + ui->size.width / 2)
			rSize.width = ui->pos.x + ui->size.width / 2;
		uiMap.push_back(ui);

		if (rSize.height - vBody->size.height > 0)
		{
			scrollSize.height = size.height - head->size.height * 2 - scrollbar->size.height;
			drawScrIntervalY = (float)(scrollSize.height) / (float)(rSize.height - size.height);
		}
		if (rSize.height - vBody->size.height > 0)
		{
			scrollSize.width = size.width - head->size.height * 2 - scrollbar->size.height;
			drawScrIntervalX = (float)(scrollSize.width) / (float)(rSize.width - size.width);
		}
	}

	void Panel::Update()
	{
		for (auto i : uiMap) i->Update();
		
		if (Mouse::Click(MOUSE_LEFT))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y, pos.x + head->size.width/2, pos.y + head->size.width/2, extendedSize.width, extendedSize
				.height)) {
				focused = true;
			}
			else
			{
				focused = false;
			}
			for (auto i : uiMap)i->focused = focused;
		}

		if (focused)
		{
			if (vScroll && rSize.height - size.height > 0)
			{
				scrollPos.y -= Mouse::wheelY * SCR_INTERVAL;
			}

			if (hScroll && rSize.width - size.width > 0)
			{
				//+,- 확인불가
				scrollPos.x -= Mouse::wheelX * SCR_INTERVAL;
			}

			if (scrollPos.x < 0)
			{
				scrollPos.x = 0;
			}

			if (scrollSize.width < scrollPos.x*drawScrIntervalX)
			{
				scrollPos.x = (float)scrollSize.width / drawScrIntervalX;
			}

			if (scrollPos.y < 0)
			{
				scrollPos.y = 0;
			}

			if (scrollSize.height < scrollPos.y*drawScrIntervalY)
			{
				scrollPos.y = (float)scrollSize.height / drawScrIntervalY;
			}

			if (Mouse::Click(MOUSE_LEFT))
			{
				//scrollbar
				if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
					pos.x + size.width/2 + head->size.width/2,
					pos.y - size.height/2 + head->size.height + scrollbar->size.height / 2 + scrollPos.y*drawScrIntervalY,
					scrollbar->size.width, scrollbar->size.height))
				{
					vScrollPressing = true;
				}
				if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
					pos.x - size.width / 2 + head->size.height + scrollbar->size.height / 2 + scrollPos.x*drawScrIntervalX,
					pos.y + size.height/2  + head->size.width/2,
					scrollbar->size.height, scrollbar->size.width))
				{
					hScrollPressing = true;
				}
				
				//head
				if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
					pos.x - size.width / 2 + size.width - scrollbar->size.width / 2 - 1 + head->size.width,
					pos.y - size.height / 2 + head->size.height + scrollbar->size.height / 2,
					scrollbar->size.width, scrollbar->size.height))
				{

				}

				//inscroll
			}
			if (Mouse::Leave(MOUSE_LEFT))
			{
				if (vScrollPressing) vScrollPressing = false;
				if (hScrollPressing) hScrollPressing = false;
			}
		}

		if (vScrollPressing)
		{
			float mouseY = parent->parent->mouse.y - (pos.y - size.height / 2)
				- head->size.height - scrollbar->size.height / 2;
			if (mouseY < 0) mouseY = 0;
			if (mouseY > size.height - head->size.height * 2 - scrollbar->size.height )
				mouseY = size.height - head->size.height * 2 - scrollbar->size.height;
			scrollPos.y = mouseY / drawScrIntervalY;
		}

		if (hScrollPressing)
		{
			float mouseX = parent->parent->mouse.x - (pos.x - size.width / 2)
				- head->size.height - scrollbar->size.height / 2;
			if (mouseX < 0) mouseX = 0;
			if (mouseX > size.width - head->size.height * 2 - scrollbar->size.height)
				mouseX = size.width - head->size.height * 2 - scrollbar->size.height;
			scrollPos.x = mouseX / drawScrIntervalX;
		}
	}



	void Panel::Draw()
	{
		SDL_SetRenderTarget(System::renderer, buffer);
		SDL_SetRenderDrawColor(System::renderer, 0, 0, 0, 0);
		SDL_RenderClear(System::renderer);
		SDL_SetRenderDrawColor(System::renderer, 255, 255, 255, 255);

		for (auto i : uiMap) { 
			i->DrawOnPanel(i->pos + pos - Ver2(System::width/2,System::height/2) - scrollPos);
		}

		if (vScroll && rSize.height - size.height > 0) {
			DrawTexture(vBody, Ver2(size.width - round(head->size.width / 2.0f) + head->size.width, round(vBody->size.height / 2.0f)), 0);
			DrawTexture(head, Ver2(size.width - round(head->size.width/2.0f) + head->size.width, round(head->size.height / 2.0f)), 0);
			DrawTexture(scrollbar, Ver2(size.width - round(scrollbar->size.width / 2.0f) - round((head->size.width - scrollbar->size.width)/2.0f) + head->size.width,
				head->size.height + round(scrollbar->size.height/2.0f) + scrollPos.y*drawScrIntervalY - 1), 0);
			DrawTexture(head, Ver2(size.width - round(head->size.width / 2.0f) + head->size.width, size.height - round(head->size.height/2.0f)-1), 180);
		}

		if (hScroll && rSize.width - size.width > 0) {
			DrawTexture(hBody, Ver2(round(hBody->size.height / 2.0f) - (hBody->size.height % 2 ==0 ? 1 : 0), size.height - round(head->size.width / 2.0f) + head->size.width ), 90);
			DrawTexture(head, Ver2(round(head->size.height / 2.0f), size.height - round(head->size.width / 2.0f) + head->size.width), -90);
			DrawTexture(scrollbar, Ver2(head->size.height + round(scrollbar->size.height / 2.0f) + scrollPos.x*drawScrIntervalX-1 ,
				size.height - round(scrollbar->size.width / 2.0f) - round((head->size.width - scrollbar->size.width) / 2.0f) + head->size.width), 90);
			DrawTexture(head, Ver2(size.width - round(head->size.height / 2.0f)-1 , size.height - round(head->size.width / 2.0f) + head->size.width), 90);
		}



		SDL_SetRenderTarget(System::renderer, System::buffer);

		SDL_Rect src, dst;
		SDL_Point point;

		point.x = size.width * 0.5 * Camera::zoom;
		point.y = size.height * 0.5 * Camera::zoom;

		src.x = 0;
		src.y = 0;
		src.w = extendedSize.width;
		src.h = extendedSize.height;

		dst.x = round((pos.x - Camera::x)*Camera::zoom + Camera::x - point.x - (Camera::x - System::width / 2) + parent->parent->x);
		dst.y = round((pos.y - Camera::y)*Camera::zoom + Camera::y - point.y - (Camera::y - System::height / 2) + parent->parent->y);
		dst.w = src.w  * Camera::zoom;
		dst.h = src.h * Camera::zoom;

		SDL_RenderCopyEx(System::renderer, buffer, &src, &dst, 0, &point, SDL_FLIP_NONE);
	}

	void Panel::DrawTexture(Texture * texture, Ver2 pos, float angle)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = texture->centerX*texture->size.width * texture->scaleX;
		point.y = texture->centerY*texture->size.height * texture->scaleY;

		src.x = 0;
		src.y = 0;
		src.w = texture->size.width;
		src.h = texture->size.height;

		dst.x = round(pos.x - point.x);
		dst.y = round(pos.y - point.y);
		dst.w = texture->size.width * texture->scaleX;
		dst.h = texture->size.height * texture->scaleY;

		SDL_SetTextureColorMod(texture->texture, texture->r, texture->g, texture->b);
		SDL_SetTextureBlendMode(texture->texture, (SDL_BlendMode)texture->blendmode);
		SDL_SetTextureAlphaMod(texture->texture, texture->alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture->texture, &src, &dst, angle, &point, SDL_FLIP_NONE);
	}


	void Panel::Release()
	{
		SDL_DestroyTexture(buffer);
		if (scrollbar != nullptr) 
		{
			scrollbar->Release();
			scrollbar = nullptr;
		}
		if (head != nullptr)
		{
			head->Release();
			head = nullptr;
		}
		if (vBody != nullptr)
		{
			vBody->Release();
			vBody = nullptr;
		}
		if (hBody != nullptr)
		{
			hBody->Release();
			hBody = nullptr;
		}
		for (auto i : uiMap) i->Release();
	}

}