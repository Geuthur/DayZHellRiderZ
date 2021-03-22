modded class DisinfectantAlcohol: Edible_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionDrinkAlcohol);
        RemoveAction(ActionForceDrinkAlcohol);
        AddAction(HRZ_ActionCleanFaceTarget);
        AddAction(HRZ_ActionCleanFace);
        AddAction(ActionForceDrinkAlcohol);
		AddAction(ActionDrinkAlcohol);        
	}
};
