#pragma once

#include "Pipeline/API.h"

#include <hash_map>

#include "Pipeline/Asset/AssetClass.h"
#include "Pipeline/Asset/Manifests/EntityManifest.h"

namespace Helium
{
    namespace Asset
    {
        class PIPELINE_API Entity : public AssetClass
        {
        private:

        public:
            REFLECT_DECLARE_CLASS(Entity, AssetClass);

            static void EnumerateClass( Reflect::Compositor<Entity>& comp );

        public:
            Entity()
            {
            }

            virtual void GatherSearchableProperties( Helium::SearchableProperties* properties ) const HELIUM_OVERRIDE;
        }; 

        typedef Helium::SmartPtr< Entity > EntityPtr;
        typedef std::vector< EntityPtr > V_Entity;

    }
}