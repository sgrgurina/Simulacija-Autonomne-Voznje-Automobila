
#pragma once
#include "WheeledVehicle.h"
#include "MyCar.generated.h"


/**
 * 
 */
UCLASS()
class AUTONOMOUSCAR_API AMyCar : public AWheeledVehicle
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float CenterSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float CloseLeftSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float CloseRightSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float MiddleLeftSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float MiddleRightSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float FarLeftSensorDist;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float FarRightSensorDist;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FString RecordedData;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool Recording;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float SteeringValue;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float ThrottleValue;
		
		UFUNCTION(BlueprintCallable)
			void writeToFile(UPARAM(ref) float speed);
};	
