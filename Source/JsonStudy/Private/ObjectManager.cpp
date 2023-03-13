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
	
	//Actor ���� Input ���
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	EnableInput(playerController);

	InputComponent->BindAction(TEXT("1"), IE_Pressed, this, &AObjectManager::CreateObject);
	InputComponent->BindAction(TEXT("2"), IE_Pressed, this, &AObjectManager::SaveObject);
	InputComponent->BindAction(TEXT("3"), IE_Pressed, this, &AObjectManager::LoadObject);
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
	int32 type = FMath::RandRange(0, meshes.Num() - 1);
	CreateObject(type, FVector(pos_x, pos_y, pos_z));
}

void AObjectManager::CreateObject(int32 typeNum, FVector position) {
	ADefaultObject* obj = GetWorld()->SpawnActor<ADefaultObject>(objectFactory, position, FRotator::ZeroRotator);
	obj->SetInit(meshes[typeNum]);

	FObjectInfo info;
	info.type = typeNum;
	info.obj = obj;

	arrayObject.Add(info);
}

void AObjectManager::SaveObject(){
	//������ -> Json Object �� ����
	TArray<TSharedPtr<FJsonValue>> jsonArray;
	for (int32 i = 0; i < arrayObject.Num(); i++) {
		TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
		jsonObject->SetNumberField("type", arrayObject[i].type);
		jsonObject->SetNumberField("pos_x", arrayObject[i].obj->GetActorLocation().X);
		jsonObject->SetNumberField("pos_Y", arrayObject[i].obj->GetActorLocation().Y);
		jsonObject->SetNumberField("pos_Z", arrayObject[i].obj->GetActorLocation().Z);

		jsonArray.Add(MakeShareable(new FJsonValueObject(jsonObject)));
	}

	//Json Object -> FString���� ����
	FString jsonString;
	TSharedRef<TJsonWriter<>> jsonWrite = TJsonWriterFactory<>::Create(&jsonString);
	FJsonSerializer::Serialize(jsonArray, jsonWrite);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);

	//Json ���·� ����� ���ڿ�(jsonString)�� ���Ϸ� ����
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("obj_info.txt"));
	FFileHelper::SaveStringToFile(jsonString, *filePath);
}

void AObjectManager::LoadObject() {
	DeleteAll();
	FString jsonString;
	//������ �о����
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("jsonTest.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);
	UE_LOG(LogTemp, Warning, TEXT("load: %s"), *jsonString);

	//FString -> Json Object
	TArray<TSharedPtr<FJsonValue>> jsonArray;
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	FJsonSerializer::Deserialize(jsonReader, jsonArray);

	//������Ʈ ����
	for (int32 i = 0; i < jsonArray.Num(); i++) {
		TSharedPtr<FJsonObject> jsonObject = jsonArray[i]->AsObject();
		int32 type = jsonObject->GetNumberField("type");
		float pos_x = jsonObject->GetNumberField("pos_x");
		float pos_y = jsonObject->GetNumberField("pos_y");
		float pos_z = jsonObject->GetNumberField("pos_z");
		CreateObject(type, FVector(pos_x, pos_y, pos_z));
	}
}

void AObjectManager::DeleteAll() {
	for (int32 i = 0; i < arrayObject.Num(); i++) {
		arrayObject[i].obj->Destroy();
	}
	arrayObject.Empty();
}
