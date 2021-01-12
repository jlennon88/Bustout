#pragma once

#include <memory>
#include <stack>

#include <SFML/Graphics.hpp>

namespace bustout
{
	enum class UILayerType
	{
		Canvas,
		Overlay,
	};

	class UILayer
	{
	public:
		virtual ~UILayer() = default;

		virtual void onActivate() = 0;
		virtual void onDeactivate() = 0;

		virtual void update() = 0;
		virtual void draw(sf::RenderTarget& target) = 0;

	protected:
		UILayer(UILayerType type) noexcept : m_type(type) {}

	private:
		UILayerType m_type;
	};

	using UILayerRef = std::shared_ptr<UILayer>;

	class UILayerStack
	{
	public:
		void pushLayer(UILayerRef layer);
		void popLayer();

		UILayer& getActiveLayer() noexcept;
		const UILayer& getActiveLayer() const noexcept;
	private:
		UILayerRef m_activeLayer = nullptr;
		std::stack<UILayerRef> m_layers;
	};
}