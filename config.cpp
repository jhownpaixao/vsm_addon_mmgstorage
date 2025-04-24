class CfgPatches
{
	class vsm_addon_mmgstorrage
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"VSM_Core", "mmg_storage"};
	};
};

class CfgMods
{
	class VSM_Addon_MMGStorage
	{
		dir = "vsm_addon_mmgstorrage";
		picture = "";
		action = "";
		hideName = 0;
		name = "VSM MMG Storage Addon";
		hidePicture = 0;
		credits = "Jhonnata Paixão";
		author = "iTzChronuZ";
		authorID = "76561199441861559";
		version = "1.0.0";
		extra = 0;
		type = "mod";
		dependencies[]= {"World"};

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"vsm_addon_mmgstorage/Scripts/4_World"};
			};
		};
	};
};