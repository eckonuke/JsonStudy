// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonTest.generated.h"

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()

public:
	FString name;
	int32 age;
	TArray<FString> userInterest;
	bool isWoman;
};

UCLASS()
class JSONSTUDY_API AJsonTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJsonTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SaveData();
	void LoadData();
};
