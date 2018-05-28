#ifndef _GENETLINK_H_
#define _GENETLINK_H_

#define GT_GENL_FAMILY_NAME "gt_genetlink"
#define GT_GENL_MCGRP0_NAME "gt_genl_mcgrp0"

#define GT_GENL_MSG_SIZE 32

enum
{
    GT_GENL_C_UNSPEC, //set 0, not used
    GT_GENL_C_MSG,
};

enum gt_genl_multicast_groups
{
    GT_GENL_MCGRP0,
    __GT_GENL_MCGRP_MAX,
};
#define GT_GENL_MCGRP_MAX (__GT_GENL_MCGRP_MAX - 1)

enum gt_genl_attrs
{
    GT_GENL_ATTR_UNSPEC, //set 0, not used
    GT_GENL_ATTR_MSG,
    __GT_GENL_ATTR_MAX,
};
#define GT_GENL_ATTR_MAX (__GT_GENL_ATTR_MAX - 1)

struct nla_policy gt_genl_policy[GT_GENL_ATTR_MAX + 1] = {
    [GT_GENL_ATTR_MSG] = {
        .type = NLA_STRING,
        .len = GT_GENL_MSG_SIZE},
};

#endif