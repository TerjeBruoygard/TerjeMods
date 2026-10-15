modded class JMESPActionMenu
{
	override void BuildMain()
	{
		super.BuildMain();
		
		if (!m_Meta || !m_Meta.target)
			return;
		
		EntityAI targetEntity = EntityAI.Cast(m_Meta.target);
		if (!targetEntity || !GetTerjeScriptableAreas())
			return;
		
		float radValue = GetTerjeScriptableAreas().GetTerjeRadiationFromEntity(targetEntity);
		Add("terje_rad", "Radiation: " + radValue.ToString(), "");
	}
}
