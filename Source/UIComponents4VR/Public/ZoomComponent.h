// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolComponent.h"
#include "ZoomComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UICOMPONENTS4VR_API UZoomComponent : public UToolComponent
{
	GENERATED_BODY()
	
public:

    /*virtual*/ void Execute(UManipulableComponent* ManipulableComponent);
	
public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
};
