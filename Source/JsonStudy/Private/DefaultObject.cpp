// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADefaultObject::ADefaultObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(compMesh);
}

// Called when the game starts or when spawned
void ADefaultObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultObject::SetInit(class UStaticMesh* mesh) {
	compMesh->SetStaticMesh(mesh);
}