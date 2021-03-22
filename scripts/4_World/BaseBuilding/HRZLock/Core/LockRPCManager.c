class HRZLockRPCManager
{
    ref HRZ_SetCodeMenu         m_HRZSetCodeMenu;
    ref HRZ_EnterCodeMenu       m_HRZEnterCodeMenu;

    bool m_CanHackLock = true;

    void HRZLockRPCManager()
    {
        // Register RPC functions.

        // Client RPC's
        GetRPCManager().AddRPC( "HRZLockRPC_Client", "HRZ_ShowSetCodeUI", this, SingeplayerExecutionType.Server );
        GetRPCManager().AddRPC( "HRZLockRPC_Client", "HRZ_ShowEnterCodeUI", this, SingeplayerExecutionType.Server );
        GetRPCManager().AddRPC( "HRZLockRPC_Client", "HRZ_ExitMenu", this, SingeplayerExecutionType.Server );
        GetRPCManager().AddRPC( "HRZLockRPC_Client", "HRZ_ShowComboError", this, SingeplayerExecutionType.Server );
        GetRPCManager().AddRPC( "HRZLockRPC_Client", "HRZ_SetConfig", this, SingeplayerExecutionType.Server );

        // Server RPC's
        GetRPCManager().AddRPC( "HRZLockRPC_Server", "HRZ_SetCode", this, SingeplayerExecutionType.Client );
        GetRPCManager().AddRPC( "HRZLockRPC_Server", "HRZ_EnterCode", this, SingeplayerExecutionType.Client );
        GetRPCManager().AddRPC( "HRZLockRPC_Server", "HRZ_EnterCodeHandler", this, SingeplayerExecutionType.Client );
        GetRPCManager().AddRPC( "HRZLockRPC_Server", "HRZ_GetConfig", this, SingeplayerExecutionType.Client );

        // Grab Config on client intialization
        if ( !GetGame().IsServer() )
        {
            GetRPCManager().SendRPC( "HRZLockRPC_Server", "HRZ_GetConfig", NULL, true );
        }
    }

// Send RPC Functions from UI
    void SendSetCodeRPC(        ref PlayerIdentity p_Identity,
                                Object m_TargetObject,
                                string p_Pin )
    {
        GetRPCManager().SendRPC( "HRZLockRPC_Server", "HRZ_SetCode", new Param2< Object, string >( m_TargetObject, p_Pin ), true, p_Identity );
    }

    void SendEnterCodeHandler(  EntityAI player,
                                Object m_TargetObject,
                                string btn_Clicked,
                                string enteredPin )
    {
        GetRPCManager().SendRPC( "HRZLockRPC_Server", "HRZ_EnterCodeHandler", new Param4< EntityAI, Object, string, string  >( player, m_TargetObject, btn_Clicked, enteredPin,  ), true, player.GetHierarchyRootPlayer().GetIdentity() );
    }
    
// Config RPC's

    // Sets the CanHackLock bool
    void HRZ_SetConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< bool > data;
        if ( !ctx.Read( data ) ) return;
        if ( type == CallType.Client )
        {
            m_CanHackLock = data.param1;
        }
    }

    // Grabs server config and sends it to client
    void HRZ_GetConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        if ( type == CallType.Server )
        {
            m_CanHackLock = g_HRZCodeLock.CanHackLock();
            GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_SetConfig", new Param1< bool >( m_CanHackLock ), true, sender );
        }
    }

