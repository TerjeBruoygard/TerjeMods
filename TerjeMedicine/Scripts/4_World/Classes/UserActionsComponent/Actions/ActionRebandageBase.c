class ActionRebandageSelf : ActionBandageSelf
{	
	void ActionRebandageSelf()
	{
		m_CallbackClass 	= ActionBandageSelfCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_CHANGE_BANDAGE";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return player.HasTerjeDirtyBandagesSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			ChangeBandage(action_data.m_MainItem, target);
		}
	}
}

class ActionRebandageTarget : ActionBandageTarget
{
	void ActionRebandageTarget()
	{
		m_CallbackClass 	= ActionBandageTargetCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_CHANGE_BANDAGE";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
			return otherPlayer.HasTerjeDirtyBandages() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (action_data.m_MainItem && target)
		{
			if (CanReceiveAction(action_data.m_Target))
				ChangeBandage(action_data.m_MainItem, target);
		}
	}
}