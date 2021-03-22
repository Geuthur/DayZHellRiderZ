enum HRZ_InstrumentCategories : GestureCategories
 {
  Instrument1, //special category selection
 }

modded class GesturesMenu
 {

 override void GetGestureItems( out ref array<ref GestureMenuItem> gesture_items, HRZ_InstrumentCategories category )
  {
	HRZ_Instruments_Base radio;
    super.GetGestureItems(gesture_items, category);
    switch (category)
  {
      	case HRZ_InstrumentCategories.CATEGORIES:
      	{
//        	if (radio.HRZ_InstrumentMenu)
//			{
				gesture_items.Insert( new GestureMenuItem( HRZ_InstrumentCategories.Instrument1, "Instrument Base", 	HRZ_InstrumentCategories.CATEGORIES ) );
//			}
       		break;
      	}
			case HRZ_InstrumentCategories.Instrument1:
			{
			gesture_items.Insert( new GestureMenuItem( EmoteConstants.ID_INST_SONG1, "Song 1", HRZ_InstrumentCategories.Instrument1 ) );
			gesture_items.Insert( new GestureMenuItem( EmoteConstants.ID_INST_SONG2, "Song 2", HRZ_InstrumentCategories.Instrument1 ) );
			gesture_items.Insert( new GestureMenuItem( EmoteConstants.ID_INST_SONG3, "Song 3", HRZ_InstrumentCategories.Instrument1 ) );
			break;
			}
		}
  }

 override void OnMenuRelease()
	{
    super.OnMenuRelease();
	}
 }