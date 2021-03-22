class HRZ_Kokain : ItemBase {};
class HRZ_Kokain_Pack : ItemBase {};
class HRZ_Kokain_Syringe : ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(HRZ_ActionInjectKokain);
	}
}
