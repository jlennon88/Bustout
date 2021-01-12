#pragma once

namespace bustout
{
	class Layer
	{
	public:
		virtual ~Layer() = 0;

		virtual void onActivate() = 0;
		virtual void onDeactivate() = 0;
	};
}