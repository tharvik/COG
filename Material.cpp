#include "Material.h"

using namespace std;

Material::Material(const std::string& name) : nom(name)
{
        cout << "Material created" << endl;
}

Material::Material(const Material&& material) : nom(move(material.nom))
{}

void Material::print() const
{
        cout << nom << endl;
}