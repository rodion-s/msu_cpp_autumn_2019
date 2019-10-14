import subprocess

def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout = subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('Error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
        print('OK')

#spaces and unary minus
print('Spaces and unary minus:')
check('2', '2\n')
check('    3', '3\n')
check('-2', '-2\n')
check('   -3', '-3\n')
check('   -4    ', '-4\n')
check('--5', '5\n')
check('---5', '-5\n')
check('  -    --   5353', '-5353\n')

#binary operations
print('Binary operations:')
check('4*7', '28\n')
check('12/4', '3\n')
check('20+30', '50\n')
check('20-30', '-10\n')

#priority
print('Priority:')
check('2+3*4', '14\n')
check('100/5/2', '10\n')
check('100/5*2', '40\n')
check('2*100/5', '40\n')
check('-2*5', '-10\n')
check('2*-5', '-10\n')
check('-40/8', '-5\n')
check('40/-8', '-5\n')
check('-40/-8', '5\n')
check('2 + 3 * 4 - -2', '16\n')

#invalid
print('Invalid input:')
check('', 'Error on lexeme: \n')
check('-', 'Error on lexeme: \n')
check('+', 'Error on lexeme: +\n')
check('*', 'Error on lexeme: *\n')
check('/', 'Error on lexeme: /\n')
check('+2', 'Error on lexeme: +\n')
check('++2', 'Error on lexeme: +\n')
check('+-2', 'Error on lexeme: +\n')
check('-+2', 'Error on lexeme: +\n')
check('-2*', 'Error on lexeme: \n')
check('2 3', 'Error on lexeme: 3\n')
check('2 3 +', 'Error on lexeme: 3\n')
check('alpha', 'Error on lexeme: a\n')
check('1a', 'Error on lexeme: a\n')
check('a1', 'Error on lexeme: a\n')
check('1    a', 'Error on lexeme: a\n')
check('   1   + 3  * 5ab', 'Error on lexeme: a\n')
check('30 * / 2', 'Error on lexeme: /\n')
check('30 / * 3', 'Error on lexeme: *\n')
check('200-/-50', 'Error on lexeme: /\n')
check(' 200    -  ', 'Error on lexeme: \n')
check(' 1 / 0', 'Error: division by zero\n')
check('  100 / 2 * 3 / 0 - 7', 'Error: division by zero\n')
#mix
print('Mix:')
check('2323  +    294 -   - 2949  * 21200 /-200 * -25', '7817467\n')
check(' -  -    --  - - 768    / 3   -- 16 + 25 * 29999', '750247\n')
check('-012 + 17 - 0000024', '-19\n')