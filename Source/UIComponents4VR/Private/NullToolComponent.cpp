// Fill out your copyright notice in the Description page of Project Settings.

#include "NullToolComponent.h"

void UNullToolComponent::Execute(UToolComponent* ToolComponent)
{
}

void UNullToolComponent::Execute(UManipulableComponent * ManipulableComponent)
{
}

void UNullToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNullToolComponent::BeginPlay()
{
    Super::BeginPlay();
}
