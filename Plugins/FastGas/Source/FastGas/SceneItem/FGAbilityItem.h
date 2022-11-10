// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "FastGas/Core/FGCharacter.h"
#include "UObject/Object.h"
#include "FGAbilityItem.generated.h"

/**
 * 
 */
UCLASS()
class FASTGAS_API AFGAbilityItem : public AActor, public IAbilitySystemInterface
{
public:

	GENERATED_UCLASS_BODY()

	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(AFGCharacter* InOwnerPawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitWithOutPawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="Reset Attributes")
	void Reset();
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetLevel()const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="Get Ability System Component", meta=(Keywords="Get ASC"))
	UFGComponent* BP_GetAbilitySystemComponent()const;
		
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UFGComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UFGAttributeSetBase* AttributeSet;
	//技能
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UFGGameplayAbility>> DefaultAbilities;

	//初始应用的GE效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;


	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AFGCharacter> OwnerPawn = nullptr;


	bool bHasInit = false;
};
