// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);



UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};
USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")		//振幅
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")		//频率
	float Frequency = 2.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintReadWrite, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float TimerRate = 3.0f;

};

UCLASS()
class RTPS_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	FOnTimerFinished OnTimerFinished;

	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="Weapon")
	int32 WeaponNum = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")				//原型才能改
	int32 KillNum = 6;
	UPROPERTY(EditInstanceOnly, Category = "Weapon")				//实例才能改
	float Health = 34.11;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool IsDead = false;
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool HasWeapon = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
	FGeometryData GeometryData;

private:
	FVector InitLocation;
	FTimerHandle TimerHandle;
	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();
	void HandleMovement();
	void SetColor(const FLinearColor& Color);
	void OnTimerFired();
};
