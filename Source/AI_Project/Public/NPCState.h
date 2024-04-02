#pragma once

#include "NPCState.generated.h"

UENUM(BlueprintType)
enum class ENPCState : uint8
{
	Collecting,
	Following,
	Masterless,
	None
};