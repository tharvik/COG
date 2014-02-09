#pragma once

#include <string>
#include <vector>
#include <array>

class Mesh
{
	public:
		Mesh();
		Mesh(std::string name,
			std::vector<std::array<float, 3>> v,
			std::vector<std::array<float, 2>> vt,
			std::vector<std::array<std::array<unsigned short, 2>, 3>>
			f);

		void draw();

		bool operator<(const Mesh &b) const;

	private:
		std::string name;
		std::vector<std::array<float, 3>> v;
		std::vector<std::array<float, 2>> vt;
		std::vector<std::array<std::array<unsigned short, 2>, 3>> f;
};
