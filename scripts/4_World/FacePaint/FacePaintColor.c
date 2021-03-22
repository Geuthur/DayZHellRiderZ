modded class PlayerBase extends ManBase
{
    static ref TStringArray HRZ_FacePaintsConfig = {
        "None",
        "Wald",
        "Jungle",
        "Green",
        "Streifen",
        "Tiger"
	};

    static ref TStringArray HRZ_FacePaintNames = {
        "None",
        "Wald",
        "Jungle",
        "Grün",
        "Streifen",
        "Tiger"
};

    protected int m_FacePaintHRZ;

    override void Init()
	{
        super.Init();

        m_FacePaintHRZ = 0;        
        RegisterNetSyncVariableInt("m_FacePaintHRZ");
    }

    string HRZ_GetFacePaint()
    {
        return HRZ_FacePaintsConfig.Get(m_FacePaintHRZ);
    }

    void HRZ_SetFacePaint(int fp)
    {
        m_FacePaintHRZ = fp;
        SetSynchDirty();
    }

	override void OnStoreSave( ParamsWriteContext ctx )
	{
        super.OnStoreSave( ctx );
        // store facepaint
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
            ctx.Write( "HRZ" );
            ctx.Write( m_FacePaintHRZ );
        }
    }

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
        if (!super.OnStoreLoad( ctx, version))
            return false;
        
        if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
            // read facepaint
            int facepaint = 0;
            string hrzfp = "";
            if (!ctx.Read(hrzfp))
            {
                return false;
            }
            if(!ctx.Read(facepaint)) {
                return false;
            }
            m_FacePaintHRZ = facepaint;
        }
        return true;
    }
}