// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastGas/SceneItem/FGAbilityItem.h"
#include "GameFramework/Actor.h"
#include "SciFi_RL/Core/RLCharacter.h"
#include "RLSceneItem.generated.h"

UCLASS()
class SCIFI_RL_API ARLSceneItem : public AFGAbilityItem
{
public:
	
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure)
	USkeletalMeshComponent* TryGetMesh();
	
	// UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	// bool TryUse(AActor* Causer, ARLCharacter* SourcePawn);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EffectsID = NAME_None;

	UFUNCTION(BlueprintCallable)
	void CopyAttributesFromOwner(const FGameplayAttribute &Attribute);
	
};

