#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

// 这个类不需要修改 - UObject接口类
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class DIGITALHUMANDEMO_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* InstigatorActor);

	// 返回交互提示文本，不同的对象可以返回不同的提示
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionHintText() const;
};