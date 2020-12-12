// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGRailroadBridgeHologram.h"
#include "FGBuildableRoad.h"
#include "FGBuildableRailroadTrack.h"
#include "FGBuildableFoundation.h"

AFGRailroadBridgeHologram::AFGRailroadBridgeHologram() : Super() {
	this->mMaxPlacementFloorAngle = 35;
	this->mValidHitClasses.Add(AFGBuildableFoundation::StaticClass()); this->mValidHitClasses.Add(AFGBuildableRailroadTrack::StaticClass()); this->mValidHitClasses.Add(AFGBuildableRoad::StaticClass());
	this->mUseBuildClearanceOverlapSnapp = true;
	this->bHidden = true;
	this->bReplicates = true;
}
void AFGRailroadBridgeHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ }
bool AFGRailroadBridgeHologram::DoMultiStepPlacement(bool isInputFromARelease){ return bool(); }
void AFGRailroadBridgeHologram::ConfigureActor( AFGBuildable* inBuildable) const{ }
AFGBuildableFoundation* AFGRailroadBridgeHologram::FindOverlappingFoundation(const FVector& location, float radius) const{ return nullptr; }