int st21nfca_connectivity_event_received(struct nfc_hci_dev *hdev, u8 host,
				u8 event, struct sk_buff *skb)
{
	int r = 0;
	struct device *dev = &hdev->ndev->dev;
	struct nfc_evt_transaction *transaction;

	pr_debug("STR", event);

	switch (event) {
	case ST21NFCA_EVT_CONNECTIVITY:
		r = nfc_se_connectivity(hdev->ndev, host);
	break;
	case ST21NFCA_EVT_TRANSACTION:
		
		if (skb->len < NFC_MIN_AID_LENGTH + 2 &&
		    skb->data[0] != NFC_EVT_TRANSACTION_AID_TAG)
			return -EPROTO;

		transaction = devm_kzalloc(dev, skb->len - 2, GFP_KERNEL);
		if (!transaction)
			return -ENOMEM;

		transaction->aid_len = skb->data[1];
		memcpy(transaction->aid, &skb->data[2],
		       transaction->aid_len);

		
		if (skb->data[transaction->aid_len + 2] !=
		    NFC_EVT_TRANSACTION_PARAMS_TAG)
			return -EPROTO;

		transaction->params_len = skb->data[transaction->aid_len + 3];
		memcpy(transaction->params, skb->data +
		       transaction->aid_len + 4, transaction->params_len);

		r = nfc_se_transaction(hdev->ndev, host, transaction);
	break;
	default:
		nfc_err(&hdev->ndev->dev, "STR");
		return 1;
	}
	kfree_skb(skb);
	return r;
}