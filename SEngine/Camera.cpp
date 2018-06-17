#include"Camera.h"

#include"System.h"

namespace gasolinn
{
	float		Camera::x = 0, Camera::y = 0;
	Rect		Camera::rect;
	float		Camera::zoom = 1.0;
	float		Camera::angle = 0;

	float		Camera::leftEnd;
	float		Camera::rightEnd;
	float		Camera::topEnd;
	float		Camera::bottomEnd;

	SDL_Rect	Camera::src, Camera::dst;
	SDL_Point	Camera::center;

	void Camera::Init(int width, int height)
	{
		Camera::rect = Rect(0, 0, width, height);

		Camera::x = width / 2;
		Camera::y = height / 2;

		Camera::center.x = width / 2;
		Camera::center.y = height / 2;
		Camera::angle = 0;

		leftEnd = rightEnd = width / 2;
		topEnd = bottomEnd = height / 2;
	}

	void Camera::Update()
	{
		src.x = rect.x;
		src.y = rect.y;
		src.w = rect.w;
		src.h = rect.h;

		dst.x = src.x;
		dst.y = src.y;
		dst.w = src.w;
		dst.h = src.h;
		
		leftEnd = (System::width / 2.0) / Camera::zoom;
		rightEnd = System::width - leftEnd;
		topEnd = (System::height / 2.0) / Camera::zoom;
		bottomEnd = System::height - topEnd;
	}
}