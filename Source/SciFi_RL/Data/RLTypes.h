// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Engine/DataTable.h"
#include "RLTypes.generated.h"


class AFGPlus_AbilityItemBase;
UENUM(BlueprintType)
enum class ESlotType:uint8
{
	None,
	Prop,
	Weapon,
	Any
};



USTRUCT(BlueprintType)
struct FSlotRuntimeData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESlotType Type;
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// AFGPlus_AbilityItemBase* Item = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Num = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* SignMesh = nullptr;
};




USTRUCT(BlueprintType)
struct FWeaponEffectsData : public  FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sound)
	USoundBase* Sound_Muzzle = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sound)
	USoundBase* Sound_Hit = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Sound)
	USoundBase* Sound_Projectile = nullptr;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX)
	bool bUseNiagaraSystem = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == true"))
	UNiagaraSystem* NS_Muzzle= nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == true"))
	UNiagaraSystem* NS_Hit = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == true"))
	UNiagaraSystem* NS_Projectile = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == false"))
	UParticleSystem* VFX_Muzzle= nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == false"))
	UParticleSystem* VFX_Hit = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=FX, meta=(EditCondition="bUseNiagaraSystem == false"))
	UParticleSystem* VFX_Projectile = nullptr;

	
};