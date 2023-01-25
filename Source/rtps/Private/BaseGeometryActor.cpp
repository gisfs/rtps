// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	this->SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitLocation = GetActorLocation(); 

	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
	
	//PrintTypes();
	//PrintStringTypes();
	//PrintTransform();s
}
void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor is dead %s"), *GetName());
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();

}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MovementType)
	{
	case EMovementType::Sin:
	{
		// z = z0 + amplitude * sin(freq * t);
		FVector CurrentLocation = GetActorLocation();
		if (GetWorld())
		{
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
	}
	break;

	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}
void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotator = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotator: %s"), *Rotator.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale: %s"), *Scale.ToString());
	UE_LOG(LogBaseGeometry, Error, TEXT("Human Transform: %s\n"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning,TEXT("ActorName: %s"),*GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("WeaponNum:%d,KillNum:%d"), WeaponNum, KillNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health:%f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead:%d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon:%d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "Join";
	UE_LOG(LogBaseGeometry, Warning, TEXT("Name:%s"), *Name);
	FString WeaponNumStr = "WeaponNum=" + FString::FromInt(WeaponNum);
	FString HealthStr = "Health=" + FString::SanitizeFloat(Health);
	FString IsDeadStr = "IsDead=" + FString(IsDead ? "true" : "false");
	FString Stat = FString::Printf(TEXT("Stat is % s % s % s"), *WeaponNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Name:%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Stat);
}
void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Warning, TEXT("TimerCount: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

