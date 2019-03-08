// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableComponent.h"
#include "ManipulableComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UICOMPONENTS4VR_API UManipulableComponent : public USelectableComponent
{
	GENERATED_BODY()

public:
    
    // Inherited via USelectableComponent
    /*virtual*/ UToolComponent* Accept(class UToolComponent * ToolComponent) override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

};
