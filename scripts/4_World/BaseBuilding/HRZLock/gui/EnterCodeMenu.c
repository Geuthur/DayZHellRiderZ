class HRZ_EnterCodeMenu extends UIScriptedMenu
{
	protected Widget w_Root;
	TextWidget txt_EditPin;
	protected EditBoxWidget box_EditPin;
	protected ButtonWidget btn_EnterPin;
	protected ButtonWidget btn_CancelPin;
    protected ButtonWidget btn_Remove;
    protected ButtonWidget btn_ChangePin;
	static protected Object m_TargetObject;
    protected EntityAI p_Player;
    protected HRZ_CodeLock hrz_Lock;
    private string passPlainText = "";
	
	void HRZ_EnterCodeMenu()
	{
	}
    
	void ~HRZ_EnterCodeMenu()
	{
	}
	
	override Widget Init()
	{
        w_Root = GetGame().GetWorkspace().CreateWidgets("DayZHellRiderZ\\scripts\\layouts\\enterComboCode.layout");
        w_Root.Show( false );

        txt_EditPin = TextWidget.Cast(w_Root.FindAnyWidget("txtEnterPin"));
        box_EditPin = EditBoxWidget.Cast(w_Root.FindAnyWidget("edtPinCode"));
        btn_EnterPin = ButtonWidget.Cast(w_Root.FindAnyWidget("btnEnterPin"));
        btn_CancelPin = ButtonWidget.Cast(w_Root.FindAnyWidget("btnCancelPin"));
        btn_Remove = ButtonWidget.Cast(w_Root.FindAnyWidget("btnRemove"));
        btn_ChangePin = ButtonWidget.Cast(w_Root.FindAnyWidget("btnChangePin"));

        box_EditPin.SetText("");

        return w_Root;
	}

    override bool OnClick( Widget w, int x, int y, int button )
    {
        super.OnClick( w, x, y, button );
        
        if ( button == MouseState.LEFT )
        {
            if ( w == btn_CancelPin )
            {
                HRZGlobalFunctions.HRZ_HideUI( this.GetID() );
            }
            else
            {
                if ( !hrz_Lock.HRZ_IsTimerActive() )
                    g_HRZLockRPCManager.SendEnterCodeHandler( p_Player, m_TargetObject, w.GetName(), passPlainText );
            }
            
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

    override bool OnChange( Widget w, int x, int y, bool finished )
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

    override void OnShow() 
    {
        if ( hrz_Lock )
        {
            if ( hrz_Lock.HRZ_IsTimerActive() )
            {
                txt_EditPin.SetText( "Sperre | " + hrz_Lock.HRZ_GetRemainingTimer() );
            }
        }
    }

    override void OnHide() { }

    void HRZ_SendEnterCodeRPC()
    {
        if ( !hrz_Lock.HRZ_IsTimerActive() )
            g_HRZLockRPCManager.SendEnterCodeHandler( p_Player, m_TargetObject, "btnEnterPin", passPlainText );
    }

    // Sets local variables
    void SetObject( Object TargetObject )
    {
        m_TargetObject = TargetObject;
    }

    void SetPlayer( EntityAI player )
    {
        p_Player = player;
    }

    void HRZ_SetCodeLock( HRZ_CodeLock HRZ_codeLock )
    {
        hrz_Lock = HRZ_codeLock;
    }

    void HRZ_LockedOut()
    {
        txt_EditPin.SetText( "Sperre | " + hrz_Lock.HRZ_GetRemainingTimer() );
    }
}