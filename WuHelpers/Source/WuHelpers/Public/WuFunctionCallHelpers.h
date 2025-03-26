/*
Copyright(c) 2025 裴鸿喆. All Rights Reserved.
版权所有(c) 2025 裴鸿喆，保留所有权利。

B站：https://space.bilibili.com/381317561
个人网站：https://www.peihongzhe.com
微信：ProgrammingWu
*/

#pragma once

class UWorld;


#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
/**
 * 我把Call放到Function后面，是防止出问题。因为我看IDE创建CallFunction会出错。可能存在冲突。
 */
class WuFunctionCallIntervalHelpers
{
public:
	//WuFunctionCallIntervalHelpers(const UObject* WorldContextObject,double InSafeInterval,FString InFunctionName)
	WuFunctionCallIntervalHelpers(double InSafeInterval,FString InFunctionName)
	{
		
		LastFunctionCallTime = MIN_dbl;
		/*
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
		checkf(World.IsValid(),TEXT("Error:World is null. Please check if the parameters were not passed correctly when constructing WuFunctionCallIntervalHelpers."))
		*/
		checkf(InSafeInterval > 0,TEXT("Error:InSafeInterval cannot be 0 or negative."));
		SafeInterval = InSafeInterval;

		FunctionName = InFunctionName;
	};
	
	void FunctionCall(const UObject* WorldContextObject)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
		if (!World.IsValid())
		{
			UE_LOG(LogTemp,Error, TEXT("Error: WuFunctionCallIntervalHelpers::FunctionCall - World is null."));
			return;
		}
		if (!CheckSafeInterval())
		{
			auto&& ErrorMessage = FString::Printf(TEXT("WuFunctionCallIntervalHelpers::FunctionCall Error: %s exceeds the call interval limit. Please check if the code is making improper calls to this function."), *FunctionName);
			FMessageLog("PIE").Error(FText::FromString( ErrorMessage));
			UE_LOG(LogTemp,Error, TEXT("%s"), *ErrorMessage);
		}
		
		LastFunctionCallTime = World->GetRealTimeSeconds();
	};

	bool CheckSafeInterval()const
	{
		if (!World.IsValid())
		{
			UE_LOG(LogTemp,Error, TEXT("Error: WuFunctionCallIntervalHelpers::CheckSafeInterval - World is null."));
			return false;;
		}
		return (LastFunctionCallTime + SafeInterval) < World->GetRealTimeSeconds();
	};
	
private:
	double SafeInterval;
	double LastFunctionCallTime;
	FString FunctionName;
	TWeakObjectPtr<UWorld> World;
};
#endif


//InFunctionName##FrequencyHelpers.FunctionCall();
#ifndef WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES
	#if!(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		/**
		 * 中文使用说明：
		 * 函数调用间隔帮助宏
		 * 当函数调用间隔内，再此调用此函数，就会抛出错误。
		 * 尤其是用在Reliable函数中 - 检查是否有代码因为失误，快速调用Reliable函数导致出现问题。
		 * 使用这个就可以再出现失误时，抛出错误。这对制作一些功能非常有帮助。
		 * 另外，此仅会再非发行构建（发行打包）中记录。当时发行构建时，会变成空，不会影响发行构建的性能
		 *
		 * 先使用WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES创建类成员。
		 * 然后再成员函数中使用WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION来进行统计
		 * 
		 * ================================
		 * 
		 * English usage instructions:
		 * Function Call Interval Helper Macro
		 * Throws an error if this function is called again within the defined interval.
		 * Primarily used for reliable functions to detect unintended rapid calls (e.g., network-related errors).
		 * This helps catch coding errors during development.
		 * Note: Errors are only logged in non-shipping builds.In shipping builds, the macro becomes empty to avoid performance overhead.
		 *
		 *	Step 1: Use WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES to create class member variables.
		 *	Step 2: In member functions, use WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION to track and profile.
		*/
		#define  WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES(InSafeInterval,Name)\
			static_assert(InSafeInterval > 0,"InSafeInterval cannot be less than or equal to 0.");\
			WuFunctionCallIntervalHelpers FrequencyHelpers_##Name =  WuFunctionCallIntervalHelpers(InSafeInterval,#Name);
	#else
		#define  WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES(InSafeInterval,Name)
	#endif
#endif


#ifndef WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION
	#if!(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		/**
		* See:WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES
		*/
		#define WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION(WorldContextObject,Name)\
			FrequencyHelpers_##Name.FunctionCall(WorldContextObject);
	#else
		#define WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION(WorldContextObject,Name)
	#endif
#endif

#if 0
//使用示例(Example usage)
//#include "WuFunctionCallHelpers.h"
class WuFunctionCallIntervalHelpersTEST //假设这是一个UE的UObject类。如Actor（Assuming this is a UE UObject class, e.g., an Actor）
{
public:
	WU_FUNCTION_CALL_INTERVAL_HELPERS_MEMBER_VARIABLES(1,Name)
	void HelpersTEST() //假设这是一个需要检查是否再调用间隔内再此调用的函数（Assuming this is a function that needs to check if it's called again within the call interval）
	{
		WU_FUNCTION_CALL_INTERVAL_HELPERS_FUNCTION(WorldContextObject,Name)
		//其他功能代码（Other functional code）
	};
	AActor* WorldContextObject;//假设这个是一个存在再场景的WorldContextObject对象（Assuming this is a WorldContextObject existing in the scene）
};
#endif

