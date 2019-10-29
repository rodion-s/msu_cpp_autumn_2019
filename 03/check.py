import subprocess

def check(args, result):
    out = subprocess.run(['./matrix', *(args.split())], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(out.stdout.decode('ascii'), result, out.stdout))
    else:
        print('OK')

for i in range(1, 12 + 1):
  check(str(i), 'OK\n')
check('13', 'out of range\nOK\n')
check('14', 'out of range\nOK\n')
check('15', 'out of range\nOK\n')