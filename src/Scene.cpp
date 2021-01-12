#include "Scene.h"

#include "SceneManager.h"

namespace bustout
{
	Scene::Scene(std::string name, SceneManager& manager)
		: m_name(std::move(name))
		, m_manager(&manager)
	{
	}
}
