#pragma once

#include "VaultMenuIDs.h"
#include "CollectionManager.h"
#include "SearchHistory.h"
#include "SearchQuery.h"

#include "Foundation/TUID.h"
#include "Foundation/Container/OrderedSet.h"
#include "Editor/WindowSettings.h"

namespace Helium
{
    namespace Editor
    {
        class VaultFrame;

        class VaultPreferences : public Reflect::ConcreteInheritor< VaultPreferences, Settings >
        {
        public:
            VaultPreferences( const tstring& defaultFolder = TXT( "" ),
                ViewOptionID thumbnailMode = ViewOptionIDs::Medium,
                u32 thumbnailSize = ThumbnailSizes::Medium );
            ~VaultPreferences();

            void GetWindowSettings( VaultFrame* browserFrame, wxAuiManager* manager = NULL );
            void SetWindowSettings( VaultFrame* browserFrame, wxAuiManager* manager = NULL );

            const ViewOptionID GetThumbnailMode() const;
            void SetThumbnailMode( ViewOptionID thumbnailMode );

            const u32 GetThumbnailSize() const;
            void SetThumbnailSize( u32 thumbnailSize );

            bool DisplayPreviewAxis() const;
            void SetDisplayPreviewAxis( bool display );
            const Reflect::Field* DisplayPreviewAxisField() const;

            u32 GetUsageCollectionRecursionDepth() const;
            void SetUsageCollectionRecursionDepth( u32 recursionDepth );
            const Reflect::Field* UsageCollectionRecursionDepth() const;

            u32 GetDependencyCollectionRecursionDepth() const;
            void SetDependencyCollectionRecursionDepth( u32 recursionDepth );
            const Reflect::Field* DependencyCollectionRecursionDepth() const;

            const tstring& GetDefaultFolderPath() const;
            void SetDefaultFolderPath( const tstring& path );

            CollectionManager* GetCollectionManager() { return m_CollectionManager; }
            SearchHistory* GetSearchHistory() { return m_SearchHistory; }

        private:
            WindowSettingsPtr     m_WindowSettings;
            tstring               m_DefaultFolder;
            ViewOptionID          m_ThumbnailMode;
            u32                   m_ThumbnailSize;
            bool                  m_DisplayPreviewAxis;
            CollectionManagerPtr  m_CollectionManager;
            SearchHistoryPtr      m_SearchHistory;
            u32                   m_DependencyCollectionRecursionDepth;
            u32                   m_UsageCollectionRecursionDepth;

        public:
            static void EnumerateClass( Reflect::Compositor< VaultPreferences >& comp )
            {
                comp.AddField( &VaultPreferences::m_WindowSettings, "m_WindowSettings", Reflect::FieldFlags::Hide );
                comp.AddField( &VaultPreferences::m_DefaultFolder, "m_DefaultFolder", Reflect::FieldFlags::Hide );
                comp.AddEnumerationField( &VaultPreferences::m_ThumbnailMode, "m_ThumbnailMode" );

                {
                    Reflect::Field* field = comp.AddField( &VaultPreferences::m_ThumbnailSize, "m_ThumbnailSize" );
                    field->SetProperty( TXT( "UIScript" ), TXT( "UI[.[slider{min=16.0; max=256.0} value{}].]" ) );
                }

                comp.AddField( &VaultPreferences::m_DisplayPreviewAxis, "m_DisplayPreviewAxis" );
                comp.AddField( &VaultPreferences::m_CollectionManager, "m_CollectionManager", Reflect::FieldFlags::Hide | Reflect::FieldFlags::Share );
                comp.AddField( &VaultPreferences::m_SearchHistory, "m_SearchHistory", Reflect::FieldFlags::Hide | Reflect::FieldFlags::Share );

                {
                    Reflect::Field* field = comp.AddField( &VaultPreferences::m_DependencyCollectionRecursionDepth, "DependencySearchDepth" );
                    field->SetProperty( TXT( "UIScript" ), TXT( "UI[.[slider{min=0; max=100} value{}].]" ) );
                }

                {
                    Reflect::Field* field = comp.AddField( &VaultPreferences::m_UsageCollectionRecursionDepth, "UsageSearchDepth" );
                    field->SetProperty( TXT( "UIScript" ), TXT( "UI[.[slider{min=0; max=100} value{}].]" ) );
                }
            }
        };

        typedef Helium::SmartPtr< VaultPreferences > VaultPreferencesPtr;
    }
}