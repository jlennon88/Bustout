#pragma once

#include <cassert>
#include <unordered_map>

#include "Scene.h"

namespace bustout
{
	class SceneManager
	{
	public:
		template<typename SceneType, typename ...Args>
		void addScene(std::string sceneName, Args&&... args)
		{
			assert((std::is_base_of_v<Scene, SceneType>));
			assert(m_scenes.find(sceneName) == std::end(m_scenes));

			m_scenes[std::move(sceneName)] = std::make_shared<SceneType>(*this, std::forward(args)...);
		}

		void activateScene(const std::string& sceneName);

		SceneRef getCurrentScene() noexcept { return m_currentScene; }

	private:
		SceneRef m_currentScene = nullptr;
		std::unordered_map<std::string, SceneRef> m_scenes;
	};
}