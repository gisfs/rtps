// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RTPS_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;


private:
	void ChangePawn();

	UPROPERTY()
	TArray<AActor*> Pawns;

	int32 CurrentPawnIndex = 0;
};