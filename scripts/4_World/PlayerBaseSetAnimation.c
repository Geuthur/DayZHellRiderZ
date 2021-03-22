modded class ModItemRegisterCallbacks
{
	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
		super.RegisterHeavy( pType, pBehavior );
		pBehavior.SetHeavyItems();
		pType.AddItemInHandsProfileIK("HRZ_Instruments_Base", "dz/anims/workspaces/player/player_main/weapons/player_main_m4a1.asi", pBehavior, "dz/anims/anm/player/ik/weapons/m4a1_ik.anm");
	};
	
	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterTwoHanded( pType, pBehavior );
		pBehavior.SetTwoHanded();
		pType.AddItemInHandsProfileIK("HRZ_Holzbalken", "dz/anims/workspaces/player/player_main/weapons/player_main_2h_extinguisher.asi", pBehavior, "dz/anims/anm/player/ik/two_handed/firewood.anm");
	};
	
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterOneHanded( pType, pBehavior );
		pBehavior.SetToolsOneHanded();
            pType.AddItemInHandsProfileIK("HRZ_Oillamp", "dz/anims/workspaces/player/player_main/props/player_main_1h_flashlight.asi", pBehavior, "dz/anims/anm/player/ik/gear/flashlight.anm");
        	pType.AddItemInHandsProfileIK("HRZ_Sherlockpipe", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
			pType.AddItemInHandsProfileIK("HRZ_Joint_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
			pType.AddItemInHandsProfileIK("HRZ_Cigarette_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
			pType.AddItemInHandsProfileIK("HRZ_Seedpack_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/zucchini_seeds_pack.anm");
			pType.AddItemInHandsProfileIK("HRZ_Empty_Pack", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/zucchini_seeds_pack.anm");
            pType.AddItemInHandsProfileIK("HRZ_Shemagh_ColorBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/BandanaFH_ground.anm");
            pType.AddItemInHandsProfileIK("HRZ_Shemagh_Facemask_ColorBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/BandanaFH_ground.anm");
            pType.AddItemInHandsProfileIK("HRZ_Shemagh_Bandit_ColorBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/BandanaFH_ground.anm");
            pType.AddItemInHandsProfileIK("HRZ_Shemagh_Scarf_ColorBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/BandanaFH_ground.anm");
			pType.AddItemInHandsProfileIK("HRZ_Pen_ColorBase", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/pen.anm");
			pType.AddItemInHandsProfileIK("HRZ_Chisel", "dz/anims/workspaces/player/player_main/weapons/player_main_1h_pipe.asi", pBehavior, "dz/anims/anm/player/ik/gear/hammer_ik.anm");
			//pType.AddItemInHandsProfileIK("HRZ_RollingPapers", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/mackerel_fillet.anm");
			pType.AddItemInHandsProfileIK("HRZ_RollingPapers", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/paper.anm");
			pType.AddItemInHandsProfileIK("HRZ_Syringe", "dz/anims/workspaces/player/player_main/props/player_main_1h_syringe.asi", pBehavior, "dz/anims/anm/player/ik/gear/Syringe_Empty.anm");
			pType().AddItemInHandsProfileIK("HRZ_Joint", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
			pType().AddItemInHandsProfileIK("HRZ_JointTop", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
			pType().AddItemInHandsProfileIK("HRZ_Cigarette", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/thermometer.anm");
	};

}

