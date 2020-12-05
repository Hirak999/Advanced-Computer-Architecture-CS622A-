# Python script for inclusive cache hierarchy

import utility as utils

#traces = ["trial1.out", "trial2.out", "trial3.out", "trial4.out" ]

traces = ["trace.out"]

# File containing the read from Trace files goes here. Use one of the names
# mentioned above to calculate hits and misses for the corresponding file

if __name__ == '__main__':

    for File_name in traces:
        L2_cache = {}
        #L3_cache = {}
        tag_id_store = {}
        tag_id = 0
        L2_stat = {'hit': 0, 'miss': 0}
        #L3_stat = {'hit': 0, 'miss': 0}

        with open(File_name) as file, open(File_name[:-4] + "_misses.out", 'w') as file2: # File_name is a global variable defined at the top of the program
            for line in file:
                #print(line)

                thread_id, operation_type, location, *rest = line.split(' ')
                miss_address = int(location)

                # 'is_hit' is the type and 'miss_address' is the address where a miss was encountered
                """if miss_address == 12885047864:
                    print("Hello")"""

                #if is_hit!= 0:  # checking for only permission misses

                L2_index, L2_tag = utils.L2_index_tag_extraction(bin(miss_address)[2:].zfill(64))  # Converting the address to binary format
                # Not taking the first two characters as they are not part of the address and are used for notation

                if L2_tag not in tag_id_store:
                    tag_id_store[L2_tag] = tag_id
                    tag_id += 1

                if utils.cache_search(L2_cache,L2_index,L2_tag, tag_id_store):
                    L2_stat['hit'] += 1

                else:
                    L2_stat['miss'] += 1
                    file2.write(location+"\n")
                    #L2_invalid_index = None
                    #L2_invalid_tag = None
                    #L3_index, L3_tag = utils.L3_index_tag_extraction(bin(miss_address)[2:].zfill(64))
                    """if L3_tag not in tag_id_store:
                            tag_id_store[L3_tag] = tag_id
                            tag_id += 1
                        if utils.cache_search(L3_cache,L3_index, L3_tag, tag_id_store):
                            L3_stat['hit'] += 1
                            # WRITE INSERT L2 FUCNTION HERE, 
                    
                        else:
                            L3_stat['miss'] += 1
                            # INSERT INTO L3 FROM MM
                            L2_invalid_index, L2_invalid_tag = utils.L3_replace(L3_cache,L3_index,L3_tag)

                            if L2_invalid_index and L2_invalid_tag:
                                if utils.invalidate_L2_cache_block(L2_cache,L2_invalid_index,L2_invalid_tag,tag_id_store) is False:
                                    L2_invalid_tag = None
                                    L2_invalid_index = None"""

                    utils.L2_replace(L2_cache,L2_index,L2_tag)

                #print(L2_stat, L3_stat)


            print("\n Analysis for ",File_name)
            print("-------------------------")
            print("Number of misses is :")
            print(L2_stat['miss'])
            print("Number of hits is :")
            print(L2_stat['hit'])

            """print("Number of misses in L3 is :")
            print(L3_stat['miss'])
            print("Number of hits in L3 is :")
            print(L3_stat['hit'])
            print("--------------------------")"""


