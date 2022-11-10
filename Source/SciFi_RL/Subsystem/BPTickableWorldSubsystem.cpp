// Fill out your copyright notice in the Description page of Project Settings.


#include "BPTickableWorldSubsystem.h"

void UBPTickableWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnInit();
}

void UBPTickableWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	OnTick(DeltaTime);
}

void UBPTickableWorldSubsystem::OnTick_Implementation(float DeltaTime)
{
}

void UBPTickableWorldSubsystem::OnInit_Implementation()
{
}