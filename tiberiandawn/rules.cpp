//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free
// software: you can redistribute it and/or modify it under the terms of
// the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed
// in the hope that it will be useful, but with permitted additional restrictions
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT
// distributed with this program. You should have received a copy of the
// GNU General Public License along with permitted additional restrictions
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

/* $Header: /CounterStrike/RULES.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : RULES.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 05/12/96                                                     *
 *                                                                                             *
 *                  Last Update : September 10, 1996 [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   DifficultyClass::DifficultyClass -- Default constructor for difficulty class object.      *
 *   RulesClass::RulesClass -- Default constructor for rules class object.                     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "function.h"
#include "ccini.h"

/***********************************************************************************************
 * DifficultyClass::DifficultyClass -- Default constructor for difficulty class object.        *
 *                                                                                             *
 *    This is the default constructor for the difficulty class object. Although it initializes *
 *    the rule data with default values, it is expected that they will all be overridden by    *
 *    the rules control file.                                                                  *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/18/2019 SKY : Created.                                                                 *
 *=============================================================================================*/
DifficultyClass::DifficultyClass(void)
    : FirepowerBias(1)
    , GroundspeedBias(1)
    , AirspeedBias(1)
    , ArmorBias(1)
    , ROFBias(1)
    , CostBias(1)
    , BuildSpeedBias(1)
    , RepairDelay(0.02f)
    , BuildDelay(0.03f)
    , IsBuildSlowdown(false)
    , IsWallDestroyer(true)
    , IsContentScan(false)
{
}

/***********************************************************************************************
 * RulesClass::RulesClass -- Default constructor for rules class object.                       *
 *                                                                                             *
 *    This is the default constructor for the rules class object. Although it initializes the  *
 *    rule data with default values, it is expected that they will all be overridden by the    *
 *    rules control file.                                                                      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/17/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
RulesClass::RulesClass(void)
    : AttackInterval(3)
    , AttackDelay(5)
    , PowerEmergencyFraction(3, 4)
    , HelipadRatio(".12")
    , HelipadLimit(6)
    , TeslaRatio(".8")
    , TeslaLimit(5)
    , AARatio(".14")
    , AALimit(10)
    , DefenseRatio(".5")
    , DefenseLimit(25)
    , WarRatio(".1")
    , WarLimit(3)
    , BarracksRatio(".16")
    , BarracksLimit(2)
    , RefineryLimit(7)
    , RefineryRatio(".18")
    , BaseSizeAdd(3)
    , PowerSurplus(50)
    , MaxIQ(5)
    , IQSuperWeapons(4)
    , IQProduction(5)
    , IQGuardArea(4)
    , IQRepairSell(1)
    , IQCrush(2)
    , IQScatter(3)
    , IQContentScan(4)
    , IQAircraft(4)
    , IQHarvester(2)
    , IQSellBack(2)
    , InfantryReserve(3000)
    , InfantryBaseMult(1)
    , IsComputerParanoid(false)
    , IsCompEasyBonus(false)
    , IsFineDifficulty(false)
    , AllowSuperWeapons(true)
    , Game("Game")
{
#ifndef REMASTER_BUILD

    /* giulianob: Bump FirepowerBias just a little, else the enemy do too much damage. */
    Diff[DIFF_EASY].FirepowerBias = "1.1";
    /* giulianob: Same thing with speed. */
    Diff[DIFF_EASY].GroundspeedBias = "1.1";
    Diff[DIFF_EASY].AirspeedBias = "1.1";
    /* giulianob: Don't bump the ArmorBias, else enemy units on hard becomes
       undestroyable.  */
    Diff[DIFF_EASY].ArmorBias = 1;
    Diff[DIFF_EASY].ROFBias = "0.8";
    Diff[DIFF_EASY].CostBias = "0.8";
    Diff[DIFF_EASY].BuildSpeedBias = "0.6";
    Diff[DIFF_EASY].RepairDelay = "0.001";
    Diff[DIFF_EASY].BuildDelay = "0.002";
    Diff[DIFF_EASY].IsBuildSlowdown = false;
    Diff[DIFF_EASY].IsWallDestroyer = true;
    Diff[DIFF_EASY].IsContentScan = true;

    Diff[DIFF_NORMAL].FirepowerBias = 1;
    Diff[DIFF_NORMAL].GroundspeedBias = 1;
    Diff[DIFF_NORMAL].AirspeedBias = 1;
    Diff[DIFF_NORMAL].ArmorBias = 1;
    Diff[DIFF_NORMAL].ROFBias = 1;
    Diff[DIFF_NORMAL].CostBias = 1;
    Diff[DIFF_NORMAL].BuildSpeedBias = 1;
    Diff[DIFF_NORMAL].RepairDelay = "0.02";
    Diff[DIFF_NORMAL].BuildDelay = "0.03";
    Diff[DIFF_NORMAL].IsBuildSlowdown = true;
    Diff[DIFF_NORMAL].IsWallDestroyer = true;
    Diff[DIFF_NORMAL].IsContentScan = true;

    Diff[DIFF_HARD].FirepowerBias = "0.9";
    Diff[DIFF_HARD].GroundspeedBias = "0.9";
    Diff[DIFF_HARD].AirspeedBias = "0.9";
    Diff[DIFF_HARD].ArmorBias = "1.05";
    Diff[DIFF_HARD].ROFBias = "1.05";
    Diff[DIFF_HARD].CostBias = 1;
    Diff[DIFF_HARD].BuildSpeedBias = 1;
    Diff[DIFF_HARD].RepairDelay = "0.05";
    Diff[DIFF_HARD].BuildDelay = "0.1";
    Diff[DIFF_HARD].IsBuildSlowdown = true;
    Diff[DIFF_HARD].IsWallDestroyer = true;
    Diff[DIFF_HARD].IsContentScan = true;
