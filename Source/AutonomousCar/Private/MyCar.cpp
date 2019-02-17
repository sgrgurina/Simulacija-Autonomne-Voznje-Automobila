
#include "AutonomousCar.h"
#include "MyCar.h"

//writes sensor values and car steering and throttle valuees into a txt file
void AMyCar::writeToFile(float speed)
{
	if (!Recording) {
		return;
	}

	FString Directory = FPaths::GameContentDir();
		
	FString FileName = FString("recording.txt");

	FString CenterText = FString::SanitizeFloat(CenterSensorDist);
	FString CloseLeftText = FString::SanitizeFloat(CloseLeftSensorDist);
	FString CloseRightText = FString::SanitizeFloat(CloseRightSensorDist);
	FString MiddleLeftText = FString::SanitizeFloat(MiddleLeftSensorDist);
	FString MiddleRightText = FString::SanitizeFloat(MiddleRightSensorDist);
	FString FarLeftText = FString::SanitizeFloat(FarLeftSensorDist);
	FString FarRightText = FString::SanitizeFloat(FarRightSensorDist);
	FString Speed = FString::SanitizeFloat(speed);

	FString Steering = FString::SanitizeFloat(SteeringValue);
	FString Throttle = FString::SanitizeFloat(ThrottleValue);

	FString filePath = Directory + "/" + FileName;
	
	FString InputLine = CenterText + " " + CloseLeftText + " " + CloseRightText + " " + MiddleLeftText + " " + MiddleRightText + " " + FarLeftText + " " + FarRightText + " " + Speed + "\n";
	FString OutputLine = Throttle + " " + Steering + "\n";
	RecordedData += InputLine;
	RecordedData += OutputLine;
		
	FFileHelper::SaveStringToFile(RecordedData, *filePath);
}
