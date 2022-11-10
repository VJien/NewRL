// Fill out your copyright notice in the Description page of Project Settings.


#include "FGAssetManager.h"
#include "AbilitySystemGlobals.h"

void UFGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

}

UFGAssetManager& UFGAssetManager::Get()
{
	UFGAssetManager* T = Cast<UFGAssetManager>(GEngine->AssetManager);
	if (T)
	{
		return *T;
	}
	else
	{
		return *NewObject<UFGAssetManager>();
	}
}

UFGAssetManager* UFGAssetManager::GetAssetManager()
{
	return &UFGAssetManager::Get();
}
