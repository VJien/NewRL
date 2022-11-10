// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "FGAssetManager.generated.h"

UCLASS(Blueprintable,BlueprintType)
class FASTGAS_API UFGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	virtual void StartInitialLoading() override;


	static UFGAssetManager& Get();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "FastGas|AssetManager")
		static UFGAssetManager* GetAssetManager();
	
	
};
