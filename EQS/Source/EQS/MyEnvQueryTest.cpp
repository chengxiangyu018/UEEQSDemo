// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnvQueryTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UMyEnvQueryTest::UMyEnvQueryTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// test�Υ����ȣ�
	Cost = EEnvTestCost::Low;

	// �����ƥ�ϺΤΥѥ��`���`���ܤ�ȡ��뤫����֡�
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UMyEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// ���`�ʩ`���Ӥʤ�
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	// �����ƥ���������֥�ؤ�
	float score = 0.0f;  // �����Ф��ˤ���
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		score += 0.05f;  // �����Ф��ˤ���
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
