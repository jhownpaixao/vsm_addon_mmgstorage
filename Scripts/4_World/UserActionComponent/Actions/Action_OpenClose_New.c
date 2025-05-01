modded class ActionMMGCloseAndOpen
{
	override void OnStartServer(ActionData action_data)
	{
		ItemBase crate = ItemBase.Cast(action_data.m_Target.GetObject());
		if (crate)
		{

			if (crate.IsOpen())
			{
				if (!crate.VSM_CanClose())
				{
					VirtualUtils.SendMessageToPlayer(action_data.m_Player, "STR_VSM_NOT_CLOSE_CONTAINER");
					return;
				}
				crate.Close();

			}
			else
			{
				if (!crate.VSM_CanOpen())
				{
					VirtualUtils.SendMessageToPlayer(action_data.m_Player, "STR_VSM_NOT_OPEN_CONTAINER");
					return;
				}
				crate.Open();
			}
		}
	}
};