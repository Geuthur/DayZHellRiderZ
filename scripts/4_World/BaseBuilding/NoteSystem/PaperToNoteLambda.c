class HRZ_PaperToNoteLambda : ReplaceItemWithNewLambdaBase
{
    protected ref WrittenNoteData m_NoteContents;

    void HRZ_PaperToNoteLambda(EntityAI old_item, string new_item_type, ref WrittenNoteData data)
    {
        m_NoteContents = data;
    }

	override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);

		HRZ_WrittenNote note = HRZ_WrittenNote.Cast(new_item);
		note.SetWrittenNoteData(m_NoteContents);
        m_NoteContents = null;

        if (!note.GetParent())
        {
            note.SetOrientation(old_item.GetOrientation());
            note.SetPosition(old_item.GetPosition());
        }
	}
}