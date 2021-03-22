class HRZ_SetCodeMenu extends UIScriptedMenu
{
	protected Widget w_Root;
    protected TextWidget txt_SetPin;
	protected EditBoxWidget box_EditPin;
	protected ButtonWidget btn_EnterPin;
	protected ButtonWidget btn_CancelPin;
    protected PlayerIdentity p_Identity;
	static protected Object m_TargetObject;
    private string passPlainText = "";
    private string p_SetPin = "";

	
	void HRZ_SetCodeMenu()
	{
	}
    
	void ~HRZ_SetCodeMenu()
	{
	}
	
	override Widget Init()
	{
        w_Root = GetGame().GetWorkspace().CreateWidgets("DayZHellRiderZ\\scripts\\layouts\\setComboCode.layout");
        w_Root.Show( false );

        txt_SetPin = TextWidget.Cast(w_Root.FindAnyWidget( "txtSetPin" ) );
        box_EditPin = EditBoxWidget.Cast(w_Root.FindAnyWidget( "edtPinCode" ) );
        btn_EnterPin = ButtonWidget.Cast(w_Root.FindAnyWidget( "btnEnterPin" ) );
        btn_CancelPin = ButtonWidget.Cast(w_Root.FindAnyWidget( "btnCancelPin" ) );

        box_EditPin.SetText( "" );
        passPlainText = "";
        p_SetPin = "";

        return w_Root;
	}

    override bool OnClick( Widget w, int x, int y, int button ) 
    {
        super.OnClick( w, x, y, button );
        
        if ( button == MouseState.LEFT && w == btn_CancelPin )
        {
            HRZGlobalFunctions.HRZ_HideUI( this.GetID() );

            return true;
        }

        if ( button == MouseState.LEFT && w == btn_EnterPin )
        {
            HRZ_CheckState();
            return true;
        }

        return false;
    }

    override bool OnKeyPress( Widget w, int x, int y, int key )
    {
        if (w == box_EditPin) 
        {
            string boxText = box_EditPin.GetText();

            // Limit length to 6 digits
            if ( boxText.Length() < 6 ) 
            {
                // Only allow numbers.
                if ( key > 47 && key < 58 ) return false;
            }

            box_EditPin.SetText(boxText);
            return true;
        }

        return false;
    }

    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        super.OnChange( w, x, y, finished );
        if ( w == box_EditPin )
        {
            string boxText = box_EditPin.GetText();
            int boxLength = boxText.Length();
            int passPlainLength = passPlainText.Length();
            if ( boxLength > passPlainLength )
            {
                passPlainText += boxText.Substring( passPlainLength, boxLength );
            }
            else 
            {
                passPlainText = passPlainText.Substring( 0, boxLength );
            }

            box_EditPin.SetText( HRZGlobalFunctions.ConvertToStars( boxText ) );

            return true;
        }

        return false;
    }

    void HRZ_CheckState()
    {
        string boxText = box_EditPin.GetText();

        if ( boxText.Length() < 3 )
        {
            TooShort();
            return;
        }

        if ( p_SetPin == "" )
        {
            p_SetPin = passPlainText;
            passPlainText = "";
            confirmCode();
            return;
        }

        if ( passPlainText == p_SetPin )
        {
            HRZGlobalFunctions.HRZ_HideUI( this.GetID() );
            g_HRZLockRPCManager.SendSetCodeRPC( p_Identity, m_TargetObject, passPlainText );
        }
        else if ( passPlainText != p_SetPin )
        {
            noMatch();
        }
    }

    void TooShort()
    {
        txt_SetPin.SetText( "Zu Kurz" );
    }

    void confirmCode()
    {
        txt_SetPin.SetText( "Bestaetige Password" );
        box_EditPin.SetText( "" );
    }

    void noMatch()
    {
        txt_SetPin.SetText( "Stimmt nicht Ueberein" );
    }

    override void OnShow() { }

    override void OnHide() { }

    // Sets local variables
    void SetObject( Object TargetObject )
    {
        m_TargetObject = TargetObject;
    }

    void SetIdentity( PlayerIdentity identity )
    {
        p_Identity = identity;
    }
}