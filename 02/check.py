import subprocess

def check(args, result):
    out = subprocess.run(['./alloc', *(args.split())], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(out.stdout.decode('ascii'), result, out.stdout))
    else:
        print('OK')

check('2 alloc:2', 'Init 2 bytes\n'
                     'Allocated 2 bytes\n')
check('2 alloc:4', 'Init 2 bytes\n'
                     'null\n')
check('2 alloc:0', 'Init 2 bytes\n'
                     'Allocated 0 bytes\n')
check('16 alloc:12 alloc:1 alloc:2 alloc:10', 'Init 16 bytes\n'
                                              'Allocated 12 bytes\n'
                                              'Allocated 1 bytes\n'
                                              'Allocated 2 bytes\n'
                                              'null\n')
check('4 alloc:4 reset alloc:2', 'Init 4 bytes\n'
                                'Allocated 4 bytes\n'
                                'Reseted\n'
                                'Allocated 2 bytes\n')


check('0', 'Init 0 bytes\n')
check('0 alloc:5', 'Init 0 bytes\n'
                    'null\n')


check('100 alloc:95 reset alloc:96 reset alloc:1 alloc:99', 'Init 100 bytes\n'
                                                            'Allocated 95 bytes\n'
                                                            'Reseted\n'
                                                            'Allocated 96 bytes\n'
                                                            'Reseted\n'
                                                            'Allocated 1 bytes\n'
                                                            'Allocated 99 bytes\n')
check('-3', 'std::bad_alloc\n')
check('4000000000', 'std::bad_alloc\n')