#traces = ["trial1.out", "trial2.out", "trial3.out", "trial4.out" ]

traces = ["trial.out"]

# File containing the read from Trace files goes here. Use one of the names
# mentioned above to calculate hits and misses for the corresponding file

import utility_sharing_profile as utils

if __name__ == '__main__':

    for File_name in traces:
        mem_blocks = {}

        """tag_id_store = {}
        tag_id = 0"""


        with open(File_name) as file:  # File_name is a global variable defined at the top of the program
            for line in file:
                # print(line)

                thread_id, operation_type, location, *rest = line.split(' ')
                thread_id = int(thread_id)
                block_id = int(location)//64

                utils.search_and_set(mem_blocks,block_id,thread_id)

        total_mem_blocks = 0
        profile = [0]*8

        for key in mem_blocks:

            total_mem_blocks += 1
            temp = sum(mem_blocks[key])

            profile[temp-1] += 1

        print("\n Analysis for ", File_name)
        print("-------------------------")

        print("Total number of memory blocks in file is")
        print(total_mem_blocks)

        for i in range(len(profile)):
            if i == 0:
                print("Number of private memory blocks are")
            else:
                print("Number of blocks shared by " + str(i+1) + " threads are")

            print(profile[i])
