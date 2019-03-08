// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "ToolComponent.h"
#include "SelectableComponent.h"
#include "SelectableTimeBasedComponent.h"
#include "MainPlayer.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EToolType : uint8
{
    TOOL_NULL 	UMETA(DisplayName = "Null"),
    TOOL_ZOOM 	UMETA(DisplayName = "Zoom")
};

UCLASS()
class UICOMPONENTS4VR_API AMainPlayer : public APawn, public ISelectableObserver, public ITimeSelectableObserver
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlayer();

    UCameraComponent* CameraComponent;

    FORCEINLINE void AddToolComponent(UToolComponent* NewToolComponent) { Tools.Emplace(NewToolComponent); }
    FORCEINLINE void RemoveToolComponent(UToolComponent* ExistingToolComponent) { Tools.Remove(ExistingToolComponent); }

    UPROPERTY(EditAnywhere, Category = "Components")
    TSet<EToolType> ToolTypes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	      

private:
    UToolComponent* CurrentTool;
    USelectableComponent* CurrentSubject;

    TArray<UToolComponent*> Tools;

    // Inherited via ISelectableObserver
    virtual void OnNotifySelectedStateChange(USelectableComponent * Subject, bool NewSelectedState) override;


    // Inherited via ITimeSelectableObserver
    virtual void OnNotifyTimeSelectedStateChange(USelectableTimeBasedComponent * Subject, bool NewTimeSelectedState) override;

    void ObserveSelectableComponents();
    void ObserveTimeSelectableComponents();

    void RegisterTools();
    
};
