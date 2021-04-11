class HRZ_Gitarre extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}

class HRZ_Ibanez extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		RemoveAction(HRZ_ActionSwitchSong);
	}
}

class HRZ_Gitarre2 extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}
class HRZ_Gitarre3 extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}
class HRZ_Gitarre4 extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		AddAction(HRZ_ActionSwitchSong);
	}
}
class HRZ_Gitarre5 extends HRZ_Instruments_Base
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}