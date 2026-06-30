#pragma once

#include "Scene.h"
#include "Hydra/Core/Base.h"


namespace YAML 
{
    class Node;
}

namespace Hydra
{

    class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

		void SerializeToStream(std::ostream& os);
    	bool DeserializeFromStream(std::istream& is);

	private:
		void DeserializeEntities(YAML::Node& data);

	private:
		Ref<Scene> m_Scene;
	};

}