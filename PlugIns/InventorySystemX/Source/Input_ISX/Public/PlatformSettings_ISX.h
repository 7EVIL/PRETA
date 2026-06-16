/*
* Inventory System X
*
* Copyright (C) 2023-2025 Mykhailo Oliinyk <m19tes@gmail.com> All Rights Reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/PlatformSettings.h"
#include "PlatformSettings_ISX.generated.h"


UENUM(BlueprintType)
enum class EInputType_ISX : uint8
{
	MouseAndKeyboard,
	Gamepad,
	Touch,
};

/**
 * 
 */
UCLASS()
class INPUT_ISX_API UPlatformSettings_ISX : public UPlatformSettings
{
	GENERATED_BODY()

	virtual void InitializePlatformDefaults() override;
	
	UPROPERTY()
	EInputType_ISX DefaultInputType;

public:
	
	EInputType_ISX GetDefaultInputType() const;
};

