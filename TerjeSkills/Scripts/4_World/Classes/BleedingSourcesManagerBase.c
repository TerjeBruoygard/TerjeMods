modded class BleedingSourcesManagerBase
{
	override bool AttemptAddBleedingSourceBySelection(string selection_name)
	{
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (selection_name == "RightFoot" || selection_name == "LeftFoot")
			{
				m_Player.GetTerjeSkills().GetPerkValue("surv", "rghfeet", perkValue)
				if (TerjeEvent(Math.AbsFloat(perkValue)))
				{
					return false;
				}
			}
			else if (selection_name == "LeftForeArmRoll" || selection_name == "RightForeArmRoll")
			{
				m_Player.GetTerjeSkills().GetPerkValue("surv", "rghhands", perkValue)
				if (TerjeEvent(Math.AbsFloat(perkValue)))
				{
					return false;
				}
				
				m_Player.SetBloodyHands(true);
			}
		}
		
		return super.AttemptAddBleedingSourceBySelection(selection_name);
	}
}