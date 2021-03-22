modded class LoadingScreen
{
	ref TStringArray loadingscreens = {
		"Client/Data/loadingscreens/LoadingScreen01.paa",
		"Client/Data/loadingscreens/LoadingScreen02.paa",
		"Client/Data/loadingscreens/LoadingScreen03.paa",
		"Client/Data/loadingscreens/LoadingScreen04.paa"
	};

	override void Show()
	{		
		string loading = loadingscreens.GetRandomElement();
		m_ImageWidgetBackground.LoadMaskTexture("");
		m_ImageWidgetBackground.LoadImageFile(0, loading);
        	m_ImageLogoCorner.LoadImageFile(0, "set:hrz_gui image:hrz_logo");
        	m_ImageLogoMid.LoadImageFile(0, "set:hrz_gui image:hrz_logo");
		m_ModdedWarning.Show(false);
		super.Show();
	}
}