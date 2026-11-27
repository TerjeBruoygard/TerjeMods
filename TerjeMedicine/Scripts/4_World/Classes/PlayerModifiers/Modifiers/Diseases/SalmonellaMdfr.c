modded class SalmonellaMdfr
{
	override protected bool ActivateCondition(PlayerBase player)
	{
		return false;
	}
	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}
	override protected void OnActivate(PlayerBase player);
	override protected void OnDeactivate(PlayerBase player);
	override void OnTick(PlayerBase player, float deltaT);
}
