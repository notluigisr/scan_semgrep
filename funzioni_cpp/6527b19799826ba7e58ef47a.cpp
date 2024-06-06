DefragVlanQinQTest(void)
{
    Packet *p1 = NULL, *p2 = NULL, *r = NULL;
    int ret = 0;

    DefragInit();

    p1 = BuildTestPacket(1, 0, 1, 'A', 8);
    if (p1 == NULL)
        goto end;
    p2 = BuildTestPacket(1, 1, 0, 'B', 8);
    if (p2 == NULL)
        goto end;

    
    if ((r = Defrag(NULL, NULL, p1, NULL)) != NULL)
        goto end;
    if ((r = Defrag(NULL, NULL, p2, NULL)) == NULL)
        goto end;
    SCFree(r);

    
    p1->vlan_id[0] = 1;
    p2->vlan_id[0] = 1;
    p1->vlan_id[1] = 1;
    p2->vlan_id[1] = 2;
    if ((r = Defrag(NULL, NULL, p1, NULL)) != NULL)
        goto end;
    if ((r = Defrag(NULL, NULL, p2, NULL)) != NULL)
        goto end;

    
    ret = 1;

end:
    if (p1 != NULL)
        SCFree(p1);
    if (p2 != NULL)
        SCFree(p2);
    DefragDestroy();

    return ret;
}