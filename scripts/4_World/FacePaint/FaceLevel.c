class HRZ_FacepaintLevel
{
	protected int m_Level;
	protected string m_MaterialName;


	void HRZ_FacepaintLevel( int level, string material_name )
	{
		m_Level = level;
		m_MaterialName = material_name;
	}

	int GetLevel()
	{
		return m_Level;
	}

	string GetMaterialName()
	{
		return m_MaterialName;
	}
}