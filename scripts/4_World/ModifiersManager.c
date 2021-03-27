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
		AddModifier(new HRZ_BlurMdfr);
	}
}