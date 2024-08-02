// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Tutorial, Log, All);

//define new logging macro
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_S(Param) UE_LOG(Tutorial, Param, TEXT("%s"), *LOG_CALLINFO)	
#define LOG(Param, Format, ...) UE_LOG(Tutorial, Param, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))