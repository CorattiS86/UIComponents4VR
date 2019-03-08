// Fill out your copyright notice in the Description page of Project Settings.

#include "ManipulableComponent.h"
#include "ToolComponent.h"


UToolComponent* UManipulableComponent::Accept(UToolComponent * ToolComponent)
{
    if (ToolComponent != nullptr)
    {
        ToolComponent->Execute(this);
    }
    return nullptr;
}

void UManipulableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UManipulableComponent::BeginPlay()
{
    Super::BeginPlay();
}
