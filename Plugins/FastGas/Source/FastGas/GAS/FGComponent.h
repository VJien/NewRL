// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "FastGas/Data/FGTypesCore.h"

#include "FGComponent.generated.h"

class UFGGameplayAbility;



USTRUCT(BlueprintType)
struct FFGGameplayAbilitySpec 
{
	GENERATED_BODY()
	FFGGameplayAbilitySpec()
	{
	}
	bool operator == (const FFGGameplayAbilitySpec& InSpec)const
	{
		return Spec.Ability == InSpec.Spec.Ability && Spec.Level == InSpec.Spec.Level &&
			(AbilityName == InSpec.AbilityName );
	}
	FFGGameplayAbilitySpec(const FString& Name, UGameplayAbility* InAbility, int32 InLevel = 1);
	
	UPROPERTY(BlueprintReadWrite)
	FGameplayAbilitySpec Spec;
	
	UPROPERTY(BlueprintReadWrite)
	FString AbilityName = TEXT("");
	
};



USTRUCT(BlueprintType)
struct FFGGameplayAbilitySpecContainer
{
	GENERATED_BODY()
	
	/** List of activatable abilities */
	UPROPERTY(BlueprintReadWrite)
	TArray<FFGGameplayAbilitySpec> Items;
	
	/** Component that owns this list */
	UPROPERTY(BlueprintReadWrite)
	UAbilitySystemComponent* Owner;

	void Add(const FString& name ,FGameplayAbilitySpec* Spec)
	{
		Items.Add(FFGGameplayAbilitySpec{name,Spec->Ability,Spec->Level});
	}
	
		
	void Remove(const FString& Name)
	{
		for (auto Item: Items)
		{
			if (Item.AbilityName == Name)
			{
				Items.Remove(Item);
				return;
			}
		}
	}
	void Remove(const TSubclassOf<UGameplayAbility> AbilityClass)
	{
		for (auto Item: Items)
		{
			if (Item.Spec.Ability->GetClass() == AbilityClass)
			{
				Items.Remove(Item);
				return;
			}
		}
	}
	// void Remove(const FGameplayTag& Tag)
	// {
	// 	for (auto Item: Items)
	// 	{
	// 		if (Item.AbilityTag == Tag)
	// 		{
	// 			Items.Remove(Item);
	// 			return;
	// 		}
	// 	}
	// }
	
	FGameplayAbilitySpec* Find(const FString& Name)
	{
		for (auto& Item: Items)
		{
			if (Item.AbilityName == Name)
			{
				return &Item.Spec;
			}
		}
		return nullptr;
	}
	
	// FGameplayAbilitySpec* Find(const FGameplayTag& Tag)
	// {
	// 	for (auto& Item: Items)
	// 	{
	// 		if (Item.AbilityTag == Tag)
	// 		{
	// 			return &Item.Spec;
	// 		}
	// 	}
	// 	return nullptr;
	// }
	FGameplayAbilitySpec* Find(const TSubclassOf<UGameplayAbility> AbilityClass)
	{
		for (auto& Item: Items)
		{
			if (Item.Spec.Ability->GetClass() == AbilityClass)
			{
				return &Item.Spec;
			}
		}
		return nullptr;
	}

	int32 Num()const
	{
		return Items.Num();
	}
};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReceiveEventDamage, UFGComponent*, SourceASC, const FFGDamageParameter&, Parameter);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DisplayName=FGComponent)
class FASTGAS_API UFGComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "ASC")
		void RPC_Ser_AddAbility(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 level = 1);
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "ASC")
		void RPC_Ser_RemoveAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "ASC")
		void RPC_Ser_RemoveAbilityByName(const FString& name);
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "ASC")
		void RPC_Ser_UpgradeAbilityByName(const FString& name, int32 upLevel=1);
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "ASC")
		void RPC_Ser_UpgradeAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel = 1);


public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	UFUNCTION(BlueprintCallable, Category = "ASC")
		bool AddNewAbility(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 level = 1);
	UFUNCTION(BlueprintCallable, Category = "ASC")
		bool RemoveAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, Category = "ASC")
		bool RemoveAbilityByName(const FString& name);
	UFUNCTION(BlueprintCallable, Category = "ASC", BlueprintAuthorityOnly)
		bool UpgradeAbilityByName(const FString& name, int32 upLevel);
	UFUNCTION(BlueprintCallable, Category = "ASC")
		bool UpgradeAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel = 1);
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintPure, Category = "ASC")
		int32 GetAbilityLevelByName(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintPure, Category = "ASC")
		int32 GetAbilityLevelByClass(TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ASC")
		UFGGameplayAbility* GetAbilityObjectByName(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ASC")
		bool HasAbility(const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ASC")
		bool HasAbilityByClass(TSubclassOf<UFGGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"), DisplayName = "ExecuteGameplayCue")
		void BP_ExecuteGameplayCue(const FGameplayTag& GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"), DisplayName = "RemoveGameplayCue")
		void  BP_RemoveGameplayCue(const FGameplayTag& GameplayCueTag);
	UFUNCTION(BlueprintCallable, Category = "ASC", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"), DisplayName = "AddGameplayCue")
		void  BP_AddGameplayCue(const FGameplayTag& GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ASC")
		FGameplayTagContainer GetAllTags();








	void PreDamage(UFGComponent* SourceASC, const FFGDamageParameter& Parameter);
	void PostDamage(UFGComponent* SourceASC,  float Damage, FHitResult HitResult);

	void PreDodge(UFGComponent* SourceASC, const FFGDamageParameter& Parameter);
	void PreBlock(UFGComponent* SourceASC, const FFGDamageParameter& Parameter);

	
	UPROPERTY(BlueprintAssignable)
	FOnReceiveEventDamage OnPreDamage;




public:
	bool bHasGiveCharacterAbilities = false;
	bool bHasApplyStartupEffects = false;

public:
	UPROPERTY(ReplicatedUsing=OnRep_AbilitySpecMap)
	FFGGameplayAbilitySpecContainer AbilitySpecs;
	UFUNCTION()
	virtual void OnRep_AbilitySpecMap(const FFGGameplayAbilitySpecContainer& Old);



	UPROPERTY(EditAnywhere,Category = "ASC")
	bool bDebugLog = false;
};
