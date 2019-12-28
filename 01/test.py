import subprocess

def test(expression, expected_out, expected_error):
    
    out = subprocess.run(['./main', expression],
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)

    result_out = out.stdout.decode('ascii').replace("\n", "")
    result_error = out.stderr.decode('ascii').replace("\n", "")
    
    if result_out != expected_out or result_error != expected_error:
        print(f"stdout: received: {result_out}, expected: {expected_out}")
        print(f"stderr: received: {result_error}, expected: {expected_error}")
    else:
        print(f"Correct stdout/stderr for {expression}")
        
# test cases
wrong_format_msg = "terminate called after throwing an instance of 'std::runtime_error'  what():  Wrong format!"

test("2 + 2", "4", "")
test("4", "4", "")
test("-100", "-100", "")
test("1 - 2 - 3 * 4 * 5 - -6 + -7", "-62", "")
test("1 - 2 - 3 * 4 * 5 - -6 + -7 * 2 * 30", "-475", "")
test("100 / -100 + -100*-100*-100", "-1000001", "")
test("2 + 2 2", "",  wrong_format_msg)
test("2 + +2", "",  wrong_format_msg)
test("", "",  wrong_format_msg)
