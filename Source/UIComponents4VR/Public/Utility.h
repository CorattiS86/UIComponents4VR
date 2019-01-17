// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

/**
 * 
 */
class UICOMPONENTS4VR_API Utility
{
public:

    static const FVector getUnitVectorX() { return FVector(1.0f, 0.0f, 0.0f); }
    static const FVector getUnitVectorY() { return FVector(0.0f, 1.0f, 0.0f); }
    static const FVector getUnitVectorZ() { return FVector(0.0f, 0.0f, 1.0f); }

    static const FRotator getUnitRotatorX() { return FRotator(0.0f, 0.0f, 1.0f); }
    static const FRotator getUnitRotatorY() { return FRotator(1.0f, 0.0f, 0.0f); }
    static const FRotator getUnitRotatorZ() { return FRotator(0.0f, 1.0f, 0.0f); }

    static const FRotator getVectorAsRotator(FVector vector) { return FRotator(vector.Y, vector.Z, vector.X); }

    static const FQuat getAsQuatForAxisX(const FVector & vector) {

        return FQuat(FVector(1.0f, 0.0f, 0.0f), FMath::DegreesToRadians(vector.X));
    }

    static const FQuat getAsQuatForAxisY(const FVector & vector) {

        return FQuat(FVector(0.0f, 1.0f, 0.0f), FMath::DegreesToRadians(vector.Y));
    }

    static const FQuat getAsQuatForAxisZ(const FVector & vector) {

        return FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(vector.Z));
    }

    static void PrintToScreen(const FString & DebugMessage, FColor DisplayColor = FColor::Cyan) {
        uint64		Key = -1;
        float		TimeToDisplay = 0.5f;
        bool		bNewerOnTop = true;
        FVector2D	TextScale = FVector2D::UnitVector;

        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(Key,
                TimeToDisplay,
                DisplayColor,
                DebugMessage,
                bNewerOnTop,
                TextScale);
        }
    }

    //FString::Printf(TEXT("[%s:%s] Example Num1: %d, Num2: %d"), FString first, FString second, int num1, int num2);
};
