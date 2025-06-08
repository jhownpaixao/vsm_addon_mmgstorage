modded class dismantle_solo_locker_green extends RecipeBase	
{	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return ingredients[0].IsEmpty() && !ingredients[0].VSM_HasVirtualItems();
	}
};