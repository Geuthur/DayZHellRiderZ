modded class SymptomBase
{
    static ref ScriptInvoker Event_OnActivatedClient = new ScriptInvoker();
    static ref ScriptInvoker Event_OnDeactivatedClient = new ScriptInvoker();
}

modded class SymptomManager
{
	override void Init()
	{
		super.Init();
		RegisterSymptom(new HRZ_KokainSymptom);
		RegisterSymptom(new HRZ_CrystalSymptom);
		RegisterSymptom(new HRZ_CannabisSymptom);
		RegisterSymptom(new HRZ_BlurSymptom);
		RegisterSymptom(new HRZ_TestSymptom);
	}
}
