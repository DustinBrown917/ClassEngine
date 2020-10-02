#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::instance = nullptr;
std::vector<Material> MaterialHandler::materials = std::vector<Material>();

MaterialHandler* MaterialHandler::GetInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new MaterialHandler);
	}
	return instance.get();
}

void MaterialHandler::AddMaterial(Material mat_)
{
	materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const std::string& matName_)
{
	for (auto m : materials) {
		if (m.name == matName_) {
			return m;
		}
	}

	return Material();
}

void MaterialHandler::OnDestroy()
{
	if (materials.size() > 0) {
		materials.clear();
	}
}

MaterialHandler::MaterialHandler()
{
	materials.reserve(10);
}

MaterialHandler::~MaterialHandler()
{
	OnDestroy();
}
