void list_add_ascending_by_address(list_t *l, block_t *newblk) {
    node_t *newNode = node_alloc(newblk);
    if (l->head == NULL || newblk->start < l->head->blk->start) {
        newNode->next = l->head;
        l->head = newNode;
        return;
    }
    node_t *current = l->head;
    while (current->next != NULL && current->next->blk->start < newblk->start) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void list_add_ascending_by_blocksize(list_t *l, block_t *newblk) {
    node_t *newNode = node_alloc(newblk);
    int newSize = newblk->end - newblk->start + 1;
    if (l->head == NULL || newSize < (l->head->blk->end - l->head->blk->start + 1)) {
        newNode->next = l->head;
        l->head = newNode;
        return;
    }
    node_t *current = l->head;
    while (current->next != NULL &&
           (current->next->blk->end - current->next->blk->start + 1) <= newSize) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void list_add_descending_by_blocksize(list_t *l, block_t *blk) {
    node_t *newNode = node_alloc(blk);
    int newSize = blk->end - blk->start + 1;
    if (l->head == NULL || newSize > (l->head->blk->end - l->head->blk->start + 1)) {
        newNode->next = l->head;
        l->head = newNode;
        return;
    }
    node_t *current = l->head;
    while (current->next != NULL &&
           (current->next->blk->end - current->next->blk->start + 1) >= newSize) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void list_coalese_nodes(list_t *l) {
    node_t *current = l->head;
    while (current != NULL && current->next != NULL) {
        if (current->blk->end + 1 == current->next->blk->start) {
            current->blk->end = current->next->blk->end;
            node_t *temp = current->next;
            current->next = temp->next;
            free(temp->blk);
            node_free(temp);
        } else {
            current = current->next;
        }
    }
}

bool list_is_in_by_pid(list_t *l, int pid) {
    node_t *current = l->head;
    while (current != NULL) {
        if (comparePid(pid, current->blk)) {
            return true;
        }
        current = current->next;
    }
    return false;
}