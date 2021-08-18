from collections import namedtuple
import copy
import time

Case = namedtuple('Case','inputs outputs')

def check_solution(case_list, solution, verbose=True, do_copy=True, print_input=True):
    success = True

    if do_copy:
        cases = copy.deepcopy(case_list)
    else:
        cases = case_list

    for i, case in enumerate(cases):
        start = time.time()
        result = solution(case.inputs)
        end = time.time()
        cur_success = result == case.outputs
        success &= cur_success

        eq_str = "==" if cur_success else '!='
        inputs  = f'| Input: {case.inputs} ' if print_input else ''
        compare = f'| {result} {eq_str} {case.outputs} '
        runtime = f'| Runtime: {end - start:04} '
        if verbose:
            print(f'Case # {i} {inputs}{compare}{runtime}')

    if success:
        print('Success 😃')
    else:
        print('Failure 🥺')

    
            