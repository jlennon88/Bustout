#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace bustout
{
	class SceneManager;

	class Scene
	{
	public:
		virtual void activate() = 0;
		virtual void deactivate() = 0;

		virtual void update(float elapsedTime) = 0;

		virtual void draw(sf::RenderTarget& target) = 0;

		virtual std::string_view getName() const noexcept { return m_name; }
	protected:
		Scene(std::string name, SceneManager& manager);

		SceneManager& getManager() noexcept { return *m_manager; }

	private:
		std::string m_name;
		SceneManager* m_manager;
	};

	using SceneRef = std::shared_ptr<Scene>;
}