// Fill out your copyright notice in the Description page of Project Settings.


#include "RLSceneItem.h"
#include "FastGas/GAS/FGComponent.h"



// Called when the game starts or when spawned
void ARLSceneItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARLSceneItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARLSceneItem::CopyAttributesFromOwner(const FGameplayAttribute &Attribute)
{
	if (AbilitySystemComponent && OwnerPawn.IsValid() && OwnerPawn->GetAbilitySystemComponent())
	{
		const float Value = OwnerPawn->GetAbilitySystemComponent()->GetNumericAttribute(Attribute);
		AbilitySystemComponent->SetNumericAttributeBase(Attribute, Value);
	}
	
}

USkeletalMeshComponent* ARLSceneItem::TryGetMesh_Implementation()
{
	return nullptr;
}
