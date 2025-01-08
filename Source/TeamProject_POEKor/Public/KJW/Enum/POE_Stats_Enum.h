// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


UENUM(BlueprintType)
enum class EStats : uint8
{
    NONE = 0 UMETA(DisplayName = "NONE"),
   
    Hp = 1 UMETA(DisplayName = "Hp"),
    Atk = 2 UMETA(DisplayName = "Atk"),
    Def = 3 UMETA(DisplayName = "Def"),

};
