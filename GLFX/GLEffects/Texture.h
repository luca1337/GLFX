#pragma once

#include <string>

namespace glfx
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& path);
		auto GetTexture() -> unsigned int;
	private:
		unsigned int texture_id;
	};
}

