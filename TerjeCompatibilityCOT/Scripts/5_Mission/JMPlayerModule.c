modded class JMPlayerModule
{
	private override void Exec_Heal( array< string > guids, PlayerIdentity ident, JMPlayerInstance instance = NULL  )
	{
		array< JMPlayerInstance > players = GetPermissionsManager().GetPlayers( guids );
		for ( int i = 0; i < players.Count(); i++ )
		{
			PlayerBase player = PlayerBase.Cast( players[i].PlayerObject );
			if ( !player )
				continue;

			GetTerjeAdmintoolSupport().OnHeal(player);
		}
		
		super.Exec_Heal(guids, ident, instance);
	}
	
	void SetTerjeValue( string id, float value, array< string > guids )
	{
		GetTerjeRPC().SendToServer("JM_COT_SetTerjeValue", new Param3<string, float, array<string>>(id, value, guids));
	}
}