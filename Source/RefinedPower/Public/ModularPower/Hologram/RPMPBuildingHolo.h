// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "Components/BoxComponent.h"
#include "../RPMPPlatform.h"
#include "../RPMPBuilding.h"
#include "../RPMPPlacementComponent.h"
#include "RPMPBuildingHolo.generated.h"

/**
 * 
 */
UCLASS()
class REFINEDPOWER_API ARPMPBuildingHolo : public AFGFactoryHologram
{
    GENERATED_BODY()
public:
    ARPMPBuildingHolo();
    ~ARPMPBuildingHolo();

    virtual void BeginPlay() override;
    virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
    virtual void CheckValidPlacement() override;

    virtual bool IsValidHitResult(const FHitResult& hitResult) const override;

    bool CheckSnapLocations(FVector TestLocation);

    FVector mSnapToPoint = FVector(0);
    FRotator mSnapPointRotation = FRotator(0);

    /*Array of all water volumes on map. Only call this once.*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<AActor*> mCachedWaterNodeArr;

    ARPMPPlatform* mPlatform;

    EMPPlatformBuildingType mHologramType;
};
