// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Data/FGTypesCore.h"
#include "GAS/FGComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "FGBlueprintLibrary.generated.h"

class UFGGameplayAbility;
class AActor;
class UAbilitySystemComponent;
class UGameplayAbility;
struct FGameplayTag;


UCLASS()
class FASTGAS_API UFGBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static  TArray<FGameplayAbilitySpec> GetActivableAbilities(UAbilitySystemComponent* ASC);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static  int32 GetAbilityLevelBySpec(FGameplayAbilitySpec Spec);

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability", meta = (AutoCreateRefTerm = "WithTags, WithoutTags"))
		static void CancelAbilityWithTag(UAbilitySystemComponent* AbilityComponent, const FGameplayTagContainer& WithTags, const FGameplayTagContainer& WithoutTags, UGameplayAbility* Ignore);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static void CancelAllAbilities(UAbilitySystemComponent* AbilityComponent, UGameplayAbility* Ignore /*= nullptr*/);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static void CancelAbility(UAbilitySystemComponent* AbilityComponent, UGameplayAbility* Ability);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static void CancelAbilityHandle(UAbilitySystemComponent* AbilityComponent, const FGameplayAbilitySpecHandle& AbilityHandle);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static void CancelAbilitySpec(UAbilitySystemComponent* AbilityComponent, const FGameplayAbilitySpec& AbilityHandle);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability", meta = (AutoCreateRefTerm = "GameplayTagContainer, WithTags"))
		static void GetActivatableGameplayAbilitySpecsByAllMatchingTags(UAbilitySystemComponent* AbilityComponent, const FGameplayTagContainer& GameplayTagContainer, TArray < struct FGameplayAbilitySpec >& MatchingGameplayAbilities, bool bOnlyAbilitiesThatSatisfyTagRequirements);


		
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool AddNewAbility(UFGComponent* AbilityComponent, TSubclassOf<UFGGameplayAbility> AbilityClass,int32 level = 1);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool RemoveAbilityByClass(UFGComponent* AbilityComponent,TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool RemoveAbilityByName(UFGComponent* AbilityComponent,const FString& name);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability", BlueprintAuthorityOnly)
		static bool UpgradeAbilityByName(UFGComponent* AbilityComponent,const FString& name, int32 upLevel);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool UpgradeAbilityByClass(UFGComponent* AbilityComponent,TSubclassOf<UFGGameplayAbility> AbilityClass, int32 upLevel = 1);
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintPure, Category = "FastGas|Lib|Ability")
		static int32 GetAbilityLevelByName(UFGComponent* AbilityComponent,const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintPure, Category = "FastGas|Lib|Ability")
		static int32 GetAbilityLevelByClass(UFGComponent* AbilityComponent,TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static UFGGameplayAbility* GetAbilityObjectByName(UFGComponent* AbilityComponent,const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static bool HasAbility(UFGComponent* AbilityComponent,const FString& name);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static bool HasAbilityByClass(UFGComponent* AbilityComponent,TSubclassOf<UFGGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability", meta = (AutoCreateRefTerm = "GameplayTagContainer, WithTags"))
		static bool HasAbilityByTag(UAbilitySystemComponent* AbilityComponent, FGameplayTag Tag);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static bool HasAbilityTag(UAbilitySystemComponent* AbilityComponent, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|GameplayCue", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"))
		static void ExecuteGameplayCueLocal(UAbilitySystemComponent* AbilityComponent, const FGameplayTag& GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|GameplayCue", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"))
		static void RemoveGameplayCueLocal(UAbilitySystemComponent* AbilityComponent, const FGameplayTag& GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|GameplayCue", meta = (AutoCreateRefTerm = "GameplayCueTag, GameplayCueParameters"))
		static void AddGameplayCueLocal(UAbilitySystemComponent* AbilityComponent, const FGameplayTag& GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);



	UFUNCTION(BlueprintCallable,  BlueprintPure, Category = "FastGas|Lib|Ability")
		static float GetScalableFloatValue(FScalableFloat ScaleFloat, int32 level);

		//在GA外面对spec参数添加目标
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability", meta = (AutoCreateRefTerm = "HitResults,TargetActors"))
		static FFGGameplayEffectContainerSpec AddTargetsToEffectContainerSpec(const FFGGameplayEffectContainerSpec& ContainerSpec, const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
	//应用自定义的GESpec
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FFGGameplayEffectContainerSpec& ContainerSpec);
	UFUNCTION(BlueprintCallable,  BlueprintPure, Category = "FastGas|Lib|Ability")
		static bool HasEffects(const FFGGameplayEffectContainerSpec& ContainerSpec);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Ability")
		static bool HasTargets(const FFGGameplayEffectContainerSpec& ContainerSpec);

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability", meta = (AutoCreateRefTerm = "HitResults,TargetActors"))
		static FFGGameplayEffectContainerSpec MakeEffectContainerExtra(AActor* ownerActor, const FFGGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 level);

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability", BlueprintPure)
		static bool TryGetActorInfo(UAbilitySystemComponent* AbilityComponent, FGameplayAbilityActorInfo& ActorInfo);

	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool TryApplyGameplayEffectByCaller(UAbilitySystemComponent* AbilitySystemComponent,FGameplayAttribute Attribute, float NewValue, TEnumAsByte<EGameplayModOp::Type> Type);

	//动态创建GE修改属性
	UFUNCTION(BlueprintCallable, Category = "FastGas|Lib|Ability")
		static bool TryApplyGameplayEffectRumtime(UAbilitySystemComponent* AbilitySystemComponent,FGameplayAttribute Attribute, float NewValue, TEnumAsByte<EGameplayModOp::Type> Type);

	template <typename TEnum>
		static FString FGEnumToString(const FString& EnumName, TEnum Enum, bool bShortName)
	{
		const UEnum* ep = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (ep)
		{
			if (bShortName)
			{
				FString tempStr = ep->GetNameByValue((int)Enum).ToString();
				TArray<FString> arr = UKismetStringLibrary::ParseIntoArray(tempStr, TEXT("::"));
				if (arr.Num() > 0)
				{
					return arr.Last();
				}
			}

			return ep->GetNameByValue((int)Enum).ToString();
		}
		return TEXT("");
	}

	template <typename TEnum>
	static TEnum FGStringToEnum(const FString& EnumName, FString EnumValue)
	{
		const UEnum* ep = FindObject<UEnum>(ANY_PACKAGE, *EnumName, 1);
		if (!ep)
		{
			return TEnum(0);
		}
		return (TEnum)ep->GetIndexByName(FName(*FString(EnumValue)));
	}


public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Data")
	static FString DamageTypeToString(EFGDamageType type);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FastGas|Lib|Data")
	static EFGDamageType StringToDamageType(const FString& name);





	
	UFUNCTION(BlueprintPure, CustomThunk, meta = (KeyWords = "ToString", CustomStructureParam = "StructReference",
		DisplayName = "Struct to Json String", BlueprintAutocast), Category = "Battle|Utility")
	static void UStructToJsonObjectString(const int32& StructReference, FString& JsonString);
	static void GenericUStructToJsonObjectString(const UStruct* StructDefinition, const void* Struct,
												 FString& OutJsonString, int64 CheckFlags,
												 int64 SkipFlags);

	DECLARE_FUNCTION(execUStructToJsonObjectString)
	{
		//Stack.Step(Stack.Object, NULL);
		Stack.StepCompiledIn<FStructProperty>(NULL);
		FStructProperty* StructProperty = CastField<FStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		//Get JsonString reference
		P_GET_PROPERTY_REF(FStrProperty, JSONString);

		P_FINISH;

		P_NATIVE_BEGIN;

		GenericUStructToJsonObjectString(StructProperty->Struct, StructPtr, JSONString, 0, 0);

		P_NATIVE_END;
	}




#if WITH_EDITOR

	
#endif
	
};

