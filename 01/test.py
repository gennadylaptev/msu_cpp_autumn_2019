import subprocess

def test(expression, expected_out):
    
    out = subprocess.run(['./main', expression],
                         stdout=subprocess.PIPE)

    result_out = out.stdout.decode('ascii').replace("\n", "")
    
    if result_out != expected_out:
        print(f"stdout: received: {result_out}, expected: {expected_out}")
    else:
        print(f"Correct stdout for {expression}")
        
# test cases
wrong_format_msg = "Wrong format! Failed to obtain the result."

test("2 + 2", "4")
test("4", "4")
test("-100", "-100")
test("  1 - 2 - 3 * 4 * 5 -   -6 +-7", "-62")
test("1 - 2 - 3 * 4 * 5 - -6 + -7 * 2 * 30", "-475")
test("100 / -100 + -100*-100*-100", "-1000001")
test("2 + 2 2", wrong_format_msg)
test("2 + +2", wrong_format_msg)
test("", wrong_format_msg)
