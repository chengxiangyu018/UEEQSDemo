// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnvQueryTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UMyEnvQueryTest::UMyEnvQueryTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// testのコスト？
	Cost = EEnvTestCost::Low;

	// アイテムは何のパラメーターを受け取れるか。多分。
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UMyEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// オーナーが居ない
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	// アイテムの数だけブン回す
	float score = 0.0f;  // いい感じにする
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		score += 0.05f;  // いい感じにする
		It.SetScore(TestPurpose, FilterType, score, MinThresholdValue, MaxThresholdValue);
	}
}

FText UMyEnvQueryTest::GetDescriptionTitle() const
{
	return Super::GetDescriptionTitle();
}

FText UMyEnvQueryTest::GetDescriptionDetails() const
{
	return DescribeFloatTestParams();
}
