#pragma once

namespace glfx
{
	/// <summary>
	/// Must be called before any opengl initialization
	/// </summary>
	class Engine
	{
	public:
		static bool Init(const int major_version, const int minor_version);
	};
}
