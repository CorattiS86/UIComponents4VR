#include "SelectableComponent.h"
#include "Classes/Camera/PlayerCameraManager.h"
#include "Engine.h"
#include "Utility.h"

// Sets default values for this component's properties
USelectableComponent::USelectableComponent()
{ 
	PrimaryComponentTick.bCanEverTick = true;
     
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");

    MeshComponent->AttachToComponent(
        this,
        FAttachmentTransformRules::KeepRelativeTransform);
}


UToolComponent* USelectableComponent::Accept(UToolComponent * ToolComponent)
{
    return nullptr;
}

// Called when the game starts
void USelectableComponent::BeginPlay()
{
	Super::BeginPlay();
     
    if (GEngine)
    {
        PlayerCameraManager = GEngine->GetFirstLocalPlayerController(GetWorld())->PlayerCameraManager;
    }

}

void USelectableComponent::SetSelectedState(bool NewSelectedState)
{
    if (bSelectedState == NewSelectedState)
    {
        return;
    }

    bSelectedState = NewSelectedState;

    NotifySelectedStateChange(bSelectedState);

    if (OnSelectedStateChanged.IsBound())
    {
        OnSelectedStateChanged.Broadcast(bSelectedState);
    }

}

void USelectableComponent::NotifySelectedStateChange(bool NewSelectedState)
{
    for (ISelectableObserver* Item : SelectedStateObservers)
    {
        Item->OnNotifySelectedStateChange(this, NewSelectedState);
    }
}

void USelectableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
 
    if (PlayerCameraManager != nullptr)
    {
        // vector between Component and Camera Origin
        FVector CameraWorldLocation = PlayerCameraManager->GetCameraLocation();
        FVector ComponentWorldLocation = GetComponentLocation();
        FVector CameraToComponentDirection = ComponentWorldLocation - CameraWorldLocation;
        CameraToComponentDirection.Normalize();

        /*FString CameraToComponentDirectionToString = FString::Printf(TEXT("CameraToComponentDirection: X:%f Y:%f Z:%f"), CameraToComponentDirection.X, CameraToComponentDirection.Y, CameraToComponentDirection.Z);
        Utility::PrintToScreen(CameraToComponentDirectionToString, FColor::Green);*/

        // Normal vector of Camera view
        FRotator CameraRotation = PlayerCameraManager->GetCameraRotation();
        FVector CameraDirection = CameraRotation.Vector(); // already normalized

        /*FString CameraDirectionToString = FString::Printf(TEXT("CameraDirection: X:%f Y:%f Z:%f"), CameraDirection.X, CameraDirection.Y, CameraDirection.Z);
        Utility::PrintToScreen(CameraDirectionToString, FColor::Red);*/

        float CosAngle = FVector::DotProduct(CameraToComponentDirection, CameraDirection);
        float AngleRadians = FMath::Acos(CosAngle);

        AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

        if (!bSelectedState)
        { 
            if (AngleDegrees <= AngleThresholdForSelection)
            {
                SetSelectedState(true);
            }
        }
        else
        {
            if (AngleDegrees > AngleThresholdForUnselection)
            {
                SetSelectedState(false);
            }
        }


        /*FString AngleToString = FString::Printf(TEXT("Angle: %f°"), AngleDegrees);
        Utility::PrintToScreen(AngleToString, FColor::Black);*/
    }
}
