// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticInstantTeleport.h"


// Sets default values
AStaticInstantTeleport::AStaticInstantTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SelectableTimeBasedComponent = CreateDefaultSubobject<USelectableTimeBasedComponent>(TEXT("TimeSelectable"));

}

// Called when the game starts or when spawned
void AStaticInstantTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaticInstantTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (SelectableTimeBasedComponent->IsSelected())
    {
        if (MainPlayer != nullptr)
        {
            FVector ThisLocation = GetComponentLocation();
            FVector PlayerLocation = MainPlayer->GetPawn()->GetActorLocation();

            if (!PlayerLocation.Equals(ThisLocation, 0.01))
            {
                    MainPlayer->GetPawn()->SetActorLocation(ThisLocation);
            }

        }
    }
}

