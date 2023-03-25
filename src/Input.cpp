#include "Camera.h"
#include "Input.h"


void Input::updateInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		// Movement
		if (event.key.keysym.sym == SDLK_w)
		{
			Camera::instance->translate(Camera::instance->forward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_s)
		{
			Camera::instance->translate(Camera::instance->backward() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			Camera::instance->translate(Camera::instance->left() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			Camera::instance->translate(Camera::instance->right() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_q)
		{
			Camera::instance->translate(Camera::instance->up() * moveSpeed);
		}
		if (event.key.keysym.sym == SDLK_e)
		{
			Camera::instance->translate(Camera::instance->down() * moveSpeed);
		}

		// Rotation
		if (event.key.keysym.sym == SDLK_UP)
		{
			Camera::instance->rotateBy(glm::vec3(-rotationSpeed, 0, 0));
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			Camera::instance->rotateBy(glm::vec3(rotationSpeed, 0, 0));
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			Camera::instance->rotateBy(glm::vec3(0, 0, rotationSpeed));
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			Camera::instance->rotateBy(glm::vec3(0, 0, -rotationSpeed));
		}

		// Toggle Fullscreen
		if (event.key.keysym.sym == SDLK_F11)
		{
			isFullscreen = !isFullscreen;
		}
	}
}
