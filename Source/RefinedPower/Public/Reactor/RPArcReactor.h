#pragma once

#include "CoreMinimal.h"
#include "Core.h"
#include "Buildables/FGBuildableGeneratorFuel.h"
#include "FGGameUserSettings.h"
#include "FGRemoteCallObject.h"
#include "RPArcReactor.generated.h"

UENUM(BlueprintType)
enum class EReactorState : uint8
{
    RP_State_SpinUp UMETA(DisplayName = "SpinUp"),
    RP_State_Producing UMETA(DisplayName = "Producing"),
    RP_State_SpinDown UMETA(DisplayName = "SpinDown"),
    RP_State_SpunDown UMETA(DisplayName = "SpunDown")
};

UCLASS()
class REFINEDPOWER_API ARPArcReactor : public AFGBuildableGeneratorFuel
{
    GENERATED_BODY()

    ARPArcReactor();
    ~ARPArcReactor();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;
    virtual void Factory_Tick(float dt) override;
    virtual void Tick(float dt) override;

    virtual bool CanStartPowerProduction_Implementation() const override;

public:
    /*#### start Main operational functions ####*/

    void CalcReactorState();

    /*#### end main operaitonal functions ####*/

    /*####Utility functions ####*/

    UFUNCTION(BlueprintCallable, Category = "RefinedPower|Reactor|ArcReactor")
    void SetReactorState(EReactorState state);

    UFUNCTION(BlueprintCallable, Category = "RefinedPower|Reactor|ArcReactor")
    EReactorState GetReactorState();

    UFUNCTION(BlueprintImplementableEvent, Category = "RefinedPower|Reactor|ArcReactor")
    void StartSpinupSound();

    UFUNCTION(BlueprintImplementableEvent, Category = "RefinedPower|Reactor|ArcReactor")
    void StartProducingSound();

    UFUNCTION(BlueprintImplementableEvent, Category = "RefinedPower|Reactor|ArcReactor")
    void StartShutdownSound();

    void IncreaseSpinAmount();

    void DecreaseSpinAmount();

    void CalcSpinningState();

    void RenderStateSpunDown();

    void RenderStateSpunUp();

    UFUNCTION()
    void UpdateParticleVariables();

    UFUNCTION()
    void CalcAudio();


    /*#### End Util functions ####*/

    /*#### Start getters and setters ####*/

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    float getReactorSpinAmount();

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    bool isSoundEnabled();

    UFUNCTION(BlueprintCallable, Category = "RefinedPower|Reactor|ArcReactor")
    void setSoundEnabled(bool enabled);

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    bool isParticlesEnabled();

    UFUNCTION(BlueprintCallable, Category = "RefinedPower|Reactor|ArcReactor")
    void setParticlesEnabled(bool enabled);

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    int getReactorCores();

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    float getReactorCoolantInternal();

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    float getReactorCoolantInternalMax();

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    float getReactorCoolantBuffer();

    UFUNCTION(BlueprintPure, Category = "RefinedPower|Reactor|ArcReactor")
    float getReactorCoolantBufferMax();

    void CacheFuelAndCoolantAmount();

    /*#### End getters and setters #####*/

    UPROPERTY(EditDefaultsOnly, SaveGame, ReplicatedUsing = UpdateParticleVariables, Category = "RefinedPower")
    bool mParticlesEnabled = false;

    UPROPERTY(EditDefaultsOnly, SaveGame, ReplicatedUsing = CalcAudio, Category = "RefinedPower")
    bool mReactorSoundEnabled = true;

    UPROPERTY(ReplicatedUsing = UpdateParticleVariables)
    bool mUpdateParticleVars;

    UPROPERTY(ReplicatedUsing = CalcAudio)
    bool mUpdateAudio;


protected:

    /*#### Start Particle vars ####*/

    UPROPERTY(VisibleAnywhere, Replicated, SaveGame, Category = "RefinedPower")
    FVector mSpinupRotation = FVector(0.0f, 0.0f, 0.0f);

    UPROPERTY(VisibleAnywhere, Replicated, SaveGame, Category = "RefinedPower")
    float mSpinupOpacity = 0.0f;

    UPROPERTY(VisibleAnywhere, SaveGame, Replicated, Category = "RefinedPower")
    float mReactorSpinAmount = 0;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "RefinedPower")
    int32 RPFuelInvIndex;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "RefinedPower")
    int32 RPCoolantInvIndex;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "RefinedPower")
    int32 mCachedReactorCoresAmount;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "RefinedPower")
    int32 mCachedCoolantAmount;

    UPROPERTY(EditDefaultsOnly, Category = "RefinedPower")
    UParticleSystemComponent* PlasmaParticles;

    /*#### End Particle vars ####*/

    /*#### Start Reactor State vars ####*/

    UPROPERTY(VisibleAnywhere, SaveGame, Replicated, Category = "RefinedPower")
    EReactorState ReactorState = EReactorState::RP_State_SpunDown;

    /*#### End Reactor State vars ####*/

    /*#### Start Input vars ####*/

    /*Min amount of resources required to start production*/
    UPROPERTY(EditDefaultsOnly, Category = "RefinedPower")
    int MinStartAmount = 20;

    /*When the resources fall below this amount, the reactor will shut off*/
    UPROPERTY(EditDefaultsOnly, Category = "RefinedPower")
    int MinStopAmount = 10;

    /*#### End input vars ####*/

    /* #### Start input connection components ####*/

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RefinedPower")
    UFGFactoryConnectionComponent* InputConveyor;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RefinedPower")
    UFGPipeConnectionComponent* InputPipe;

    /*#### end input connection components ####*/

    /*#### start misc componenents ####*/

    UPROPERTY(VisibleAnywhere, Category = "RefinedPower")
    USpotLightComponent* SpotLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RefinedPower")
    UAudioComponent* ArcReactorSound;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UFGPowerConnectionComponent* FGPowerConnection;

    /*#### end misc components ####*/
};

UCLASS()
class REFINEDPOWER_API URPArcReactorRCO : public UFGRemoteCallObject
{
    GENERATED_BODY()

    public:
    UFUNCTION(Server, WithValidation, Unreliable)
    void SetParticlesEnabled(ARPArcReactor* reactor, bool enabled);

    UFUNCTION(Server, WithValidation, Unreliable)
    void SetSoundEnabled(ARPArcReactor* reactor, bool enabled);

    UPROPERTY(Replicated)
    bool bTest = true;
};