#endif
}

/***********************************************************************************************
 * Difficulty_Get -- Fetch the difficulty bias values.                                         *
 *                                                                                             *
 *    This will fetch the difficulty bias values for the section specified.                    *
 *                                                                                             *
 * INPUT:   ini   -- Reference the INI database to fetch the values from.                      *
 *                                                                                             *
 *          diff  -- Reference to the difficulty class object to fill in with the values.      *
 *                                                                                             *
 *          section  -- The section identifier to lift the values from.                        *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/11/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
static void Difficulty_Get(CCINIClass& ini, DifficultyClass& diff, char const* section)
{
    if (ini.Is_Present(section)) {
        diff.FirepowerBias = ini.Get_Fixed(section, "FirePower", diff.FirepowerBias);
        diff.GroundspeedBias = ini.Get_Fixed(section, "Groundspeed", diff.GroundspeedBias);
        diff.AirspeedBias = ini.Get_Fixed(section, "Airspeed", diff.AirspeedBias);
        diff.ArmorBias = ini.Get_Fixed(section, "Armor", diff.ArmorBias);
        diff.ROFBias = ini.Get_Fixed(section, "ROF", diff.ROFBias);
        diff.CostBias = ini.Get_Fixed(section, "Cost", diff.CostBias);
        diff.RepairDelay = ini.Get_Fixed(section, "RepairDelay", diff.RepairDelay);
        diff.BuildDelay = ini.Get_Fixed(section, "BuildDelay", diff.BuildDelay);
        diff.IsBuildSlowdown = ini.Get_Bool(section, "BuildSlowdown", diff.IsBuildSlowdown);
        diff.BuildSpeedBias = ini.Get_Fixed(section, "BuildTime", diff.BuildSpeedBias);
        diff.IsWallDestroyer = ini.Get_Bool(section, "DestroyWalls", diff.IsWallDestroyer);
        diff.IsContentScan = ini.Get_Bool(section, "ContentScan", diff.IsContentScan);
    }
}

/***********************************************************************************************
 * Difficulty_Put -- Fetch the difficulty bias values.                                         *
 *                                                                                             *
 *    This will fetch the difficulty bias values for the section specified.                    *
 *                                                                                             *
 * INPUT:   ini   -- Reference the INI database to fetch the values from.                      *
 *                                                                                             *
 *          diff  -- Reference to the difficulty class object to fill in with the values.      *
 *                                                                                             *
 *          section  -- The section identifier to lift the values from.                        *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/11/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
static void Difficulty_Put(CCINIClass& ini, DifficultyClass& diff, char const* section)
{
    ini.Put_Fixed(section, "FirePower", diff.FirepowerBias);
    ini.Put_Fixed(section, "Groundspeed", diff.GroundspeedBias);
    ini.Put_Fixed(section, "Airspeed", diff.AirspeedBias);
    ini.Put_Fixed(section, "Armor", diff.ArmorBias);
    ini.Put_Fixed(section, "ROF", diff.ROFBias);
    ini.Put_Fixed(section, "Cost", diff.CostBias);
    ini.Put_Fixed(section, "RepairDelay", diff.RepairDelay);
    ini.Put_Fixed(section, "BuildDelay", diff.BuildDelay);
    ini.Put_Bool(section, "BuildSlowdown", diff.IsBuildSlowdown);
    ini.Put_Fixed(section, "BuildTime", diff.BuildSpeedBias);
    ini.Put_Bool(section, "DestroyWalls", diff.IsWallDestroyer);
    ini.Put_Bool(section, "ContentScan", diff.IsContentScan);
}

/***********************************************************************************************
 * RulesClass::Process -- Fetch the bulk of the rule data from the control file.               *
 *                                                                                             *
 *    This routine will fetch the rule data from the control file.                             *
 *                                                                                             *
 * INPUT:   file  -- Reference to the rule file to process.                                    *
 *                                                                                             *
 * OUTPUT:  bool; Was the rule file processed?                                                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/17/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Process(CCINIClass& ini)
{
    AI(ini);
    IQ(ini);
    Difficulty(ini);
    Import_Game(ini);

    return (true);
}

/***********************************************************************************************
 * RulesClass::Process -- Fetch the bulk of the rule data from the control file.               *
 *                                                                                             *
 *    This routine will fetch the rule data from the control file.                             *
 *                                                                                             *
 * INPUT:   file  -- Reference to the rule file to process.                                    *
 *                                                                                             *
 * OUTPUT:  bool; Was the rule file processed?                                                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/17/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Export(CCINIClass& ini)
{
    Export_AI(ini);
    Export_IQ(ini);
    Export_Difficulty(ini);
    Export_Game(ini);

    return (true);
}

/***********************************************************************************************
 * RulesClass::AI -- Processes the AI control constants from the database.                     *
 *                                                                                             *
 *    This will examine the database specified and set the AI override values accordingly.     *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database that holds the AI overrides.                *
 *                                                                                             *
 * OUTPUT:  bool; Was the AI section found and processed?                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/08/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::AI(CCINIClass& ini)
{
    static const char AI[] = "AI";

    if (ini.Is_Present(AI)) {
        AttackInterval = ini.Get_Fixed(AI, "AttackInterval", AttackInterval);
        AttackDelay = ini.Get_Fixed(AI, "AttackDelay", AttackDelay);
        InfantryReserve = ini.Get_Int(AI, "InfantryReserve", InfantryReserve);
        InfantryBaseMult = ini.Get_Int(AI, "InfantryBaseMult", InfantryBaseMult);
        PowerSurplus = ini.Get_Int(AI, "PowerSurplus", PowerSurplus);
        BaseSizeAdd = ini.Get_Int(AI, "BaseSizeAdd", BaseSizeAdd);
        RefineryRatio = ini.Get_Fixed(AI, "RefineryRatio", RefineryRatio);
        RefineryLimit = ini.Get_Int(AI, "RefineryLimit", RefineryLimit);
        BarracksRatio = ini.Get_Fixed(AI, "BarracksRatio", BarracksRatio);
        BarracksLimit = ini.Get_Int(AI, "BarracksLimit", BarracksLimit);
        WarRatio = ini.Get_Fixed(AI, "WarRatio", WarRatio);
        WarLimit = ini.Get_Int(AI, "WarLimit", WarLimit);
        DefenseRatio = ini.Get_Fixed(AI, "DefenseRatio", DefenseRatio);
        DefenseLimit = ini.Get_Int(AI, "DefenseLimit", DefenseLimit);
        AARatio = ini.Get_Fixed(AI, "AARatio", AARatio);
        AALimit = ini.Get_Int(AI, "AALimit", AALimit);
        TeslaRatio = ini.Get_Fixed(AI, "ObeliskRatio", TeslaRatio);
        TeslaLimit = ini.Get_Int(AI, "ObeliskLimit", TeslaLimit);
        HelipadRatio = ini.Get_Fixed(AI, "HelipadRatio", HelipadRatio);
        HelipadLimit = ini.Get_Int(AI, "HelipadLimit", HelipadLimit);
        IsCompEasyBonus = ini.Get_Bool(AI, "CompEasyBonus", IsCompEasyBonus);
        IsComputerParanoid = ini.Get_Bool(AI, "Paranoid", IsComputerParanoid);
        PowerEmergencyFraction = ini.Get_Fixed(AI, "PowerEmergency", PowerEmergencyFraction);
        return (true);
    }
    return (false);
}

/***********************************************************************************************
 * RulesClass::Export_AI -- Processes the AI control constants to the database.                *
 *                                                                                             *
 *    This will examine the database specified and set the AI override values accordingly.     *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database that holds the AI overrides.                *
 *                                                                                             *
 * OUTPUT:  bool; Was the AI section found and processed?                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/08/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Export_AI(CCINIClass& ini)
{
    static const char AI[] = "AI";

    ini.Put_Fixed(AI, "AttackInterval", AttackInterval);
    ini.Put_Fixed(AI, "AttackDelay", AttackDelay);
    ini.Put_Int(AI, "InfantryReserve", InfantryReserve);
    ini.Put_Int(AI, "InfantryBaseMult", InfantryBaseMult);
    ini.Put_Int(AI, "PowerSurplus", PowerSurplus);
    ini.Put_Int(AI, "BaseSizeAdd", BaseSizeAdd);
    ini.Put_Fixed(AI, "RefineryRatio", RefineryRatio);
    ini.Put_Int(AI, "RefineryLimit", RefineryLimit);
    ini.Put_Fixed(AI, "BarracksRatio", BarracksRatio);
    ini.Put_Int(AI, "BarracksLimit", BarracksLimit);
    ini.Put_Fixed(AI, "WarRatio", WarRatio);
    ini.Put_Int(AI, "WarLimit", WarLimit);
    ini.Put_Fixed(AI, "DefenseRatio", DefenseRatio);
    ini.Put_Int(AI, "DefenseLimit", DefenseLimit);
    ini.Put_Fixed(AI, "AARatio", AARatio);
    ini.Put_Int(AI, "AALimit", AALimit);
    ini.Put_Fixed(AI, "ObeliskRatio", TeslaRatio);
    ini.Put_Int(AI, "ObeliskLimit", TeslaLimit);
    ini.Put_Fixed(AI, "HelipadRatio", HelipadRatio);
    ini.Put_Int(AI, "HelipadLimit", HelipadLimit);
    ini.Put_Bool(AI, "CompEasyBonus", IsCompEasyBonus);
    ini.Put_Bool(AI, "Paranoid", IsComputerParanoid);
    ini.Put_Fixed(AI, "PowerEmergency", PowerEmergencyFraction);
    return (true);
}

/***********************************************************************************************
 * RulesClass::IQ -- Fetches the IQ control values from the INI database.                      *
 *                                                                                             *
 *    This will scan the database specified and retrieve the IQ control values from it. These  *
 *    IQ control values are what gives the IQ rating meaning. It fundimentally controls how    *
 *    the computer behaves.                                                                    *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database to read the IQ controls from.               *
 *                                                                                             *
 * OUTPUT:  bool; Was the IQ section found and processed?                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::IQ(CCINIClass& ini)
{
    static const char IQCONTROL[] = "IQ";

    if (ini.Is_Present(IQCONTROL)) {
        MaxIQ = ini.Get_Int(IQCONTROL, "MaxIQLevels", MaxIQ);
        IQSuperWeapons = ini.Get_Int(IQCONTROL, "SuperWeapons", IQSuperWeapons);
        IQProduction = ini.Get_Int(IQCONTROL, "Production", IQProduction);
        IQGuardArea = ini.Get_Int(IQCONTROL, "GuardArea", IQGuardArea);
        IQRepairSell = ini.Get_Int(IQCONTROL, "RepairSell", IQRepairSell);
        IQCrush = ini.Get_Int(IQCONTROL, "AutoCrush", IQCrush);
        IQScatter = ini.Get_Int(IQCONTROL, "Scatter", IQScatter);
        IQContentScan = ini.Get_Int(IQCONTROL, "ContentScan", IQContentScan);
        IQAircraft = ini.Get_Int(IQCONTROL, "Aircraft", IQAircraft);
        IQHarvester = ini.Get_Int(IQCONTROL, "Harvester", IQHarvester);
        IQSellBack = ini.Get_Int(IQCONTROL, "SellBack", IQSellBack);

        return (true);
    }
    return (false);
}

/***********************************************************************************************
 * RulesClass::Export_IQ -- Exports the IQ control values from the INI database.               *
 *                                                                                             *
 *    This will scan the database specified and retrieve the IQ control values from it. These  *
 *    IQ control values are what gives the IQ rating meaning. It fundimentally controls how    *
 *    the computer behaves.                                                                    *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database to read the IQ controls from.               *
 *                                                                                             *
 * OUTPUT:  bool; Was the IQ section found and processed?                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/11/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Export_IQ(CCINIClass& ini)
{
    static const char IQCONTROL[] = "IQ";

    ini.Put_Int(IQCONTROL, "MaxIQLevels", MaxIQ);
    ini.Put_Int(IQCONTROL, "SuperWeapons", IQSuperWeapons);
    ini.Put_Int(IQCONTROL, "Production", IQProduction);
    ini.Put_Int(IQCONTROL, "GuardArea", IQGuardArea);
    ini.Put_Int(IQCONTROL, "RepairSell", IQRepairSell);
    ini.Put_Int(IQCONTROL, "AutoCrush", IQCrush);
    ini.Put_Int(IQCONTROL, "Scatter", IQScatter);
    ini.Put_Int(IQCONTROL, "ContentScan", IQContentScan);
    ini.Put_Int(IQCONTROL, "Aircraft", IQAircraft);
    ini.Put_Int(IQCONTROL, "Harvester", IQHarvester);
    ini.Put_Int(IQCONTROL, "SellBack", IQSellBack);

    return (true);
}

/***********************************************************************************************
 * RulesClass::Difficulty -- Fetch the various difficulty group settings.                      *
 *                                                                                             *
 *    This routine is used to fetch the various group settings for the difficulty levels.      *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database that has the difficulty setting values.     *
 *                                                                                             *
 * OUTPUT:  bool; Was the difficulty section found and processed.                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/10/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Difficulty(CCINIClass& ini)
{
#ifndef REMASTER_BUILD
    Difficulty_Get(ini, Diff[DIFF_EASY], "Easy");
    Difficulty_Get(ini, Diff[DIFF_NORMAL], "Normal");
    Difficulty_Get(ini, Diff[DIFF_HARD], "Difficult");
#endif
    return (true);
}

/***********************************************************************************************
 * RulesClass::Export_Difficulty -- Export the various difficulty group settings.              *
 *                                                                                             *
 *    This routine is used to fetch the various group settings for the difficulty levels.      *
 *                                                                                             *
 * INPUT:   ini   -- Reference to the INI database that has the difficulty setting values.     *
 *                                                                                             *
 * OUTPUT:  bool; Was the difficulty section found and processed.                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/10/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool RulesClass::Export_Difficulty(CCINIClass& ini)
{
#ifndef REMASTER_BUILD
    Difficulty_Put(ini, Diff[DIFF_EASY], "Easy");
    Difficulty_Put(ini, Diff[DIFF_NORMAL], "Normal");
    Difficulty_Put(ini, Diff[DIFF_HARD], "Difficult");
#endif
    return (true);
}

bool RulesClass::Import_Game(CCINIClass& ini)
{
    DBG_INFO("RulesClass::Import_Game - Importing [%s] rule section", Game.SectionName);

    Game.With_Context<RuleSectionContext>(ini, [](auto& c) {
          // map
        c << MAX_BUILD_DISTANCE_RULE << 2
          << PREVENT_BUILDING_IN_SHROUD_RULE << true
          << ALLOW_BUILDING_BESIDE_WALLS_RULE << true
          << TIBERIUM_GROWS_RULE << true
          << TIBERIUM_SPREADS_RULE << true
          << SLOW_TIBERIUM_GROWTH_AND_SPREAD_RULE << false
          << TIBERIUM_GROWTH_RATE_RULE << fixed(1)
          << TIBERIUM_SPREAD_RATE_RULE << fixed(1)
          << TIBERIUM_INFANTRY_DAMAGE_RULE << 2
          << TIBERIUM_BLOSSOM_TREE_DAMAGE_RULE << 5

          // harvesting
          << CREDITS_PER_TIBERIUM_SCOOP_RULE << 25
          << MAX_HARVESTER_CAPACITY_RULE << 28

          // factories
          << PRODUCTION_STEPS_PER_TICK_RULE << 1
          << FACTORY_COUNT_STEP_MULTIPLIER_RULE << fixed(1)
          << TOTAL_PRODUCTION_STEPS_RULE << 108

          // repair
          << UNIT_REPAIR_FACTOR_RULE << fixed(1.02f)
          << UNIT_REPAIR_STRENGTH_STEP_RULE << 4
          << AIRCRAFT_REPAIR_FACTOR_RULE << fixed(1.02f)
          << AIRCRAFT_REPAIR_STRENGTH_STEP_RULE << 2

          // misc
          << SMART_DEFENCE_RULE << false
          << TARGET_TREES_RULE << false
          << MCV_REDEPLOYABLE_RULE << false
          << SPAWN_VISCEROIDS_RULE << false
          << VEHICLES_DO_THREE_POINT_TURNS_RULE << false
          << SHOW_BIBS_ON_BUILDINGS_RULE << false
          << SHOW_CIVILIAN_BUILDING_NAMES_RULE << false
          << ONLY_ALLOW_NUKE_IF_ALL_PARTS_HAVE_BEEN_COLLECTED_RULE << true
          << ONLY_ALLOW_USING_ONE_NUKE_PER_SCENARIO_RULE << true
          << HELIPADS_AND_AIRCRAFT_BOUGHT_SEPERATELY_RULE << false
          << DESTROYED_BUILDINGS_HAVE_SURVIVORS_RULE << true

          // house specific
          << HIDE_TEMPLE_FROM_GDI_RULE << true
          << HIDE_OBELISK_FROM_GDI_RULE << true
          << HIDE_APC_FROM_NOD_RULE << true
          << HIDE_ROCKET_LAUNCHER_FROM_NOD_RULE << true
          << HIDE_HELIPAD_FROM_NOD_RULE << true
          << HIDE_ADVANCED_COMM_CENTER_FROM_NOD_RULE << true
          << ONLY_GDI_CAN_USE_ION_CANNON_RULE << true

          // level specific
          << SET_BUILD_LEVEL_TO_1_IN_GDI_SCENARIO_2_RULE << true
          << RENAME_TECH_CENTER_TO_PRISION_IN_NOD_SCENARIO_3_RULE << true
          << HIDE_BAZOOKA_FROM_GDI_UNTIL_SENARIO_8_RULE << true
          << HIDE_ROCKET_LAUNCHER_FROM_GDI_UNTIL_SCENARIO_9_RULE << true
          << HIDE_SANDBAG_FROM_GDI_UNTIL_SCENARIO_9_RULE << true
          << ALLOW_NOD_TO_BUILD_ADVANCED_POWER_IN_SCENARIO_12_RULE << true

          // cheats
          << ALLOW_BUILDING_ALL_FOR_CURRENT_HOUSE_RULE << false
          << UNITS_ARE_INDESTRUCTIBLE_RULE << false
          << INFANTRY_AUTO_SCATTERS_RULE << false
          << GIVE_ATTACKERS_AN_ADVANTAGE_RULE << false
          << SPEEDY_BUILDS_RULE << false;
    });

    return true;
}

bool RulesClass::Export_Game(CCINIClass& ini)
{
    // TODO: export Game section
    return (true);
}
