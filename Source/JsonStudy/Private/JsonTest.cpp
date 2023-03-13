// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonTest.h"

// Sets default values
AJsonTest::AJsonTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJsonTest::BeginPlay()
{
	Super::BeginPlay();
	LoadData();
}


void AJsonTest::SaveData() {
	//Json ����� �߰��ؾ��Ѵ�
	FString userName = TEXT("David");
	int32 userAge = 32;
	TArray<FString> interest = { "Game", "Real Madrid", "Stock" };
	bool isWoman = false;
	//������ ����ִ� �����͸� Json Object�� ���� �Ѵ�
	//FJsonObject* jsonObject;//���� �޸𸮸� �����Ѵ�

	FUserInfo info;
	info.name = "David";
	info.age = 32;
	for (int32 i = 0; i < 3; i++) {
		info.userInterest.Add(interest[i]);
	}


	//�𸮾� �������� �ڵ����� �޸� ����
	//�������� �����͸� ������ �ִ�, NULL���� ����
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	jsonObject->SetStringField("userName", userName);
	jsonObject->SetNumberField("userAge", userAge);
	jsonObject->SetBoolField("isWoman", isWoman);

	//FString -> FJsonValue�� ��ȯ�ؼ� JsonArray ����
	TArray<TSharedPtr<FJsonValue>> arrayInterests;
	for (int32 i = 0; i < info.userInterest.Num(); i++) {
		arrayInterests.Add(MakeShareable(new FJsonValueString(info.userInterest[i])));
	}
	jsonObject->SetArrayField("userInterest", arrayInterests);

	//Json Object�� ���ڿ�(string)�� ��������
	FString jsonString;
	//�Ѱ��� �����͸� ����, NULL�� �Ұ���
	TSharedRef<TJsonWriter<>> jsonWriter = TJsonWriterFactory<>::Create(&jsonString);//������ ����
	//������ Json Object�� ���ڿ��� ��ȯ�Ѵ�
	if(FJsonSerializer::Serialize(jsonObject.ToSharedRef(), jsonWriter)) {
		//json �������� �� �ۼ��Ǿ��� �α׷� Ȯ��
		UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);

		//Json ���·� ����� ���ڿ�(jsonString)�� ���Ϸ� ����
		FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("jsonTest.txt"));
		FFileHelper::SaveStringToFile(jsonString, *filePath);
	}
}

void AJsonTest::LoadData() {
	FString jsonString;
	//������ �о����
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("jsonTest.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);
	UE_LOG(LogTemp, Warning, TEXT("load: %s"), *jsonString);

	//string -> JsonObject�� ��ȯ
	TSharedPtr<FJsonObject> jsonObject;
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	if (FJsonSerializer::Deserialize(jsonReader, jsonObject)) {
		FString userName = jsonObject->GetStringField("userName");
		int32 userAge = jsonObject->GetNumberField("userAge");
		bool isWoman = jsonObject->GetBoolField("isWoman");
		
		TArray<FString> userInterest;
		TArray<TSharedPtr<FJsonValue>> arrayInterests = jsonObject->GetArrayField("userInterests");
		for (int32 i = 0; i < arrayInterests.Num(); i++) {
			userInterest.Add(arrayInterests[i]->AsString());
		}

	}
}

// Called every frame
void AJsonTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
