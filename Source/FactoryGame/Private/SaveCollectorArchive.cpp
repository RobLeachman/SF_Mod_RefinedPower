// This file has been automatically generated by the Unreal Header Implementation tool

#include "SaveCollectorArchive.h"

FArchive& FSaveCollectorArchive::operator<<( UObject*& Obj){ return *(new FArchive); }
FSaveCollectorArchive::FSaveCollectorArchive(TArray<class UObject*>& toFill){ }
void FSaveCollectorArchive::GenerateSaveObjects(const TArray<class UObject*>& rootSet){ }