#include "SceneManager.h"
#include "Scene.h"

namespace bustout
{
	void SceneManager::activateScene(const std::string& sceneName)
	{
		assert(m_scenes.find(sceneName) != std::end(m_scenes));

		if (m_currentScene)
			m_currentScene->deactivate();
		m_currentScene = m_scenes[sceneName];
		m_currentScene->activate();
	}
}