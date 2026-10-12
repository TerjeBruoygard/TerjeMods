modded class TerjeConsumableEffects
{
	override void TerjeApplyPositiveEffects(string classname, PlayerBase player, float amount, float perkPharmacMod)
	{
		int medLevel;
		float medValue;
		float medTimeSec;
		
		int medActiveLevel;
		float medActiveValue;
		float medActiveTimeSec;
		
		int MaxTimeSec;
		float ActiveTimeSec;
		
		medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " overdosedIncrement" );
		if (medValue < 0)
		{
			player.GetTerjeStats().SetOverdoseValue( Math.Clamp(player.GetTerjeStats().GetOverdoseValue() + (medValue * amount), 0, player.GetTerjeStats().GetOverdoseValue()));
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medPainkillerLevel" );
		if (medLevel > 0)
		{
			TerjeSkillModification(medLevel, player, "anestlog", medLevel);
			
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetPainkiller(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medPainkillerTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "Painkiller");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetPainkiller(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibioticLevel" );
		if (medLevel > 0)
		{
			TerjeSkillModification(medLevel, player, "expantib", medLevel);
			
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetAntibiotic(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibioticTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antibiotic");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetAntibiotic(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medRabiesAntibioticLevel" );
		if (medLevel > 0)
		{
			TerjeSkillModification(medLevel, player, "expantib", medLevel);
			
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetRabiesCure(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesAntibioticTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "RabiesAntibiotic");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetRabiesCure(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntipoisonLevel" );
		if (medLevel > 0)
		{
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetAntipoison(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntipoisonTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antipoison");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetAntipoison(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibiohazardLevel" );
		if (medLevel > 0)
		{
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetAntibiohazard(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibiohazardTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antibiohazard");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetAntibiohazard(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntidepresantLevel" );
		if (medLevel > 0)
		{
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetAntidepresant(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntidepresantTimeSec" );
			if (medLevel >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antidepresant");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetAntidepresant(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodHemostaticValue" );
		if (medValue > 0)
		{
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetHemostatic(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodHemostaticTimeSec" );
			if (medValue >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "BloodHemostatic");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetHemostatic(medValue, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodRegenValue" );
		if (medValue > 0)
		{
			medActiveLevel = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetBloodRegen(medActiveLevel, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodRegenTimeSec" );
			if (medValue >= medActiveLevel && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "BloodRegen");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetBloodRegen(medValue, Math.Min(MaxTimeSec, ActiveTimeSec));
			}	
		}
		
		medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainValue" );
		if (medValue > 0)
		{
			medActiveValue = 0;
			medActiveTimeSec = 0;
			player.GetTerjeStats().GetImmunityGainValue(medActiveValue, medActiveTimeSec);
			
			medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainTimeSec" );
			if (medValue >= medActiveValue && medTimeSec > 0)
			{
				MaxTimeSec = TerjeGetMaxTimeSec(classname, "ImmunityGain");
				ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
				player.GetTerjeStats().SetImmunityGainValue(medValue, Math.Min(MaxTimeSec, ActiveTimeSec));
			}
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medMindDegradationTime" );
		if (medTimeSec > 0)
		{
			medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medMindDegradationForce" );
			if (medValue > 0)
			{
				player.GetTerjeStats().AddMindDegradation(medValue, medTimeSec * amount);
			}
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medSleepingIncrementTimeSec" );
		if (medTimeSec > 0)
		{
			medValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medSleepingIncrementValue" );
			if (medValue > 0)
			{
				player.GetTerjeStats().AddSleepingIncrement(medValue, medTimeSec * amount);
			}
			else if (medValue < 0)
			{
				player.GetTerjeStats().AddSleepingDecrement(Math.AbsFloat(medValue), medTimeSec * amount);
			}
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medHealthgainTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "Healthgain");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetHealthExtraRegenTimer(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetHealthExtraRegenTimer(Math.Min(MaxTimeSec, ActiveTimeSec));
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medZAntidotTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "ZAntidot");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetZAntidotValue(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetZAntidotValue(Math.Min(MaxTimeSec, ActiveTimeSec));
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntisepsisTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antisepsis");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetAntisepsisValue(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetAntisepsisValue(Math.Min(MaxTimeSec, ActiveTimeSec));
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medConcussionHealTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "ConcussionHeal");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetContusionHealValue(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetContusionHealValue(Math.Min(MaxTimeSec, ActiveTimeSec));
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medHematomaHealTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "HematomaHeal");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetSalveValue(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetSalveValue(Math.Min(MaxTimeSec, ActiveTimeSec));
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAdrenalinTimeSec" );
		if (medTimeSec > 0)
		{
			MaxTimeSec = TerjeGetMaxTimeSec(classname, "Adrenalin");
			ActiveTimeSec = TerjeGetActiveTimeSec(player.GetTerjeStats().GetAdrenalinValue(), medTimeSec, amount, perkPharmacMod);
			player.GetTerjeStats().SetAdrenalinValue(Math.Min(MaxTimeSec, ActiveTimeSec));
			
			player.GetStaminaHandler().SetStamina(player.GetStaminaHandler().GetStaminaMax());
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medInfluenzaVacineTimeSec" );
		if (medTimeSec > 0)
		{
			player.GetTerjeStats().SetInfluenzaVacineValue(medTimeSec * amount * perkPharmacMod);
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medZVirusVacineTimeSec" );
		if (medTimeSec > 0)
		{
			player.GetTerjeStats().SetZVirusVacineValue(medTimeSec * amount * perkPharmacMod);
		}
		
		medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesVacineTimeSec" );
		if (medTimeSec > 0)
		{
			player.GetTerjeStats().SetRabiesVacineValue(medTimeSec * amount * perkPharmacMod);
		}
		
		super.TerjeApplyPositiveEffects(classname, player, amount, perkPharmacMod);
	}
	
	override void TerjeApplyNegativeEffects(string classname, PlayerBase player, float amount)
	{
		float medDmgValue;
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionLight");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionHeavy");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat( classname + " overdosedIncrement" );
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetOverdoseValue(player.GetTerjeStats().GetOverdoseValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat( classname + " biohazardIncrement" );
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetBiohazardValue(player.GetTerjeStats().GetBiohazardValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medHematomasIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetHematomas(player.GetTerjeStats().GetHematomas() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medFoodPoisonIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetPoisonValue(player.GetTerjeStats().GetPoisonValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medInfluenzaInfectionIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetInfluenzaValue(player.GetTerjeStats().GetInfluenzaValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medZombieVirusIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetZVirusValue(player.GetTerjeStats().GetZVirusValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSepsisInfectionIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medRabiesVirusIncrement");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetRabiesValue(player.GetTerjeStats().GetRabiesValue() + (medDmgValue * amount));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPsiDamageValue");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().AddMindDegradation(medDmgValue, GetTerjeGameConfig().ConfigGetFloat(classname + " medPsiDamageTimeSec"));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSleepDamageValue");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().AddSleepingDecrement(medDmgValue, GetTerjeGameConfig().ConfigGetFloat(classname + " medSleepDamageTimeSec"));
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPainSet");
		if (medDmgValue > 0)
		{
			player.GetTerjeStats().SetPainValue(medDmgValue);
		}
		
		super.TerjeApplyNegativeEffects(classname, player, amount);
	}
	
	override private string DescribePositiveEffects(string classname)
	{
		string result = super.DescribePositiveEffects(classname);
		
		result += TerjeGetEffectString_Level("Painkiller", "#STR_TERJEMED_EFFECT_PAINKILLER", classname);
		result += TerjeGetEffectString_Level("Antibiotic", "#STR_TERJEMED_EFFECT_ANTIBIOTIC", classname);
		result += TerjeGetEffectString_Level("RabiesAntibiotic", "#STR_TERJEMED_EFFECT_RABIESCURE", classname);
		result += TerjeGetEffectString_Level("Antipoison", "#STR_TERJEMED_EFFECT_ANTIPOISON", classname);
		result += TerjeGetEffectString_Level("Antibiohazard", "#STR_TERJEMED_EFFECT_ANTIBIOHAZARD", classname);
		result += TerjeGetEffectString_Level("Antidepresant", "#STR_TERJEMED_EFFECT_ANTIDEPRESANT", classname);
		
		result += TerjeGetEffectString_Time("BloodHemostatic", "#STR_TERJEMED_EFFECT_HEMOSTATIC", classname);
		result += TerjeGetEffectString_Time("BloodRegen", "#STR_TERJEMED_EFFECT_BLOODREGEN", classname);
		result += TerjeGetEffectString_Time("ImmunityGain", "#STR_TERJEMED_EFFECT_IMMUNGAIN", classname);
		
	//	result += TerjeGetEffectString_Time("SleepingIncrement", "#STR_TERJEMED_EFFECT_", classname);
		
		result += TerjeGetEffectString_Time("Healthgain", "#STR_TERJEMED_EFFECT_HEALTHREGEN", classname);
		result += TerjeGetEffectString_Time("ZAntidot", "#STR_TERJEMED_EFFECT_ZANTIDOT", classname);
		result += TerjeGetEffectString_Time("Antisepsis", "#STR_TERJEMED_EFFECT_ANTISEPSIS", classname);
		result += TerjeGetEffectString_Time("ConcussionHeal", "#STR_TERJEMED_EFFECT_CONTUSIONCURE", classname);
		result += TerjeGetEffectString_Time("HematomaHeal", "#STR_TERJEMED_EFFECT_HEMATOMA", classname);
		result += TerjeGetEffectString_Time("Adrenalin", "#STR_TERJEMED_EFFECT_ADRENALIN", classname);
		
		result += TerjeGetEffectString_Time("InfluenzaVacine", "#STR_TERJEMED_EFFECT_INFVACINE", classname);
		result += TerjeGetEffectString_Time("ZVirusVacine", "#STR_TERJEMED_EFFECT_ZEDVACINE", classname);
		result += TerjeGetEffectString_Time("RabiesVacine", "#STR_TERJEMED_EFFECT_RABIESVACCINE", classname);
		
		return result;
	}
	
	override private string DescribeNegativeEffects(string classname)
	{
		string result = super.DescribeNegativeEffects(classname);
		
		result += TerjeGetEffectString_Percent("overdosed", "#STR_TERJEMED_EFFECT_OVERDOSE", classname);
		result += TerjeGetEffectString_Percent("biohazard", "#STR_TERJEMED_EFFECT_BIOHAZARD", classname);
		
		result += TerjeGetEffectString_Contussion("Light", "#STR_TERJEMED_EFFECT_DMG_CONTLIGHT", classname);
		result += TerjeGetEffectString_Contussion("Heavy", "#STR_TERJEMED_EFFECT_DMG_CONTHEAVY", classname);
		
		result += TerjeGetEffectString_Increment("Hematomas", "#STR_TERJEMED_EFFECT_DMG_HEMATOMA", classname);
		result += TerjeGetEffectString_Increment("FoodPoison", "#STR_TERJEMED_EFFECT_DMG_FOODPOISON", classname);
		result += TerjeGetEffectString_Increment("InfluenzaInfection", "#STR_TERJEMED_EFFECT_DMG_INFLUENZA", classname);
		result += TerjeGetEffectString_Increment("ZombieVirus", "#STR_TERJEMED_EFFECT_DMG_ZOMBIE", classname);
		result += TerjeGetEffectString_Increment("SepsisInfection", "#STR_TERJEMED_EFFECT_DMG_SEPSIS", classname);
		result += TerjeGetEffectString_Increment("RabiesVirus", "#STR_TERJEMED_EFFECT_DMG_RABIES", classname);
		
		result += TerjeGetEffectString_DamageTime("Psi", "#STR_TERJEMED_EFFECT_DMG_PSI", classname);
		result += TerjeGetEffectString_DamageTime("Sleep", "#STR_TERJEMED_EFFECT_DMG_SLEEP", classname);
		
		result += TerjeGetEffectString_DamageLevel("Pain", "#STR_TERJEMED_EFFECT_DMG_PAIN", classname);
		
		return result;
	}
}
