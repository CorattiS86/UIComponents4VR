// Fill out your copyright notice in the Description page of Project Settings.

#include "ToolComponent.h"


// Sets default values for this component's properties
UToolComponent::UToolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UToolComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UToolComponent::Execute(UToolComponent * ToolComponent)
{
}

void UToolComponent::Execute(UManipulableComponent * ManipulableComponent)
{
}

void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UToolComponent* UToolComponent::Accept(UToolComponent * ToolComponent)
{
    if (ToolComponent != nullptr)
    {
        ToolComponent->Execute(this);
    }

    return this;
}
