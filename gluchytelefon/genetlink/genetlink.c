#include <linux/module.h>
#include <linux/kernel.h>
#include <net/genetlink.h>

#include "genetlink.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RS");
MODULE_DESCRIPTION("Linux Kernel Module over generic netlink.");
MODULE_VERSION("1.0");

static struct genl_family gt_genl_family;

static void forward_msg(unsigned int group, char *message)
{
    void *hdr;
    int res, flags = GFP_ATOMIC;
    char msg[GT_GENL_MSG_SIZE];
    struct sk_buff *skb = genlmsg_new(NLMSG_DEFAULT_SIZE, flags);

    strncpy(msg, message, GT_GENL_MSG_SIZE);

    skb = genlmsg_new(NLMSG_DEFAULT_SIZE, flags);
    if (!skb)
    {
        printk(KERN_ERR "%d: Genl msg new", __LINE__);
        return;
    }

    hdr = genlmsg_put(skb, 0, 0, &gt_genl_family, flags, GT_GENL_C_MSG);
    if (!hdr)
    {
        printk(KERN_ERR "%d: Genl msg put", __LINE__);
        goto failure;
    }

    res = nla_put_string(skb, GT_GENL_ATTR_MSG, msg);
    if (res)
    {
        printk(KERN_ERR "%d: nla put string %d ", __LINE__, res);
        goto failure;
    }

    genlmsg_end(skb, hdr);
    genlmsg_multicast(&gt_genl_family, skb, 0, group, flags);
    return;

failure:
    genlmsg_cancel(skb, hdr);
    nlmsg_free(skb);
    return;
}

static int gt_genl_rx_msg(struct sk_buff *skb, struct genl_info *info)
{
    if (!info->attrs[GT_GENL_ATTR_MSG])
    {
        printk(KERN_ERR "empty message from %d!!\n", info->snd_portid);
        printk(KERN_ERR "%p\n", info->attrs[GT_GENL_ATTR_MSG]);
        return -EINVAL;
    }

    forward_msg(GT_GENL_MCGRP0, (char *)nla_data(info->attrs[GT_GENL_ATTR_MSG]));
    return 0;
}

static const struct genl_ops gt_genl_ops[] = {
    {
        .cmd = GT_GENL_C_MSG,
        .policy = gt_genl_policy,
        .doit = gt_genl_rx_msg,
        .dumpit = NULL,
    },
};

static const struct genl_multicast_group gt_genl_mcgrps[] = {
    [GT_GENL_MCGRP0] = {
        .name = GT_GENL_MCGRP0_NAME,
    },
};

static struct genl_family gt_genl_family = {
    .name = GT_GENL_FAMILY_NAME,
    .version = 1,
    .maxattr = GT_GENL_ATTR_MAX,
    .netnsok = false,
    .module = THIS_MODULE,
    .ops = gt_genl_ops,
    .n_ops = ARRAY_SIZE(gt_genl_ops),
    .mcgrps = gt_genl_mcgrps,
    .n_mcgrps = ARRAY_SIZE(gt_genl_mcgrps),
};

static int __init gt_genl_init(void)
{
    int rc;

    printk(KERN_INFO "gt_genetlink: initializing netlink\n");

    rc = genl_register_family(&gt_genl_family);
    if (rc)
    {
        goto failure;
    }
    return 0;

failure:
    printk(KERN_DEBUG "gt_genetlink: error occurred in %s\n", __func__);
    return -EINVAL;
}

static void gt_genl_exit(void)
{
    genl_unregister_family(&gt_genl_family);
    printk(KERN_INFO "gt_genetlink: deinitializing netlink\n");
}

module_init(gt_genl_init);
module_exit(gt_genl_exit);