/*
* Inventory System X
*
* Copyright (C) 2023-2025 Mykhailo Oliinyk <m19tes@gmail.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityTask.h"
#include "CopyInventoryUtilityTask.generated.h"

/**
 * 
 */
UCLASS()
class UCopyInventoryUtilityTask : public UEditorUtilityTask
{
	GENERATED_BODY()

protected:
	virtual void BeginExecution() override;

public:
	static bool CopyFolderFromEngineToProject();
	static bool RemoveProjectFolder();
	static bool MovePluginContendDirToProjectContentDir();
};
