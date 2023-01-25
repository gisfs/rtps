// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};

UCLASS()
class RTPS_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;		//指向同类

	UPROPERTY(EditAnywhere)						
	UClass* UClassTest;									//指向任意类

	UPROPERTY(EditAnywhere)
	ABaseGeometryActor * GeometryActorTest;				//指向场景里的同类实例


	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

private:
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);

	void OnTimerFinished(AActor* Actor);
};
