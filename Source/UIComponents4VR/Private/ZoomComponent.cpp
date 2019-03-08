// Fill out your copyright notice in the Description page of Project Settings.

#include "ZoomComponent.h"

void UZoomComponent::Execute(UManipulableComponent * ManipulableComponent)
{
    if(ManipulableComponent != nullptr)
    {
        if (ManipulableComponent->IsSelected())
        {
            float AngleDegrees = ManipulableComponent->GetAngleDegrees();
            float ScaleFactor = 0.5f;
            float ScaleValue = 1.0f + (AngleDegrees * ScaleFactor);

            ManipulableComponent->SetRelativeScale3D(FVector(ScaleValue, ScaleValue, ScaleValue));
        }
        else
        {
            ManipulableComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
        }
    }
}

void UZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UZoomComponent::BeginPlay()
{
    Super::BeginPlay();
}
