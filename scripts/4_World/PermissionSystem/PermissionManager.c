class HRZMember {
	string steamID;
	string faction;
	string roles;

    bool IsPlayer(string id) {
        if (steamID == id) {
            return true;
        }
        return false;
    }

    string GetId()
    {
        return steamID;
    }

    string GetFaction()
    {
        return faction;
    }
	
    string GetRole()
    {
        return roles;
    }
	
    HRZMember NoFile()
    {
        HRZMember c = new HRZMember();
        c.steamID 	= "76561197960364065";
        c.faction 	= "Geuthur";
		c.roles 	= "ADMIN";
		
        return c;
    }
	
    HRZMember Copy()
    {
        HRZMember c = new HRZMember();
        c.steamID 	= steamID;
        c.faction 	= faction;
		c.roles 	= roles;
		
        return c;
    }
	
    HRZMember New()
    {
		PlayerIdentity identity;
        HRZMember c = new HRZMember();
        c.steamID 	= identity.GetPlainId();
        c.faction 	= "";
		c.roles 	= "Trial";
		
        return c;
    }
}

class HRZ_PermissionManager : PluginBase {
    private ref array<ref HRZMember> members;
    private ref array<ref HRZMember> membersForClient;
    private ref array<ref HRZMember> membersForClientEmpty;
    private string permsFile;
    private string clientId;

    void HRZ_PermissionManager() {
        if (!members) {
            members = new array<ref HRZMember>();
            membersForClient = new array<ref HRZMember>();
            membersForClientEmpty = new array<ref HRZMember>();
        }

        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) {
            return;
        }

        permsFile = "$profile:\\HellRiderZ\\Permission.json";

        if (!FileExist(permsFile)) {            
            CreatePermissionFile();
        }
        LoadPermissions();
    }

    private void CreatePermissionFile() {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) { return; }

        MakeDirectory("$profile:\\HellRiderZ\\");
        HRZMember exPlayer = new HRZMember();
		HRZMember nofile = exPlayer.NoFile();
        members.Insert(nofile);
        JsonFileLoader<ref array<ref HRZMember>>.JsonSaveFile(permsFile, members);
    }
	
    void UpdatePermissionFile() {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) { return; }

        HRZMember exPlayer = new HRZMember();
        HRZMember newclient = exPlayer.New();               
        members.Insert(newclient);
        JsonFileLoader<ref array<ref HRZMember>>.JsonSaveFile(permsFile, members);
    }

    void LoadPermissions() {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) { return; }

        JsonFileLoader<ref array<ref HRZMember>>.JsonLoadFile(permsFile, members);

        if (members.Count() < 1) {
            CreatePermissionFile();
        }
    }

    ref array<ref HRZMember> GetMembers() {
        return members;
    }

    ref array<ref HRZMember> GetMembersForClient(string plainId) {
        membersForClient = new array<ref HRZMember>();
        for (int i = 0; i < members.Count(); i ++)
        {
            HRZMember member = members[i];
            if (member.IsPlayer(plainId))
            {
                HRZMember copy = member.Copy();               
                membersForClient.Insert(copy);
            }
        }
        return membersForClient;
    }

    void SetClientMembers(ref array<ref HRZMember> cMembers, string plainId) {
        if (GetGame().IsServer() || !GetGame().IsClient()) { return; }
        members = cMembers;
        clientId = plainId;
    }

    bool MemberExists(string playerId)
    {
        for (int i = 0; i < members.Count(); i ++)
        {
            HRZMember member = members[i];
            if (member.IsPlayer(playerId))
            {
                return true;
            }
        }
        return false;
    }

    bool IsFactionMember(PlayerBase player, string faction)
    {
        if (!GetGame().IsMultiplayer())
        {
            return true;
        }
        string playerId = "";
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) {
            playerId = clientId;
        } else {
            playerId = player.GetIdentity().GetPlainId();
        } 
        if (playerId == string.Empty) { return false; }
        for (int i = 0; i < members.Count(); i++)
        {
            HRZMember member = members[i];
            if (member.IsPlayer(playerId) && (member.GetFaction() == faction || member.GetFaction() == "ADMIN"))
            {
                return true;
            }
        }
        return false;
    }

    string GetFaction(PlayerBase player)
    {
        string noFaction = "";
        if (!GetGame().IsMultiplayer())
        {
            return "";
        }
        string playerId = "";
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) {
            playerId = clientId;
        } else {
            playerId = player.GetIdentity().GetPlainId();
        } 
        if (playerId == string.Empty) { return noFaction; }
        for (int i = 0; i < members.Count(); i++)
        {
            HRZMember member = members[i];
            if (member.IsPlayer(playerId))
            {
                return member.GetFaction();
            }
        }
        return noFaction;
    }
	
    string GetRole(PlayerBase player)
    {
        string noRole = "";
        if (!GetGame().IsMultiplayer())
        {
            return "";
        }
        string playerId = "";
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer()) {
            playerId = clientId;
        } else {
            playerId = player.GetIdentity().GetPlainId();
        } 
        if (playerId == string.Empty) { return noRole; }
        for (int i = 0; i < members.Count(); i++)
        {
            HRZMember member = members[i];
            if (member.IsPlayer(playerId))
            {
                return member.GetRole();
            }
        }
        return noRole;
    }
}

HRZ_PermissionManager GetHRZPermissionManager()
{
    return HRZ_PermissionManager.Cast(GetPlugin(HRZ_PermissionManager));
}

class HRZ_PermissionClient : PluginBase {
    void HRZ_PermissionClient() {
        if (GetGame().IsServer() && GetGame().IsMultiplayer()) { return; }

        GetDayZGame().Event_OnRPC.Insert(PermissionClientHandler);
    }

    void ~HRZ_PermissionClient() {
        GetDayZGame().Event_OnRPC.Remove(PermissionClientHandler);
    }

    void PermissionClientHandler(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

		if (GetGame().IsServer() && GetGame().IsMultiplayer()) {
            delete this;
            return;
        }
        switch (rpc_type) {      
            case 20200103:
                {
                    Param2<ref array<ref HRZMember>, string> data;
                    ctx.Read(data);

                    ref array<ref HRZMember> members = data.param1;
                    string clientPlainId = data.param2;                    
                    GetHRZPermissionManager().SetClientMembers(members, clientPlainId);
                    break;
                }
			/*
            case 20200104:
                {
                    Param2<ref array<ref HRZMember>, string> data;
                    ctx.Write(data);

                    ref array<ref HRZMember> members = data.param1;
                    string clientPlainId = data.param2;                    
                    GetHRZPermissionManager().SetClientMembers(members, clientPlainId);
                    break;
                }
			*/
        }
	}
}