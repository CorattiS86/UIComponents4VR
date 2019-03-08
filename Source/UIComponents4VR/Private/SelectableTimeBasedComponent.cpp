// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectableTimeBasedComponent.h"

USelectableTimeBasedComponent::USelectableTimeBasedComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    
}

void USelectableTimeBasedComponent::BeginPlay()
{
    Super::BeginPlay();

    Reset();
}

void USelectableTimeBasedComponent::NotifySelectedStateChange(bool NewSelectedState)
{
    Super::NotifySelectedStateChange(NewSelectedState);

    if (!NewSelectedState)
    {
        Reset();
    }
}

void USelectableTimeBasedComponent::NotifyTimeSelectedStateChange(bool NewTimeSelectedState)
{
    for (ITimeSelectableObserver* Item : TimeSelectedStateObservers)
    {
        Item->OnNotifyTimeSelectedStateChange(this, NewTimeSelectedState);
    }
}


void USelectableTimeBasedComponent::SetTimeSelectedState(bool NewTimeSelectedState)
{
    if (bTimeSelectedState == NewTimeSelectedState)
    {
        return;
    }

    bTimeSelectedState = NewTimeSelectedState;

    if (OnTimeSelectedStateChanged.IsBound())
    {
        OnTimeSelectedStateChanged.Broadcast(bTimeSelectedState);
    }
}

void USelectableTimeBasedComponent::Reset()
{
    TimeCounter = 0.0f;
    bTimeSelectedState = false;
}

void USelectableTimeBasedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (Super::IsSelected() && !bTimeSelectedState)
    {
        TimeCounter += DeltaTime;

        if (TimeCounter > TimeSelectionThreshold)
        {
            bTimeSelectedState = true;
            TimeCounter = 0.0f;
        }

    }
    
}


