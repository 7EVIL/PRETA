/*
* Inventory System X
*
* Copyright (C) 2023-2025 Mykhailo Oliinyk <m19tes@gmail.com> All Rights Reserved.
*/

#pragma once

#include "Modules/ModuleManager.h"

class FInventorySystemXModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
