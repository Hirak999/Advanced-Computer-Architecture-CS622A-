from node import Node


def L2_index_tag_extraction(miss_address):
    tag = miss_address[0:47]
    index = miss_address[47:58]  # CONVERT
    return index, tag


def L3_index_tag_extraction(miss_address):
    tag = miss_address[0:47]
    index = miss_address[47:58]  # CONVERT
    return index, tag


def init_cache_index(cache, index):
    cache[index] = {'head_pointer': None, 'end_pointer': None, 'num_of_blocks': 0}


def cache_search(cache, index, tag, tag_id_store):
    if index not in cache:
        return False

    head = cache[index]['head_pointer']
    # tail = cache[index]['end_pointer']

    while head is not None:
        if head.valid_bit and tag in tag_id_store and tag_id_store[head.tag] == tag_id_store[tag]:
            reposition_block(cache, index, head)
            return True
        head = head.next

    return False


def L3_replace(cache, index, tag):
    L2_index = None
    L2_tag = None

    insert(cache, index, tag)

    if cache[index]['num_of_blocks'] > 16:
        remove_address = cache[index]['head_pointer'].tag + index + '0' * 6  # PROBLEM
        L2_index, L2_tag = L2_index_tag_extraction(remove_address)
        delete_LRU(cache, index)

    return L2_index, L2_tag


def insert(cache, index, tag):
    new_node = Node(tag)

    if index not in cache:
        init_cache_index(cache, index)  # First node insert

    # When count < 16
    # if cache[index]['num_of_blocks'] < 16:
    tail = cache[index]['end_pointer']

    if tail:
        tail.set_next_pointer(new_node)  # DOUBT
        # new_node.set_next_pointer(None)
        new_node.set_previous_pointer(tail)

    else:
        cache[index]['head_pointer'] = new_node

    cache[index]['end_pointer'] = new_node
    cache[index]['num_of_blocks'] += 1


def delete_LRU(cache, index):
    cache[index]['num_of_blocks'] -= 1

    cache[index]['head_pointer'] = cache[index]['head_pointer'].next
    cache[index]['head_pointer'].previous.next = None
    cache[index]['head_pointer'].previous = None


def invalidate_L2_cache_block(cache, index, tag, tag_id_store):
    if index not in cache:
        return

    invalid_block_found = False
    head = cache[index]['head_pointer']

    while head is not None:
        if tag in tag_id_store and tag_id_store[head.tag] == tag_id_store[tag]:
            head.valid_bit = 0
            invalid_block_found =True
            break
        head = head.next

    return invalid_block_found

def L2_replace(cache, index, tag):
    insert(cache, index, tag)

    # First checking for invalidated block

    """ if invalid_index and invalid_tag:
        head = cache[index]['head_pointer']
        while head is not None:
            if head.valid_bit == 0:
                delete_invalid(cache, invalid_index, head)
                break
            head = head.next"""

    if cache[index]['num_of_blocks'] > 16:
        delete_LRU(cache, index)


def delete_invalid(cache, index, node):
    cache[index]['num_of_blocks'] -= 1

    if node.previous is None:
        cache[index]['head_pointer'] = node.next

    if node.next is None:
        cache[index]['end_pointer'] = node.previous

    if node.previous is not None:
        node.previous.next = node.next

    if node.next is not None:
        node.next.previous = node.previous

    node.next = None
    node.previous = None


def reposition_block(cache, index, node):
    if cache[index]['num_of_blocks'] == 1 or node.next is None:
        return

    if node.previous is None:
        cache[index]['head_pointer'] = node.next

    if node.previous is not None:
        node.previous.next = node.next

    if node.next is not None:
        node.next.previous = node.previous

    node.next = None
    node.previous = cache[index]['end_pointer']
    cache[index]['end_pointer'].next = node
    cache[index]['end_pointer'] = node
