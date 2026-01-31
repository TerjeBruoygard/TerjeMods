modded class JMObjectSpawnerModule
{
	override private void SetupEntity( EntityAI entity, float quantity, float health, float temp, int itemState, PlayerBase player, COT_ObjectSetupMode mode = COT_ObjectSetupMode.NONE )
	{
		ItemBase item;
		if ( itemState < 0 && Class.CastTo( item, entity ) && item.IsLiquidContainer() )
		{
			super.SetupEntity(entity, quantity, health, temp, 0, player, mode);
			item.SetTerjeLiquidType(-itemState);
		}
		else
		{
			super.SetupEntity(entity, quantity, health, temp, itemState, player, mode);
		}
	}
}