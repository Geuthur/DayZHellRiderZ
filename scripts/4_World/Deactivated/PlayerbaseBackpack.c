modded class PlayerBase extends ManBase
{
	/*
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		ChangeStrapsCheck(true, slot_name, item);
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		ChangeStrapsCheck(false, slot_name, item);
	}

	void ChangeStrapsCheck(bool attach = false, string slot_name = "", EntityAI item = NULL)
	{
		HRZ_Backpack_Canvas_Base bag = HRZ_Backpack_Canvas_Base.Cast(FindAttachmentBySlotName("Back"));
		if (!bag || !item || (slot_name != "Vest" && slot_name != "Back")) return;

		if (slot_name == "Back") item = FindAttachmentBySlotName("Vest");

		if (FindAttachmentBySlotName("Vest") && !item.IsKindOf("ChestHolster"))
		{
			bag.HideUnhideSelection("shoulder_straps_tight", !attach);
			bag.HideUnhideSelection("shoulder_straps_large", attach);
		}
		else
		{
			bag.HideUnhideSelection("shoulder_straps_large", 0);
			bag.HideUnhideSelection("shoulder_straps_tight", 1);
		}
		
	}
	*/
}