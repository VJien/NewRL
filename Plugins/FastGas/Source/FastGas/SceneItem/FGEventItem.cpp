// Fill out your copyright notice in the Description page of Project Settings.


#include "FGEventItem.h"


// Sets default values
AFGEventItem::AFGEventItem(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFGEventItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFGEventItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

