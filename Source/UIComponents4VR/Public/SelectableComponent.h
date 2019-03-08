#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SelectableComponent.generated.h"


class APlayerCameraManager;
class ISelectableObserver;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectableComponentOnSelectedStateChangedSignature, bool, NewSelectedState);

class UToolComponent;

UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UICOMPONENTS4VR_API USelectableComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    USelectableComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "5.0", ClampMax = "90.0", UIMin = "5.0", UIMax = "90.0"))
    float AngleThresholdForSelection;

    UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "15.0", ClampMax = "90.0", UIMin = "15.0", UIMax = "90.0"))
    float AngleThresholdForUnselection;

    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Selected Changed"))
    FSelectableComponentOnSelectedStateChangedSignature OnSelectedStateChanged;

    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    UFUNCTION(BlueprintCallable)
    FORCEINLINE float GetAngleDegrees() { return AngleDegrees; }

    UFUNCTION(BlueprintCallable)
    FORCEINLINE bool  IsSelected() { return bSelectedState; }

    FORCEINLINE void AddObserver(ISelectableObserver* NewSelectableObserver) { SelectedStateObservers.Emplace(NewSelectableObserver); }
    FORCEINLINE void RemoveObserver(ISelectableObserver* ExistingSelectableObserver) { SelectedStateObservers.Remove(ExistingSelectableObserver); }

    virtual UToolComponent* Accept(UToolComponent* ToolComponent);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    void SetSelectedState(bool NewSelectedState);
    virtual void NotifySelectedStateChange(bool NewSelectedState);


    float AngleDegrees;

    bool bSelectedState;
    APlayerCameraManager* PlayerCameraManager;

private:
    
    TSet<ISelectableObserver* > SelectedStateObservers;

};

class ISelectableObserver
{

public:
    virtual void OnNotifySelectedStateChange(USelectableComponent* Subject, bool NewSelectedState) = 0;
};