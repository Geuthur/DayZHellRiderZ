modded class ActionConstructor 
{    
	override void RegisterActions(TTypenameArray actions) 
	{
		super.RegisterActions(actions);
		
		//Drugs
		actions.Insert(HRZ_ActionEatCrack);
		actions.Insert(HRZ_ActionInjectKokain);
		actions.Insert(HRZ_ActionInjectTest);
		actions.Insert(HRZ_ActionInjectTest2);
		
        	actions.Insert(HRZ_ActionJointSmokeSelf);
		actions.Insert(HRZ_ActionSmokeSelf); 
        	actions.Insert(HRZ_ActionFoldBloodPack);
		//Shemags
		actions.Insert( HRZ_ActionUnfoldShemagh );
		actions.Insert( HRZ_ActionFoldShemaghBandit );
		actions.Insert( HRZ_ActionFoldShemaghFacemask );
		actions.Insert( HRZ_ActionFoldShemaghScarf );
		// Instruments
		actions.Insert( HRZ_ActionSwitchSong );
		actions.Insert( HRZ_ActionBlowWhistleWolf );	
		actions.Insert( HRZ_ActionChangeHornSound );
		actions.Insert( HRZ_ActionBlowHorn );	
		// FacePaint
		actions.Insert( HRZ_ActionPaintFace );
		actions.Insert( HRZ_ActionPaintFaceTarget );
		actions.Insert( HRZ_ActionChangeFacePaintStyle );
		actions.Insert( HRZ_ActionCleanFace );
		actions.Insert( HRZ_ActionCleanFaceTarget );	
		actions.Insert( HRZ_ActionCleanFace );
		// NoteSystem
		actions.Insert(ActionReadPaper);
		actions.Insert(ActionWritePaper);
        	actions.Insert(HRZ_ActionReadPaper);
        	actions.Insert(HRZ_ActionReadPaperTarget);
        	actions.Insert(HRZ_ActionWritePaper);
        	actions.Insert(HRZ_ActionSwitchPen);
	}
};