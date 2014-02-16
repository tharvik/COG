#include "MeshManager.h"

// Constructor
MeshManager::MeshManager()
{}

Mesh& MeshManager::load(const std::string path)
{
	// test if already existing
	const auto iter = this->map.find(path);
	if(iter != this->map.end())
		return iter->second;

	// setup manager
	this->lineCount = 0;
	this->path = path;
	this->file.open(path);

	// current object
	std::string name;
	std::vector<std::array<float, 3>> v;
	std::vector<std::array<float, 2>> vt;
	std::vector<std::array<std::array<unsigned short, 2>, 3>> f;

	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	std::string word = "#";
	do {
		if (word == "o") {
			name = word;

		} else if (word == "v") {
			v.push_back(parseV<3>());

		} else if (word == "vt") {
			vt.push_back(parseV<2>());

		} else if (word == "f") {
			f.push_back(parseF());
		}

		if (word.size() == 0 || word[0] == '#')
			cleanLine(word, false);
		else
			cleanLine(word, true);

		// get next word
		getline(file, word, ' ');

	} while(file);

	file.close();
	logger::info("Parsing done for \"" + path + '\'', FL);

	std::vector<std::array<float, 2>> vt_reorder;
	vt_reorder.insert(vt_reorder.begin(), v.size(), {{ 0, 0 }} );
	// TODO remove indices temporary and directly parse it
	std::vector<unsigned short> indices;
	for(auto i : f) {
		for(auto j : i) {
			indices.push_back(j[0] - 1);
			vt_reorder[j[0] - 1] = vt[j[1] - 1];
		}
	}

	this->map[path] = Mesh(v, vt_reorder, indices);
	return this->map[path];
}

template<unsigned short size>
std::array<float, size> MeshManager::parseV()
{
	std::array<float, size> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<std::array<unsigned short, 2>, 3>
	MeshManager::parseF()
{
	std::array<std::array<unsigned short, 2>, 3> array;
	for(unsigned short i = 0; i < array.size(); i++) {

		file >> array[i][0];

		if(file.peek() != '/') {
			array[i][1] = 0;
		} else {
			file.get();
			file >> array[i][1];
		}
	}

	return array;
}

void MeshManager::cleanLine(const std::string word, const bool log)
{
	lineCount++;

	std::string tmp;
	getline(file, tmp);

	if(tmp.size() != 0 && log)
		logger::warn("Discarding remaining results: \"" + word + " " +
				tmp + "\"", path, lineCount);
}

// Destructor
MeshManager::~MeshManager()
{}
