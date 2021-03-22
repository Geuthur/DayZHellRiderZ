class HRZ_FacePaint_Base extends Inventory_Base
{

	protected int m_facePaintIndex = 0;
	protected int m_maxFacePaintIndex = -1;
	protected ref array<string> m_FacePaintStyles;

	void HRZ_FacePaint_Base()
	{
		string config_path =  "cfgVehicles " + GetType() + " facePaintStyles";
		if ( GetGame().ConfigIsExisting( config_path ) ) {
			m_FacePaintStyles = new array<string>;
			GetGame().ConfigGetTextArray( config_path, m_FacePaintStyles );
			m_maxFacePaintIndex = m_FacePaintStyles.Count() - 1;
		}
        RegisterNetSyncVariableInt("m_facePaintIndex");
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(HRZ_ActionChangeFacePaintStyle);
        AddAction(HRZ_ActionPaintFaceTarget);
        AddAction(HRZ_ActionPaintFace);        
	}

	bool CanSelectNextFacePaint()
	{
		return m_maxFacePaintIndex > 0;
	}

	void SelectNextFacePaint()
	{
		m_facePaintIndex++;
		if (m_facePaintIndex > m_maxFacePaintIndex)
			m_facePaintIndex = 0;
        SetSynchDirty();            
	}
	
	string GetCurrentFacePaintName()
	{
		return PlayerBase.HRZ_FacePaintNames.Get(GetGlobalFacePaintIndex());
	}

	int GetGlobalFacePaintIndex()
	{
		if (m_maxFacePaintIndex == -1)
			return 1;
		int idx = 1; 

		string style = m_FacePaintStyles[m_facePaintIndex];
		for( int i=0;i<PlayerBase.HRZ_FacePaintsConfig.Count();i++)
		{
			if (PlayerBase.HRZ_FacePaintsConfig[i] == style)
			{
				idx = i;
			}
		}
		return idx;
	}
}
