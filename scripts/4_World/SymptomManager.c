enum HRZ_SymptomIDs {
	SYMPTOM_SHAKEHRZ = 1001
};
modded class SymptomManager
{
	override void Init()
	{
		super.Init();
		RegisterSymptom(new HRZ_KokainSymptom);
	}
}
