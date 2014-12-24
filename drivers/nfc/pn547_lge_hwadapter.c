#include <linux/nfc/pn547_lge_hwadapter.h>

int pn547_get_hw_revision(void)
{
#if defined(CONFIG_LGE_NFC_HW_TI_OMAP4430)
    int  hw_revision = LGE_PCB_MAX;
    hw_revision = system_rev;
#else
    hw_rev_type hw_revision = HW_REV_MAX;
    hw_revision = lge_get_board_revno();
#endif
    dprintk(PN547_DRV_NAME ":ioctl: pn547_read hw revision : %d\n", hw_revision);
    return (int)hw_revision;
}

unsigned int pn547_get_irq_pin(struct pn547_dev *dev)
{
#if defined(CONFIG_LGE_NFC_HW_TI_OMAP4430)
    return OMAP_GPIO_IRQ(dev->irq_gpio);
#elif defined(CONFIG_LGE_NFC_HW_NV_AP3X)
    return dev->client->irq;
#else
    return dev->client->irq;
#endif
}

int pn547_gpio_to_irq(struct pn547_dev *dev)
{
#if defined(CONFIG_LGE_NFC_HW_TI_OMAP4430)||defined(CONFIG_LGE_NFC_HW_QCT_MSM8255)
    return gpio_to_irq(dev->irq_gpio);
#else
    return dev->client->irq;
#endif
}

void pn547_gpio_enable(struct pn547_dev *pn547_dev)
{
#if defined(CONFIG_LGE_NFC_HW_NV_AP3X)
    tegra_gpio_enable(pn547_dev->ven_gpio);
    tegra_gpio_enable(pn547_dev->firm_gpio);
    tegra_gpio_enable(pn547_dev->irq_gpio);
#endif
    return;
}

void pn547_shutdown_cb(struct pn547_dev *pn547_dev)
{
#if defined(CONFIG_LGE_NFC_HW_QCT_MSM8660)
    dprintk("================ pn547_shutdown() start ================\n");

    // Make all output GPIOs to Low
    gpio_set_value(pn547_dev->ven_gpio, 0);
    gpio_set_value(pn547_dev->firm_gpio, 0);
    msleep(10);
    dprintk("Output GPIO Status : VEN = %d, FIRM = %d\n",
    gpio_get_value(pn547_dev->ven_gpio),
    gpio_get_value(pn547_dev->firm_gpio));

    dprintk("================ pn547_shutdown() end ================\n");

#elif defined(CONFIG_LGE_NFC_HW_NV_AP3X)
    gpio_set_value(pn547_dev->ven_gpio, 0);
#endif
    return;
}
