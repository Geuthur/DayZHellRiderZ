modded class ActionConstructor
{
	override void RegisterActions( TTypenameArray actions )
	{
		super.RegisterActions( actions );
		actions.Insert( HRZ_ActionAttachCodeLock );
		actions.Insert( HRZ_ActionDestroyCodeLock );
		actions.Insert( HRZ_ActionCodeLockonEntity );
	}
};