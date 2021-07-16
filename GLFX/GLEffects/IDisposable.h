#pragma once

namespace glfx
{
	class IDisposable
	{
	public:
		virtual auto Dispose() -> void = 0;
	};
}