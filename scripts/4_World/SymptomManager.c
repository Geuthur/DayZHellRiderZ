modded class SymptomBase
{
    static ref ScriptInvoker Event_OnActivatedClient = new ScriptInvoker();
    static ref ScriptInvoker Event_OnGetDeactivatedClient = new ScriptInvoker();
}

modded class SymptomManager
{
	override void Init()
	{
		super.Init();
		RegisterSymptom(new HRZ_KokainSymptom);
	}
}
