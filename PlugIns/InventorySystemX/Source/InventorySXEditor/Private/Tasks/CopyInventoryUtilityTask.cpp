/*
* Inventory System X
*
* Copyright (C) 2023-2025 Mykhailo Oliinyk <m19tes@gmail.com> All Rights Reserved.
*/


#include "CopyInventoryUtilityTask.h"
#include "Modules/ModuleManager.h"


void UCopyInventoryUtilityTask::BeginExecution()
{
	Super::BeginExecution();
	SetTaskNotificationText(FText::FromString(TEXT("Copy Inventory Plugin Folder To Project Dir...")));
	if (CopyFolderFromEngineToProject())
	{
		SetTaskNotificationText(FText::FromString(TEXT("The folder was copied successfully.")));
	}
	else
	{
		SetTaskNotificationText(FText::FromString(TEXT("Error copying folder.")));
	}
	FinishExecutingTask();
}

bool UCopyInventoryUtilityTask::CopyFolderFromEngineToProject()
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    
   
    const FString EngineMarketplacePath = FPaths::Combine(FPaths::EnginePluginsDir(), TEXT("Marketplace"));
    
    const FString ProjectPluginsPath = FPaths::ProjectPluginsDir();
    const FString DestinationPath = FPaths::Combine(ProjectPluginsPath, TEXT("InventorySystemX"));
    
  
    if (!PlatformFile.DirectoryExists(*ProjectPluginsPath))
    {
        PlatformFile.CreateDirectory(*FPaths::Combine(FPaths::ProjectDir(), TEXT("Plugins")));
    }

    class FPluginFileVisitor : public IPlatformFile::FDirectoryVisitor
    {
    public:
        FString FoundPath;
        bool bFileFound = false;

        virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
        {
            if (!bIsDirectory)
            {
                FString FileName = FPaths::GetCleanFilename(FilenameOrDirectory);
                if (FileName.Equals(TEXT("InventorySystemX.uplugin"), ESearchCase::IgnoreCase))
                {
                    FoundPath = FPaths::GetPath(FilenameOrDirectory);
                    bFileFound = true;
                    return false; 
                }
            }
            return true; 
        }
    };

    FPluginFileVisitor Visitor;
    PlatformFile.IterateDirectoryRecursively(*EngineMarketplacePath, Visitor);

    if (Visitor.bFileFound)
    {
        const FString SourcePath = Visitor.FoundPath;
        if (PlatformFile.CopyDirectoryTree(*DestinationPath, *SourcePath, true))
        {
            UE_LOG(LogTemp, Warning, TEXT("The InventorySystemX folder was copied successfully from %s to %s"), *SourcePath, *DestinationPath);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Error copying folder from %s to %s"), *SourcePath, *DestinationPath);
            return false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InventorySystemX.uplugin not found in Engine/Plugins/Marketplace/ directory!"));
        return false;
    }
}

bool UCopyInventoryUtilityTask::RemoveProjectFolder()
{
	const FString DestinationPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("InventorySystemX"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (PlatformFile.DeleteDirectory(*DestinationPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("The Inventory folder was removed successfully."))
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error removing folder."))
	return false;
}

bool UCopyInventoryUtilityTask::MovePluginContendDirToProjectContentDir()
{

	const FString SourcePath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("InventorySystemX/Content"));
	const FString DestinationPath = FPaths::ProjectContentDir();
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	
	if (PlatformFile.CopyDirectoryTree(*DestinationPath, *SourcePath, false))
	{
		PlatformFile.DeleteDirectoryRecursively(*SourcePath);
		UE_LOG(LogTemp, Warning, TEXT("The content folder was copied successfully."))
		
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error copying folder."))
	return false;
}
