// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "RefinedPower/Public/Turbine/RPTurbineBaseActor.h"
#include "RPWaterTurbineNode.h"
#include "RPWaterTurbine.generated.h"

/**
 * 
 */
UCLASS()
class REFINEDPOWER_API ARPWaterTurbine : public ARPTurbineBaseActor
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

    virtual void calculateTurbinePowerProduction() override;

    ARPWaterTurbineNode* mWaterTurbineNode;

    void GetWaterTurbineNode();
};
