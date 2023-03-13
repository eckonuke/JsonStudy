// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "DefaultObject.h"

// Sets default values
AObjectManager::AObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectManager::BeginPlay()
{
	Super::BeginPlay();
	
	//Actor 에서 Input 등록
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	EnableInput(playerController);

	InputComponent->BindAction(TEXT("1"), IE_Pressed, this, &AObjectManager::CreateObject);
}

// Called every frame
void AObjectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectManager::CreateObject() {
	float pos_x = FMath::RandRange(-1000.0f, 1000.0f);
	float pos_y = FMath::RandRange(-1000.0f, 1000.0f);
	float pos_z = FMath::RandRange(0.0f, 1000.0f);
	ADefaultObject* obj = GetWorld()->SpawnActor<ADefaultObject>(objectFactory, FVector(pos_x, pos_y, pos_z), FRotator::ZeroRotator);
	
	int32 type = FMath::RandRange(0, meshes.Num() - 1);
	obj->SetInit(meshes[type]);
}