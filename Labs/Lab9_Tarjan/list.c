#include "list.h"

int isEmptyList(List list) {
    return list == NULL;
}

List initList(V data)
{
	List list;

	list = (List) malloc(sizeof(struct list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return list;
}

List addFirst(List list, V data)
{
	List new;

	if (list == NULL)
		return initList(data);
	new = initList(data);
	new->next = list;
	list->prev = new;
	return new;
}

List addLast(List list, V data)
{
	List new, tmp;

	if (list == NULL)
		return initList(data);
	new = initList(data);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return list;
}

List deleteItem(List l, V data) {
	if(l == NULL) {
		return NULL;
	} else {
		List tmp = l, prev;
		if(tmp->data == data) {
			l = l->next;
			free(tmp);
            if (l != NULL && l->prev != NULL) {
                l->prev = NULL;
            }
            return l;
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
		while(tmp != NULL) {
			if(tmp->data == data) {
                prev->next = tmp->next;
				if (tmp->next != NULL)
					tmp->next->prev = prev;
                printf("tPdsadsal\n");
				free(tmp);
				return l;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		return l;
	}
}

List freeList(List list)
{
	List tmp;

	if (list == NULL)
		return list;
	while (list != NULL) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return NULL;
}
