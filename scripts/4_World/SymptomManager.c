enum SymptomIDs2 {
	SYMPTOM_SHAKEHRZ = 1099
};
modded class SymptomManager
{
	override void Init()
	{
		super.Init();
		RegisterSymptom(new HRZ_ShakeSymptom);
	}
}