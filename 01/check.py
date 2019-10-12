import subprocess

def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
        print('OK')

#spaces and unary minus
print('Spaces and unary minus:')
check('2', '2')
check('    3', '3')
check('-2', '-2')
check('   -3', '-3')
check('   -4    ', '-4')
check('--5', '5')
check('---5', '-5')
check('  -    --   5353', '-5353')

#binary operations
print('Binary operations:')
check('4*7', '28')
check('12/4', '3')
check('20+30', '50')
check('20-30', '-10')

#priority
print('Priority:')
check('2+3*4', '14')
check('100/5/2', '10')
check('100/5*2', '40')
check('2*100/5', '40')
check('-2*5', '-10')
check('2*-5', '-10')
check('-40/8', '-5')
check('40/-8', '-5')
check('-40/-8', '5')
check('2 + 3 * 4 - -2', '16')

#invalid
print('Invalid input:')
check('', 'invalid_argument')
check('-', 'invalid_argument')
check('+', 'invalid_argument')
check('*', 'invalid_argument')
check('/', 'invalid_argument')
check('+2', 'invalid_argument')
check('++2', 'invalid_argument')
check('+-2', 'invalid_argument')
check('-+2', 'invalid_argument')
check('-2*', 'invalid_argument')
check('2 3', 'invalid_argument')
check('2 3 +', 'invalid_argument')
check('alpha', 'invalid_argument')
check('1a', 'invalid_argument')
check('a1', 'invalid_argument')
check('1    a', 'invalid_argument')
check('   1   + 3  * 5ab', 'invalid_argument')
check('30 * / 2', 'invalid_argument')
check('30 / * 3', 'invalid_argument')
check('200-/-50', 'invalid_argument')
check(' 200    -  ', 'invalid_argument')

#mix
print('Mix:')
check('2323  +    294 -   - 2949  * 21200 /-200 * -25', '7817467')
check(' -  -    --  - - 768    / 3   -- 16 + 25 * 29999', '750247')
check('-012 + 17 - 0000024', '-19')