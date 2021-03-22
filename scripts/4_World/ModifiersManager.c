modded class ModifierBase
{
    static ref ScriptInvoker Event_OnActivate = new ScriptInvoker();
    static ref ScriptInvoker Event_OnDeactivate = new ScriptInvoker();
}

modded class ModifiersManager
{
	void ModifiersManager(PlayerBase player)
	{
		AddModifier(new HRZ_VomitMdfr);
		AddModifier(new HRZ_HustenMdfr);
		AddModifier(new HRZ_StonedMdfr);
		AddModifier(new HRZ_CrystalMdfr);
		AddModifier(new HRZ_KokainMdfr);	
		AddModifier(new HRZ_TestMdfr);
	}
}