// UI RPC's

    // Shows the set code UI
    void HRZ_ShowSetCodeUI ( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        if ( type == CallType.Client )
        {
        	Param1< Object > data;
			if ( !ctx.Read( data ) ) return;
            
            if ( HRZ_CheckMenus( HRZ_SET_CODE_MENU ) ) return;

            if ( m_HRZSetCodeMenu == NULL )
            {
                m_HRZSetCodeMenu = new HRZ_SetCodeMenu();
                m_HRZSetCodeMenu.SetID( HRZ_SET_CODE_MENU );
            }

            m_HRZSetCodeMenu.SetObject( data.param1 );
            m_HRZSetCodeMenu.SetIdentity( sender );

            GetGame().GetUIManager().ShowScriptedMenu( m_HRZSetCodeMenu, NULL );

            HRZGlobalFunctions.HRZ_ShowUI();
        }
    }

    // Shows the enter Code UI
    void HRZ_ShowEnterCodeUI ( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        if ( type == CallType.Client )
        {
        	Param3< EntityAI, Object, HRZ_CodeLock > data;
			if ( !ctx.Read( data ) ) return;
            
            if ( HRZ_CheckMenus( HRZ_ENTER_CODE_MENU ) ) return;

            if ( m_HRZEnterCodeMenu == NULL )
            {
                m_HRZEnterCodeMenu = new HRZ_EnterCodeMenu();
                m_HRZEnterCodeMenu.SetID( HRZ_ENTER_CODE_MENU );
            }
            
            m_HRZEnterCodeMenu.SetObject( data.param2 );
            m_HRZEnterCodeMenu.SetPlayer( data.param1 );
            m_HRZEnterCodeMenu.HRZ_SetCodeLock( data.param3 );

            GetGame().GetUIManager().ShowScriptedMenu( m_HRZEnterCodeMenu, NULL );

            HRZGlobalFunctions.HRZ_ShowUI();
        }
    }

    // Shows "Incorrect Pin"
    void HRZ_ShowComboError( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sendIdentity, ref Object target )
    {
        Param1< string > data;
        if ( !ctx.Read( data ) ) return;

        if ( type == CallType.Client )
        {
            string errorType = data.param1;

            TextWidget box_EditPin = TextWidget.Cast( GetWidgetUnderCursor().GetParent().FindAnyWidget("txtEnterPin") );
            box_EditPin.SetText( errorType );
        }
    }

    // Hides open UI's
    void HRZ_ExitMenu( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sendIdentity, ref Object target )
    {
        if ( type == CallType.Client )
        {
            HRZGlobalFunctions.HRZ_HideUI( HRZ_ENTER_CODE_MENU );
        }
    }

    bool HRZ_CheckMenus( int menuID )
    {
        if ( GetGame().GetUIManager().IsMenuOpen( menuID ) ) return true;

        for (int i = 5; i < 37; i++)
        {
            //if ( i == 9 ) continue;
            if ( GetGame().GetUIManager().IsMenuOpen( i ) ) return true;
        }

        return false;
    }

// Server related functions

    // Sets the code onto the Lock
    void HRZ_SetCode( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        if ( type == CallType.Server )
        {
            Param2< Object, string > data;
            if ( !ctx.Read( data ) ) return;

            ItemBase m_TargetObject = ItemBase.Cast( data.param1 );

            HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( m_TargetObject.FindAttachmentBySlotName( "Att_CombinationLock" ) );

            if ( hrz_Lock )
            {
                hrz_Lock.LockServer( m_TargetObject, data.param2 );
            }
        }
    }

    // Changes the code on a lock
    void HRZ_ChangeCode( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        if ( type == CallType.Server )
        {
            Param2< Object, string > data;
            if ( !ctx.Read( data ) ) return;

            ItemBase m_TargetObject = ItemBase.Cast( data.param1 );

            HRZ_CodeLock hrz_Lock = HRZ_CodeLock.Cast( m_TargetObject.FindAttachmentBySlotName( "Att_CombinationLock" ) );

            if ( hrz_Lock )
            {
                hrz_Lock.SetPasscode( data.param2 );
            }
        }
    }

    // Handles functions of the enterCode UI
    void HRZ_EnterCodeHandler( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {

        if( type == CallType.Server )
		{
            Param4< EntityAI, Object, string, string > data;
            if ( !ctx.Read( data ) ) return;

            EntityAI player         = EntityAI.Cast( data.param1 );
            Fence fence             = Fence.Cast( data.param2 );
            HRZ_CodeLock hrz_Lock   = HRZ_CodeLock.Cast( fence.GetHRZLock() );
            string btn_Clicked      = data.param3;
            string enteredCode      = data.param4;
            string errorType;

            if ( hrz_Lock.HRZ_IsTimerActive() )
                return;

            if ( !hrz_Lock.IsLocked( enteredCode ) )
            {
                hrz_Lock.HRZ_ClearBadAttempts();
                GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ExitMenu", NULL, true, sender );

                switch ( btn_Clicked )
                {
                    case "btnEnterPin":
                    {
                        fence.OpenFence();
                        break;
                    }
                    
                    case "btnRemove":
                        hrz_Lock.UnlockServer( player, fence );
                        break;

                    case "btnChangePin":
				        GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ShowSetCodeUI", new Param1< EntityAI >( fence ), true, sender );
                        break;
                }
                return;
            }
            else
            {
                hrz_Lock.HRZ_IncrementBadAttempts();

                if ( hrz_Lock.HRZ_GetBadAttempts() >= hrz_Lock.HRZ_GetMaxAttempts() )
                {
                    hrz_Lock.HRZ_StartLockout();
                    hrz_Lock.HRZ_Tick();
                    return;
                }
                
                errorType = "Password Ungueltig!";
                GetRPCManager().SendRPC( "HRZLockRPC_Client", "HRZ_ShowComboError", new Param1< string >( errorType ), true, sender );
                return;
            }
        }
    }
}

static ref HRZLockRPCManager g_HRZLockRPCManager;
static ref HRZLockRPCManager GetHRZLockRPCManager()
{
    if ( !g_HRZLockRPCManager )
    {
        g_HRZLockRPCManager = new ref HRZLockRPCManager();
    }
    
    return g_HRZLockRPCManager;
}