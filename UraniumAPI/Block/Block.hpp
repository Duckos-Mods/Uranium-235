#pragma once
#include <string>
#include "../RP/TextureMetadata.hpp"
#include "../RP/Texture.hpp"
#include "../Utils/Logger/Logger.hpp"
#include "../Utils/strUtil.hpp"
#include "../Utils/rapidProxy.hpp"
#include "../Utils/Category.hpp"
#include "../Utils/ItemGroups.hpp"
#include "../Utils/strUtil.hpp"
#include "../Utils/NonOwningPointer.hpp"
#include "../ProjectConfig.hpp"
#include "../Component/BlockComponents/BlockComponent.hpp"
#include "BlockStates.hpp"
#include "Permutations/Permutation.hpp"
#include "../Events/Event.hpp"
#include "../Utils/macros.hpp"

namespace Uranium::Blocks
{
    struct BlockMenuCategory
    {
        Catagories::Catagory category = Catagories::Catagory::none;
        ItemGroups::ItemGroup itemGroup = ItemGroups::ItemGroup::NUL;
        bool isHiddenInCommands = false;
    };

    class Block
    {
    public:

        Block(
            CStrWithLength displayName,
            CStrWithLength identifierIn,
            Version formatVersion = LATEST_FORMAT_VERSION
        ) 
        {
            if (Uranium::containsUppercase(identifierIn))
            {
                Logs::Logger::Warning("Block identifier contains uppercase characters, this may cause issues with the game! Converting to lowercase");
                Uranium::toLowercase(identifierIn);
            }
            m_displayName = displayName;
			m_name = identifierIn;
            setFormatVersion(formatVersion);
            m_name.setAutoDelete(true);
            m_displayName.setAutoDelete(true);

        };

        CStrWithLength GetDisplayName() { return m_displayName; }
        CStrWithLength GetName() { return m_name; }

        void setCategoryData(const BlockMenuCategory& categoryData) { setCategoryDataInternal(categoryData); }
        BlockMenuCategory getCategoryData() const { return getCategoryData(); }
        void addComponent(Components::Blocks::BlockComponent* component) { m_components.push_back(component); }
        void addBlockState(States::BlockState* blockState);
        void addPermutation(const Permutation& permutation) { m_permutations.push_back(permutation); }
        //void addEvent(Events::Event* event) { m_events.push_back(event); }

        void compileBlock(
            ProjectSettings* projectSettings,
            rapidjson::Document* endJson

        );
        void SetTexture(const BlockTexture& texture) { m_texture = texture; };
        //void SetGeometry(class Geometry* geometry) { m_textureMetadata.SetCustomModel(geometry); };
        BlockTextureMetadata GetTextureMetadata() { return m_textureMetadata; }
    private:
        void recursiveCompile(
            NonOwningPointer<ProjectSettings> projectSettings,
            RapidProxy::DefaultValueWriter writer
        );

        void recursiveCompileStates(
			NonOwningPointer<ProjectSettings> projectSettings,
			RapidProxy::DefaultValueWriter writer
		);

        void recursiveCompilePermutations(
            NonOwningPointer<ProjectSettings> projectSettings,
            RapidProxy::DefaultValueWriter writer
        );

        /*void recursiveCompileEvents(
			NonOwningPointer<ProjectSettings> projectSettings,
			RapidProxy::DefaultValueWriter writer
		);*/
    private:
        CStrWithLength m_displayName;
        CStrWithLength m_name;
        CStrWithLength m_texturePath;
        BlockTexture m_texture;
        BlockTextureMetadata m_textureMetadata;
        std::vector<Components::Blocks::BlockComponent*> m_components;
        std::vector<States::BlockState*> m_blockStates;
        std::vector<Permutation> m_permutations;
        //std::vector<Events::Event*> m_events;
       /* Version m_formatVersion;
        BlockMenuCategory m_categoryData;*/
    private:
        constexpr static size_t formatVersionOffset = 0x19;
        constexpr static size_t categoryDataOffset = formatVersionOffset + sizeof(Version);
        void inline setFormatVersion(Version version) 
        {
            BlockTextureMetadata* metaData = &m_textureMetadata;
            memcpy((void*)((uint64_t)metaData + formatVersionOffset), &version, sizeof(Version));
        }
        Version& getFormatVersion() 
		{
			BlockTextureMetadata* metaData = &m_textureMetadata;
			return *(Version*)((uint64_t)metaData + formatVersionOffset);
		}
		void inline setCategoryDataInternal(const BlockMenuCategory& categoryData) 
		{
			BlockTextureMetadata* metaData = &m_textureMetadata;
			memcpy((void*)((uint64_t)metaData + categoryDataOffset), &categoryData, sizeof(BlockMenuCategory));
		}
        BlockMenuCategory& getCategoryData()
        {
            BlockTextureMetadata* metaData = &m_textureMetadata;
			return *(BlockMenuCategory*)((uint64_t)metaData + categoryDataOffset);
        }


    };
}