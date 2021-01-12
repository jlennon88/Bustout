#pragma once

#include "Scene.h"
#include "Canvas.h"

namespace bustout
{
	class MainMenuScene final : public Scene
	{
	public:
		virtual void activate() final;
		virtual void deactivate() final;

		virtual void update(float elapsedTime) final;

		virtual void draw(sf::RenderTarget& target) final;

	private:
		MainMenuScene(SceneManager& manager);

	};
}