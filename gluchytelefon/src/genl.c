#define INCLUDE_GT_GENL_MCGRP_NAMES
#define INCLUDE_GT_GENL_POLICY

#include "genl.h"

static unsigned int mcgroups;
static char rx_message[GT_GENL_MSG_SIZE + 1];

char *gt_get_message()
{
    return rx_message;
}

int gt_skip_seq_check(struct nl_msg *msg, void *arg)
{
    return NL_OK;
}

void gt_add_group(unsigned int group)
{
    if (group > GT_GENL_MCGRP_MAX - 1)
    {
        printf("Invalid group number %u. Values allowed 0:%u\n", group, GT_GENL_MCGRP_MAX - 1);
        exit(0);
    }

    mcgroups |= 1 << (group);
}

int gt_genl_receive_msg(struct nl_msg *msg, void *arg)
{
    struct nlattr *attr[GT_GENL_ATTR_MAX + 1];

    genlmsg_parse(nlmsg_hdr(msg), 0, attr, GT_GENL_ATTR_MAX, gt_genl_policy);

    if (!attr[GT_GENL_ATTR_MSG])
    {
        printf("Empty message!!\n");
        return NL_OK;
    }

    strncpy(rx_message, nla_get_string(attr[GT_GENL_ATTR_MSG]), GT_GENL_MSG_SIZE);
    rx_message[GT_GENL_MSG_SIZE + 1] = '\0';

    return NL_OK;
}

void gt_genl_send_msg(struct nl_sock *sock, const char *message)
{
    struct nl_msg *msg;
    int family_id, err = 0;

    family_id = genl_ctrl_resolve(sock, GT_GENL_FAMILY_NAME);
    if (family_id < 0)
    {
        perror("Couldn't resolve family name");
        exit(0);
    }

    msg = nlmsg_alloc();
    if (!msg)
    {
        perror("Couldn't allocate netlink message");
        exit(0);
    }

    if (!genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ, family_id, 0, NLM_F_REQUEST, GT_GENL_C_MSG, 0))
    {
        perror("Couldn't put genl message");
        err = -ENOMEM;
        goto out;
    }

    err = nla_put_string(msg, GT_GENL_ATTR_MSG, message);
    if (err)
    {
        perror("Couldn't put nl string");
        goto out;
    }

    err = nl_send_auto(sock, msg);
    if (err < 0)
    {
        perror("Couldn't send nl message");
    }

out:
    nlmsg_free(msg);
}

void gt_genl_prep_sock(struct nl_sock **nlsock)
{
    int family_id, grp_id;
    unsigned int bit = 0;

    *nlsock = nl_socket_alloc();
    if (!*nlsock)
    {
        perror("Couldn't alloc nl socket");
        exit(0);
    }

    nl_socket_disable_seq_check(*nlsock);
    nl_socket_disable_auto_ack(*nlsock);

    if (genl_connect(*nlsock))
    {
        perror("Couldn't connect to genl");
        exit(0);
    }

    family_id = genl_ctrl_resolve(*nlsock, GT_GENL_FAMILY_NAME);
    if (family_id < 0)
    {
        perror("Couldn't resolve family name");
        exit(0);
    }

    if (!mcgroups)
    {
        return;
    }

    while (bit < sizeof(unsigned int))
    {
        if (!(mcgroups & (1 << bit)))
        {
            goto next;
        }

        grp_id = genl_ctrl_resolve_grp(*nlsock, GT_GENL_FAMILY_NAME, gt_genl_mcgrp_names[bit]);

        if (grp_id < 0)
        {
            printf("Couldn't resolve group name for %u", (1 << bit));
            exit(0);
        }
        if (nl_socket_add_membership(*nlsock, grp_id))
        {
            printf("Couldn't join group %u", (1 << bit));
            exit(0);
        }
    next:
        bit++;
    }
}