#pragma once
#include "../../Utils/rapidProxy.hpp"
#include "../../Component/BlockComponents/BlockComponent.hpp"
#include "../../Utils/NonOwningPointer.hpp"
#include <vector>

namespace Uranium
{
	class Permutation
	{
	public:
		Permutation() {};
		Permutation(std::string condition, std::vector<Components::BlockComponent*> components) : condition(condition), components(components) {};

		std::string getCondition() { return condition; };
		std::vector<Components::BlockComponent*> getComponents() { return components; };

		void setCondition(std::string condition) { this->condition = condition; };
		void setComponents(std::vector<Components::BlockComponent*> components) { this->components = components; };

		rapidjson::Value compilePermutation(rapidjson::Document::AllocatorType& allocator, NonOwningPointer<ProjectSettings> pjs) const;

	private:
		std::string condition;
		std::vector<Components::BlockComponent*> components;
	};

}