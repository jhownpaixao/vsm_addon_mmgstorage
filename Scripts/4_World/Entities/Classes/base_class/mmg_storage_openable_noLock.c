modded class mmg_storage_openable_noLock_base
{
    void mmg_storage_openable_noLock_base()
    {
        VSM_StartAutoClose();
    }

	override void Open()
	{
        if (VSM_CanOpen())
        {
            super.Open();

            if (GetGame().IsServer() && VSM_IsOpen())
                VirtualStorageModule.GetModule().OnLoadVirtualStore(this);
        }
	}

	override void Close()
	{ 
        if (VSM_CanClose())
        {
            if (GetGame().IsServer())
                VirtualStorageModule.GetModule().OnSaveVirtualStore(this);
            
            super.Close();
        }
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

    bool CanDisplayAttachmentCategory( string category_name )
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
        return IsOpen();
    }

    override void VSM_Open()
    {
        super.VSM_Open();
        if (!VSM_IsOpen())
        {
            Open();
        }
    }

    override void VSM_Close()
    {
        super.VSM_Close();

        if (VSM_IsOpen())
        {
           	Close();
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
        ctx.Write(m_VSM_HasVirtualItems);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) return false;
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