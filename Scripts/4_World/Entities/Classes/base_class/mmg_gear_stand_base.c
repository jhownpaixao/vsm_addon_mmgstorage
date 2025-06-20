modded class mmg_gear_stand_base
{
    protected ref OpenableBehaviour m_Openable;
    protected bool m_IsOpenedLocal;

    void mmg_gear_stand_base()
    {
        VSM_StartAutoClose();
    }

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

	//! mesclar caracteristicas do storage para virtual
    override bool CanPutInCargo(EntityAI parent)
    {
        if (!super.CanPutInCargo(parent))
            return false;

        return !VSM_HasVirtualItems();
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!super.CanPutIntoHands(parent))
            return false;

        return !VSM_HasVirtualItems();
    }

    // so aceita itens se estiver aberto
    override bool CanReceiveItemIntoCargo(EntityAI item)
    {
        if (VSM_CanManipule())
            return super.CanReceiveItemIntoCargo(item);

        return false;
    }

    override bool CanReleaseCargo(EntityAI cargo)
    {
        if (VSM_CanManipule())
            return super.CanReleaseCargo(cargo);

        return false;
    }

    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        if (VSM_IsOpen())
            return super.CanReceiveAttachment(attachment, slotId);

        return false;

    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (VSM_CanManipule())
            return super.CanReleaseAttachment(attachment);

        return false;
    }

    override bool CanDisplayAttachmentSlot(int slot_id)
    {
        if (VSM_CanManipule())
            return super.CanDisplayAttachmentSlot(slot_id);

        return false;
    }

    override bool CanDisplayCargo()
    {
        if (VSM_CanManipule())
            return super.CanDisplayCargo();

        return false;
    }

    override bool CanDisplayAttachmentCategory(string category_name)
    {
        if (VSM_CanManipule())
            return super.CanDisplayAttachmentCategory(category_name);

        return false;
    }

    //! virtualização
    override bool VSM_CanVirtualize()
    {
        return true;
    }

    override bool VSM_IsOpen()
    {
        return m_Openable.IsOpened();
    }

    override void VSM_Open()
	{
        if(VSM_CanOpen())
        {
            super.VSM_Open();

           
            m_Openable.Open();
            SetSynchDirty();

            if (GetGame().IsServer())
                VirtualStorageModule.GetModule().OnLoadVirtualStore(this);      
        }
	}

	override void VSM_Close()
	{
        if(VSM_CanClose())
        {
            super.VSM_Close();

            if (GetGame().IsServer())
				VirtualStorageModule.GetModule().OnSaveVirtualStore(this);

            m_Openable.Close();
			SetSynchDirty();
        }
	}

    override void EEInit()
    {
        super.EEInit();

        if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnInitContainer(this);
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnDeleteContainer(this);
    }

    override void OnDamageDestroyed(int oldLevel)
	{
		super.OnDamageDestroyed(oldLevel);
		if (GetGame().IsServer())
            VirtualStorageModule.GetModule().OnDestroyed(this);
	};

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        
        if(!VirtualStorageModule.GetModule().IsRemoving())
            ctx.Write(m_VSM_HasVirtualItems);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) return false;

        if(!VirtualStorageModule.GetModule().IsNew())
            ctx.Read(m_VSM_HasVirtualItems);

        return true;
    }

    override void AfterStoreLoad()
    {
        super.AfterStoreLoad();
        VSM_SetHasItems(m_VSM_HasVirtualItems);
    }

    override void VSM_OnBeforeVirtualize()
    {
        super.VSM_OnBeforeVirtualize();

        if (!VSM_IsOpen()) //! se estiver fechado, os itens são perdidos, caso seja virtualizado dentro de outro container
            VSM_Open();
    }
};