modded class dismantle_fridge_beige extends RecipeBase	
{	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return ingredients[0].IsEmpty() && !ingredients[0].VSM_HasVirtualItems();
	}
};