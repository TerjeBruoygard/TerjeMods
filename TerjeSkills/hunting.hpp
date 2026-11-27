class Hunting: SkillsBase
{
	id="hunt";
	enabled=1;
	displayName="#STR_TERJESKILL_HUNTING_NAME";
	description="#STR_TERJESKILL_HUNTING_DESC";
	icon="set:TerjeSkills_icon image:ts_hunting";
	class Modifiers
	{
		class MeatCountModifier
		{
			id="meatcountmod";
			enabled=1;
			text="#STR_TERJESKILL_HUNTING_MOD0";
			value=0.02;
		};
	};
	class Perks
	{
		class MeatHunter
		{
			id="meathunt";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_MEATHUNTER";
			description="#STR_TERJEPERK_HUNT_MEATHUNTER_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_meathunt";
			enabledIcon="set:TerjePerk_icon image:tp_meathunt";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,2,3};
			values[]={0.1,0.2,0.4,0.6,0.8,1.0};
		};
		class QuickSkinning
		{
			id="quickcut";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_QUICKCUTTING";
			description="#STR_TERJEPERK_HUNT_QUICKCUTTING_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_quickcutm";
			enabledIcon="set:TerjePerk_icon image:tp_quickcutm";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={-0.1,-0.2,-0.3,-0.4,-0.6,-0.8};
		};
		class MasterKnife
		{
			id="mknife";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_MASTERKNIFE";
			description="#STR_TERJEPERK_HUNT_MASTERKNIFE_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_masterknife";
			enabledIcon="set:TerjePerk_icon image:tp_masterknife";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={-0.1,-0.2,-0.3,-0.5,-0.7,-0.9};
		};
		class TrapExpert
		{
			id="trapexp";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_TRAPEXPERT";
			description="#STR_TERJEPERK_HUNT_TRAPEXPERT_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_trapexpert";
			enabledIcon="set:TerjePerk_icon image:tp_trapexpert";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.4,0.6,0.8,1.0};
		};
		class PeltMaster
		{
			id="plmaster";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_SKINMASTER";
			description="#STR_TERJEPERK_HUNT_SKINMASTER_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_prhides";
			enabledIcon="set:TerjePerk_icon image:tp_prhides";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.3,0.5,0.75,1.0};
		};
		class ExperiencedHunter
		{
			id="exphunter";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_EXPERIENCEDHUNTER";
			description="#STR_TERJEPERK_HUNT_EXPERIENCEDHUNTER_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_exphunter";
			enabledIcon="set:TerjePerk_icon image:tp_exphunter";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.3,0.5,1.0,1.5};
		};
		class KnowledgeAnatomy
		{
			id="knwanatomy";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_KNOWLEDGEANATOMY";
			description="#STR_TERJEPERK_HUNT_KNOWLEDGEANATOMY_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_knwanatomy";
			enabledIcon="set:TerjePerk_icon image:tp_knwanatomy";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.3,0.5,1.0,1.5};
		};
		class RemovingRot
		{
			id="remvrot";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_REMOVINGROT";
			description="#STR_TERJEPERK_HUNT_REMOVINGROT_DES";
			stagesCount=1;
			disabledIcon="set:TerjePerkBlack_icon image:tp_removrot";
			enabledIcon="set:TerjePerk_icon image:tp_removrot";
			requiredSkillLevels[]={1};
			requiredPerkPoints[]={1};
			values[]={0.0};
		};
		class Pathfinder
		{
			id="pathfindr";
			enabled=1;
			displayName="#STR_TERJEPERK_HUNT_PATHFINDER";
			description="#STR_TERJEPERK_HUNT_PATHFINDER_DES";
			stagesCount=1;
			disabledIcon="set:TerjePerkBlack_icon image:tp_pathfindr";
			enabledIcon="set:TerjePerk_icon image:tp_pathfindr";
			requiredSkillLevels[]={35};
			requiredPerkPoints[]={4};
			values[]={0.0};
		};
	};
};