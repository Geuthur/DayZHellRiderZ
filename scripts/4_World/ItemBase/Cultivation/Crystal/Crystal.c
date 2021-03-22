class HRZ_Crystal_Base: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(HRZ_ActionEatCrack);
	}
}
