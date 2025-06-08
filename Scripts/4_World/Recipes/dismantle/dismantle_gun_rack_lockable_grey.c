modded class dismantle_mmg_lockable_gun_rack_grey extends RecipeBase
{	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return ingredients[0].IsEmpty() && !ingredients[0].VSM_HasVirtualItems();
	}
};