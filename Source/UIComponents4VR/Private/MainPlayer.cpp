// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SelectableComponent.h"
#include "NullToolComponent.h"
#include "ZoomComponent.h"
#include "Engine.h"
#include "Utility.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    
    CurrentTool = nullptr;
    CurrentSubject = nullptr;

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
    ObserveSelectableComponents();
    ObserveTimeSelectableComponents();
    RegisterTools();

}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CurrentSubject != nullptr)
    {
        UToolComponent* ReturnToolComponent = CurrentSubject->Accept(CurrentTool);

        if (ReturnToolComponent != nullptr
            && ReturnToolComponent != CurrentTool)
        {
            CurrentTool = ReturnToolComponent;
        }
    }
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainPlayer::OnNotifySelectedStateChange(USelectableComponent * Subject, bool NewSelectedState)
{    

    Utility::PrintToScreen(TEXT("SELECTION"), FColor::Green);

    if (CurrentSubject != Subject)
    {
        if (CurrentSubject != nullptr)
        {
            if (CurrentSubject->IsSelected())
            {
                return;
            }

            CurrentSubject->Accept(CurrentTool);
        }
        CurrentSubject = Subject;
    }
    else
    {
        if(CurrentSubject != nullptr)
        {
            if (!NewSelectedState)
            {
                CurrentSubject->Accept(CurrentTool);
                CurrentSubject = nullptr;
            }
        }
    }
    
    
}

void AMainPlayer::OnNotifyTimeSelectedStateChange(USelectableTimeBasedComponent * Subject, bool NewTimeSelectedState)
{
    Utility::PrintToScreen(TEXT("TIME SELECTION"), FColor::Red);
}

void AMainPlayer::ObserveSelectableComponents()
{
    TArray<AActor* > AllSceneActors;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        AActor::StaticClass(),
        AllSceneActors
    );


    for (AActor* SceneActor : AllSceneActors)
    {
        TInlineComponentArray<USelectableComponent*> SelectableComponents(SceneActor);
        SceneActor->GetComponents(SelectableComponents);

        for (USelectableComponent* SelectableComponent : SelectableComponents)
        {
            SelectableComponent->AddObserver(this);
        }
    }
}

void AMainPlayer::ObserveTimeSelectableComponents()
{
    TArray<AActor* > AllSceneActors;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        AActor::StaticClass(),
        AllSceneActors
    );


    for (AActor* SceneActor : AllSceneActors)
    {
        TInlineComponentArray<USelectableTimeBasedComponent*> TimeSelectableComponents(SceneActor);
        SceneActor->GetComponents(TimeSelectableComponents);

        for (USelectableTimeBasedComponent* TimeSelectableComponent : TimeSelectableComponents)
        {
            TimeSelectableComponent->AddObserver(this);
        }
    }
}

void AMainPlayer::RegisterTools()
{
    for (EToolType ToolType : ToolTypes)
    {
        UToolComponent* NewToolComponent = nullptr;

        switch (ToolType)
        {
        case EToolType::TOOL_NULL:
        {
            FString ToolComponentName = "ToolComponent_Null";
            NewToolComponent = NewObject<UNullToolComponent>(this, FName(*ToolComponentName));
        }
        break;

        case EToolType::TOOL_ZOOM:
        {
            FString ToolComponentName = "ToolComponent_Zoom";
            NewToolComponent = NewObject<UZoomComponent>(this, FName(*ToolComponentName));
        }
        break;

        default:
            break;
        }

        if (NewToolComponent != nullptr)
        {
            NewToolComponent->AngleThresholdForSelection = 15.0f;
            NewToolComponent->AngleThresholdForUnselection = 25.0f;
            NewToolComponent->RegisterComponent();
            Tools.Add(NewToolComponent);
        }
    }

    if (Tools.Num() > 0)
    {
        CurrentTool = Tools[0];
    }
}

