class HRZ_WrittenNote extends Paper
{
	void SetWrittenNoteData(WrittenNoteData data)
	{
		m_NoteContents = data;
	}

    override void SetActions()
	{
		super.SetActions();

		AddAction(HRZ_ActionReadPaper);
		AddAction(HRZ_ActionReadPaperTarget);
	}
}