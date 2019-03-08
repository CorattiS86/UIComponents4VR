// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolComponent.h"
#include "NullToolComponent.generated.h"

/**
 * 
 */
UCLASS()
class UICOMPONENTS4VR_API UNullToolComponent : public UToolComponent
{
	GENERATED_BODY()
	
public:

    /*virtual*/ void Execute(UToolComponent* ToolComponent);
    /*virtual*/ void Execute(UManipulableComponent* ManipulableComponent);
	
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
};
