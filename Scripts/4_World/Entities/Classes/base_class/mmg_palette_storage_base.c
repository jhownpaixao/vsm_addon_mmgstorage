modded class mmg_palette_storage_base
{
    protected ref OpenableBehaviour m_Openable;
    protected bool m_IsOpenedLocal;

    override void InitItemVariables()
    {
        super.InitItemVariables();
        m_Openable = new OpenableBehaviour(false);
        RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
    }

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionVSM_Open);
        AddAction(ActionVSM_Close);
    }

    override void Open()
    {
        if (VSM_CanOpen())
        {
            m_Openable.Open();
            SetSynchDirty();

            if (GetGame().IsServer())
                VirtualStorageModule.GetModule().OnLoadVirtualStore(this);
        }
    }

    override void Close()
    {

        if (VSM_CanClose())
        {
            if (GetGame().IsServer())
                VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            
            m_Openable.Close();
            SetSynchDirty();
        }
    }

    //! virtualização
    override bool VSM_IsOpen()
    {
        return m_Openable.IsOpened();
    }
};