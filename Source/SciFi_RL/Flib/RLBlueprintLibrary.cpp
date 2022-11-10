// Fill out your copyright notice in the Description page of Project Settings.


#include "RLBlueprintLibrary.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

void URLBlueprintLibrary::SetWidgetComponentClass(UWidgetComponent* WidgetComponent, TSubclassOf<UUserWidget> NewClass)
{
	
	if (WidgetComponent && NewClass)
	{
		WidgetComponent->SetWidgetClass(NewClass);
	}
	

}
