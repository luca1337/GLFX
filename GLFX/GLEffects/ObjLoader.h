#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>

namespace glfx
{
	class ObjLoader
	{
	public:
		static auto Load(const std::string& file_name, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn) -> void
		{
			FILE* file = std::fopen(file_name.c_str(), "r");
			if (!file)
			{
				std::cout << "error while opening file" << std::endl;
				return;
			}

			std::vector<glm::vec3> temp_v = {};
			std::vector<glm::vec3> temp_vn = {};
			std::vector<glm::vec2> temp_vt = {};

			std::vector<unsigned> indices_v = {};
			std::vector<unsigned> indices_vn = {};
			std::vector<unsigned> indices_vt = {};

			for (;;)
			{
				char header[256] = {};

				int result = fscanf(file, "%s", header);
				if (result == EOF)
					break;

				if (!strcmp(header, "v"))
				{
					glm::vec3 v = {};
					std::fscanf(file, "%f %f %f", &v.x, &v.y, &v.z);
					temp_v.push_back(v);
				}

				if (!strcmp(header, "vt"))
				{
					glm::vec2 vt = {};
					std::fscanf(file, "%f %f", &vt.x, &vt.y);
					temp_vt.push_back(vt);
				}

				if (!strcmp(header, "vn"))
				{
					glm::vec3 vn = {};
					std::fscanf(file, "%f %f %f", &vn.x, &vn.y, &vn.z);
					temp_vn.push_back(vn);
				}

				if (!strcmp(header, "f"))
				{
					int v1v, v1t, v1n,
						v2v, v2t, v2n,
						v3v, v3t, v3n;

					std::fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1v, &v1t, &v1n,
																	&v2v, &v2t, &v2n,
																	&v3v, &v3t, &v3n);

					indices_v.push_back(v1v);
					indices_v.push_back(v2v);
					indices_v.push_back(v3v);

					indices_vt.push_back(v1t);
					indices_vt.push_back(v2t);
					indices_vt.push_back(v3t);

					indices_vn.push_back(v1n);
					indices_vn.push_back(v2n);
					indices_vn.push_back(v3n);
				}
			}

			for (size_t i = 0; i < indices_v.size(); i++)
			{
				const auto vertex_index = indices_v[i];
				const auto vertex = temp_v[vertex_index - 1];
				v.push_back(vertex);
			}

			for (size_t i = 0; i < indices_vn.size(); i++)
			{
				const auto vertex_normal_index = indices_vn[i];
				const auto normal = temp_vn[vertex_normal_index - 1];
				vn.push_back(normal);
			}

			for (size_t i = 0; i < indices_v.size(); i++)
			{
				const auto vertex_texture_index = indices_vt[i];
				const auto vertex_texture = temp_vt[vertex_texture_index - 1];
				vt.push_back(vertex_texture);
			}
		}
	};
}
