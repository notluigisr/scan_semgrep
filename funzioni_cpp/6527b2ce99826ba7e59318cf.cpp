static CPLXMLNode* FLTFindGeometryNode(CPLXMLNode* psXMLNode,
                                       int* pbPoint,
                                       int* pbLine,
                                       int* pbPolygon)
{
    CPLXMLNode *psGMLElement = NULL;

    psGMLElement = CPLGetXMLNode(psXMLNode, "STR");
    if (!psGMLElement)
        psGMLElement =  CPLGetXMLNode(psXMLNode, "STR");
    if (psGMLElement)
        *pbPoint =1;
    else {
      psGMLElement= CPLGetXMLNode(psXMLNode, "STR");
      if (psGMLElement)
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "STR")))
        *pbPoint = 1;
    }
    return psGMLElement;
}