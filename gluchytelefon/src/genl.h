#ifndef GENL_TEST_H
#define GENL_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netlink/msg.h>
#include <netlink/attr.h>

#include <linux/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>

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
};
#define GT_GENL_MCGRP_MAX 1

#ifdef INCLUDE_GT_GENL_MCGRP_NAMES
static char *gt_genl_mcgrp_names[GT_GENL_MCGRP_MAX] = {
    GT_GENL_MCGRP0_NAME,
};
#endif

enum gt_genl_attrs
{
    GT_GENL_ATTR_UNSPEC, //set 0, not used
    GT_GENL_ATTR_MSG,
    __GT_GENL_ATTR__MAX,
};
#define GT_GENL_ATTR_MAX (__GT_GENL_ATTR__MAX - 1)

#ifdef INCLUDE_GT_GENL_POLICY
static struct nla_policy gt_genl_policy[GT_GENL_ATTR_MAX + 1] = {
    [GT_GENL_ATTR_MSG] = {
        .type = NLA_STRING,
        .maxlen = GT_GENL_MSG_SIZE},
};
#endif

void gt_genl_send_msg(struct nl_sock *sock, const char *message);
void gt_genl_prep_sock(struct nl_sock **nlsock);

#endif
