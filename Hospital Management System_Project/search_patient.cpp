ListNode *searchNextPatient(ListNode *head, int (*findPatient)(PatientInfo *), PatientInfo *patient)
{
	// check if list is empty
	if (head == NULL)
	{
		return NULL;
	}
	ListNode *temp = NULL;
	temp = head;
	// while list is not empty
	while (temp != NULL)
	{
		// check if criteria is matched
		if (findPatient(&temp->patient) == 0)
		{
			// assign patient data and return node
			*patient = temp->patient;
			return temp;
		}
		else
		{
			temp = temp->next;
		}
	}
	temp = NULL;
	// if no node found then return NULL
	return NULL;
}