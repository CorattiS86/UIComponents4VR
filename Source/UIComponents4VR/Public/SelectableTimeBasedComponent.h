// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectableComponent.h"
#include "SelectableTimeBasedComponent.generated.h"

class ITimeSelectableObserver;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectableTimeBasedComponentOnSelectedStateChangedSignature, bool, NewTimeSelectedState);

UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UICOMPONENTS4VR_API USelectableTimeBasedComponent : public USelectableComponent
{
	GENERATED_BODY()
	
public:
    USelectableTimeBasedComponent();

    UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "0.5", ClampMax = "60.0", UIMin = "0.5", UIMax = "60.0"))
    float TimeSelectionThreshold;

    UFUNCTION(BlueprintCallable)
    FORCEINLINE int32 GetPercentage() { return FMath::Clamp((int32)(100 * TimeCounter / TimeSelectionThreshold), 0, 100); }

    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Time-Based Selected Changed"))
    FSelectableTimeBasedComponentOnSelectedStateChangedSignature OnTimeSelectedStateChanged;

    FORCEINLINE void AddObserver(ITimeSelectableObserver* NewTimeSelectableObserver) { TimeSelectedStateObservers.Emplace(NewTimeSelectableObserver); }
    FORCEINLINE void RemoveObserver(ITimeSelectableObserver* ExistingTimeSelectableObserver) { TimeSelectedStateObservers.Remove(ExistingTimeSelectableObserver); }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void NotifySelectedStateChange(bool NewSelectedState);
    virtual void NotifyTimeSelectedStateChange(bool NewTimeSelectedState);

    void SetTimeSelectedState(bool NewTimeSelectedState);
    void Reset();

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

    bool bTimeSelectedState;
    float TimeCounter;
	
    TSet<ITimeSelectableObserver* > TimeSelectedStateObservers;
};

class ITimeSelectableObserver
{

public:
    virtual void OnNotifyTimeSelectedStateChange(USelectableTimeBasedComponent* Subject, bool NewTimeSelectedState) = 0;
};
