#include "Texture.h"

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace glfx
{
	Texture::Texture(const std::string& path)
	{
		// prepare a block of memory bind texture object to an id
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		int width, height, channels;
		const auto pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);
		if (!pixels) {
			std::cout << "could not read texture pixel.." << std::endl;
			return;
		}

		// finally generate the texture in memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(pixels);
	}

	auto Texture::GetTexture() -> unsigned int
	{
		return texture_id;
	}
}
