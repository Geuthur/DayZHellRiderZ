class HRZ_Shemagh_ColorBase extends Clothing
{
	override void SetActions()
	{
		super.SetActions();		
		AddAction(HRZ_ActionFoldShemaghScarf);
	}
}

class HRZ_Shemagh_Scarf_ColorBase extends Clothing
{
	override void SetActions()
	{
		super.SetActions();		
		AddAction(HRZ_ActionFoldShemaghFacemask);
	}
}


class HRZ_Shemagh_Facemask_ColorBase extends Clothing
{
	override void SetActions()
	{
		super.SetActions();		
		AddAction(HRZ_ActionFoldShemaghBandit);
	}
}

class HRZ_Shemagh_Bandit_ColorBase extends Clothing
{
	override void SetActions()
	{
		super.SetActions();		
		AddAction(HRZ_ActionUnfoldShemagh);
	}
}


