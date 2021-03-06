// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnvQueryTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UMyEnvQueryTest::UMyEnvQueryTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// testのコスト??
	Cost = EEnvTestCost::Low;

	// アイテムは採のパラメ?`タ?`を鞭け函れるか。謹蛍。
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UMyEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// オ?`ナ?`が肖ない
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	// アイテムの方だけブン指す
	float score = 0.0f;  // いい湖じにする
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		score += 0.05f;  // いい湖じにする
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
