
def search_and_set(mem_blocks,block_id,thread_id):
    if block_id not in mem_blocks:
        mem_blocks[block_id] = [0]*8

    mem_blocks[block_id][thread_id] = 1

