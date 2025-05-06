#pragma once

namespace Debug
{
	static void Print(const FString& msg, const FColor& color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, color, msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
		}
	}
}
