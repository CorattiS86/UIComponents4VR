// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableComponent.h"
#include "ToolComponent.generated.h"

class UManipulableComponent;

UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UICOMPONENTS4VR_API UToolComponent : public USelectableComponent
{
	GENERATED_BODY()

public:	
	UToolComponent();
    
    // Inherited via USelectableComponent
    /*virtual*/ UToolComponent* Accept(UToolComponent * ToolComponent) override;

    virtual void Execute(UToolComponent* ToolComponent);
    virtual void Execute(UManipulableComponent* ManipulableComponent);

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;	


};