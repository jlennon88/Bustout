#include "UIState.h"

#include <cassert>

namespace bustout
{
	void UILayerStack::pushLayer(UILayerRef layer)
	{
		m_layers.push(layer);
		m_activeLayer = layer;
		m_activeLayer->onActivate();
	}

	void UILayerStack::popLayer()
	{
		assert(!m_layers.empty());

		m_layers.top()->onDeactivate();
		m_layers.pop();
		if (!m_layers.empty())
		{
			m_activeLayer = m_layers.top();
			m_activeLayer->onActivate();
		}
		else
			m_activeLayer = nullptr;
	}

	UILayer& UILayerStack::getActiveLayer() noexcept
	{
		assert(m_activeLayer != nullptr);
		
		return *m_activeLayer;
	}
	const UILayer& UILayerStack::getActiveLayer() const noexcept
	{
		assert(m_activeLayer != nullptr);

		return *m_activeLayer;
	}
}