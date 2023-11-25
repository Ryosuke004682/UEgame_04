// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game_4.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Game_4, "Game_4" );


static TAutoConsoleVariable<int32> CVarExtraMgnetism
(
    TEXT("OurGame.ExtraMagnetism"),
    0,
    TEXT("Defines whether we should cheat in getting our bearings into their goals.\n")
    TEXT("  0: no extra magnetism\n")
    TEXT("  1: extra magnetism\n"),
    ECVF_Scalability | ECVF_RenderThreadSafe
)