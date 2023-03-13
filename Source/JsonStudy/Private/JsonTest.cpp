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
	//Json 모듈을 추가해야한다
	FString userName = TEXT("David");
	int32 userAge = 32;
	TArray<FString> interest = { "Game", "Real Madrid", "Stock" };
	bool isWoman = false;
	//변수에 담겨있는 데이터를 Json Object로 변경 한다
	//FJsonObject* jsonObject;//내가 메모리를 관리한다

	FUserInfo info;
	info.name = "David";
	info.age = 32;
	for (int32 i = 0; i < 3; i++) {
		info.userInterest.Add(interest[i]);
	}


	//언리얼 엔진에서 자동으로 메모리 관리
	//여러개의 포인터를 가질수 있다, NULL값도 가능
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	jsonObject->SetStringField("userName", userName);
	jsonObject->SetNumberField("userAge", userAge);
	jsonObject->SetBoolField("isWoman", isWoman);

	//FString -> FJsonValue로 변환해서 JsonArray 셋팅
	TArray<TSharedPtr<FJsonValue>> arrayInterests;
	for (int32 i = 0; i < info.userInterest.Num(); i++) {
		arrayInterests.Add(MakeShareable(new FJsonValueString(info.userInterest[i])));
	}
	jsonObject->SetArrayField("userInterest", arrayInterests);

	//Json Object를 문자열(string)로 변경하자
	FString jsonString;
	//한가지 포인터만 가능, NULL값 불가능
	TSharedRef<TJsonWriter<>> jsonWriter = TJsonWriterFactory<>::Create(&jsonString);//변수만 생성
	//실제로 Json Object를 문자열로 변환한다
	if(FJsonSerializer::Serialize(jsonObject.ToSharedRef(), jsonWriter)) {
		//json 형식으로 잘 작성되었는 로그로 확인
		UE_LOG(LogTemp, Warning, TEXT("%s"), *jsonString);

		//Json 형태로 변경된 문자열(jsonString)을 파일로 저장
		FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("jsonTest.txt"));
		FFileHelper::SaveStringToFile(jsonString, *filePath);
	}
}

void AJsonTest::LoadData() {
	FString jsonString;
	//파일을 읽어오자
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("jsonTest.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);
	UE_LOG(LogTemp, Warning, TEXT("load: %s"), *jsonString);

	//string -> JsonObject로 변환
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
