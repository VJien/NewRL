// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "FastGas/Data/FGTypesCore.h"
#include "GameFramework/Character.h"
#include "FGCharacter.generated.h"

class UFGAttributeSetBase;
class UAbilitySystemComponent;
class UFGComponent;

UCLASS()
class FASTGAS_API AFGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_UCLASS_BODY()

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController)override;


#pragma region Ability
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent()const override;
protected:
	//初始化属性
	virtual void InitAttributes();
	//添加初始技能
	virtual void AddCharacterStartupAbilities();
	//添加初始效果
	virtual void AddStartUpEffects();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status")
	int32 GetLevel()const;

	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ASC")
	UFGAttributeSetBase* GetAttributeSet()
	{
		return AttributeSet;
	};

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attribute")
	float GetHealth_Current() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attribute")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attribute")
	float GetShield_Current() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attribute")
	float GetMaxShield() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName="GetAttribute")
	UFGAttributeSetBase* BP_GetAttribute();

	const UFGAttributeSetBase* GetAttribute() const;

	//注意, 这一步还没有真正改变属性值, 慎用GetHealth等方法去判定条件
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character", DisplayName="Receive Damage From Gameplay Effcet Execution Calculation")
	void PreDamage(UFGComponent* SourceASC, const FFGDamageParameter& Parameter);
	//注意, 这一步还没有真正改变属性值, 慎用GetHealth等方法去判定条件
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character", DisplayName="Receive Death From Gameplay Effcet Execution Calculation")
	void PreDeath(UFGComponent* SourceASC, const FFGDamageParameter& Parameter);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	void PostDamage(UFGComponent* SourceASC,  float Damage, FHitResult HitResult);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	void PostDeath(UFGComponent* SourceASC, float  Damage, FHitResult HitResult);
protected:
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UFGComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UFGAttributeSetBase* AttributeSet;

	//角色技能
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UFGGameplayAbility>> CharacterAbilities;

	//初始效果,用来初始化属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	//初始应用的GE效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UPROPERTY()
	TMap<FString, TSubclassOf<class UGameplayAbility>> CurrentAbilitiesMap;


#pragma endregion Ability
};
