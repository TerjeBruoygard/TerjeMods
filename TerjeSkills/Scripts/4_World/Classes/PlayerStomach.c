modded class StomachItem
{
	override bool ProcessDigestion(float digestion_points, out float water, out float energy, out float toxicity, out float volume, out int agents, out float consumed_amount)
	{
		bool emptyStomach = super.ProcessDigestion(digestion_points, water, energy, toxicity, volume, agents, consumed_amount);
		if (!emptyStomach)
		{
			TerjeProcessDigestion(water, energy, water, energy);
		}
		return emptyStomach;
	}
	
	void TerjeProcessDigestion(float waterIn, float energyIn, out float waterOut, out float energyOut)
	{
		if (m_Player && m_Player.GetTerjeSkills())
		{
			if (energyIn > 0)
			{
				float incaloriePerkValue;
				if (m_Player.GetTerjeSkills().GetPerkValue("mtblsm", "incalorie", incaloriePerkValue))
				{
					energyOut = energyIn * (1.0 + incaloriePerkValue);
				}
			}
			
			if (waterIn > 0)
			{
				float incrhydrPerkValue;
				if (m_Player.GetTerjeSkills().GetPerkValue("mtblsm", "incrhydr", incrhydrPerkValue))
				{
					waterOut = waterIn * (1.0 + incrhydrPerkValue);
				}
			}
		}
	}
}

modded class PlayerStomach
{
	private float m_terjeMetabolismSkillExpBuffer = 0;
	private float m_terjeMetabolismSkillExpTimer = 0;
	
	override void Update(float delta_time)
	{
		super.Update(delta_time);
		if (m_Player && m_Player.GetTerjeSkills())
		{
			if (m_terjeMetabolismSkillExpTimer > 3)
			{
				m_terjeMetabolismSkillExpTimer = 0;
				if (m_terjeMetabolismSkillExpBuffer >= 1)
				{
					m_Player.GetTerjeSkills().AddSkillExperience("mtblsm", (int)m_terjeMetabolismSkillExpBuffer);
					m_terjeMetabolismSkillExpBuffer = 0;
				}
			}
			else
			{
				m_terjeMetabolismSkillExpTimer += delta_time;
			}	
		}
	}
	
	override void AddToStomach(string class_name, float amount, int food_stage = 0, int agents = 0, float temperature = 0)
	{
		NutritionalProfile profile = Liquid.GetNutritionalProfileByName(class_name);
		if (!profile)
		{
			profile = Edible_Base.GetNutritionalProfile(null, class_name, food_stage);
		}
		
		if (profile)
		{
			if (g_Game.IsDedicatedServer())
			{
				float energy = profile.GetEnergy() * amount;
				if (energy > 0)
				{
					float metabolismConsumeFoodExpMod;
					if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_METABOLISM_CONSUME_FOOD_EXP_MOD, metabolismConsumeFoodExpMod))
					{
						m_terjeMetabolismSkillExpBuffer += energy * metabolismConsumeFoodExpMod * 0.001;
					}
				}
				
				float water = profile.GetWaterContent() * amount;
				if (water > 0)
				{
					float metabolismConsumeWaterExpMod;
					if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_METABOLISM_CONSUME_WATER_EXP_MOD, metabolismConsumeWaterExpMod))
					{
						m_terjeMetabolismSkillExpBuffer += water * metabolismConsumeFoodExpMod * 0.002;
					}
				}
			}
			
			if (m_Player && m_Player.GetTerjeSkills())
			{
				bool hasSalmonella = (agents & eAgents.SALMONELLA);
				if (hasSalmonella && m_Player.GetTerjeSkills().GetPerkLevel("mtblsm", "wmlover") > 0)
				{
					agents = (agents & ~eAgents.SALMONELLA);
				}
			}
		}

		super.AddToStomach(class_name, amount, food_stage, agents, temperature);
	}
}
